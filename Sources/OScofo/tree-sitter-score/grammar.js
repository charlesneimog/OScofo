module.exports = grammar({
  name: "score",
  rules: {
    source_file: ($) => repeat(choice($.EVENT, $.CONFIG, $.COMMENT)),

    // Things
    CONFIG: ($) =>
      choice(
        seq("BPM", choice($.float, $.integer)),
        seq("TRANSPOSE", choice($.float, $.integer)),
      ),

    // Comments
    COMMENT: () => choice(seq("#", /.*/), seq(";", /.*/), seq("//", /.*/)),

    // Events
    EVENT: ($) => choice($.NOTE, $.TRILL, $.REST),

    NOTE: ($) =>
      seq(
        "NOTE",
        $.pitch,
        $.duration,
        optional(repeat($.ACTION)),
        optional($.COMMENT),
      ),
    TRILL: ($) =>
      seq(
        "TRILL",
        $.pitches,
        $.duration,
        optional(repeat($.ACTION)),
        optional($.COMMENT),
      ),
    REST: ($) =>
      seq("REST", $.duration, optional(repeat($.ACTION)), optional($.COMMENT)),

    // Actions
    ACTION: ($) =>
      seq(choice($.two_spaces, $.four_spaces, $.tab), choice($.delay)),

    delay: ($) => seq("delay", $.integer),

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
    alteration: () => choice("#", "b"),
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

    two_spaces: () => "  ", // Match exactly two spaces
    four_spaces: () => "    ", // Match exactly four spaces
    tab: () => "\t", // Match tabs
  },
  extras: ($) => [
    /\s|\\\r?\n/, // Espaços em branco e quebras de linha
    $.COMMENT, // Comentários
  ],
});
