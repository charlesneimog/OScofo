#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 27
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 26
#define ALIAS_COUNT 0
#define TOKEN_COUNT 15
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 4
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  anon_sym_BPM = 1,
  aux_sym_CONFIG_token1 = 2,
  anon_sym_delay = 3,
  anon_sym_execlua = 4,
  anon_sym_LBRACE = 5,
  aux_sym_LUA_token1 = 6,
  anon_sym_RBRACE = 7,
  anon_sym_NOTE = 8,
  anon_sym_POUND = 9,
  aux_sym_COMMENT_token1 = 10,
  anon_sym_SEMI = 11,
  aux_sym_pitch_token1 = 12,
  aux_sym_duration_token1 = 13,
  anon_sym_SLASH = 14,
  sym_source_file = 15,
  sym_CONFIG = 16,
  sym_ACTION = 17,
  sym_LUA = 18,
  sym_EVENT = 19,
  sym_NOTE = 20,
  sym_COMMENT = 21,
  sym_pitch = 22,
  sym_duration = 23,
  aux_sym_source_file_repeat1 = 24,
  aux_sym_EVENT_repeat1 = 25,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_BPM] = "BPM",
  [aux_sym_CONFIG_token1] = "CONFIG_token1",
  [anon_sym_delay] = "delay",
  [anon_sym_execlua] = "exec lua",
  [anon_sym_LBRACE] = "{",
  [aux_sym_LUA_token1] = "LUA_token1",
  [anon_sym_RBRACE] = "}",
  [anon_sym_NOTE] = "NOTE",
  [anon_sym_POUND] = "#",
  [aux_sym_COMMENT_token1] = "COMMENT_token1",
  [anon_sym_SEMI] = ";",
  [aux_sym_pitch_token1] = "pitch_token1",
  [aux_sym_duration_token1] = "duration_token1",
  [anon_sym_SLASH] = "/",
  [sym_source_file] = "source_file",
  [sym_CONFIG] = "CONFIG",
  [sym_ACTION] = "ACTION",
  [sym_LUA] = "LUA",
  [sym_EVENT] = "EVENT",
  [sym_NOTE] = "NOTE",
  [sym_COMMENT] = "COMMENT",
  [sym_pitch] = "pitch",
  [sym_duration] = "duration",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_EVENT_repeat1] = "EVENT_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_BPM] = anon_sym_BPM,
  [aux_sym_CONFIG_token1] = aux_sym_CONFIG_token1,
  [anon_sym_delay] = anon_sym_delay,
  [anon_sym_execlua] = anon_sym_execlua,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [aux_sym_LUA_token1] = aux_sym_LUA_token1,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_NOTE] = anon_sym_NOTE,
  [anon_sym_POUND] = anon_sym_POUND,
  [aux_sym_COMMENT_token1] = aux_sym_COMMENT_token1,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [aux_sym_pitch_token1] = aux_sym_pitch_token1,
  [aux_sym_duration_token1] = aux_sym_duration_token1,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [sym_source_file] = sym_source_file,
  [sym_CONFIG] = sym_CONFIG,
  [sym_ACTION] = sym_ACTION,
  [sym_LUA] = sym_LUA,
  [sym_EVENT] = sym_EVENT,
  [sym_NOTE] = sym_NOTE,
  [sym_COMMENT] = sym_COMMENT,
  [sym_pitch] = sym_pitch,
  [sym_duration] = sym_duration,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_EVENT_repeat1] = aux_sym_EVENT_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_BPM] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_CONFIG_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_delay] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_execlua] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_LUA_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_NOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_POUND] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_COMMENT_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_pitch_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_duration_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_CONFIG] = {
    .visible = true,
    .named = true,
  },
  [sym_ACTION] = {
    .visible = true,
    .named = true,
  },
  [sym_LUA] = {
    .visible = true,
    .named = true,
  },
  [sym_EVENT] = {
    .visible = true,
    .named = true,
  },
  [sym_NOTE] = {
    .visible = true,
    .named = true,
  },
  [sym_COMMENT] = {
    .visible = true,
    .named = true,
  },
  [sym_pitch] = {
    .visible = true,
    .named = true,
  },
  [sym_duration] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_EVENT_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(21);
      ADVANCE_MAP(
        '#', 32,
        '/', 43,
        ';', 35,
        'B', 37,
        'N', 4,
        'd', 38,
        'e', 39,
        '{', 27,
        '}', 30,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(23);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(40);
      END_STATE();
    case 1:
      if (lookahead == ' ') ADVANCE(13);
      END_STATE();
    case 2:
      if (lookahead == 'E') ADVANCE(31);
      END_STATE();
    case 3:
      if (lookahead == 'M') ADVANCE(22);
      END_STATE();
    case 4:
      if (lookahead == 'O') ADVANCE(6);
      END_STATE();
    case 5:
      if (lookahead == 'P') ADVANCE(3);
      END_STATE();
    case 6:
      if (lookahead == 'T') ADVANCE(2);
      END_STATE();
    case 7:
      if (lookahead == 'a') ADVANCE(16);
      END_STATE();
    case 8:
      if (lookahead == 'a') ADVANCE(26);
      END_STATE();
    case 9:
      if (lookahead == 'c') ADVANCE(1);
      END_STATE();
    case 10:
      if (lookahead == 'e') ADVANCE(12);
      END_STATE();
    case 11:
      if (lookahead == 'e') ADVANCE(9);
      END_STATE();
    case 12:
      if (lookahead == 'l') ADVANCE(7);
      END_STATE();
    case 13:
      if (lookahead == 'l') ADVANCE(14);
      END_STATE();
    case 14:
      if (lookahead == 'u') ADVANCE(8);
      END_STATE();
    case 15:
      if (lookahead == 'x') ADVANCE(11);
      END_STATE();
    case 16:
      if (lookahead == 'y') ADVANCE(25);
      END_STATE();
    case 17:
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(17);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(24);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(40);
      END_STATE();
    case 18:
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(28);
      if (lookahead != 0 &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(29);
      END_STATE();
    case 19:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 20:
      if (eof) ADVANCE(21);
      if (lookahead == '#') ADVANCE(32);
      if (lookahead == '/') ADVANCE(43);
      if (lookahead == ';') ADVANCE(35);
      if (lookahead == 'B') ADVANCE(5);
      if (lookahead == 'N') ADVANCE(4);
      if (lookahead == 'd') ADVANCE(10);
      if (lookahead == 'e') ADVANCE(15);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(20);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(anon_sym_BPM);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(aux_sym_CONFIG_token1);
      if (lookahead == '.') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(23);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(aux_sym_CONFIG_token1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(24);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(anon_sym_delay);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(anon_sym_execlua);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(aux_sym_LUA_token1);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(28);
      if (lookahead != 0 &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(29);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(aux_sym_LUA_token1);
      if (lookahead != 0 &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(29);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_NOTE);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(aux_sym_COMMENT_token1);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(33);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead)) ADVANCE(34);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(aux_sym_COMMENT_token1);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(34);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(aux_sym_pitch_token1);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(aux_sym_pitch_token1);
      if (lookahead == 'P') ADVANCE(3);
      if (lookahead == '#' ||
          lookahead == 'b') ADVANCE(41);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(36);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(aux_sym_pitch_token1);
      if (lookahead == 'e') ADVANCE(12);
      if (lookahead == '#' ||
          lookahead == 'b') ADVANCE(41);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(36);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(aux_sym_pitch_token1);
      if (lookahead == 'x') ADVANCE(11);
      if (lookahead == '#' ||
          lookahead == 'b') ADVANCE(41);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(36);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(aux_sym_pitch_token1);
      if (lookahead == '#' ||
          lookahead == 'b') ADVANCE(41);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(36);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(aux_sym_pitch_token1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(36);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(aux_sym_duration_token1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 20},
  [2] = {.lex_state = 20},
  [3] = {.lex_state = 20},
  [4] = {.lex_state = 20},
  [5] = {.lex_state = 20},
  [6] = {.lex_state = 20},
  [7] = {.lex_state = 20},
  [8] = {.lex_state = 20},
  [9] = {.lex_state = 20},
  [10] = {.lex_state = 20},
  [11] = {.lex_state = 20},
  [12] = {.lex_state = 20},
  [13] = {.lex_state = 20},
  [14] = {.lex_state = 20},
  [15] = {.lex_state = 20},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 17},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 0},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 33},
  [24] = {.lex_state = 18},
  [25] = {.lex_state = 0},
  [26] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_BPM] = ACTIONS(1),
    [aux_sym_CONFIG_token1] = ACTIONS(1),
    [anon_sym_delay] = ACTIONS(1),
    [anon_sym_execlua] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_NOTE] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [aux_sym_pitch_token1] = ACTIONS(1),
    [aux_sym_duration_token1] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(22),
    [sym_CONFIG] = STATE(6),
    [sym_EVENT] = STATE(6),
    [sym_NOTE] = STATE(5),
    [sym_COMMENT] = STATE(6),
    [aux_sym_source_file_repeat1] = STATE(6),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_BPM] = ACTIONS(5),
    [anon_sym_NOTE] = ACTIONS(7),
    [anon_sym_POUND] = ACTIONS(9),
    [anon_sym_SEMI] = ACTIONS(9),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 5,
    ACTIONS(13), 1,
      anon_sym_delay,
    ACTIONS(15), 1,
      anon_sym_execlua,
    STATE(9), 1,
      sym_LUA,
    STATE(3), 2,
      sym_ACTION,
      aux_sym_EVENT_repeat1,
    ACTIONS(11), 5,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_NOTE,
      anon_sym_POUND,
      anon_sym_SEMI,
  [21] = 5,
    ACTIONS(19), 1,
      anon_sym_delay,
    ACTIONS(22), 1,
      anon_sym_execlua,
    STATE(9), 1,
      sym_LUA,
    STATE(3), 2,
      sym_ACTION,
      aux_sym_EVENT_repeat1,
    ACTIONS(17), 5,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_NOTE,
      anon_sym_POUND,
      anon_sym_SEMI,
  [42] = 6,
    ACTIONS(25), 1,
      ts_builtin_sym_end,
    ACTIONS(27), 1,
      anon_sym_BPM,
    ACTIONS(30), 1,
      anon_sym_NOTE,
    STATE(5), 1,
      sym_NOTE,
    ACTIONS(33), 2,
      anon_sym_POUND,
      anon_sym_SEMI,
    STATE(4), 4,
      sym_CONFIG,
      sym_EVENT,
      sym_COMMENT,
      aux_sym_source_file_repeat1,
  [65] = 5,
    ACTIONS(13), 1,
      anon_sym_delay,
    ACTIONS(15), 1,
      anon_sym_execlua,
    STATE(9), 1,
      sym_LUA,
    STATE(2), 2,
      sym_ACTION,
      aux_sym_EVENT_repeat1,
    ACTIONS(36), 5,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_NOTE,
      anon_sym_POUND,
      anon_sym_SEMI,
  [86] = 6,
    ACTIONS(5), 1,
      anon_sym_BPM,
    ACTIONS(7), 1,
      anon_sym_NOTE,
    ACTIONS(38), 1,
      ts_builtin_sym_end,
    STATE(5), 1,
      sym_NOTE,
    ACTIONS(9), 2,
      anon_sym_POUND,
      anon_sym_SEMI,
    STATE(4), 4,
      sym_CONFIG,
      sym_EVENT,
      sym_COMMENT,
      aux_sym_source_file_repeat1,
  [109] = 2,
    ACTIONS(42), 1,
      anon_sym_SLASH,
    ACTIONS(40), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_delay,
      anon_sym_execlua,
      anon_sym_NOTE,
      anon_sym_POUND,
      anon_sym_SEMI,
  [122] = 1,
    ACTIONS(40), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_delay,
      anon_sym_execlua,
      anon_sym_NOTE,
      anon_sym_POUND,
      anon_sym_SEMI,
  [132] = 1,
    ACTIONS(44), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_delay,
      anon_sym_execlua,
      anon_sym_NOTE,
      anon_sym_POUND,
      anon_sym_SEMI,
  [142] = 1,
    ACTIONS(46), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_delay,
      anon_sym_execlua,
      anon_sym_NOTE,
      anon_sym_POUND,
      anon_sym_SEMI,
  [152] = 1,
    ACTIONS(48), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_delay,
      anon_sym_execlua,
      anon_sym_NOTE,
      anon_sym_POUND,
      anon_sym_SEMI,
  [162] = 1,
    ACTIONS(50), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_delay,
      anon_sym_execlua,
      anon_sym_NOTE,
      anon_sym_POUND,
      anon_sym_SEMI,
  [172] = 1,
    ACTIONS(52), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_delay,
      anon_sym_execlua,
      anon_sym_NOTE,
      anon_sym_POUND,
      anon_sym_SEMI,
  [182] = 1,
    ACTIONS(54), 5,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_NOTE,
      anon_sym_POUND,
      anon_sym_SEMI,
  [190] = 1,
    ACTIONS(56), 5,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_NOTE,
      anon_sym_POUND,
      anon_sym_SEMI,
  [198] = 3,
    ACTIONS(58), 1,
      aux_sym_CONFIG_token1,
    ACTIONS(60), 1,
      aux_sym_duration_token1,
    STATE(10), 1,
      sym_duration,
  [208] = 2,
    STATE(16), 1,
      sym_pitch,
    ACTIONS(62), 2,
      aux_sym_CONFIG_token1,
      aux_sym_pitch_token1,
  [216] = 2,
    ACTIONS(64), 1,
      aux_sym_CONFIG_token1,
    ACTIONS(66), 1,
      aux_sym_duration_token1,
  [223] = 1,
    ACTIONS(68), 1,
      aux_sym_CONFIG_token1,
  [227] = 1,
    ACTIONS(70), 1,
      anon_sym_LBRACE,
  [231] = 1,
    ACTIONS(72), 1,
      aux_sym_CONFIG_token1,
  [235] = 1,
    ACTIONS(74), 1,
      ts_builtin_sym_end,
  [239] = 1,
    ACTIONS(76), 1,
      aux_sym_COMMENT_token1,
  [243] = 1,
    ACTIONS(78), 1,
      aux_sym_LUA_token1,
  [247] = 1,
    ACTIONS(80), 1,
      aux_sym_CONFIG_token1,
  [251] = 1,
    ACTIONS(82), 1,
      anon_sym_RBRACE,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 21,
  [SMALL_STATE(4)] = 42,
  [SMALL_STATE(5)] = 65,
  [SMALL_STATE(6)] = 86,
  [SMALL_STATE(7)] = 109,
  [SMALL_STATE(8)] = 122,
  [SMALL_STATE(9)] = 132,
  [SMALL_STATE(10)] = 142,
  [SMALL_STATE(11)] = 152,
  [SMALL_STATE(12)] = 162,
  [SMALL_STATE(13)] = 172,
  [SMALL_STATE(14)] = 182,
  [SMALL_STATE(15)] = 190,
  [SMALL_STATE(16)] = 198,
  [SMALL_STATE(17)] = 208,
  [SMALL_STATE(18)] = 216,
  [SMALL_STATE(19)] = 223,
  [SMALL_STATE(20)] = 227,
  [SMALL_STATE(21)] = 231,
  [SMALL_STATE(22)] = 235,
  [SMALL_STATE(23)] = 239,
  [SMALL_STATE(24)] = 243,
  [SMALL_STATE(25)] = 247,
  [SMALL_STATE(26)] = 251,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [11] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_EVENT, 2, 0, 0),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_EVENT_repeat1, 2, 0, 0),
  [19] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_EVENT_repeat1, 2, 0, 0), SHIFT_REPEAT(19),
  [22] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_EVENT_repeat1, 2, 0, 0), SHIFT_REPEAT(20),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [27] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(21),
  [30] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(17),
  [33] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(23),
  [36] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_EVENT, 1, 0, 0),
  [38] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [40] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_duration, 1, 0, 0),
  [42] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [44] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 1, 0, 0),
  [46] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_NOTE, 3, 0, 0),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 2, 0, 0),
  [50] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_duration, 3, 0, 0),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_LUA, 4, 0, 0),
  [54] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_COMMENT, 2, 0, 0),
  [56] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_CONFIG, 2, 0, 0),
  [58] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [60] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [62] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [64] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitch, 1, 0, 0),
  [66] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitch, 1, 0, 0),
  [68] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [70] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [72] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [74] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [78] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [80] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [82] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_score(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
