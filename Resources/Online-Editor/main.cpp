#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <tree_sitter/api.h>
#include <tree_sitter/highlight.h>

extern "C" TSLanguage *tree_sitter_scofo();

int main() {
    const char *highlight_names[] = {
        "keyword",  // "keyword" might be a syntax element like 'for', 'if', etc.
        "function", // "function" might be a function name
        "string"    // "string" could be string literals
    };

    // List of HTML attributes to apply for each highlight
    const char *attribute_strings[] = {
        "color: red; font-weight: bold;",       // Attribute for keywords
        "color: blue; font-style: italic;",     // Attribute for functions
        "color: green; font-family: monospace;" // Attribute for strings
    };

    uint32_t highlight_count = 3;
    TSHighlighter *highlighter = ts_highlighter_new(highlight_names, attribute_strings, highlight_count);

    if (!highlighter) {
        fprintf(stderr, "Error initializing highlighter\n");
        return 1;
    }

    // Create a highlight buffer to store the output
    TSHighlightBuffer *buffer = ts_highlight_buffer_new();
    if (!buffer) {
        fprintf(stderr, "Error initializing highlight buffer\n");
        ts_highlighter_delete(highlighter);
        return 1;
    }

    const char *scope_name = "score";
    const char *injection_regex = ""; // Empty string for no injection regex
    const char *highlight_query = ""; // Empty string for no highlight query
    const char *injection_query = ""; // Empty string for no injection query
    const char *locals_query = "";
    uint32_t highlight_query_len = 0;
    uint32_t injection_query_len = 0;
    uint32_t locals_query_len = 0;

    TSHighlightError error = ts_highlighter_add_language(highlighter, "scofo", "source.scofo", NULL, tree_sitter_scofo(), highlight_query,
                                                         injection_query, locals_query, highlight_query_len, injection_query_len, locals_query_len);

    // Highlight some source code
    const char *source_code = "NOTE C4 2";
    error = ts_highlighter_highlight(highlighter, "text.html.basic", source_code, strlen(source_code), buffer, NULL);
    if (error != TSHighlightOk) {
        fprintf(stderr, "Error highlighting source code: %d\n", error);
        ts_highlighter_delete(highlighter);
        ts_highlight_buffer_delete(buffer);
        return 1;
    }

    // Get the HTML content and line offsets from the buffer
    uint32_t html_len = ts_highlight_buffer_len(buffer);
    uint32_t html_line_count = ts_highlight_buffer_line_count(buffer);
    const uint8_t *html = ts_highlight_buffer_content(buffer);
    const uint32_t *html_line_offsets = ts_highlight_buffer_line_offsets(buffer);

    printf("The HTML's length is %u\n", html_len);
    printf("The HTML has %u lines\n", html_line_count);
    if (html_line_count > 1) {
        printf("The HTML's second line starts at byte %u\n", html_line_offsets[1]);
    } else {
        printf("There is no second line in the HTML.\n");
    }

    // Print the HTML content
    printf("Here's the HTML:\n%.*s\n", html_len, html);

    // Clean up
    ts_highlighter_delete(highlighter);
    ts_highlight_buffer_delete(buffer);

    return 0;
}
