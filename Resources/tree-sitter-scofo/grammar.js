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
        lua_call: ($) =>
            field(
                "lua_call",
                repeat1(choice(/[^()`]+/, seq("(", optional($.lua_call), ")"))),
            ),
        lua_function: ($) => $.keyword,
        lua_comment: (_) => /--[^\n]*/,

        //╭─────────────────────────────────────╮
        //│               Config                │
        //╰─────────────────────────────────────╯
        CONFIG: ($) => choice($.numberConfig),
        configId: ($) =>
            field(
                "configId",
                choice(
                    // Time Configuration
                    alias(token("BPM"), $.keyword),
                    alias(token("PhaseCoupling"), $.keyword),
                    alias(token("SyncStrength"), $.keyword),

                    // Score
                    alias(token("TRANSPOSE"), $.keyword),

                    // Listening module
                    alias(choice(token("ENTROPY"), token("Entropy")), $.keyword),
                    alias(token("PitchSigma"), $.keyword),

                    // Audio
                    alias(token("FFTSize"), $.keyword),
                    alias(token("HopSize"), $.keyword),
                ),
            ),
        numberConfig: ($) => seq($.configId, $.numberSet),
        numberSet: ($) => $.number,

        //╭─────────────────────────────────────╮
        //│               Events                │
        //╰─────────────────────────────────────╯
        EVENT: ($) => choice($.pitchEvent, $.restEvent, $.freeEvent),
        pitchEventId: ($) =>
            field(
                "pitchEventId",
                choice(
                    alias(token("NOTE"), $.keyword),
                    alias(token("TRILL"), $.keyword),
                    alias(token("CHORD"), $.keyword),
                ),
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
                optional(field("timedAction", $.timedAction)),
                field("exec", $.exec),
                repeat(seq(token(","), $.exec)),
            ),

        timedAction: ($) =>
            choice(
                seq(
                    field("actionKey", token("delay")),
                    field("value", $.number),
                    field("timeUnit", $.timeUnit),
                ),
            ),

        actionKeyword: ($) => choice($.lua_function, $.keyword),

        exec: ($) =>
            choice(
                seq(
                    field("keyword", token("sendto")),
                    field("receiver", $.receiver),
                    optional(field("pdargs", $.pdargs)),
                ),
                seq(
                    field("keyword", token("luacall")),
                    field("luabody", seq("(", $.lua_call, ")")),
                ),
            ),

        pdargs: ($) => seq("[", repeat1($.pdarg), "]"),
        pdarg: ($) => field("pdarg", choice($.symbol, $.number)),
        receiver: ($) => $.keyword,
        actionKey: (_) => /[a-zA-Z][a-zA-Z0-9_]*/,

        //╭─────────────────────────────────────╮
        //│                ATOMS                │
        //╰─────────────────────────────────────╯
        number: (_) => choice(/-?[0-9]+/, /-?[0-9]+\.[0-9]+/),
        symbol: (_) => /[a-zA-Z][a-zA-Z0-9_]*/,

        comment: (_) =>
            token(
                choice(
                    seq("//", /(\\+(.|\r?\n)|[^\\\n])*/),
                    seq("/*", /[^*]*\*+([^/*][^*]*\*+)*/, "/"),
                ),
            ),
        timeUnit: (_) => field("timeUnit", choice("tempo", "sec", "ms")),
    },
    extras: ($) => [/\s|\\\r?\n/, $.comment],
});
