module.exports = grammar({
  name: "score",

  rules: {
    source_file: ($) => repeat(choice($.EVENT, $.CONFIG, $.COMMENT)),

    EVENT: ($) => seq(choice($.NOTE), optional(repeat($.ACTION))),

    ACTION: ($) =>
      choice(
        seq(
          "delay",
          /\d+/, // Definindo a ação como um atraso
        ),
        $.LUA,
      ),

    LUA: ($) => seq("exec lua", "{", /[^{}]+/, "}"),
    CONFIG: ($) => choice(seq("BPM", /\d+/)),

    // Definição de eventos de sintaxe
    NOTE: ($) =>
      seq(
        "NOTE",
        $.pitch, // O primeiro token é o pitch
        $.duration, // O segundo token é a duração
      ),

    COMMENT: ($) => choice(seq("#", /.*/), seq(";", /.*/)),

    // Definir código Lua dentro de {}

    // Tokens especiais
    pitch: ($) => choice(/[A-Ga-g][#b]?(\d)?/, /\d+/),

    // Tokens permitidos, duração pode ser 1/3
    duration: ($) => choice(/\d+/, seq(/\d+/, "/", /\d+/)),
  },
});
