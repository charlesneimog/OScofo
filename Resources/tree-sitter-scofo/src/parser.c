#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 35
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 39
#define ALIAS_COUNT 0
#define TOKEN_COUNT 20
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 3
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  anon_sym_LUA = 1,
  anon_sym_LBRACE = 2,
  anon_sym_RBRACE = 3,
  anon_sym_BPM = 4,
  anon_sym_TRANSPOSE = 5,
  anon_sym_NOTE = 6,
  anon_sym_TRILL = 7,
  anon_sym_CHORD = 8,
  anon_sym_REST = 9,
  anon_sym_LPAREN = 10,
  anon_sym_RPAREN = 11,
  sym_midi = 12,
  sym_pitchname = 13,
  anon_sym_POUND = 14,
  anon_sym_b = 15,
  sym_octave = 16,
  aux_sym_number_token1 = 17,
  aux_sym_number_token2 = 18,
  sym_comment = 19,
  sym_score = 20,
  sym__statement = 21,
  sym_EVENT = 22,
  sym_CONFIG = 23,
  sym_configId = 24,
  sym_numberConfig = 25,
  sym_numberSet = 26,
  sym_pitchEventId = 27,
  sym_restEventId = 28,
  sym_pitchEvent = 29,
  sym_rest = 30,
  sym_pitches = 31,
  sym_pitch = 32,
  sym_noteName = 33,
  sym_alteration = 34,
  sym_duration = 35,
  sym_number = 36,
  aux_sym_score_repeat1 = 37,
  aux_sym_pitches_repeat1 = 38,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_LUA] = "LUA",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_BPM] = "identifier",
  [anon_sym_TRANSPOSE] = "identifier",
  [anon_sym_NOTE] = "identifier",
  [anon_sym_TRILL] = "identifier",
  [anon_sym_CHORD] = "identifier",
  [anon_sym_REST] = "identifier",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_midi] = "midi",
  [sym_pitchname] = "pitchname",
  [anon_sym_POUND] = "#",
  [anon_sym_b] = "b",
  [sym_octave] = "octave",
  [aux_sym_number_token1] = "number_token1",
  [aux_sym_number_token2] = "number_token2",
  [sym_comment] = "comment",
  [sym_score] = "score",
  [sym__statement] = "_statement",
  [sym_EVENT] = "EVENT",
  [sym_CONFIG] = "CONFIG",
  [sym_configId] = "configId",
  [sym_numberConfig] = "numberConfig",
  [sym_numberSet] = "numberSet",
  [sym_pitchEventId] = "pitchEventId",
  [sym_restEventId] = "restEventId",
  [sym_pitchEvent] = "pitchEvent",
  [sym_rest] = "rest",
  [sym_pitches] = "pitches",
  [sym_pitch] = "pitch",
  [sym_noteName] = "noteName",
  [sym_alteration] = "alteration",
  [sym_duration] = "duration",
  [sym_number] = "number",
  [aux_sym_score_repeat1] = "score_repeat1",
  [aux_sym_pitches_repeat1] = "pitches_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_LUA] = anon_sym_LUA,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_BPM] = anon_sym_BPM,
  [anon_sym_TRANSPOSE] = anon_sym_BPM,
  [anon_sym_NOTE] = anon_sym_BPM,
  [anon_sym_TRILL] = anon_sym_BPM,
  [anon_sym_CHORD] = anon_sym_BPM,
  [anon_sym_REST] = anon_sym_BPM,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_midi] = sym_midi,
  [sym_pitchname] = sym_pitchname,
  [anon_sym_POUND] = anon_sym_POUND,
  [anon_sym_b] = anon_sym_b,
  [sym_octave] = sym_octave,
  [aux_sym_number_token1] = aux_sym_number_token1,
  [aux_sym_number_token2] = aux_sym_number_token2,
  [sym_comment] = sym_comment,
  [sym_score] = sym_score,
  [sym__statement] = sym__statement,
  [sym_EVENT] = sym_EVENT,
  [sym_CONFIG] = sym_CONFIG,
  [sym_configId] = sym_configId,
  [sym_numberConfig] = sym_numberConfig,
  [sym_numberSet] = sym_numberSet,
  [sym_pitchEventId] = sym_pitchEventId,
  [sym_restEventId] = sym_restEventId,
  [sym_pitchEvent] = sym_pitchEvent,
  [sym_rest] = sym_rest,
  [sym_pitches] = sym_pitches,
  [sym_pitch] = sym_pitch,
  [sym_noteName] = sym_noteName,
  [sym_alteration] = sym_alteration,
  [sym_duration] = sym_duration,
  [sym_number] = sym_number,
  [aux_sym_score_repeat1] = aux_sym_score_repeat1,
  [aux_sym_pitches_repeat1] = aux_sym_pitches_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_LUA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BPM] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_TRANSPOSE] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_NOTE] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_TRILL] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_CHORD] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_REST] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [sym_midi] = {
    .visible = true,
    .named = true,
  },
  [sym_pitchname] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_POUND] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_b] = {
    .visible = true,
    .named = false,
  },
  [sym_octave] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_number_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_number_token2] = {
    .visible = false,
    .named = false,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_score] = {
    .visible = true,
    .named = true,
  },
  [sym__statement] = {
    .visible = false,
    .named = true,
  },
  [sym_EVENT] = {
    .visible = true,
    .named = true,
  },
  [sym_CONFIG] = {
    .visible = true,
    .named = true,
  },
  [sym_configId] = {
    .visible = true,
    .named = true,
  },
  [sym_numberConfig] = {
    .visible = true,
    .named = true,
  },
  [sym_numberSet] = {
    .visible = true,
    .named = true,
  },
  [sym_pitchEventId] = {
    .visible = true,
    .named = true,
  },
  [sym_restEventId] = {
    .visible = true,
    .named = true,
  },
  [sym_pitchEvent] = {
    .visible = true,
    .named = true,
  },
  [sym_rest] = {
    .visible = true,
    .named = true,
  },
  [sym_pitches] = {
    .visible = true,
    .named = true,
  },
  [sym_pitch] = {
    .visible = true,
    .named = true,
  },
  [sym_noteName] = {
    .visible = true,
    .named = true,
  },
  [sym_alteration] = {
    .visible = true,
    .named = true,
  },
  [sym_duration] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_score_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_pitches_repeat1] = {
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
  [19] = 17,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 21,
  [26] = 26,
  [27] = 22,
  [28] = 23,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 32,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(41);
      ADVANCE_MAP(
        '#', 60,
        '(', 51,
        ')', 52,
        '/', 8,
        '0', 53,
        '1', 54,
        'B', 59,
        'C', 58,
        'L', 34,
        'N', 22,
        'R', 14,
        'T', 27,
      );
      if (lookahead == '\\') SKIP(37);
      if (lookahead == 'b') ADVANCE(61);
      if (lookahead == '{') ADVANCE(43);
      if (lookahead == '}') ADVANCE(44);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(56);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(57);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(7);
      END_STATE();
    case 2:
      if (lookahead == '\n') SKIP(7);
      if (lookahead == '\r') SKIP(1);
      END_STATE();
    case 3:
      if (lookahead == '\n') SKIP(6);
      END_STATE();
    case 4:
      if (lookahead == '\n') SKIP(6);
      if (lookahead == '\r') SKIP(3);
      END_STATE();
    case 5:
      if (lookahead == '\r') ADVANCE(69);
      if (lookahead == '\\') ADVANCE(67);
      if (lookahead != 0) ADVANCE(68);
      END_STATE();
    case 6:
      if (lookahead == '#') ADVANCE(60);
      if (lookahead == '/') ADVANCE(8);
      if (lookahead == '1') ADVANCE(63);
      if (lookahead == '\\') SKIP(4);
      if (lookahead == 'b') ADVANCE(61);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(6);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(62);
      END_STATE();
    case 7:
      if (lookahead == '(') ADVANCE(51);
      if (lookahead == ')') ADVANCE(52);
      if (lookahead == '/') ADVANCE(8);
      if (lookahead == '0') ADVANCE(53);
      if (lookahead == '1') ADVANCE(54);
      if (lookahead == '\\') SKIP(2);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(7);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(56);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(57);
      END_STATE();
    case 8:
      if (lookahead == '*') ADVANCE(10);
      if (lookahead == '/') ADVANCE(68);
      END_STATE();
    case 9:
      if (lookahead == '*') ADVANCE(9);
      if (lookahead == '/') ADVANCE(66);
      if (lookahead != 0) ADVANCE(10);
      END_STATE();
    case 10:
      if (lookahead == '*') ADVANCE(9);
      if (lookahead != 0) ADVANCE(10);
      END_STATE();
    case 11:
      if (lookahead == 'A') ADVANCE(42);
      END_STATE();
    case 12:
      if (lookahead == 'A') ADVANCE(21);
      if (lookahead == 'I') ADVANCE(19);
      END_STATE();
    case 13:
      if (lookahead == 'D') ADVANCE(49);
      END_STATE();
    case 14:
      if (lookahead == 'E') ADVANCE(30);
      END_STATE();
    case 15:
      if (lookahead == 'E') ADVANCE(47);
      END_STATE();
    case 16:
      if (lookahead == 'E') ADVANCE(46);
      END_STATE();
    case 17:
      if (lookahead == 'H') ADVANCE(23);
      END_STATE();
    case 18:
      if (lookahead == 'L') ADVANCE(48);
      END_STATE();
    case 19:
      if (lookahead == 'L') ADVANCE(18);
      END_STATE();
    case 20:
      if (lookahead == 'M') ADVANCE(45);
      END_STATE();
    case 21:
      if (lookahead == 'N') ADVANCE(29);
      END_STATE();
    case 22:
      if (lookahead == 'O') ADVANCE(33);
      END_STATE();
    case 23:
      if (lookahead == 'O') ADVANCE(28);
      END_STATE();
    case 24:
      if (lookahead == 'O') ADVANCE(31);
      END_STATE();
    case 25:
      if (lookahead == 'P') ADVANCE(20);
      END_STATE();
    case 26:
      if (lookahead == 'P') ADVANCE(24);
      END_STATE();
    case 27:
      if (lookahead == 'R') ADVANCE(12);
      END_STATE();
    case 28:
      if (lookahead == 'R') ADVANCE(13);
      END_STATE();
    case 29:
      if (lookahead == 'S') ADVANCE(26);
      END_STATE();
    case 30:
      if (lookahead == 'S') ADVANCE(32);
      END_STATE();
    case 31:
      if (lookahead == 'S') ADVANCE(16);
      END_STATE();
    case 32:
      if (lookahead == 'T') ADVANCE(50);
      END_STATE();
    case 33:
      if (lookahead == 'T') ADVANCE(15);
      END_STATE();
    case 34:
      if (lookahead == 'U') ADVANCE(11);
      END_STATE();
    case 35:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(65);
      END_STATE();
    case 36:
      if (eof) ADVANCE(41);
      if (lookahead == '\n') SKIP(0);
      END_STATE();
    case 37:
      if (eof) ADVANCE(41);
      if (lookahead == '\n') SKIP(0);
      if (lookahead == '\r') SKIP(36);
      END_STATE();
    case 38:
      if (eof) ADVANCE(41);
      if (lookahead == '\n') SKIP(40);
      END_STATE();
    case 39:
      if (eof) ADVANCE(41);
      if (lookahead == '\n') SKIP(40);
      if (lookahead == '\r') SKIP(38);
      END_STATE();
    case 40:
      if (eof) ADVANCE(41);
      if (lookahead == '/') ADVANCE(8);
      if (lookahead == 'B') ADVANCE(25);
      if (lookahead == 'C') ADVANCE(17);
      if (lookahead == 'N') ADVANCE(22);
      if (lookahead == 'R') ADVANCE(14);
      if (lookahead == 'T') ADVANCE(27);
      if (lookahead == '\\') SKIP(39);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(40);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(64);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_LUA);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_BPM);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(anon_sym_TRANSPOSE);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_NOTE);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(anon_sym_TRILL);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(anon_sym_CHORD);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(anon_sym_REST);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(sym_midi);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(sym_midi);
      if (lookahead == '2') ADVANCE(55);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(56);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(53);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(53);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(53);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_pitchname);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'H') ADVANCE(23);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'P') ADVANCE(20);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_b);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_octave);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_octave);
      if (('0' <= lookahead && lookahead <= '2')) ADVANCE(62);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(35);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(64);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(aux_sym_number_token2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(65);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\r') ADVANCE(69);
      if (lookahead == '\\') ADVANCE(67);
      if (lookahead != 0) ADVANCE(68);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(5);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(68);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(5);
      if (lookahead != 0) ADVANCE(68);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 40},
  [2] = {.lex_state = 40},
  [3] = {.lex_state = 40},
  [4] = {.lex_state = 40},
  [5] = {.lex_state = 40},
  [6] = {.lex_state = 40},
  [7] = {.lex_state = 40},
  [8] = {.lex_state = 40},
  [9] = {.lex_state = 40},
  [10] = {.lex_state = 40},
  [11] = {.lex_state = 40},
  [12] = {.lex_state = 7},
  [13] = {.lex_state = 7},
  [14] = {.lex_state = 7},
  [15] = {.lex_state = 7},
  [16] = {.lex_state = 40},
  [17] = {.lex_state = 6},
  [18] = {.lex_state = 40},
  [19] = {.lex_state = 6},
  [20] = {.lex_state = 40},
  [21] = {.lex_state = 7},
  [22] = {.lex_state = 7},
  [23] = {.lex_state = 7},
  [24] = {.lex_state = 7},
  [25] = {.lex_state = 40},
  [26] = {.lex_state = 40},
  [27] = {.lex_state = 40},
  [28] = {.lex_state = 40},
  [29] = {.lex_state = 40},
  [30] = {.lex_state = 40},
  [31] = {.lex_state = 6},
  [32] = {.lex_state = 6},
  [33] = {.lex_state = 0},
  [34] = {.lex_state = 6},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_LUA] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_BPM] = ACTIONS(1),
    [anon_sym_TRANSPOSE] = ACTIONS(1),
    [anon_sym_NOTE] = ACTIONS(1),
    [anon_sym_TRILL] = ACTIONS(1),
    [anon_sym_CHORD] = ACTIONS(1),
    [anon_sym_REST] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym_midi] = ACTIONS(1),
    [sym_pitchname] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [anon_sym_b] = ACTIONS(1),
    [sym_octave] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_score] = STATE(33),
    [sym__statement] = STATE(3),
    [sym_EVENT] = STATE(3),
    [sym_CONFIG] = STATE(3),
    [sym_configId] = STATE(16),
    [sym_numberConfig] = STATE(6),
    [sym_pitchEventId] = STATE(14),
    [sym_restEventId] = STATE(20),
    [sym_pitchEvent] = STATE(8),
    [sym_rest] = STATE(8),
    [aux_sym_score_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_BPM] = ACTIONS(7),
    [anon_sym_TRANSPOSE] = ACTIONS(7),
    [anon_sym_NOTE] = ACTIONS(9),
    [anon_sym_TRILL] = ACTIONS(9),
    [anon_sym_CHORD] = ACTIONS(9),
    [anon_sym_REST] = ACTIONS(11),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      ts_builtin_sym_end,
    ACTIONS(21), 1,
      anon_sym_REST,
    STATE(6), 1,
      sym_numberConfig,
    STATE(14), 1,
      sym_pitchEventId,
    STATE(16), 1,
      sym_configId,
    STATE(20), 1,
      sym_restEventId,
    ACTIONS(15), 2,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
    STATE(8), 2,
      sym_pitchEvent,
      sym_rest,
    ACTIONS(18), 3,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
    STATE(2), 4,
      sym__statement,
      sym_EVENT,
      sym_CONFIG,
      aux_sym_score_repeat1,
  [41] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_REST,
    ACTIONS(24), 1,
      ts_builtin_sym_end,
    STATE(6), 1,
      sym_numberConfig,
    STATE(14), 1,
      sym_pitchEventId,
    STATE(16), 1,
      sym_configId,
    STATE(20), 1,
      sym_restEventId,
    ACTIONS(7), 2,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
    STATE(8), 2,
      sym_pitchEvent,
      sym_rest,
    ACTIONS(9), 3,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
    STATE(2), 4,
      sym__statement,
      sym_EVENT,
      sym_CONFIG,
      aux_sym_score_repeat1,
  [82] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(26), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [95] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(28), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [108] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(30), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [121] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(32), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [134] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(34), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [147] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(36), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [160] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [173] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(40), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [186] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(42), 1,
      anon_sym_RPAREN,
    ACTIONS(44), 1,
      sym_midi,
    ACTIONS(47), 1,
      sym_pitchname,
    STATE(21), 1,
      sym_noteName,
    STATE(12), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [206] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(50), 1,
      anon_sym_RPAREN,
    ACTIONS(52), 1,
      sym_midi,
    ACTIONS(54), 1,
      sym_pitchname,
    STATE(21), 1,
      sym_noteName,
    STATE(12), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [226] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(56), 1,
      anon_sym_LPAREN,
    ACTIONS(58), 1,
      sym_midi,
    ACTIONS(60), 1,
      sym_pitchname,
    STATE(25), 1,
      sym_noteName,
    STATE(18), 2,
      sym_pitches,
      sym_pitch,
  [246] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(52), 1,
      sym_midi,
    ACTIONS(54), 1,
      sym_pitchname,
    STATE(21), 1,
      sym_noteName,
    STATE(13), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [263] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(62), 1,
      aux_sym_number_token1,
    ACTIONS(64), 1,
      aux_sym_number_token2,
    STATE(10), 1,
      sym_numberSet,
    STATE(11), 1,
      sym_number,
  [279] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(68), 1,
      sym_octave,
    STATE(32), 1,
      sym_alteration,
    ACTIONS(66), 2,
      anon_sym_POUND,
      anon_sym_b,
  [293] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(62), 1,
      aux_sym_number_token1,
    ACTIONS(64), 1,
      aux_sym_number_token2,
    STATE(4), 1,
      sym_duration,
    STATE(5), 1,
      sym_number,
  [309] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      sym_octave,
    STATE(34), 1,
      sym_alteration,
    ACTIONS(66), 2,
      anon_sym_POUND,
      anon_sym_b,
  [323] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(62), 1,
      aux_sym_number_token1,
    ACTIONS(64), 1,
      aux_sym_number_token2,
    STATE(5), 1,
      sym_number,
    STATE(7), 1,
      sym_duration,
  [339] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(72), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [348] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [357] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(76), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [366] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(78), 3,
      anon_sym_LPAREN,
      sym_midi,
      sym_pitchname,
  [375] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(72), 1,
      aux_sym_number_token2,
    ACTIONS(80), 1,
      aux_sym_number_token1,
  [385] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(82), 1,
      aux_sym_number_token1,
    ACTIONS(84), 1,
      aux_sym_number_token2,
  [395] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 1,
      aux_sym_number_token2,
    ACTIONS(86), 1,
      aux_sym_number_token1,
  [405] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(76), 1,
      aux_sym_number_token2,
    ACTIONS(88), 1,
      aux_sym_number_token1,
  [415] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(90), 1,
      aux_sym_number_token1,
    ACTIONS(92), 1,
      aux_sym_number_token2,
  [425] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(94), 1,
      aux_sym_number_token1,
    ACTIONS(96), 1,
      aux_sym_number_token2,
  [435] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(98), 1,
      sym_octave,
  [442] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(100), 1,
      sym_octave,
  [449] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      ts_builtin_sym_end,
  [456] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(104), 1,
      sym_octave,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 41,
  [SMALL_STATE(4)] = 82,
  [SMALL_STATE(5)] = 95,
  [SMALL_STATE(6)] = 108,
  [SMALL_STATE(7)] = 121,
  [SMALL_STATE(8)] = 134,
  [SMALL_STATE(9)] = 147,
  [SMALL_STATE(10)] = 160,
  [SMALL_STATE(11)] = 173,
  [SMALL_STATE(12)] = 186,
  [SMALL_STATE(13)] = 206,
  [SMALL_STATE(14)] = 226,
  [SMALL_STATE(15)] = 246,
  [SMALL_STATE(16)] = 263,
  [SMALL_STATE(17)] = 279,
  [SMALL_STATE(18)] = 293,
  [SMALL_STATE(19)] = 309,
  [SMALL_STATE(20)] = 323,
  [SMALL_STATE(21)] = 339,
  [SMALL_STATE(22)] = 348,
  [SMALL_STATE(23)] = 357,
  [SMALL_STATE(24)] = 366,
  [SMALL_STATE(25)] = 375,
  [SMALL_STATE(26)] = 385,
  [SMALL_STATE(27)] = 395,
  [SMALL_STATE(28)] = 405,
  [SMALL_STATE(29)] = 415,
  [SMALL_STATE(30)] = 425,
  [SMALL_STATE(31)] = 435,
  [SMALL_STATE(32)] = 442,
  [SMALL_STATE(33)] = 449,
  [SMALL_STATE(34)] = 456,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_score, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0),
  [15] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(29),
  [18] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(24),
  [21] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(30),
  [24] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_score, 1, 0, 0),
  [26] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEvent, 3, 0, 0),
  [28] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_duration, 1, 0, 0),
  [30] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_CONFIG, 1, 0, 0),
  [32] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rest, 2, 0, 0),
  [34] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_EVENT, 1, 0, 0),
  [36] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_number, 1, 0, 0),
  [38] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberConfig, 2, 0, 0),
  [40] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberSet, 1, 0, 0),
  [42] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0),
  [44] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(21),
  [47] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(19),
  [50] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [52] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [56] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [58] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [60] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [62] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [64] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [68] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [70] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitch, 1, 0, 0),
  [74] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_noteName, 2, 0, 0),
  [76] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_noteName, 3, 0, 0),
  [78] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEventId, 1, 0, 0),
  [80] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitch, 1, 0, 0),
  [82] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitches, 3, 0, 0),
  [84] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitches, 3, 0, 0),
  [86] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_noteName, 2, 0, 0),
  [88] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_noteName, 3, 0, 0),
  [90] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_configId, 1, 0, 0),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_configId, 1, 0, 0),
  [94] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_restEventId, 1, 0, 0),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_restEventId, 1, 0, 0),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alteration, 1, 0, 0),
  [100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [102] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
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

TS_PUBLIC const TSLanguage *tree_sitter_scofo(void) {
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
