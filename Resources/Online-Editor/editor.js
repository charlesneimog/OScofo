class ScofoHighlighter {
    constructor(textInputSelector, highlightOutputSelector, lineNumbersSelector, parserLanguageUrl) {
        this.textInput = document.querySelector(textInputSelector);
        this.highlightOutput = document.querySelector(highlightOutputSelector);
        this.lineNumbers = document.querySelector(lineNumbersSelector);
        this.Parser = window.TreeSitter;
        this.ScofoParser = null;
        this.parserLanguageUrl = parserLanguageUrl;
        this.htmlFormatterCode = "";
        this.linesWithErrors = {}; // Track lines with errors
        this.musicxmlScore = [];

        // Initialize the parser and setup event listeners
        this.initParser().then(() => {
            this.initEventListeners();
        });
    }

    async initParser() {
        await this.Parser.init();
        this.ScofoParser = new this.Parser();
        await this.setScofoParse();
    }

    async setScofoParse() {
        const scoreScofo = await this.Parser.Language.load(this.parserLanguageUrl);
        this.ScofoParser.setLanguage(scoreScofo);
    }

    applySelection(text, selectionStart, selectionEnd) {
        const selectedText = text.slice(selectionStart, selectionEnd);
        return `<span class="highlight-selection">${selectedText}</span>`;
    }

    highlightCode(input, node, errors) {
        const keywords = ["NOTE", "TRILL", "REST"];
        const config = ["BPM"];

        let highlightedText = "";
        if (node.namedChildCount > 0) {
            let lastPosition = node.startIndex;
            node.namedChildren.forEach((child) => {
                const line = input.slice(0, child.startIndex).split("\n").length;
                if (child.type === "ERROR") {
                    errors[line] = true;
                }
                const nodeTxtStrNoSpace = input.slice(lastPosition, child.startIndex).trim();
                if (nodeTxtStrNoSpace.length > 0 && keywords.includes(nodeTxtStrNoSpace)) {
                    highlightedText += `<span class="KEYWORD">${nodeTxtStrNoSpace}</span>`;
                    highlightedText += " ";
                } else if (nodeTxtStrNoSpace.length > 0 && config.includes(nodeTxtStrNoSpace)) {
                    highlightedText += `<span class="CONFIG">${nodeTxtStrNoSpace}</span>`;
                    highlightedText += " ";
                } else {
                    highlightedText += input.slice(lastPosition, child.startIndex);
                }
                highlightedText += this.highlightCode(input, child, errors);
                lastPosition = child.endIndex;
            });
            highlightedText += input.slice(lastPosition, node.endIndex);
        } else {
            let nodeTxtStrNoSpace = input.slice(node.startIndex, node.endIndex).trim();
            if (keywords.includes(nodeTxtStrNoSpace)) {
                highlightedText += `<span class="KEYWORD">${nodeTxtStrNoSpace}</span>`;
            } else {
                if (node.type == "COMMENT") {
                    nodeTxtStrNoSpace = input.slice(node.startIndex, node.endIndex);
                }
                highlightedText += `<span class="${node.type}">${nodeTxtStrNoSpace}</span>`;
            }
        }
        return highlightedText;
    }

    updateLineNumbers(errors) {
        const lineCount = this.textInput.value.split("\n").length;
        this.lineNumbers.innerHTML = Array.from({ length: lineCount }, (_, i) => {
            const lineNumber = i + 1;
            if (errors[lineNumber]) {
                return `<div class="line-number-error">❌</div>`;
            } else {
                return `<div>${lineNumber}</div>`;
            }
        }).join("");
        this.syncScrollPosition();
        this.adjustLineNumbersHeight();
    }

    updateHighlightOutput() {
        this.resizeInput();
        const value = this.textInput.value;
        const tree = this.ScofoParser.parse(value);
        let errors = {};
        let styledCode = this.highlightCode(value, tree.rootNode, errors);
        this.highlightOutput.innerHTML = styledCode;
        this.updateLineNumbers(errors);

        // Dynamically adjust height of text input based on its content
        this.adjustTextInputHeight();
    }

    adjustTextInputHeight() {
        this.textInput.style.height = `${this.textInput.scrollHeight}px`;
    }

    adjustLineNumbersHeight() {
        this.lineNumbers.style.height = `${this.textInput.scrollHeight}px`;
    }

    simulateSelection() {
        const value = this.textInput.value;
        const selectionStart = this.textInput.selectionStart;
        const selectionEnd = this.textInput.selectionEnd;
        this.highlightOutput.innerHTML = this.applySelection(value, selectionStart, selectionEnd);
    }

    downloadScore() {
        const content = this.textInput.value;
        const blob = new Blob([content], { type: "text/plain" });
        const a = document.createElement("a");
        a.href = URL.createObjectURL(blob);
        a.download = "score.scofo.txt";
        a.click();
    }

    resizeInput() {
        this.textInput.style.height = "auto";
        this.textInput.style.height = `${this.textInput.scrollHeight}px`;
        this.highlightOutput.style.height = `${this.textInput.scrollHeight}px`;
        this.lineNumbers.style.height = `${this.textInput.scrollHeight}px`;
    }

    syncScrollPosition() {
        this.highlightOutput.scrollTop = this.textInput.scrollTop;
        this.highlightOutput.scrollLeft = this.textInput.scrollLeft;
        this.lineNumbers.scrollTop = this.textInput.scrollTop; // Sync the line numbers with text input
    }

    click() {
        if (this.textInput.value === "// Edit your score here") {
            this.textInput.value = "";
        }

        this.textInput.focus();
        this.updateHighlightOutput();
    }

    generateOScofoScore() {
        let score = "";
        score += `BPM ${this.musicxmlScore[0][0].bpm}`;
        let allNotes = [];
        for (let i = 0; i < this.musicxmlScore.length; i++) {
            const currentMeasure = this.musicxmlScore[i];
            for (let note of currentMeasure) {
                allNotes.push(note);
            }
        }

        let lastMeasureNumber = 0;
        for (let i = 0; i < allNotes.length; i++) {
            let note = allNotes[i];
            if (note !== undefined) {
                if (note.measureNumber != lastMeasureNumber) {
                    score += "\n\n; Measure number " + note.measureNumber + "";
                    lastMeasureNumber = note.measureNumber;
                }
            }
            score += "\n";
            if (note.rest) {
                score += "REST ";
                score += `${note.duration}`;
            } else if (note.tremolo) {
                score += "TRILL (";
                let duration = 0;
                while (true) {
                    note = allNotes[i];
                    if (note === undefined) {
                        break;
                    }
                    if (duration > 0) {
                        score += " ";
                    }

                    score += `${note.step}`;
                    if (note.alter) {
                        if (note.alter == "1") {
                            score += `#`;
                        } else if (note.alter == "-1") {
                            score += "b";
                        } else {
                            alert("not supported");
                        }
                    }
                    score += `${note.octave}`;
                    duration += parseInt(note.duration);
                    if (note.tremolo == false) {
                        break;
                    }
                    i++;
                }
                score += `) ${duration}`;
            } else if (note.tied) {
                score += "NOTE ";
                let pitchclass = note.step;
                if (note.alter) {
                    if (note.alter == "1") {
                        pitchclass += `#`;
                    } else if (note.alter == "-1") {
                        pitchclass += "b";
                    } else {
                        alert("not supported");
                    }
                }
                pitchclass += `${note.octave}`;
                let duration = 0;
                while (true) {
                    note = allNotes[i];
                    if (note === undefined) {
                        break;
                    }
                    if (note.tremolo) {
                        alert("Tied notes cannot be tremolo, OScofo does not support this");
                        return;
                    }
                    duration += parseFloat(note.duration);
                    if (note.tied == false) {
                        break;
                    }
                    i++;
                }
                score += `${pitchclass} ${duration} ; tied`;
            } else {
                score += `NOTE ${note.step}`;
                if (note.alter) {
                    if (note.alter == "1") {
                        score += `#`;
                    } else if (note.alter == "-1") {
                        score += "b";
                    } else {
                        alert("not supported");
                    }
                }
                score += `${note.octave} `;
                score += `${note.duration}`;
            }
        }
        this.textInput.value = score;
        this.updateHighlightOutput();
    }

    parseScore(doc) {
        const part = doc.getElementsByTagName("score-partwise")[0];
        const measures = part.getElementsByTagName("measure");
        let bpm = 60;
        let beatUnit = "quarter";
        this.musicxmlScore = [];
        let isTremolo = false;
        let isTied = false;
        let divisionsFactor = 1;
        for (let measure of measures) {
            let divisions = measure.getElementsByTagName("divisions");
            if (divisions.length > 0) {
                divisionsFactor = parseFloat(divisions[0].textContent);
            }
            let metronome = measure.getElementsByTagName("metronome")[0];
            if (metronome) {
                beatUnit = metronome.getElementsByTagName("beat-unit")[0].textContent;
                bpm = metronome.getElementsByTagName("per-minute")[0].textContent;
            }
            let measureNumber = measure.getAttribute("number");
            let notes = measure.getElementsByTagName("note");
            let measureNotes = [];
            for (let i = 0; i < notes.length; i++) {
                let note = notes[i];
                let pitch = note.getElementsByTagName("pitch")[0];
                let tremolo = note.getElementsByTagName("tremolo");
                let tied = note.getElementsByTagName("tied");

                if (tremolo.length > 0) {
                    if (tremolo[0].getAttribute("type") == "start") {
                        isTremolo = true;
                    }
                    if (tremolo[0].getAttribute("type") == "stop") {
                        isTremolo = false;
                    }
                }
                if (tied.length > 0) {
                    if (tied[0].getAttribute("type") == "start") {
                        isTied = true;
                    }
                    if (tied[0].getAttribute("type") == "stop") {
                        isTied = false;
                    }
                }

                let step, octave, alter;
                if (!pitch) {
                    step = null;
                    octave = null;
                } else {
                    step = pitch.getElementsByTagName("step")[0].textContent;
                    octave = pitch.getElementsByTagName("octave")[0].textContent;
                    const alterElement = pitch.getElementsByTagName("alter")[0]; // Get the first <alter> element
                    if (alterElement) {
                        alter = alterElement.textContent; // If it exists, get its text content
                    } else {
                        alter = null;
                    }
                }

                let duration = note.getElementsByTagName("duration")[0].textContent;
                let rest = note.getElementsByTagName("rest")[0];
                let noteObj = {
                    bpm: bpm,
                    step: step,
                    octave: octave,
                    alter: alter,
                    duration: parseFloat(duration) / divisionsFactor,
                    rest: false,
                    tremolo: isTremolo,
                    tied: isTied,
                    measureNumber: measureNumber,
                };
                if (rest) {
                    noteObj["rest"] = true;
                }

                measureNotes.push(noteObj);
            }
            this.musicxmlScore.push(measureNotes);
        }
        this.generateOScofoScore();
    }

    uploadScore() {
        const fileInput = document.getElementById("fileInput");
        fileInput.focus(); // Ensure the element is in focus
        fileInput.click();

        fileInput.onchange = (event) => {
            // Get the first file uploaded
            const file = event.target.files[0];
            if (!file) {
                console.error("No file selected");
                return;
            }

            // If it's an MXL file (compressed MusicXML), handle it differently
            if (file.name.endsWith(".mxl")) {
                const reader = new FileReader();
                reader.onload = (e) => {
                    // Create a JSZip object from the file content
                    JSZip.loadAsync(e.target.result)
                        .then((zip) => {
                            zip.file("score.xml")
                                .async("string")
                                .then((xmlString) => {
                                    const parser = new DOMParser();
                                    const doc = parser.parseFromString(xmlString, "application/xml");
                                    this.parseScore(doc); // Parse the MusicXML
                                });
                        })
                        .catch((error) => {
                            console.error("Error extracting MXL file:", error);
                        });
                };
                reader.onerror = (error) => {
                    alert("There was an error reading the file:", error);
                };
                reader.readAsArrayBuffer(file); // Read the MXL as an array buffer
            } else if (file.name.endsWith(".xml") || file.name.endsWith(".musicxml")) {
                const reader = new FileReader();
                reader.onload = (e) => {
                    const xmlString = e.target.result;
                    const parser = new DOMParser();
                    const doc = parser.parseFromString(xmlString, "application/xml");
                    this.parseScore(doc); // Parse the MusicXML
                };
                reader.onerror = (error) => {
                    alert("There was an error reading the file:", error);
                };
                reader.readAsText(file); // Read the XML as text
            } else {
                console.error("Unsupported file type");
            }
        };
    }

    saveToCookies() {
        let input = document.querySelector(".text-input");
        const value = input.value;
        document.cookie = `textInputValue=${encodeURIComponent(value)}; path=/; max-age=86400; SameSite=None; Secure`;
    }

    getCookie(name) {
        const value = `; ${document.cookie}`;
        const parts = value.split(`; ${name}=`);
        if (parts.length === 2) return decodeURIComponent(parts.pop().split(";").shift());
        return null;
    }

    initEventListeners() {
        this.textInput.addEventListener("input", () => this.updateHighlightOutput());
        this.textInput.addEventListener("select", () => this.simulateSelection());
        this.textInput.addEventListener("scroll", () => this.syncScrollPosition());
        this.textInput.addEventListener("click", () => this.click());
        setInterval(this.saveToCookies, 15000);

        const downloadButton = document.querySelector("#download-score");
        const uploadButtom = document.querySelector("#upload-score");
        if (downloadButton && uploadButtom) {
            downloadButton.addEventListener("click", () => this.downloadScore());
            uploadButtom.addEventListener("click", () => this.uploadScore());
        }

        const recoveredValue = this.getCookie("textInputValue");
        this.textInput.value = recoveredValue;
        if (!recoveredValue) {
            this.textInput.value = "// Edit your score here";
        }
        this.updateHighlightOutput();
    }
}

// Instantiate the class
const scofoHighlighter = new ScofoHighlighter(
    ".text-input",
    ".highlight-output",
    ".line-numbers",
    "tree-sitter-score.wasm",
);
