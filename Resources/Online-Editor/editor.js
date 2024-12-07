class ScofoHighlighter {
    constructor(textInputSelector, highlightOutputSelector, parserLanguageUrl) {
        this.textInput = document.querySelector(textInputSelector);
        this.highlightOutput = document.querySelector(highlightOutputSelector);
        this.Parser = window.TreeSitter;
        this.ScofoParser = null;
        this.parserLanguageUrl = parserLanguageUrl;

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

    highlightKeywords(text) {
        return text
            .replace(/NOTE/g, '<span class="keyword-blue">NOTE</span>')
            .replace(/C5/g, '<span class="keyword-red">C5</span>');
    }

    applySelection(text, selectionStart, selectionEnd) {
        const beforeSelection = text.slice(0, selectionStart);
        const selectedText = text.slice(selectionStart, selectionEnd);
        const afterSelection = text.slice(selectionEnd);

        return (
            this.highlightKeywords(beforeSelection) +
            `<span class="highlight-selection">${this.highlightKeywords(selectedText)}</span>` +
            this.highlightKeywords(afterSelection)
        );
    }

    updateHighlightOutput() {
        const value = this.textInput.value;
        this.highlightOutput.innerHTML = this.highlightKeywords(value);

        console.log(this.highlightKeywords(value));

        // print tree-sitter output string
        const tree = this.ScofoParser.parse(value);
        console.log(tree.rootNode.toString());
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
