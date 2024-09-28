module.exports = grammar({
  name: "score",
  rules: {
    source_file: ($) => repeat(choice($.EVENT, $.CONFIG, $.COMMENT)),

    //╭─────────────────────────────────────╮
    //│            Score Config             │
    //╰─────────────────────────────────────╯
    CONFIG: ($) => choice(seq("BPM", /\d+/)),
    // TODO: add score variance
    // TODO: add score variance

    //╭─────────────────────────────────────╮
    //│               Actions               │
    //╰─────────────────────────────────────╯
    ACTION: ($) =>
      choice(
        seq(
          "delay",
          /\d+/, // Definindo a ação como um atraso
        ),
        $.LUA,
      ),
    LUA: ($) => seq("exec lua", "{", /[^{}]+/, "}"),

    //╭─────────────────────────────────────╮
    //│               Events                │
    //╰─────────────────────────────────────╯
    EVENT: ($) => seq(choice($.NOTE), optional(repeat($.ACTION))),

    NOTE: ($) =>
      seq(
        "NOTE",
        $.pitch, // O primeiro token é o pitch
        $.duration, // O segundo token é a duração
      ),

    //╭─────────────────────────────────────╮
    //│              Comments               │
    //╰─────────────────────────────────────╯
    COMMENT: ($) => choice(seq("#", /.*/), seq(";", /.*/)),

    //╭─────────────────────────────────────╮
    //│             music atoms             │
    //╰─────────────────────────────────────╯
    pitch: ($) => choice(/[A-Ga-g][#b]?(\d)?/, /\d+/),
    duration: ($) => choice(/\d+/, /\d+\.\d+/, seq(/\d+/, "/", /\d+/)),
  },
});
