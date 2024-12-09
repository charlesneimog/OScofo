#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 33
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 39
#define ALIAS_COUNT 0
#define TOKEN_COUNT 21
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
  anon_sym_CONFIG2 = 6,
  anon_sym_NOTE = 7,
  anon_sym_REST = 8,
  anon_sym_TRILL = 9,
  anon_sym_CHORD = 10,
  anon_sym_LPAREN = 11,
  anon_sym_RPAREN = 12,
  sym_midi = 13,
  sym_pitchname = 14,
  anon_sym_POUND = 15,
  anon_sym_b = 16,
  sym_octave = 17,
  aux_sym_number_token1 = 18,
  aux_sym_number_token2 = 19,
  sym_comment = 20,
  sym_score = 21,
  sym__statement = 22,
  sym_EVENT = 23,
  sym_CONFIG = 24,
  sym_configId = 25,
  sym_numberConfig = 26,
  sym_numberSet = 27,
  sym_eventId = 28,
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
  [anon_sym_CONFIG2] = "identifier",
  [anon_sym_NOTE] = "identifier",
  [anon_sym_REST] = "identifier",
  [anon_sym_TRILL] = "identifier",
  [anon_sym_CHORD] = "identifier",
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
  [sym_eventId] = "eventId",
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
  [anon_sym_CONFIG2] = anon_sym_BPM,
  [anon_sym_NOTE] = anon_sym_BPM,
  [anon_sym_REST] = anon_sym_BPM,
  [anon_sym_TRILL] = anon_sym_BPM,
  [anon_sym_CHORD] = anon_sym_BPM,
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
  [sym_eventId] = sym_eventId,
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
  [anon_sym_CONFIG2] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_NOTE] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_REST] = {
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
  [sym_eventId] = {
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
  [19] = 19,
  [20] = 17,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 21,
  [25] = 25,
  [26] = 22,
  [27] = 27,
  [28] = 23,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 31,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(49);
      ADVANCE_MAP(
        '#', 73,
        '(', 60,
        ')', 61,
        '/', 10,
        '0', 62,
        '1', 67,
        'B', 72,
        'C', 71,
        'L', 42,
        'N', 30,
        'R', 18,
        'T', 35,
      );
      if (lookahead == '\\') SKIP(45);
      if (lookahead == 'b') ADVANCE(74);
      if (lookahead == '{') ADVANCE(51);
      if (lookahead == '}') ADVANCE(52);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(69);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(70);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(8);
      END_STATE();
    case 2:
      if (lookahead == '\n') SKIP(8);
      if (lookahead == '\r') SKIP(1);
      END_STATE();
    case 3:
      if (lookahead == '\n') SKIP(9);
      END_STATE();
    case 4:
      if (lookahead == '\n') SKIP(9);
      if (lookahead == '\r') SKIP(3);
      END_STATE();
    case 5:
      if (lookahead == '\n') SKIP(13);
      END_STATE();
    case 6:
      if (lookahead == '\n') SKIP(13);
      if (lookahead == '\r') SKIP(5);
      END_STATE();
    case 7:
      if (lookahead == '\r') ADVANCE(82);
      if (lookahead == '\\') ADVANCE(80);
      if (lookahead != 0) ADVANCE(81);
      END_STATE();
    case 8:
      if (lookahead == '(') ADVANCE(60);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '0') ADVANCE(66);
      if (lookahead == '1') ADVANCE(63);
      if (lookahead == '\\') SKIP(2);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(8);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(65);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(70);
      END_STATE();
    case 9:
      if (lookahead == ')') ADVANCE(61);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '0') ADVANCE(62);
      if (lookahead == '1') ADVANCE(67);
      if (lookahead == '\\') SKIP(4);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(9);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(69);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(70);
      END_STATE();
    case 10:
      if (lookahead == '*') ADVANCE(12);
      if (lookahead == '/') ADVANCE(81);
      END_STATE();
    case 11:
      if (lookahead == '*') ADVANCE(11);
      if (lookahead == '/') ADVANCE(79);
      if (lookahead != 0) ADVANCE(12);
      END_STATE();
    case 12:
      if (lookahead == '*') ADVANCE(11);
      if (lookahead != 0) ADVANCE(12);
      END_STATE();
    case 13:
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '\\') SKIP(6);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(13);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(77);
      END_STATE();
    case 14:
      if (lookahead == '2') ADVANCE(55);
      END_STATE();
    case 15:
      if (lookahead == 'A') ADVANCE(50);
      END_STATE();
    case 16:
      if (lookahead == 'A') ADVANCE(29);
      if (lookahead == 'I') ADVANCE(26);
      END_STATE();
    case 17:
      if (lookahead == 'D') ADVANCE(59);
      END_STATE();
    case 18:
      if (lookahead == 'E') ADVANCE(38);
      END_STATE();
    case 19:
      if (lookahead == 'E') ADVANCE(56);
      END_STATE();
    case 20:
      if (lookahead == 'E') ADVANCE(54);
      END_STATE();
    case 21:
      if (lookahead == 'F') ADVANCE(24);
      END_STATE();
    case 22:
      if (lookahead == 'G') ADVANCE(14);
      END_STATE();
    case 23:
      if (lookahead == 'H') ADVANCE(31);
      if (lookahead == 'O') ADVANCE(28);
      END_STATE();
    case 24:
      if (lookahead == 'I') ADVANCE(22);
      END_STATE();
    case 25:
      if (lookahead == 'L') ADVANCE(58);
      END_STATE();
    case 26:
      if (lookahead == 'L') ADVANCE(25);
      END_STATE();
    case 27:
      if (lookahead == 'M') ADVANCE(53);
      END_STATE();
    case 28:
      if (lookahead == 'N') ADVANCE(21);
      END_STATE();
    case 29:
      if (lookahead == 'N') ADVANCE(37);
      END_STATE();
    case 30:
      if (lookahead == 'O') ADVANCE(41);
      END_STATE();
    case 31:
      if (lookahead == 'O') ADVANCE(36);
      END_STATE();
    case 32:
      if (lookahead == 'O') ADVANCE(39);
      END_STATE();
    case 33:
      if (lookahead == 'P') ADVANCE(27);
      END_STATE();
    case 34:
      if (lookahead == 'P') ADVANCE(32);
      END_STATE();
    case 35:
      if (lookahead == 'R') ADVANCE(16);
      END_STATE();
    case 36:
      if (lookahead == 'R') ADVANCE(17);
      END_STATE();
    case 37:
      if (lookahead == 'S') ADVANCE(34);
      END_STATE();
    case 38:
      if (lookahead == 'S') ADVANCE(40);
      END_STATE();
    case 39:
      if (lookahead == 'S') ADVANCE(20);
      END_STATE();
    case 40:
      if (lookahead == 'T') ADVANCE(57);
      END_STATE();
    case 41:
      if (lookahead == 'T') ADVANCE(19);
      END_STATE();
    case 42:
      if (lookahead == 'U') ADVANCE(15);
      END_STATE();
    case 43:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(78);
      END_STATE();
    case 44:
      if (eof) ADVANCE(49);
      if (lookahead == '\n') SKIP(0);
      END_STATE();
    case 45:
      if (eof) ADVANCE(49);
      if (lookahead == '\n') SKIP(0);
      if (lookahead == '\r') SKIP(44);
      END_STATE();
    case 46:
      if (eof) ADVANCE(49);
      if (lookahead == '\n') SKIP(48);
      END_STATE();
    case 47:
      if (eof) ADVANCE(49);
      if (lookahead == '\n') SKIP(48);
      if (lookahead == '\r') SKIP(46);
      END_STATE();
    case 48:
      if (eof) ADVANCE(49);
      ADVANCE_MAP(
        '#', 73,
        '/', 10,
        '1', 76,
        'B', 33,
        'C', 23,
        'N', 30,
        'R', 18,
        'T', 35,
      );
      if (lookahead == '\\') SKIP(47);
      if (lookahead == 'b') ADVANCE(74);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(48);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(75);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(anon_sym_LUA);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(anon_sym_BPM);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_TRANSPOSE);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(anon_sym_CONFIG2);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(anon_sym_NOTE);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(anon_sym_REST);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(anon_sym_TRILL);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(anon_sym_CHORD);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_midi);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_midi);
      if (lookahead == '.') ADVANCE(43);
      if (lookahead == '2') ADVANCE(64);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(65);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(66);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_midi);
      if (lookahead == '.') ADVANCE(43);
      if (lookahead == '8' ||
          lookahead == '9') ADVANCE(77);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(66);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_midi);
      if (lookahead == '.') ADVANCE(43);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(66);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_midi);
      if (lookahead == '.') ADVANCE(43);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(77);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_midi);
      if (lookahead == '2') ADVANCE(68);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(69);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(62);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(62);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(62);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(sym_pitchname);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'H') ADVANCE(31);
      if (lookahead == 'O') ADVANCE(28);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'P') ADVANCE(27);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_b);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(sym_octave);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(sym_octave);
      if (('0' <= lookahead && lookahead <= '2')) ADVANCE(75);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(43);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(77);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(aux_sym_number_token2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(78);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\r') ADVANCE(82);
      if (lookahead == '\\') ADVANCE(80);
      if (lookahead != 0) ADVANCE(81);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(7);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(81);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(7);
      if (lookahead != 0) ADVANCE(81);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 48},
  [2] = {.lex_state = 48},
  [3] = {.lex_state = 48},
  [4] = {.lex_state = 8},
  [5] = {.lex_state = 48},
  [6] = {.lex_state = 48},
  [7] = {.lex_state = 48},
  [8] = {.lex_state = 48},
  [9] = {.lex_state = 48},
  [10] = {.lex_state = 48},
  [11] = {.lex_state = 48},
  [12] = {.lex_state = 48},
  [13] = {.lex_state = 9},
  [14] = {.lex_state = 9},
  [15] = {.lex_state = 9},
  [16] = {.lex_state = 8},
  [17] = {.lex_state = 48},
  [18] = {.lex_state = 13},
  [19] = {.lex_state = 13},
  [20] = {.lex_state = 48},
  [21] = {.lex_state = 9},
  [22] = {.lex_state = 9},
  [23] = {.lex_state = 9},
  [24] = {.lex_state = 13},
  [25] = {.lex_state = 13},
  [26] = {.lex_state = 13},
  [27] = {.lex_state = 13},
  [28] = {.lex_state = 13},
  [29] = {.lex_state = 0},
  [30] = {.lex_state = 48},
  [31] = {.lex_state = 48},
  [32] = {.lex_state = 48},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_LUA] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_BPM] = ACTIONS(1),
    [anon_sym_TRANSPOSE] = ACTIONS(1),
    [anon_sym_CONFIG2] = ACTIONS(1),
    [anon_sym_NOTE] = ACTIONS(1),
    [anon_sym_REST] = ACTIONS(1),
    [anon_sym_TRILL] = ACTIONS(1),
    [anon_sym_CHORD] = ACTIONS(1),
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
    [sym_score] = STATE(29),
    [sym__statement] = STATE(3),
    [sym_EVENT] = STATE(3),
    [sym_CONFIG] = STATE(3),
    [sym_configId] = STATE(19),
    [sym_numberConfig] = STATE(8),
    [sym_eventId] = STATE(4),
    [sym_pitchEvent] = STATE(9),
    [sym_rest] = STATE(9),
    [aux_sym_score_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_BPM] = ACTIONS(7),
    [anon_sym_TRANSPOSE] = ACTIONS(7),
    [anon_sym_CONFIG2] = ACTIONS(7),
    [anon_sym_NOTE] = ACTIONS(9),
    [anon_sym_REST] = ACTIONS(9),
    [anon_sym_TRILL] = ACTIONS(9),
    [anon_sym_CHORD] = ACTIONS(9),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      ts_builtin_sym_end,
    STATE(4), 1,
      sym_eventId,
    STATE(8), 1,
      sym_numberConfig,
    STATE(19), 1,
      sym_configId,
    STATE(9), 2,
      sym_pitchEvent,
      sym_rest,
    ACTIONS(13), 3,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_CONFIG2,
    ACTIONS(16), 4,
      anon_sym_NOTE,
      anon_sym_REST,
      anon_sym_TRILL,
      anon_sym_CHORD,
    STATE(2), 4,
      sym__statement,
      sym_EVENT,
      sym_CONFIG,
      aux_sym_score_repeat1,
  [37] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      ts_builtin_sym_end,
    STATE(4), 1,
      sym_eventId,
    STATE(8), 1,
      sym_numberConfig,
    STATE(19), 1,
      sym_configId,
    STATE(9), 2,
      sym_pitchEvent,
      sym_rest,
    ACTIONS(7), 3,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_CONFIG2,
    ACTIONS(9), 4,
      anon_sym_NOTE,
      anon_sym_REST,
      anon_sym_TRILL,
      anon_sym_CHORD,
    STATE(2), 4,
      sym__statement,
      sym_EVENT,
      sym_CONFIG,
      aux_sym_score_repeat1,
  [74] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_LPAREN,
    ACTIONS(23), 1,
      sym_midi,
    ACTIONS(25), 1,
      sym_pitchname,
    ACTIONS(27), 1,
      aux_sym_number_token1,
    ACTIONS(29), 1,
      aux_sym_number_token2,
    STATE(6), 1,
      sym_number,
    STATE(7), 1,
      sym_duration,
    STATE(24), 1,
      sym_noteName,
    STATE(18), 2,
      sym_pitches,
      sym_pitch,
  [106] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 8,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_CONFIG2,
      anon_sym_NOTE,
      anon_sym_REST,
      anon_sym_TRILL,
      anon_sym_CHORD,
  [120] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 8,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_CONFIG2,
      anon_sym_NOTE,
      anon_sym_REST,
      anon_sym_TRILL,
      anon_sym_CHORD,
  [134] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(35), 8,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_CONFIG2,
      anon_sym_NOTE,
      anon_sym_REST,
      anon_sym_TRILL,
      anon_sym_CHORD,
  [148] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 8,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_CONFIG2,
      anon_sym_NOTE,
      anon_sym_REST,
      anon_sym_TRILL,
      anon_sym_CHORD,
  [162] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(39), 8,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_CONFIG2,
      anon_sym_NOTE,
      anon_sym_REST,
      anon_sym_TRILL,
      anon_sym_CHORD,
  [176] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(41), 8,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_CONFIG2,
      anon_sym_NOTE,
      anon_sym_REST,
      anon_sym_TRILL,
      anon_sym_CHORD,
  [190] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(43), 8,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_CONFIG2,
      anon_sym_NOTE,
      anon_sym_REST,
      anon_sym_TRILL,
      anon_sym_CHORD,
  [204] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 8,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_CONFIG2,
      anon_sym_NOTE,
      anon_sym_REST,
      anon_sym_TRILL,
      anon_sym_CHORD,
  [218] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 1,
      anon_sym_RPAREN,
    ACTIONS(49), 1,
      sym_midi,
    ACTIONS(51), 1,
      sym_pitchname,
    STATE(21), 1,
      sym_noteName,
    STATE(14), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [238] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(53), 1,
      anon_sym_RPAREN,
    ACTIONS(55), 1,
      sym_midi,
    ACTIONS(58), 1,
      sym_pitchname,
    STATE(21), 1,
      sym_noteName,
    STATE(14), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [258] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      sym_midi,
    ACTIONS(51), 1,
      sym_pitchname,
    STATE(21), 1,
      sym_noteName,
    STATE(13), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [275] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(63), 2,
      sym_midi,
      aux_sym_number_token1,
    ACTIONS(61), 3,
      anon_sym_LPAREN,
      sym_pitchname,
      aux_sym_number_token2,
  [288] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(67), 1,
      sym_octave,
    STATE(31), 1,
      sym_alteration,
    ACTIONS(65), 2,
      anon_sym_POUND,
      anon_sym_b,
  [302] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(27), 1,
      aux_sym_number_token1,
    ACTIONS(29), 1,
      aux_sym_number_token2,
    STATE(5), 1,
      sym_duration,
    STATE(6), 1,
      sym_number,
  [318] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(27), 1,
      aux_sym_number_token1,
    ACTIONS(29), 1,
      aux_sym_number_token2,
    STATE(11), 1,
      sym_numberSet,
    STATE(12), 1,
      sym_number,
  [334] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(69), 1,
      sym_octave,
    STATE(32), 1,
      sym_alteration,
    ACTIONS(65), 2,
      anon_sym_POUND,
      anon_sym_b,
  [348] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(71), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [357] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(73), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [366] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(75), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [375] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(71), 1,
      aux_sym_number_token2,
    ACTIONS(77), 1,
      aux_sym_number_token1,
  [385] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(79), 1,
      aux_sym_number_token1,
    ACTIONS(81), 1,
      aux_sym_number_token2,
  [395] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(73), 1,
      aux_sym_number_token2,
    ACTIONS(83), 1,
      aux_sym_number_token1,
  [405] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(85), 1,
      aux_sym_number_token1,
    ACTIONS(87), 1,
      aux_sym_number_token2,
  [415] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(75), 1,
      aux_sym_number_token2,
    ACTIONS(89), 1,
      aux_sym_number_token1,
  [425] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(91), 1,
      ts_builtin_sym_end,
  [432] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      sym_octave,
  [439] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(95), 1,
      sym_octave,
  [446] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 1,
      sym_octave,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 37,
  [SMALL_STATE(4)] = 74,
  [SMALL_STATE(5)] = 106,
  [SMALL_STATE(6)] = 120,
  [SMALL_STATE(7)] = 134,
  [SMALL_STATE(8)] = 148,
  [SMALL_STATE(9)] = 162,
  [SMALL_STATE(10)] = 176,
  [SMALL_STATE(11)] = 190,
  [SMALL_STATE(12)] = 204,
  [SMALL_STATE(13)] = 218,
  [SMALL_STATE(14)] = 238,
  [SMALL_STATE(15)] = 258,
  [SMALL_STATE(16)] = 275,
  [SMALL_STATE(17)] = 288,
  [SMALL_STATE(18)] = 302,
  [SMALL_STATE(19)] = 318,
  [SMALL_STATE(20)] = 334,
  [SMALL_STATE(21)] = 348,
  [SMALL_STATE(22)] = 357,
  [SMALL_STATE(23)] = 366,
  [SMALL_STATE(24)] = 375,
  [SMALL_STATE(25)] = 385,
  [SMALL_STATE(26)] = 395,
  [SMALL_STATE(27)] = 405,
  [SMALL_STATE(28)] = 415,
  [SMALL_STATE(29)] = 425,
  [SMALL_STATE(30)] = 432,
  [SMALL_STATE(31)] = 439,
  [SMALL_STATE(32)] = 446,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_score, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [11] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0),
  [13] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(25),
  [16] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(16),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_score, 1, 0, 0),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [31] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEvent, 3, 0, 0),
  [33] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_duration, 1, 0, 0),
  [35] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rest, 2, 0, 0),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_CONFIG, 1, 0, 0),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_EVENT, 1, 0, 0),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_number, 1, 0, 0),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberConfig, 2, 0, 0),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberSet, 1, 0, 0),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [53] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0),
  [55] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(21),
  [58] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(20),
  [61] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_eventId, 1, 0, 0),
  [63] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_eventId, 1, 0, 0),
  [65] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [69] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitch, 1, 0, 0),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_noteName, 2, 0, 0),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_noteName, 3, 0, 0),
  [77] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitch, 1, 0, 0),
  [79] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_configId, 1, 0, 0),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_configId, 1, 0, 0),
  [83] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_noteName, 2, 0, 0),
  [85] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitches, 3, 0, 0),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitches, 3, 0, 0),
  [89] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_noteName, 3, 0, 0),
  [91] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alteration, 1, 0, 0),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
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
