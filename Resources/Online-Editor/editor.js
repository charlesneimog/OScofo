class ScofoHighlighter {
    constructor(textInputSelector, highlightOutputSelector, parserLanguageUrl) {
        this.textInput = document.querySelector(textInputSelector);
        this.highlightOutput = document.querySelector(highlightOutputSelector);
        this.Parser = window.TreeSitter;
        this.ScofoParser = null;
        this.parserLanguageUrl = parserLanguageUrl;
        this.htmlFormatterCode = "";

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

    highlightCode(input, node) {
        const styles = {
            open_parenthesis: "color: black; font-weight: bold;",
            close_parenthesis: "color: black; font-weight: bold;",
            ERROR: "color: red; font-weight: bold; text-decoration: underline;", // Added underline
            NOTE: "color: red; font-weight: bold;",
            octave: "color: green; font-weight: bold;",
            pitchclass: "color: green; font-weight: bold;",
            midi: "color: green; font-weight: bold;",
            integer: "color: blue; font-weight: bold;",
        };

        let highlightedText = "";
        if (node.namedChildCount > 0) {
            let lastPosition = node.startIndex;
            node.namedChildren.forEach((child) => {
                highlightedText += input.slice(lastPosition, child.startIndex);
                highlightedText += this.highlightCode(input, child);
                lastPosition = child.endIndex;
            });
            highlightedText += input.slice(lastPosition, node.endIndex);
        } else {
            const nodeTypeStyle = styles[node.type] || "";
            if (styles.hasOwnProperty(node.type)) {
                highlightedText += `<span style="${nodeTypeStyle}">${input.slice(node.startIndex, node.endIndex)}</span>`;
            } else {
                highlightedText += `<span style="${nodeTypeStyle}">${input.slice(node.startIndex, node.endIndex)}</span>`;
                console.log(node.type);
            }
        }
        return highlightedText;
    }

    updateHighlightOutput() {
        const value = this.textInput.value;
        const tree = this.ScofoParser.parse(value);
        const styledCode = this.highlightCode(value, tree.rootNode);
        this.highlightOutput.innerHTML = styledCode;
    }

    simulateSelection() {
        const value = this.textInput.value;
        const selectionStart = this.textInput.selectionStart;
        const selectionEnd = this.textInput.selectionEnd;
        this.highlightOutput.innerHTML = this.applySelection(value, selectionStart, selectionEnd);
    }

    syncScrollPosition() {
        this.highlightOutput.scrollTop = this.textInput.scrollTop;
        this.highlightOutput.scrollLeft = this.textInput.scrollLeft;
    }

    initEventListeners() {
        this.textInput.addEventListener("input", () => this.updateHighlightOutput());
        this.textInput.addEventListener("select", () => this.simulateSelection());
        this.textInput.addEventListener("scroll", () => this.syncScrollPosition());
    }
}

// Instantiate the class
const scofoHighlighter = new ScofoHighlighter(".text-input", ".highlight-output", "tree-sitter-score.wasm");
