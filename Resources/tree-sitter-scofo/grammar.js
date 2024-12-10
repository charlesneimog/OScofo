module.exports = grammar({
    name: "scofo",
    rules: {
        score: ($) => repeat($._statement),
        _statement: ($) => choice($.CONFIG, $.EVENT),
        identifier: (_) => /[a-zA-Z_][a-zA-Z0-9_]*/,

        EVENT: ($) => choice($.pitchEvent, $.rest),
        CONFIG: ($) => choice($.numberConfig),

        // Lua
        luaBlock: ($) => seq("LUA", "{", repeat($._lua_code), "}"),
        _lua_code: (_) => token(/.*/),

        // Config
        configId: ($) => choice(alias(token("BPM"), $.identifier), alias(token("TRANSPOSE"), $.identifier)),

        numberConfig: ($) => seq($.configId, $.numberSet),
        numberSet: ($) => $.number,

        // Events
        pitchEventId: ($) =>
            choice(
                alias(token("NOTE"), $.identifier), // Treat "NOTE" as an identifier
                alias(token("TRILL"), $.identifier), // Treat "TRILL" as an identifier
                alias(token("CHORD"), $.identifier), // Treat "CHORD" as an identifier
            ),
        restEventId: ($) => alias(token("REST"), $.identifier), // Treat "NOTE" as an identifier

        pitchEvent: ($) => seq($.pitchEventId, choice($.pitches, $.pitch), $.duration),
        rest: ($) => seq($.restEventId, $.duration),

        // Pitch
        pitches: ($) => seq("(", repeat1($.pitch), ")"),
        pitch: ($) => choice($.noteName, $.midi),
        midi: (_) => token(/(0|[1-9][0-9]?|1[0-1][0-9]|12[0-7])/),
        noteName: ($) => seq($.pitchname, optional($.alteration), $.octave),

        // Pitch Atoms
        pitchname: (_) => /[A-Ga-g]/,
        alteration: (_) => choice("#", "b"),
        octave: (_) => /[0-9]|1[0-2]/,

        // Duration
        duration: ($) => $.number,

        // global
        number: (_) => choice(/[0-9]+/, /[0-9]+\.[0-9]+/),
        comment: (_) => token(choice(seq("//", /(\\+(.|\r?\n)|[^\\\n])*/), seq("/*", /[^*]*\*+([^/*][^*]*\*+)*/, "/"))),
    },
    extras: ($) => [/\s|\\\r?\n/, $.comment],
});
