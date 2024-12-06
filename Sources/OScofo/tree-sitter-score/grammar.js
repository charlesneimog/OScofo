module.exports = grammar({
  name: "score",
  rules: {
    source_file: ($) => repeat(choice($.EVENT, $.CONFIG, $.COMMENT)),

    // Things
    CONFIG: ($) => choice($.BPM),
    BPM: ($) => seq("BPM", choice($.float, $.integer)),
    COMMENT: () => choice(seq("#", /.*/), seq(";", /.*/)),
    EVENT: ($) => choice($.NOTE, $.TRILL, $.REST),

    // Events
    NOTE: ($) => seq("NOTE", $.pitch, $.duration),
    TRILL: ($) => seq("TRILL", $.pitches, $.duration),
    REST: ($) => seq("REST", $.duration),

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
