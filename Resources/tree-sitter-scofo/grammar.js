module.exports = grammar({
    name: "scofo",
    precedence: "left",
    rules: {
        score: ($) => repeat($._statement),
        _statement: ($) => choice($.CONFIG, $.EVENT, $.LUA),
        keyword: (_) => /[a-zA-Z_][a-zA-Z0-9_]*/,

        //╭─────────────────────────────────────╮
        //│                 LUA                 │
        //╰─────────────────────────────────────╯
        LUA: ($) =>
            seq(alias(token("LUA"), $.identifier), "{", optional($.lua_body), "}"),
        lua_body: ($) =>
            repeat1(
                choice(/[^{}`]+/, seq("{", optional($.lua_body), "}"), $.lua_comment),
            ),
        lua_call: ($) => repeat1(choice(/[^()`]+/, seq("(", optional($.lua_call), ")"))),

        lua_comment: (_) => /--[^\n]*/,

        //╭─────────────────────────────────────╮
        //│               Config                │
        //╰─────────────────────────────────────╯
        CONFIG: ($) => choice($.numberConfig),
        configId: ($) =>
            choice(
                alias(token("BPM"), $.keyword),
                alias(token("TRANSPOSE"), $.keyword),
                alias(token("ENTROPY"), $.keyword),
            ),
        numberConfig: ($) => seq($.configId, $.numberSet),
        numberSet: ($) => $.number,

        //╭─────────────────────────────────────╮
        //│               Events                │
        //╰─────────────────────────────────────╯
        EVENT: ($) => choice($.pitchEvent, $.restEvent, $.freeEvent),
        pitchEventId: ($) =>
            choice(
                alias(token("NOTE"), $.keyword),
                alias(token("TRILL"), $.keyword),
                alias(token("CHORD"), $.keyword),
            ),
        restEventId: ($) => seq(alias(token("REST"), $.keyword)),
        timeEventId: ($) => seq(alias(token("EVENT"), $.keyword)),

        pitchEvent: ($) =>
            seq($.pitchEventId, choice($.pitches, $.pitch), $.duration, repeat($.ACTION)),
        restEvent: ($) => seq($.restEventId, $.duration, repeat($.ACTION)),
        freeEvent: ($) => seq($.timeEventId, $.eventId, $.duration, repeat1($.ACTION)),

        //

        eventId: (_) => choice("timed", "internal"),

        // Pitch
        pitches: ($) => seq("(", repeat1($.pitch), ")"),
        pitch: ($) => choice($.noteName, $.midi),
        midi: (_) => token(/(0|[1-9][0-9]?|1[0-1][0-9]|12[0-7])/),
        noteName: ($) => seq($.pitchname, optional($.alteration), $.octave),

        // Pitch Atoms
        pitchname: (_) => /[A-Ga-g]/,
        alteration: (_) => choice("#", "b"),
        octave: (_) => /[0-9]|1[0-2]/,

        // duration
        duration: ($) => $.number,

        //╭─────────────────────────────────────╮
        //│               ACTIONS               │
        //╰─────────────────────────────────────╯
        ACTION: ($) =>
            seq(
                optional(alias(token("ACTION"), $.keyword)),
                optional($.timedAction),
                $.exec,
                repeat(seq(token(","), $.exec)),
            ),

        timedAction: ($) =>
            choice(
                seq(alias(token("delay"), $.actionKey), $.number, $.timeUnit),
                // seq(token("now")),
            ),

        actionKeyword: ($) => choice($.luafunction, $.keyword),

        exec: ($) =>
            choice(
                // seq(token("call("), $.identifier, ")"),
                seq(alias(token("send"), $.keyword), $.receiver),
                seq(
                    alias(token("sendto"), $.keyword),
                    $.receiver,
                    optional(seq("[", repeat($.pdargs), "]")),
                ),
                seq(alias(token("call"), $.keyword), "(", $.lua_call, ")"),
            ),

        pdargs: ($) => choice($.symbol, $.number),
        receiver: ($) => $.keyword,
        luafunction: ($) => $.keyword,
        actionKey: (_) => /[a-zA-Z][a-zA-Z0-9_]*/,

        //╭─────────────────────────────────────╮
        //│                ATOMS                │
        //╰─────────────────────────────────────╯

        // global
        number: (_) => choice(/[0-9]+/, /[0-9]+\.[0-9]+/),
        symbol: (_) => /[a-zA-Z][a-zA-Z0-9_]*/,

        comment: (_) =>
            token(
                choice(
                    seq("//", /(\\+(.|\r?\n)|[^\\\n])*/),
                    seq("/*", /[^*]*\*+([^/*][^*]*\*+)*/, "/"),
                ),
            ),
        timeUnit: (_) => choice("tempo", "s", "ms", "us", "ns"),
    },
    extras: ($) => [/\s|\\\r?\n/, $.comment],
});
