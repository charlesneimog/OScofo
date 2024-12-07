#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 39
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 34
#define ALIAS_COUNT 0
#define TOKEN_COUNT 19
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 4
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  anon_sym_BPM = 1,
  anon_sym_POUND = 2,
  aux_sym_COMMENT_token1 = 3,
  anon_sym_SEMI = 4,
  anon_sym_NOTE = 5,
  anon_sym_TRILL = 6,
  anon_sym_REST = 7,
  anon_sym_SPACE = 8,
  sym_midi = 9,
  sym_pitchclass = 10,
  anon_sym_b = 11,
  anon_sym_POUND_POUND = 12,
  anon_sym_bb = 13,
  sym_octave = 14,
  sym_float = 15,
  sym_integer = 16,
  sym_open_parenthesis = 17,
  sym_close_parenthesis = 18,
  sym_source_file = 19,
  sym_CONFIG = 20,
  sym_BPM = 21,
  sym_COMMENT = 22,
  sym_EVENT = 23,
  sym_NOTE = 24,
  sym_TRILL = 25,
  sym_REST = 26,
  sym_pitches = 27,
  sym_pitch = 28,
  sym_pitchname = 29,
  sym_alteration = 30,
  sym_duration = 31,
  aux_sym_source_file_repeat1 = 32,
  aux_sym_pitches_repeat1 = 33,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_BPM] = "BPM",
  [anon_sym_POUND] = "#",
  [aux_sym_COMMENT_token1] = "COMMENT_token1",
  [anon_sym_SEMI] = ";",
  [anon_sym_NOTE] = "NOTE",
  [anon_sym_TRILL] = "TRILL",
  [anon_sym_REST] = "REST",
  [anon_sym_SPACE] = " ",
  [sym_midi] = "midi",
  [sym_pitchclass] = "pitchclass",
  [anon_sym_b] = "b",
  [anon_sym_POUND_POUND] = "##",
  [anon_sym_bb] = "bb",
  [sym_octave] = "octave",
  [sym_float] = "float",
  [sym_integer] = "integer",
  [sym_open_parenthesis] = "open_parenthesis",
  [sym_close_parenthesis] = "close_parenthesis",
  [sym_source_file] = "source_file",
  [sym_CONFIG] = "CONFIG",
  [sym_BPM] = "BPM",
  [sym_COMMENT] = "COMMENT",
  [sym_EVENT] = "EVENT",
  [sym_NOTE] = "NOTE",
  [sym_TRILL] = "TRILL",
  [sym_REST] = "REST",
  [sym_pitches] = "pitches",
  [sym_pitch] = "pitch",
  [sym_pitchname] = "pitchname",
  [sym_alteration] = "alteration",
  [sym_duration] = "duration",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_pitches_repeat1] = "pitches_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_BPM] = anon_sym_BPM,
  [anon_sym_POUND] = anon_sym_POUND,
  [aux_sym_COMMENT_token1] = aux_sym_COMMENT_token1,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_NOTE] = anon_sym_NOTE,
  [anon_sym_TRILL] = anon_sym_TRILL,
  [anon_sym_REST] = anon_sym_REST,
  [anon_sym_SPACE] = anon_sym_SPACE,
  [sym_midi] = sym_midi,
  [sym_pitchclass] = sym_pitchclass,
  [anon_sym_b] = anon_sym_b,
  [anon_sym_POUND_POUND] = anon_sym_POUND_POUND,
  [anon_sym_bb] = anon_sym_bb,
  [sym_octave] = sym_octave,
  [sym_float] = sym_float,
  [sym_integer] = sym_integer,
  [sym_open_parenthesis] = sym_open_parenthesis,
  [sym_close_parenthesis] = sym_close_parenthesis,
  [sym_source_file] = sym_source_file,
  [sym_CONFIG] = sym_CONFIG,
  [sym_BPM] = sym_BPM,
  [sym_COMMENT] = sym_COMMENT,
  [sym_EVENT] = sym_EVENT,
  [sym_NOTE] = sym_NOTE,
  [sym_TRILL] = sym_TRILL,
  [sym_REST] = sym_REST,
  [sym_pitches] = sym_pitches,
  [sym_pitch] = sym_pitch,
  [sym_pitchname] = sym_pitchname,
  [sym_alteration] = sym_alteration,
  [sym_duration] = sym_duration,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_pitches_repeat1] = aux_sym_pitches_repeat1,
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
  [anon_sym_NOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TRILL] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_REST] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SPACE] = {
    .visible = true,
    .named = false,
  },
  [sym_midi] = {
    .visible = true,
    .named = true,
  },
  [sym_pitchclass] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_b] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_POUND_POUND] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bb] = {
    .visible = true,
    .named = false,
  },
  [sym_octave] = {
    .visible = true,
    .named = true,
  },
  [sym_float] = {
    .visible = true,
    .named = true,
  },
  [sym_integer] = {
    .visible = true,
    .named = true,
  },
  [sym_open_parenthesis] = {
    .visible = true,
    .named = true,
  },
  [sym_close_parenthesis] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_CONFIG] = {
    .visible = true,
    .named = true,
  },
  [sym_BPM] = {
    .visible = true,
    .named = true,
  },
  [sym_COMMENT] = {
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
  [sym_TRILL] = {
    .visible = true,
    .named = true,
  },
  [sym_REST] = {
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
  [sym_pitchname] = {
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
  [aux_sym_source_file_repeat1] = {
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
  [13] = 12,
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
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 30,
  [32] = 24,
  [33] = 26,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 34,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(18);
      ADVANCE_MAP(
        '#', 21,
        '(', 42,
        ')', 43,
        '0', 29,
        '1', 30,
        ';', 24,
        'B', 34,
        'N', 10,
        'R', 4,
        'T', 12,
        'b', 35,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(32);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(33);
      END_STATE();
    case 1:
      if (lookahead == ' ') ADVANCE(28);
      if (lookahead == ')') ADVANCE(43);
      if (('\t' <= lookahead && lookahead <= '\r')) SKIP(1);
      END_STATE();
    case 2:
      if (lookahead == '#') ADVANCE(21);
      if (lookahead == 'b') ADVANCE(36);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(39);
      END_STATE();
    case 3:
      if (lookahead == '0') ADVANCE(29);
      if (lookahead == '1') ADVANCE(30);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(3);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(32);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(33);
      END_STATE();
    case 4:
      if (lookahead == 'E') ADVANCE(13);
      END_STATE();
    case 5:
      if (lookahead == 'E') ADVANCE(25);
      END_STATE();
    case 6:
      if (lookahead == 'I') ADVANCE(8);
      END_STATE();
    case 7:
      if (lookahead == 'L') ADVANCE(26);
      END_STATE();
    case 8:
      if (lookahead == 'L') ADVANCE(7);
      END_STATE();
    case 9:
      if (lookahead == 'M') ADVANCE(19);
      END_STATE();
    case 10:
      if (lookahead == 'O') ADVANCE(15);
      END_STATE();
    case 11:
      if (lookahead == 'P') ADVANCE(9);
      END_STATE();
    case 12:
      if (lookahead == 'R') ADVANCE(6);
      END_STATE();
    case 13:
      if (lookahead == 'S') ADVANCE(14);
      END_STATE();
    case 14:
      if (lookahead == 'T') ADVANCE(27);
      END_STATE();
    case 15:
      if (lookahead == 'T') ADVANCE(5);
      END_STATE();
    case 16:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(40);
      END_STATE();
    case 17:
      if (eof) ADVANCE(18);
      if (lookahead == '#') ADVANCE(20);
      if (lookahead == ';') ADVANCE(24);
      if (lookahead == 'B') ADVANCE(11);
      if (lookahead == 'N') ADVANCE(10);
      if (lookahead == 'R') ADVANCE(4);
      if (lookahead == 'T') ADVANCE(12);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(17);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(anon_sym_BPM);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(anon_sym_POUND);
      if (lookahead == '#') ADVANCE(37);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(aux_sym_COMMENT_token1);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(22);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead)) ADVANCE(23);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(aux_sym_COMMENT_token1);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(23);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(anon_sym_NOTE);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(anon_sym_TRILL);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_REST);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_SPACE);
      if (lookahead == ' ') ADVANCE(28);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(sym_midi);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(sym_midi);
      if (lookahead == '2') ADVANCE(31);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(32);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(29);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(29);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(29);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(sym_pitchclass);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(sym_pitchclass);
      if (lookahead == 'P') ADVANCE(9);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_b);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_b);
      if (lookahead == 'b') ADVANCE(38);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_POUND_POUND);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_bb);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(sym_octave);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(sym_float);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(40);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(sym_integer);
      if (lookahead == '.') ADVANCE(16);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(sym_open_parenthesis);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_close_parenthesis);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 17},
  [2] = {.lex_state = 17},
  [3] = {.lex_state = 17},
  [4] = {.lex_state = 17},
  [5] = {.lex_state = 17},
  [6] = {.lex_state = 17},
  [7] = {.lex_state = 17},
  [8] = {.lex_state = 17},
  [9] = {.lex_state = 17},
  [10] = {.lex_state = 17},
  [11] = {.lex_state = 17},
  [12] = {.lex_state = 2},
  [13] = {.lex_state = 2},
  [14] = {.lex_state = 3},
  [15] = {.lex_state = 3},
  [16] = {.lex_state = 3},
  [17] = {.lex_state = 1},
  [18] = {.lex_state = 17},
  [19] = {.lex_state = 1},
  [20] = {.lex_state = 1},
  [21] = {.lex_state = 17},
  [22] = {.lex_state = 17},
  [23] = {.lex_state = 17},
  [24] = {.lex_state = 17},
  [25] = {.lex_state = 0},
  [26] = {.lex_state = 17},
  [27] = {.lex_state = 17},
  [28] = {.lex_state = 1},
  [29] = {.lex_state = 17},
  [30] = {.lex_state = 17},
  [31] = {.lex_state = 1},
  [32] = {.lex_state = 1},
  [33] = {.lex_state = 1},
  [34] = {.lex_state = 2},
  [35] = {.lex_state = 2},
  [36] = {.lex_state = 22},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 2},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_BPM] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_NOTE] = ACTIONS(1),
    [anon_sym_TRILL] = ACTIONS(1),
    [anon_sym_REST] = ACTIONS(1),
    [sym_midi] = ACTIONS(1),
    [sym_pitchclass] = ACTIONS(1),
    [anon_sym_b] = ACTIONS(1),
    [anon_sym_POUND_POUND] = ACTIONS(1),
    [sym_octave] = ACTIONS(1),
    [sym_open_parenthesis] = ACTIONS(1),
    [sym_close_parenthesis] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(37),
    [sym_CONFIG] = STATE(2),
    [sym_BPM] = STATE(5),
    [sym_COMMENT] = STATE(2),
    [sym_EVENT] = STATE(2),
    [sym_NOTE] = STATE(6),
    [sym_TRILL] = STATE(6),
    [sym_REST] = STATE(6),
    [aux_sym_source_file_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_BPM] = ACTIONS(5),
    [anon_sym_POUND] = ACTIONS(7),
    [anon_sym_SEMI] = ACTIONS(7),
    [anon_sym_NOTE] = ACTIONS(9),
    [anon_sym_TRILL] = ACTIONS(11),
    [anon_sym_REST] = ACTIONS(13),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 9,
    ACTIONS(5), 1,
      anon_sym_BPM,
    ACTIONS(9), 1,
      anon_sym_NOTE,
    ACTIONS(11), 1,
      anon_sym_TRILL,
    ACTIONS(13), 1,
      anon_sym_REST,
    ACTIONS(15), 1,
      ts_builtin_sym_end,
    STATE(5), 1,
      sym_BPM,
    ACTIONS(7), 2,
      anon_sym_POUND,
      anon_sym_SEMI,
    STATE(6), 3,
      sym_NOTE,
      sym_TRILL,
      sym_REST,
    STATE(3), 4,
      sym_CONFIG,
      sym_COMMENT,
      sym_EVENT,
      aux_sym_source_file_repeat1,
  [34] = 9,
    ACTIONS(17), 1,
      ts_builtin_sym_end,
    ACTIONS(19), 1,
      anon_sym_BPM,
    ACTIONS(25), 1,
      anon_sym_NOTE,
    ACTIONS(28), 1,
      anon_sym_TRILL,
    ACTIONS(31), 1,
      anon_sym_REST,
    STATE(5), 1,
      sym_BPM,
    ACTIONS(22), 2,
      anon_sym_POUND,
      anon_sym_SEMI,
    STATE(6), 3,
      sym_NOTE,
      sym_TRILL,
      sym_REST,
    STATE(3), 4,
      sym_CONFIG,
      sym_COMMENT,
      sym_EVENT,
      aux_sym_source_file_repeat1,
  [68] = 1,
    ACTIONS(34), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_REST,
  [78] = 1,
    ACTIONS(36), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_REST,
  [88] = 1,
    ACTIONS(38), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_REST,
  [98] = 1,
    ACTIONS(40), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_REST,
  [108] = 1,
    ACTIONS(42), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_REST,
  [118] = 1,
    ACTIONS(44), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_REST,
  [128] = 1,
    ACTIONS(46), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_REST,
  [138] = 1,
    ACTIONS(48), 7,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_REST,
  [148] = 4,
    ACTIONS(54), 1,
      sym_octave,
    STATE(38), 1,
      sym_alteration,
    ACTIONS(50), 2,
      anon_sym_POUND,
      anon_sym_b,
    ACTIONS(52), 2,
      anon_sym_POUND_POUND,
      anon_sym_bb,
  [163] = 4,
    ACTIONS(56), 1,
      sym_octave,
    STATE(34), 1,
      sym_alteration,
    ACTIONS(50), 2,
      anon_sym_POUND,
      anon_sym_b,
    ACTIONS(52), 2,
      anon_sym_POUND_POUND,
      anon_sym_bb,
  [178] = 4,
    ACTIONS(58), 1,
      sym_midi,
    ACTIONS(60), 1,
      sym_pitchclass,
    STATE(17), 1,
      sym_pitch,
    STATE(31), 1,
      sym_pitchname,
  [191] = 4,
    ACTIONS(62), 1,
      sym_midi,
    ACTIONS(64), 1,
      sym_pitchclass,
    STATE(21), 1,
      sym_pitch,
    STATE(30), 1,
      sym_pitchname,
  [204] = 4,
    ACTIONS(58), 1,
      sym_midi,
    ACTIONS(60), 1,
      sym_pitchclass,
    STATE(28), 1,
      sym_pitch,
    STATE(31), 1,
      sym_pitchname,
  [217] = 3,
    ACTIONS(66), 1,
      anon_sym_SPACE,
    ACTIONS(68), 1,
      sym_close_parenthesis,
    STATE(20), 1,
      aux_sym_pitches_repeat1,
  [227] = 3,
    ACTIONS(70), 1,
      sym_float,
    ACTIONS(72), 1,
      sym_integer,
    STATE(9), 1,
      sym_duration,
  [237] = 3,
    ACTIONS(74), 1,
      anon_sym_SPACE,
    ACTIONS(77), 1,
      sym_close_parenthesis,
    STATE(19), 1,
      aux_sym_pitches_repeat1,
  [247] = 3,
    ACTIONS(66), 1,
      anon_sym_SPACE,
    ACTIONS(79), 1,
      sym_close_parenthesis,
    STATE(19), 1,
      aux_sym_pitches_repeat1,
  [257] = 3,
    ACTIONS(70), 1,
      sym_float,
    ACTIONS(72), 1,
      sym_integer,
    STATE(11), 1,
      sym_duration,
  [267] = 3,
    ACTIONS(70), 1,
      sym_float,
    ACTIONS(72), 1,
      sym_integer,
    STATE(10), 1,
      sym_duration,
  [277] = 2,
    ACTIONS(81), 1,
      sym_float,
    ACTIONS(83), 1,
      sym_integer,
  [284] = 2,
    ACTIONS(85), 1,
      sym_float,
    ACTIONS(87), 1,
      sym_integer,
  [291] = 2,
    ACTIONS(89), 1,
      sym_open_parenthesis,
    STATE(22), 1,
      sym_pitches,
  [298] = 2,
    ACTIONS(91), 1,
      sym_float,
    ACTIONS(93), 1,
      sym_integer,
  [305] = 2,
    ACTIONS(95), 1,
      sym_float,
    ACTIONS(97), 1,
      sym_integer,
  [312] = 2,
    ACTIONS(77), 1,
      sym_close_parenthesis,
    ACTIONS(99), 1,
      anon_sym_SPACE,
  [319] = 2,
    ACTIONS(101), 1,
      sym_float,
    ACTIONS(103), 1,
      sym_integer,
  [326] = 2,
    ACTIONS(105), 1,
      sym_float,
    ACTIONS(107), 1,
      sym_integer,
  [333] = 2,
    ACTIONS(105), 1,
      anon_sym_SPACE,
    ACTIONS(107), 1,
      sym_close_parenthesis,
  [340] = 2,
    ACTIONS(85), 1,
      anon_sym_SPACE,
    ACTIONS(87), 1,
      sym_close_parenthesis,
  [347] = 2,
    ACTIONS(91), 1,
      anon_sym_SPACE,
    ACTIONS(93), 1,
      sym_close_parenthesis,
  [354] = 1,
    ACTIONS(109), 1,
      sym_octave,
  [358] = 1,
    ACTIONS(111), 1,
      sym_octave,
  [362] = 1,
    ACTIONS(113), 1,
      aux_sym_COMMENT_token1,
  [366] = 1,
    ACTIONS(115), 1,
      ts_builtin_sym_end,
  [370] = 1,
    ACTIONS(117), 1,
      sym_octave,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 34,
  [SMALL_STATE(4)] = 68,
  [SMALL_STATE(5)] = 78,
  [SMALL_STATE(6)] = 88,
  [SMALL_STATE(7)] = 98,
  [SMALL_STATE(8)] = 108,
  [SMALL_STATE(9)] = 118,
  [SMALL_STATE(10)] = 128,
  [SMALL_STATE(11)] = 138,
  [SMALL_STATE(12)] = 148,
  [SMALL_STATE(13)] = 163,
  [SMALL_STATE(14)] = 178,
  [SMALL_STATE(15)] = 191,
  [SMALL_STATE(16)] = 204,
  [SMALL_STATE(17)] = 217,
  [SMALL_STATE(18)] = 227,
  [SMALL_STATE(19)] = 237,
  [SMALL_STATE(20)] = 247,
  [SMALL_STATE(21)] = 257,
  [SMALL_STATE(22)] = 267,
  [SMALL_STATE(23)] = 277,
  [SMALL_STATE(24)] = 284,
  [SMALL_STATE(25)] = 291,
  [SMALL_STATE(26)] = 298,
  [SMALL_STATE(27)] = 305,
  [SMALL_STATE(28)] = 312,
  [SMALL_STATE(29)] = 319,
  [SMALL_STATE(30)] = 326,
  [SMALL_STATE(31)] = 333,
  [SMALL_STATE(32)] = 340,
  [SMALL_STATE(33)] = 347,
  [SMALL_STATE(34)] = 354,
  [SMALL_STATE(35)] = 358,
  [SMALL_STATE(36)] = 362,
  [SMALL_STATE(37)] = 366,
  [SMALL_STATE(38)] = 370,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [19] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(27),
  [22] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(36),
  [25] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(15),
  [28] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(25),
  [31] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(18),
  [34] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_duration, 1, 0, 0),
  [36] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_CONFIG, 1, 0, 0),
  [38] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_EVENT, 1, 0, 0),
  [40] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_BPM, 2, 0, 0),
  [42] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_COMMENT, 2, 0, 0),
  [44] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_REST, 2, 0, 0),
  [46] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_TRILL, 3, 0, 0),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_NOTE, 3, 0, 0),
  [50] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [52] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [56] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [58] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [60] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [62] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [64] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [68] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [70] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [72] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [74] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(16),
  [77] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0),
  [79] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitches, 3, 0, 0),
  [83] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitches, 3, 0, 0),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchname, 2, 0, 0),
  [87] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitchname, 2, 0, 0),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchname, 3, 0, 0),
  [93] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitchname, 3, 0, 0),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [97] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitches, 4, 0, 0),
  [103] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitches, 4, 0, 0),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitch, 1, 0, 0),
  [107] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitch, 1, 0, 0),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alteration, 1, 0, 0),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [115] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [117] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
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
