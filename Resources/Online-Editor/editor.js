class ScofoOnlineEditor {
    constructor(textInputSelector, highlightOutputSelector, lineNumbersSelector, parserLanguageUrl) {
        this.textInput = document.querySelector(textInputSelector);
        this.highlightOutput = document.querySelector(highlightOutputSelector);
        this.lineNumbers = document.querySelector(lineNumbersSelector);

        this.Parser = window.TreeSitter;
        this.ScofoParser = null;
        this.parserLanguageUrl = parserLanguageUrl;
        this.htmlFormatterCode = "";
        this.linesWithErrors = {}; // Track lines with errors
        this.musicxmlScore = {};
        this.lastUpdate = Date.now();
        this.highglightIds = ["pitch", "duration"];

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
        // console.log(this.ScofoParser.language);
    }

    applySelection(text, selectionStart, selectionEnd) {
        const selectedText = text.slice(selectionStart, selectionEnd);
        return `<span class="highlight-selection">${selectedText}</span>`;
    }

    showError(message) {
        const errorContainer = document.querySelector(".error-messages");
        const errorElement = document.createElement("p");
        errorElement.textContent = message;
        errorContainer.appendChild(errorElement);
    }

    // Example usage
    highlightCode(input, rootNode) {
        const desiredTypes = ["eventId", "pitch", "duration", "comment", "configId", "numberSet"];
        let result = "";
        let lastIndex = 0;

        function processNode(myClass, node) {
            if (desiredTypes.includes(node.type)) {
                const start = node.startIndex;
                let end = node.endIndex;
                if (start == end) {
                    end++;
                }

                let hasError = myClass.checkErrors(node);
                let classCss = node.type;
                if (hasError) {
                    classCss += " error";
                }

                if (start > lastIndex) {
                    result += `<span>${input.slice(lastIndex, start)}</span>`;
                }
                result += `<span class="${classCss}">${input.slice(start, end)}</span>`;
                lastIndex = end;
            }
            for (let i = 0; i < node.namedChildCount; i++) {
                processNode(myClass, node.namedChild(i));
            }
        }
        for (let i = 0; i < rootNode.namedChildCount; i++) {
            const eventNode = rootNode.namedChild(i);
            processNode(this, eventNode);
        }
        if (lastIndex < input.length) {
            result += `<span>${input.slice(lastIndex)}</span>`;
        }
        this.checkErrors(rootNode);
        return result;
    }

    checkErrors(node, errors = {}) {
        if (node.text == "" && node.type != "score") {
            let line = node.parent.startPosition.row;
            errors[line] = {};
            errors[line].line = line;
            errors[line].init = node.startIndex;
            errors[line].end = node.endIndex;
            errors[line].error = true;
            errors[line].message = "Error: " + node.parent.type + " is empty";
            return true;
        }
        return false;
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

    resizeInputCanvas() {
        let lines = this.textInput.value.split("\n");
        let biggerLine = lines.reduce((a, b) => (a.length > b.length ? a : b));
        let width = biggerLine.length + "ch";
        this.textInput.style.width = width;
        let widthInPixels = this.textInput.getBoundingClientRect().width;
        let heightInPixels = this.textInput.getBoundingClientRect().height;
        this.highlightOutput.style.width = widthInPixels + "px";
        this.highlightOutput.style.height = heightInPixels + "px";
    }

    updateHighlightOutput() {
        const errorContainer = document.querySelector(".error-messages");
        errorContainer.innerHTML = "";

        this.resizeInputCanvas();

        // this.resizeInput();
        const value = this.textInput.value;
        const tree = this.ScofoParser.parse(value);
        let errors = {};
        // console.log(tree.rootNode.toString());
        let styledCode = this.highlightCode(value, tree.rootNode);

        this.highlightOutput.innerHTML = styledCode;
        this.updateLineNumbers(errors);

        for (let errorLine in errors) {
            this.showError("Error at line " + errorLine + ".");
        }

        this.adjustTextInputHeight();
    }

    adjustTextInputHeight() {
        this.textInput.style.height = `${this.textInput.scrollHeight}px`;
    }

    adjustLineNumbersHeight() {
        this.lineNumbers.style.height = `${this.textInput.scrollHeight}px`;
    }

    downloadScore() {
        const content = this.textInput.value;
        const blob = new Blob([content], { type: "text/plain" });
        const a = document.createElement("a");
        a.href = URL.createObjectURL(blob);
        a.download = "score.scofo.txt";
        a.click();
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

    getPitch(note) {
        let pitch = `${note.step}`;
        if (note.alter) {
            if (note.alter == "1") {
                pitch += `#`;
            } else if (note.alter == "-1") {
                pitch += "b";
            } else {
                alert("accident " + note.alter + "is not supported by OScofo yet");
            }
        }
        pitch += `${note.octave}`;
        return pitch;
    }

    getAllPitches(allNotes, index) {
        let chords = [];

        return;
    }

    generateOScofoScore() {
        let score = "";

        score += `/* Generated by OScofo online editor\n`;
        score += `${this.musicxmlScore.pieceName} by ${this.musicxmlScore.pieceComposer}\n`;
        score += `*/\n\n`;

        score += `BPM ${this.musicxmlScore.measures[1][0].bpm}`;
        let bpm = this.musicxmlScore.measures[1][0].bpm;
        let allNotes = [];

        for (let measureNumber in this.musicxmlScore.measures) {
            const measure = this.musicxmlScore.measures[measureNumber];
            for (let note of measure) {
                allNotes.push(note);
            }
        }

        let lastMeasureNumber = 0;
        for (let i = 0; i < allNotes.length; i++) {
            let note = allNotes[i];
            if (note !== undefined) {
                if (note.measureNumber != lastMeasureNumber) {
                    score += `\n\n// Measure number ${note.measureNumber}`;
                    lastMeasureNumber = note.measureNumber;
                }
            }
            if (note.bpm != bpm) {
                score += `\nBPM ${note.bpm}\n`;
                bpm = note.bpm;
            }
            score += "\n";
            if (note.isRest) {
                score += `REST ${note.duration}`;
            } else {
                let isTied = note.isTied;
                let pitches = [this.getPitch(note)];
                let duration = note.duration;
                let type = "NOTE";
                let nextNote = allNotes[i + 1];

                // tied pitches
                if (note.isTied && !nextNote.isChord) {
                    while (true) {
                        i++;
                        nextNote = allNotes[i];
                        if (nextNote.isTied) {
                            duration += nextNote.duration;
                        } else {
                            i--;
                            break;
                        }
                    }
                }

                // process chord not tied
                if (nextNote.isChord && !note.isTied) {
                    type = "CHORD";
                    while (true) {
                        i++;
                        nextNote = allNotes[i];
                        if (nextNote.isChord) {
                            pitches.push(this.getPitch(nextNote));
                        } else {
                            i--;
                            break;
                        }
                    }
                }

                // process chord tied
                if (nextNote.isChord && note.isTied) {
                    type = "CHORD";
                    let chords = [];
                    let lastNote = note;
                    while (true) {
                        i++;
                        nextNote = allNotes[i];
                        if (nextNote === undefined) {
                            break;
                        }

                        if (!nextNote.isChord) {
                            chords.push(pitches);
                            pitches = [this.getPitch(nextNote)];
                        }

                        if (nextNote.isChord) {
                            pitches.push(this.getPitch(nextNote));
                        } else if (!nextNote.isTied || (nextNote.tiedType == "start" && lastNote.tiedType == "stop")) {
                            i--;
                            break;
                        }

                        if (nextNote.isTied && !nextNote.isChord) {
                            duration += nextNote.duration;
                        }
                        lastNote = nextNote;
                    }
                    pitches = chords[0];
                }

                // process tremolo
                if (note.isTremolo) {
                    type = "TRILL";
                    while (true) {
                        i++;
                        nextNote = allNotes[i];
                        if (nextNote === undefined) {
                            i--;
                            break;
                        }
                        if (nextNote.isTremolo) {
                            pitches.push(this.getPitch(nextNote));
                            duration += nextNote.duration;
                        } else {
                            i--;
                            break;
                        }
                    }
                }

                if (pitches.length > 1) {
                    score += `${type} (${pitches.join(" ")}) ${duration}`;
                } else {
                    score += `${type} ${pitches[0]} ${duration}`;
                }
                if (note.isTied) {
                    score += " // TIED";
                }
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
        this.musicxmlScore = {};
        this.musicxmlScore.measures = {};
        let isTremolo = false;
        let isTied = false;
        let tremoloType = null;
        let tiedType = null;
        let pieceName = part.getElementsByTagName("work")[0].getElementsByTagName("work-title")[0].textContent;
        let pieceComposer = part.getElementsByTagName("creator")[0].textContent;
        this.musicxmlScore.pieceName = pieceName;
        this.musicxmlScore.pieceComposer = pieceComposer;

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
                let chord = note.getElementsByTagName("chord").length;
                let pitch = note.getElementsByTagName("pitch")[0];
                let tremolo = note.getElementsByTagName("tremolo");
                let tied = note.getElementsByTagName("tied");
                if (tremolo.length > 0) {
                    isTremolo = true;
                    tremoloType = tremolo[0].getAttribute("type");
                } else {
                    isTremolo = false;
                    tremoloType = null;
                }
                if (tied.length > 0) {
                    isTied = true;
                    tiedType = tied[0].getAttribute("type");
                } else {
                    isTied = false;
                    tiedType = null;
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
                        alter = parseInt(alterElement.textContent); // If it exists, get its text content
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
                    isRest: false,
                    isTremolo: isTremolo,
                    tremoloType: tremoloType,
                    isTied: isTied,
                    tiedType: tiedType,
                    measureNumber: measureNumber,
                    isChord: chord == 1,
                    firstChordNote: false,
                };
                if (rest) {
                    noteObj.isRest = true;
                }
                measureNotes.push(noteObj);
            }
            this.musicxmlScore.measures[measureNumber] = {};
            this.musicxmlScore.measures[measureNumber] = measureNotes;
        }
        this.generateOScofoScore();
        this.resizeInputCanvas();
    }

    uploadScore() {
        const fileInput = document.getElementById("fileInput");
        fileInput.click();
        fileInput.onchange = (event) => {
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
                            alert("Error extracting MXL file:", error);
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
                alert("Unsupported file type");
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

    preventDefault(e) {
        if (e.key === "Tab") {
            e.preventDefault();
            this.textInput.value += "    ";
        }
    }

    initEventListeners() {
        this.textInput.addEventListener("input", () => this.updateHighlightOutput());
        this.textInput.addEventListener("keydown", (e) => this.preventDefault(e));
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
        this.resizeInputCanvas();
    }
}

// Instantiate the class
const scofoEditor = new ScofoOnlineEditor(
    ".text-input",
    ".highlight-output",
    ".line-numbers",
    "tree-sitter-scofo.wasm",
);
