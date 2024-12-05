module.exports = grammar({
  name: "score",
  rules: {
    source_file: ($) => repeat(choice($.EVENT, $.CONFIG, $.COMMENT)),

    // config keys
    CONFIG: ($) => choice($.BPM),

    BPM: ($) => seq("BPM", choice($.float, $.integer)),

    // Comments
    COMMENT: () => choice(seq("#", /.*/), seq(";", /.*/)),

    // Events
    EVENT: ($) => choice($.NOTE, $.TRILL),
    NOTE: ($) => seq("NOTE", $.pitch, $.duration),
    TRILL: ($) => seq("TRILL", $.pitches, $.duration),
    TYPE: () => choice("NOTE", "TRILL"),

    // Pitch
    pitches: ($) =>
      seq(
        $.open_parenthesis,
        $.pitch,
        repeat(seq(" ", $.pitch)),
        $.close_parenthesis,
      ),
    pitch: ($) => choice($.pitchname, $.midi),
    pitchname: ($) => seq($.pitchclass, optional($.alteration), $.octave),
    midi: () => /([0-9]|[1-9][0-9]|1[01][0-9]|12[0-7])/,
    pitchclass: () => /[A-Ga-g]/,
    alteration: () => choice("#", "b", "##", "bb"),
    octave: () => /[0-9]/,

    // Duration
    duration: ($) =>
      choice(
        $.float, // Matches float durations (e.g., 1.5, 0.25)
        $.integer, // Matches integer durations (e.g., 1, 2)
      ),
    float: () => /\d+\.\d+/, // Matches float numbers (e.g., 1.5, 0.25)
    integer: () => /\d+/, // Matches integer numbers (e.g., 1, 2)

    // Tokens
    open_parenthesis: () => "(",
    close_parenthesis: () => ")",
  },
});
