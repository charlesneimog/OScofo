function myCustomAutocomplete(cm) {
    cm.showHint({
        hint: customHint,
    });
}

function customHint(editor) {
    var cur = editor.getCursor();
    var token = editor.getTokenAt(cur);
    var word = token.string;

    var keywords = ["NOTE", "REST", "TRILL", "CHORD", "BPM"];

    var matches = keywords.filter(function (kw) {
        return kw.startsWith(word);
    });

    return {
        list: matches,
        from: { line: cur.line, ch: token.start },
        to: { line: cur.line, ch: token.end },
    };
}

class ScofoOnlineEditor {
    constructor() {
        this.Parser = window.TreeSitter;

        // debug option
        this.showTree = true;

        this.ScofoParser = null;
        this.parserOScofoWasm = "tree-sitter-scofo.wasm";
        this.parserLuaWasm = "tree-sitter-lua.wasm";

        this.htmlFormatterCode = "";
        this.linesWithErrors = {};
        this.musicxmlScore = {};

        this.htmlFormatter = {};
        this.bigTextWarning = false;

        this.initParser().then(() => {
            this.handleCodeChange();
        });

        this.codeInput = document.getElementById("code-input");
        this.codeEditor = CodeMirror.fromTextArea(this.codeInput, {
            lineNumbers: true,
            showCursorWhenSelecting: true,
            placeholder: "// Editor your score here",
            extraKeys: {
                "Ctrl-Z": function (cm) {
                    console.log("Ctrl-Z");
                    cm.undo();
                },
                "Ctrl-Y": function (cm) {
                    cm.redo();
                },
                "Cmd-Z": function (cm) {
                    cm.undo();
                },
                "Cmd-Shift-Z": function (cm) {
                    cm.redo();
                },
                "Ctrl-Space": function (cm) {
                    myCustomAutocomplete(cm);
                },
                "Ctrl-;": function (cm) {
                    const selection = cm.getSelection();
                    if (selection) {
                        cm.replaceSelection(`/* ${selection} */`);
                    } else {
                        const cursor = cm.getCursor();
                        const line = cm.getLine(cursor.line);
                        cm.replaceRange(
                            "// " + line,
                            { line: cursor.line, ch: 0 },
                            { line: cursor.line, ch: line.length },
                        );
                    }
                },
            },
        });

        this.codeEditor.on("cursorActivity", () => {
            const cursorPos = this.codeEditor.getCursor();
            this.showCodeSuggestions(this.codeEditor, cursorPos);
        });

        this.codeContainer = document.getElementById("code-container");

        // this.codeContainer.addEventListener("scroll", () => {
        //     let codeInput = document.getElementById("code-input");
        //     let lines = codeInput.value.split("\n");
        //     let biggerLine = lines.reduce((a, b) => (a.length > b.length ? a : b));
        //     let width = biggerLine.length + "ch";
        //     let height = lines.length + "em";
        //     codeInput.style.width = width;
        //     codeInput.style.height = height;
        // });

        this.loadState();
        this.saveStateOnChange = this.debounce(this.saveState, 2000);
        this.runTreeQueryOnChange = this.debounce(this.runTreeQuery, 100);

        this.handleCodeChange = this.handleCodeChange.bind(this);
        this.treeEditForEditorChange = this.treeEditForEditorChange.bind(this);
        this.codeEditor.on("changes", this.handleCodeChange);

        // Styles
        this.highlights = {
            oscofo: {
                keyword: "color: var(--red); font-weight: bold;",
                pitch: "color: var(--blue); font-weight: bold;",
                duration: "color: var(--yellow); font-weight: bold;",
                comment: "color: var(--comment); opacity: 0.7; font-style: italic;",
                config: "color: var(--purple); font-weight: bold;",
                error: "text-decoration: underline; text-decoration-style: wavy; text-decoration-color: var(--red);",
                action: "color: var(--green);",
                actionKey: "color: var(--purple);",
                timeUnit: "color: var(--highlight);",
                number: "color: var(--highlight);",
                exec: "color: var(--fg); font-weight: bold;",
                receiver: "color: var(--green);",
                pdargs: "color: var(--fg); font-style: italic;",
                timedAction: "color: var(--highlight); font-weight: 100;",
            },
            lua: {
                comment: "color: var(--comment); opacity: 0.4; font-style: italic; opacity: var(--lua-opacity)",
                string: "color: var(--green); font-style: italic; font-weight: 100, opacity: var(--lua-opacity)",

                "function.bracket": "color: var(--fg); font-weight: bold; opacity: var(--lua-opacity)",
                "function.call.lua": "color: var(--cyan); font-weight: 100; opacity: var(--lua-opacity)",
                "function.name": "color: var(--cyan); font-weight: 100; opacity: var(--lua-opacity)",

                "keyword.repeat": "color: var(--cyan); font-weight: 100; opacity: var(--lua-opacity)",
                "keyword.conditional": "color: var(--cyan); font-weight: 100; opacity: var(--lua-opacity)",
                "keyword.return": "color: var(--purple); opacity: var(--lua-opacity)",
                "keyword.function": "color: var(--red); opacity: var(--lua-opacity)",

                variable: "color: var(--blue); opacity: var(--lua-opacity)",
            },
        };

        this.OScofoHighlightQuery = `
            (pitchEventId) @keyword
            (restEventId) @keyword
            (timeEventId) @keyword
            (identifier) @keyword
            (configId) @config
            (comment) @comment
            (pitch) @pitch
            (duration) @duration
            (numberSet) @duration
            (ACTION (keyword) @ACTION)
            (actionKey) @actionKey
            (timedAction (number) @number)

            (timeUnit) @timeUnit
            (exec (keyword) @exec) 
            (receiver) @receiver
            ((pdargs)  @pdargs)

            (lua_body) @lua_body
            (lua_call) @lua_body

            (ERROR) @error
        `;

        this.LuaStringQuery = null;
        this.fetchTextFile("highlight/lua.scm");

        // Buttons
        const downloadButton = document.querySelector("#download-score");
        const uploadButtom = document.querySelector("#upload-score");
        const loadButtom = document.querySelector("#load-score");

        if (downloadButton && uploadButtom && loadButtom) {
            downloadButton.addEventListener("click", () => this.downloadScore());
            uploadButtom.addEventListener("click", () => this.uploadScore());
            loadButtom.addEventListener("click", () => this.loadTxtScore());
        } else {
            alert("Buttons not found");
        }
    }

    //╭─────────────────────────────────────╮
    //│      Editor and Text Rendering      │
    //╰─────────────────────────────────────╯
    showCodeSuggestions(cm, startPos) {
        const line = startPos.line;
        const ch = startPos.ch;
        const currentWord = cm.getLine(line).slice(0, ch).split(/\s+/).pop();
        const suggestions = {
            NOTE: "NOTE",
            TRILL: "TRILL",
            CHORD: "CHORD",
        };

        if (suggestions[currentWord]) {
            this.addGhostText(line, suggestions[currentWord]);
        }
    }

    async fetchTextFile(filePath) {
        try {
            const response = await fetch(filePath);
            if (!response.ok) {
                throw new Error(`Error fetching file: ${response.statusText}`);
            }
            const text = await response.text(); // Get the text content
            this.LuaStringQuery = text;
        } catch (error) {
            console.error("Error:", error);
        }
    }

    addGhostText(line, text) {
        return;
    }

    getHighlights(language, capture) {
        return this.highlights[language][capture] || "";
    }

    async handleCodeChange(_, changes) {
        const newText = this.codeEditor.getValue();
        const edits = this.tree && changes && changes.map(this.treeEditForEditorChange);
        if (edits) {
            for (const edit of edits) {
                this.tree.edit(edit);
            }
        }
        const newTree = this.ScofoParser.parse(newText, this.tree);
        let needParse = this.runFormatterAfterParse(newTree.rootNode);
        if (needParse) {
            this.handleCodeChange(_, changes);
            return;
        }

        this.checkErrors(newTree);
        if (this.tree) this.tree.delete();
        this.tree = newTree;
        this.runTreeQueryOnChange();
        this.saveStateOnChange();
    }

    treeEditForEditorChange(change) {
        const oldLineCount = change.removed.length;
        const newLineCount = change.text.length;
        const lastLineLength = change.text[newLineCount - 1].length;
        const startPosition = { row: change.from.line, column: change.from.ch };
        const oldEndPosition = { row: change.to.line, column: change.to.ch };
        const newEndPosition = {
            row: startPosition.row + newLineCount - 1,
            column: newLineCount === 1 ? startPosition.column + lastLineLength : lastLineLength,
        };
        const startIndex = this.codeEditor.indexFromPos(change.from);
        let newEndIndex = startIndex + newLineCount - 1;
        let oldEndIndex = startIndex + oldLineCount - 1;
        for (let i = 0; i < newLineCount; i++) newEndIndex += change.text[i].length;
        for (let i = 0; i < oldLineCount; i++) oldEndIndex += change.removed[i].length;
        return {
            startIndex,
            oldEndIndex,
            newEndIndex,
            startPosition,
            oldEndPosition,
            newEndPosition,
        };
    }

    luaFormatter(luaTree, luaPositionStart) {
        console.log("here");
        return;
    }

    luaHighlight(luaNode, luaPositionStart) {
        let luaTxt = luaNode.text;
        let luaTree = this.LuaParser.parse(luaTxt);

        if (luaTree.hasError) {
            return;
        }

        const captures = this.LuaQuery.captures(
            luaTree.rootNode,
            { row: 0, column: 0 },
            { row: Infinity, column: Infinity },
        );

        for (const { name, node } of captures) {
            const { startPosition, endPosition } = node;
            let luaStart = {
                row: startPosition.row + luaPositionStart.row,
                column: startPosition.column + (startPosition.row === 0 ? luaPositionStart.column : 0),
            };
            let luaEnd = {
                row: endPosition.row + luaPositionStart.row,
                column: endPosition.column + (endPosition.row === 0 ? luaPositionStart.column : 0),
            };

            this.codeEditor.markText(
                { line: luaStart.row, ch: luaStart.column },
                { line: luaEnd.row, ch: luaEnd.column },
                {
                    inclusiveLeft: true,
                    inclusiveRight: true,
                    css: this.getHighlights("lua", name),
                },
            );
        }
    }

    luaChildOfLuaBody(node) {
        let parent = node.parent;
        while (parent) {
            if (parent.type === "lua_body") {
                return true;
            }
            parent = parent.parent;
        }
        return false;
    }

    luaIndentBody(node) {
        if (node.parent.hasError) {
            return false;
        }
        let luaTxt = node.text;
        if (luaTxt.trim(" ") === "") {
            return false;
        }
        let lines = luaTxt.split("\n");

        const cursorPos = this.codeEditor.getCursor();
        const cursorLine = cursorPos.line;
        const cursorCh = cursorPos.ch;
        let needIndent = false;
        let indentedLines = lines.map((line, index) => {
            let modifiedLine = line;
            let addedSpaces = 0;
            if (!(line.startsWith("    ") || line.startsWith("\t")) && index !== lines.length - 1) {
                needIndent = true;
                const match = line.match(/^(\s*)/);
                let neededSpaces = 4;
                if (match) {
                    neededSpaces = 4 - (match[1].length % 4);
                }
                modifiedLine = " ".repeat(neededSpaces) + line;
                addedSpaces = neededSpaces;
            }
            if (index === cursorLine && addedSpaces > 0 && cursorCh <= line.length) {
                cursorPos.ch += addedSpaces;
            }
            return modifiedLine;
        });

        if (needIndent) {
            const indentedText = indentedLines.join("\n");
            const startPosition = { line: node.startPosition.row, ch: node.startPosition.column };
            const endPosition = { line: node.endPosition.row, ch: node.endPosition.column };
            this.codeEditor.replaceRange(indentedText, startPosition, endPosition);
            this.codeEditor.setCursor(cursorPos);
            return true;
        }

        return false;
    }

    runFormatterBeforeParser() {
        return;
    }

    runFormatterAfterParse(node) {
        let oscofoFormatter = {
            EVENT: { column: 0, toLowerCase: false, toUpperCase: false },
            ACTION: { column: 4, toLowerCase: false, toUpperCase: false },
            pitch: { column: null, toLowerCase: false, toUpperCase: true },
        };
        let wasFormatted = false;

        function formatNode(node, formatter) {
            if (formatter && node.type in formatter) {
                let thingFormat = formatter[node.type];
                const startPos = { line: node.startPosition.row, column: node.startPosition.column };
                let lineText = this.codeEditor.getLine(node.startPosition.row);
                let lineTextBefore = lineText.substring(0, node.startPosition.column);

                // place
                if (thingFormat.column !== null) {
                    if (lineTextBefore.trim() === "" && startPos.column !== formatter[node.type].column) {
                        this.codeEditor.replaceRange(node.text, { line: node.startPosition.row, ch: 0 }, startPos);
                        wasFormatted = true;
                    } else if (startPos.column !== formatter[node.type].column && lineTextBefore.trim() !== "") {
                        wasFormatted = true;
                        let intendation = " ".repeat(formatter[node.type].column);
                        this.codeEditor.replaceRange(
                            lineTextBefore + "\n" + intendation + node.text,
                            { line: node.startPosition.row, ch: 0 },
                            startPos,
                        );
                    }
                }

                // check if the text
                if (thingFormat.toUpperCase) {
                    return;
                    let newText = node.text.toUpperCase();
                    this.codeEditor.replaceRange(newText, startPos, startPos);
                }
            }

            node.children.forEach((child) => formatNode.call(this, child, formatter));
        }

        formatNode.call(this, node, oscofoFormatter);
        return wasFormatted;
    }

    runTreeQuery(_, startRow, endRow) {
        if (endRow == null) {
            const viewport = this.codeEditor.getViewport();
            startRow = viewport.from;
            endRow = viewport.to;
        }

        console.log(this.tree.rootNode.toString());

        this.codeEditor.operation(() => {
            const marks = this.codeEditor.getAllMarks();
            marks.forEach((m) => m.clear());

            if (this.tree && this.OScofoQuery) {
                const captures = this.OScofoQuery.captures(
                    this.tree.rootNode,
                    { row: startRow, column: 0 },
                    { row: endRow, column: 0 },
                );

                let lastNodeId;
                for (const { name, node } of captures) {
                    if (node.id === lastNodeId) continue;
                    lastNodeId = node.id;
                    const { startPosition, endPosition } = node;
                    if (!node.hasError) {
                        if (name === "lua_body" && !this.luaChildOfLuaBody(node)) {
                            if (!this.luaIndentBody(node)) {
                                this.luaHighlight(node, startPosition);
                            }
                        } else {
                            this.codeEditor.markText(
                                { line: startPosition.row, ch: startPosition.column },
                                { line: endPosition.row, ch: endPosition.column },
                                {
                                    inclusiveLeft: true,
                                    inclusiveRight: true,
                                    css: this.getHighlights("oscofo", name),
                                },
                            );
                        }
                    }
                }
            }
        });
    }

    loadState() {
        const sourceCode = localStorage.getItem("sourceCode");
        if (sourceCode) {
            this.codeInput.value = sourceCode;
        } else {
            this.codeInput.value = `// Edit you score here`;
        }
    }

    saveState() {
        localStorage.setItem("sourceCode", this.codeEditor.getValue());
    }

    debounce(func, wait, immediate) {
        var timeout;
        return function () {
            var context = this,
                args = arguments;
            var later = function () {
                timeout = null;
                if (!immediate) func.apply(context, args);
            };
            var callNow = immediate && !timeout;
            clearTimeout(timeout);
            timeout = setTimeout(later, wait);
            if (callNow) func.apply(context, args);
        };
    }

    // ─────────────────────────────────────

    async initParser() {
        await this.Parser.init();

        // OScofo
        this.ScofoParser = new this.Parser();
        const scoreScofo = await this.Parser.Language.load(this.parserOScofoWasm);
        this.ScofoParser.setLanguage(scoreScofo);

        // Lua
        this.LuaParser = new this.Parser();
        const luaParser = await this.Parser.Language.load(this.parserLuaWasm);
        this.LuaParser.setLanguage(luaParser);

        this.OScofoQuery = this.ScofoParser.getLanguage().query(this.OScofoHighlightQuery);
        this.LuaQuery = this.LuaParser.getLanguage().query(this.LuaStringQuery);
    }

    getMissing(node, list) {
        for (let i = 0; i < node.namedChildCount; i++) {
            let child = node.namedChild(i);
            console.log(child.toString());
            if (child.isMissing) {
                list.push(child);
            }
            this.getMissing(child);
        }
    }

    checkErrors(node) {
        node = node.rootNode;
        var lineWithErrors = [];
        var lineWithUnexpected = [];
        const errorContainer = document.querySelector(".error-messages");
        errorContainer.innerHTML = "";

        // let missing = [];
        // this.getMissing(node, missing);
        // console.log(missing);

        function checkNode(node) {
            for (let i = 0; i < node.namedChildCount; i++) {
                const errorElement = document.createElement("p");
                let child = node.namedChild(i);
                if (child.hasError) {
                    let message = "";
                    lineWithErrors.push(child.startPosition.row + 1);
                    if (child.type === "number") {
                        if (child.text === "") {
                            message =
                                "Missing " +
                                child.parent.type +
                                " at line " +
                                (child.parent.endPosition.row + 1) +
                                ", column " +
                                (child.parent.endPosition.column + 1);
                        }
                    } else if (child.type === "pitch") {
                        if (child.text === "") {
                            message = `Missing pitch at line ${child.endPosition.row + 1}`;
                        }
                    } else {
                        // message = `Unknown error at line ${child.endPosition.row + 1}`;
                    }
                    errorElement.textContent = message;
                    errorContainer.appendChild(errorElement);
                }
                let treeString = child.toString();
                if (treeString.startsWith("(UNEXPECTED") && !lineWithUnexpected.includes(child.startPosition.row + 1)) {
                    lineWithUnexpected.push(child.startPosition.row + 1);
                    errorElement.textContent = "UNEXPECTED keyword at line " + (child.startPosition.row + 1);
                    errorContainer.appendChild(errorElement);
                }
                checkNode(child);
            }
        }

        checkNode(node);
    }

    downloadScore() {
        const content = this.codeInput.value;
        const blob = new Blob([content], { type: "text/plain" });
        const a = document.createElement("a");
        a.href = URL.createObjectURL(blob);
        a.download = "score.scofo.txt";
        a.click();
    }

    //╭─────────────────────────────────────╮
    //│            Import Module            │
    //╰─────────────────────────────────────╯
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

    generateOScofoScore() {
        let score = "";

        score += `/* Generated by OScofo online editor`;
        if (this.musicxmlScore.pieceName && this.musicxmlScore.pieceComposer) {
            score += `\n${this.musicxmlScore.pieceName} by ${this.musicxmlScore.pieceComposer}\n`;
            score += `*/\n\n`;
        } else {
            score += ` */\n\n`;
        }

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
                if (nextNote !== undefined && nextNote.isChord && !note.isTied) {
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
                if (nextNote !== undefined && nextNote.isChord && note.isTied) {
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
                        if (nextNote.tremoloType === "stop") {
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
                    score += " // tied";
                }
            }
        }

        this.codeEditor.setValue(score);
        this.handleCodeChange();
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
        let credits = part.getElementsByTagName("credit");
        if (credits.elements !== 0) {
            for (let credit of credits) {
                let creditType = credit.getElementsByTagName("credit-type")[0];
                if (creditType) {
                    let text = creditType.textContent;
                    if (text == "title") {
                        let creditWords = credit.getElementsByTagName("credit-words");
                        if (creditWords.length > 0) {
                            this.musicxmlScore.pieceName = creditWords[0].textContent;
                        }
                    } else if (text == "composer") {
                        let creditWords = credit.getElementsByTagName("credit-words");
                        if (creditWords.length > 0) {
                            this.musicxmlScore.pieceComposer = creditWords[0].textContent;
                        }
                    }
                }
            }
        }

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

                let duration = note.getElementsByTagName("duration");
                if (duration.length == 0) {
                    duration = 0;
                } else {
                    duration = note.getElementsByTagName("duration")[0].textContent;
                }

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
        this.handleCodeChange();
    }

    uploadScore() {
        const fileInput = document.getElementById("scoreXmlInput");
        if (!fileInput) {
            console.error("File input not found");
            return;
        }
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
                    JSZip.loadAsync(e.target.result)
                        .then((zip) => {
                            const xmlFile = Object.keys(zip.files).find(
                                (fileName) => fileName.endsWith(".xml") && !fileName.includes("META-INF/"),
                            );
                            console.log(xmlFile);
                            if (xmlFile) {
                                zip.file(xmlFile)
                                    .async("string")
                                    .then((xmlString) => {
                                        const parser = new DOMParser();
                                        const doc = parser.parseFromString(xmlString, "application/xml");
                                        this.parseScore(doc); // Parse the MusicXML
                                    })
                                    .catch((error) => {
                                        alert("Error parsing XML:", error);
                                    });
                            } else {
                                alert("No XML file found in the ZIP archive.");
                            }
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

    loadTxtScore() {
        const fileInput = document.getElementById("scoreTxtInput");
        if (!fileInput) {
            console.error("File input not found");
            return;
        }

        fileInput.click();
        fileInput.onchange = (event) => {
            const file = event.target.files[0];
            if (!file) {
                console.error("No file selected");
                return;
            }
            const reader = new FileReader();
            reader.onload = (e) => {
                const fileContent = e.target.result; // Contains the content of the file
                this.codeEditor.setValue(fileContent);

                this.handleCodeChange();
            };
            reader.onerror = (e) => {
                console.error("Error reading file:", e);
            };
            reader.readAsText(file); // Read file as plain text
        };
    }
}

// Instantiate the class
const scofoEditor = new ScofoOnlineEditor("tree-sitter-scofo.wasm");
