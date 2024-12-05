#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 37
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 32
#define ALIAS_COUNT 0
#define TOKEN_COUNT 18
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
  anon_sym_SPACE = 7,
  sym_midi = 8,
  sym_pitchclass = 9,
  anon_sym_b = 10,
  anon_sym_POUND_POUND = 11,
  anon_sym_bb = 12,
  sym_octave = 13,
  sym_float = 14,
  sym_integer = 15,
  sym_open_parenthesis = 16,
  sym_close_parenthesis = 17,
  sym_source_file = 18,
  sym_CONFIG = 19,
  sym_BPM = 20,
  sym_COMMENT = 21,
  sym_EVENT = 22,
  sym_NOTE = 23,
  sym_TRILL = 24,
  sym_pitches = 25,
  sym_pitch = 26,
  sym_pitchname = 27,
  sym_alteration = 28,
  sym_duration = 29,
  aux_sym_source_file_repeat1 = 30,
  aux_sym_pitches_repeat1 = 31,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_BPM] = "BPM",
  [anon_sym_POUND] = "#",
  [aux_sym_COMMENT_token1] = "COMMENT_token1",
  [anon_sym_SEMI] = ";",
  [anon_sym_NOTE] = "NOTE",
  [anon_sym_TRILL] = "TRILL",
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
  [12] = 4,
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
  [27] = 27,
  [28] = 28,
  [29] = 25,
  [30] = 22,
  [31] = 24,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 32,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(15);
      ADVANCE_MAP(
        '#', 18,
        '(', 38,
        ')', 39,
        '0', 25,
        '1', 26,
        ';', 21,
        'B', 30,
        'N', 9,
        'T', 11,
        'b', 31,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(28);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(29);
      END_STATE();
    case 1:
      if (lookahead == ' ') ADVANCE(24);
      if (lookahead == ')') ADVANCE(39);
      if (('\t' <= lookahead && lookahead <= '\r')) SKIP(1);
      END_STATE();
    case 2:
      if (lookahead == '#') ADVANCE(18);
      if (lookahead == 'b') ADVANCE(32);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(35);
      END_STATE();
    case 3:
      if (lookahead == '0') ADVANCE(25);
      if (lookahead == '1') ADVANCE(26);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(3);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(28);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(29);
      END_STATE();
    case 4:
      if (lookahead == 'E') ADVANCE(22);
      END_STATE();
    case 5:
      if (lookahead == 'I') ADVANCE(7);
      END_STATE();
    case 6:
      if (lookahead == 'L') ADVANCE(23);
      END_STATE();
    case 7:
      if (lookahead == 'L') ADVANCE(6);
      END_STATE();
    case 8:
      if (lookahead == 'M') ADVANCE(16);
      END_STATE();
    case 9:
      if (lookahead == 'O') ADVANCE(12);
      END_STATE();
    case 10:
      if (lookahead == 'P') ADVANCE(8);
      END_STATE();
    case 11:
      if (lookahead == 'R') ADVANCE(5);
      END_STATE();
    case 12:
      if (lookahead == 'T') ADVANCE(4);
      END_STATE();
    case 13:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(36);
      END_STATE();
    case 14:
      if (eof) ADVANCE(15);
      if (lookahead == '#') ADVANCE(17);
      if (lookahead == ';') ADVANCE(21);
      if (lookahead == 'B') ADVANCE(10);
      if (lookahead == 'N') ADVANCE(9);
      if (lookahead == 'T') ADVANCE(11);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(14);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(37);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(anon_sym_BPM);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(anon_sym_POUND);
      if (lookahead == '#') ADVANCE(33);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(aux_sym_COMMENT_token1);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(19);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead)) ADVANCE(20);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(aux_sym_COMMENT_token1);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(20);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(anon_sym_NOTE);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(anon_sym_TRILL);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_SPACE);
      if (lookahead == ' ') ADVANCE(24);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(sym_midi);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(sym_midi);
      if (lookahead == '2') ADVANCE(27);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(28);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(25);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(25);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(25);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(sym_pitchclass);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(sym_pitchclass);
      if (lookahead == 'P') ADVANCE(8);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_b);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_b);
      if (lookahead == 'b') ADVANCE(34);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_POUND_POUND);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_bb);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(sym_octave);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(sym_float);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(36);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(sym_integer);
      if (lookahead == '.') ADVANCE(13);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(37);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(sym_open_parenthesis);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(sym_close_parenthesis);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 14},
  [2] = {.lex_state = 14},
  [3] = {.lex_state = 14},
  [4] = {.lex_state = 2},
  [5] = {.lex_state = 14},
  [6] = {.lex_state = 14},
  [7] = {.lex_state = 14},
  [8] = {.lex_state = 14},
  [9] = {.lex_state = 14},
  [10] = {.lex_state = 14},
  [11] = {.lex_state = 14},
  [12] = {.lex_state = 2},
  [13] = {.lex_state = 3},
  [14] = {.lex_state = 3},
  [15] = {.lex_state = 3},
  [16] = {.lex_state = 14},
  [17] = {.lex_state = 1},
  [18] = {.lex_state = 14},
  [19] = {.lex_state = 1},
  [20] = {.lex_state = 1},
  [21] = {.lex_state = 14},
  [22] = {.lex_state = 14},
  [23] = {.lex_state = 14},
  [24] = {.lex_state = 14},
  [25] = {.lex_state = 14},
  [26] = {.lex_state = 1},
  [27] = {.lex_state = 14},
  [28] = {.lex_state = 0},
  [29] = {.lex_state = 1},
  [30] = {.lex_state = 1},
  [31] = {.lex_state = 1},
  [32] = {.lex_state = 2},
  [33] = {.lex_state = 2},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 19},
  [36] = {.lex_state = 2},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_BPM] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_NOTE] = ACTIONS(1),
    [anon_sym_TRILL] = ACTIONS(1),
    [sym_midi] = ACTIONS(1),
    [sym_pitchclass] = ACTIONS(1),
    [anon_sym_b] = ACTIONS(1),
    [anon_sym_POUND_POUND] = ACTIONS(1),
    [sym_octave] = ACTIONS(1),
    [sym_open_parenthesis] = ACTIONS(1),
    [sym_close_parenthesis] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(34),
    [sym_CONFIG] = STATE(3),
    [sym_BPM] = STATE(8),
    [sym_COMMENT] = STATE(3),
    [sym_EVENT] = STATE(3),
    [sym_NOTE] = STATE(9),
    [sym_TRILL] = STATE(9),
    [aux_sym_source_file_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_BPM] = ACTIONS(5),
    [anon_sym_POUND] = ACTIONS(7),
    [anon_sym_SEMI] = ACTIONS(7),
    [anon_sym_NOTE] = ACTIONS(9),
    [anon_sym_TRILL] = ACTIONS(11),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 8,
    ACTIONS(13), 1,
      ts_builtin_sym_end,
    ACTIONS(15), 1,
      anon_sym_BPM,
    ACTIONS(21), 1,
      anon_sym_NOTE,
    ACTIONS(24), 1,
      anon_sym_TRILL,
    STATE(8), 1,
      sym_BPM,
    ACTIONS(18), 2,
      anon_sym_POUND,
      anon_sym_SEMI,
    STATE(9), 2,
      sym_NOTE,
      sym_TRILL,
    STATE(2), 4,
      sym_CONFIG,
      sym_COMMENT,
      sym_EVENT,
      aux_sym_source_file_repeat1,
  [30] = 8,
    ACTIONS(5), 1,
      anon_sym_BPM,
    ACTIONS(9), 1,
      anon_sym_NOTE,
    ACTIONS(11), 1,
      anon_sym_TRILL,
    ACTIONS(27), 1,
      ts_builtin_sym_end,
    STATE(8), 1,
      sym_BPM,
    ACTIONS(7), 2,
      anon_sym_POUND,
      anon_sym_SEMI,
    STATE(9), 2,
      sym_NOTE,
      sym_TRILL,
    STATE(2), 4,
      sym_CONFIG,
      sym_COMMENT,
      sym_EVENT,
      aux_sym_source_file_repeat1,
  [60] = 4,
    ACTIONS(33), 1,
      sym_octave,
    STATE(36), 1,
      sym_alteration,
    ACTIONS(29), 2,
      anon_sym_POUND,
      anon_sym_b,
    ACTIONS(31), 2,
      anon_sym_POUND_POUND,
      anon_sym_bb,
  [75] = 1,
    ACTIONS(35), 6,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
  [84] = 1,
    ACTIONS(37), 6,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
  [93] = 1,
    ACTIONS(39), 6,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
  [102] = 1,
    ACTIONS(41), 6,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
  [111] = 1,
    ACTIONS(43), 6,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
  [120] = 1,
    ACTIONS(45), 6,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
  [129] = 1,
    ACTIONS(47), 6,
      ts_builtin_sym_end,
      anon_sym_BPM,
      anon_sym_POUND,
      anon_sym_SEMI,
      anon_sym_NOTE,
      anon_sym_TRILL,
  [138] = 4,
    ACTIONS(49), 1,
      sym_octave,
    STATE(32), 1,
      sym_alteration,
    ACTIONS(29), 2,
      anon_sym_POUND,
      anon_sym_b,
    ACTIONS(31), 2,
      anon_sym_POUND_POUND,
      anon_sym_bb,
  [153] = 4,
    ACTIONS(51), 1,
      sym_midi,
    ACTIONS(53), 1,
      sym_pitchclass,
    STATE(17), 1,
      sym_pitch,
    STATE(29), 1,
      sym_pitchname,
  [166] = 4,
    ACTIONS(51), 1,
      sym_midi,
    ACTIONS(53), 1,
      sym_pitchclass,
    STATE(26), 1,
      sym_pitch,
    STATE(29), 1,
      sym_pitchname,
  [179] = 4,
    ACTIONS(55), 1,
      sym_midi,
    ACTIONS(57), 1,
      sym_pitchclass,
    STATE(16), 1,
      sym_pitch,
    STATE(25), 1,
      sym_pitchname,
  [192] = 3,
    ACTIONS(59), 1,
      sym_float,
    ACTIONS(61), 1,
      sym_integer,
    STATE(5), 1,
      sym_duration,
  [202] = 3,
    ACTIONS(63), 1,
      anon_sym_SPACE,
    ACTIONS(65), 1,
      sym_close_parenthesis,
    STATE(20), 1,
      aux_sym_pitches_repeat1,
  [212] = 3,
    ACTIONS(59), 1,
      sym_float,
    ACTIONS(61), 1,
      sym_integer,
    STATE(7), 1,
      sym_duration,
  [222] = 3,
    ACTIONS(67), 1,
      anon_sym_SPACE,
    ACTIONS(70), 1,
      sym_close_parenthesis,
    STATE(19), 1,
      aux_sym_pitches_repeat1,
  [232] = 3,
    ACTIONS(63), 1,
      anon_sym_SPACE,
    ACTIONS(72), 1,
      sym_close_parenthesis,
    STATE(19), 1,
      aux_sym_pitches_repeat1,
  [242] = 2,
    ACTIONS(74), 1,
      sym_float,
    ACTIONS(76), 1,
      sym_integer,
  [249] = 2,
    ACTIONS(78), 1,
      sym_float,
    ACTIONS(80), 1,
      sym_integer,
  [256] = 2,
    ACTIONS(82), 1,
      sym_float,
    ACTIONS(84), 1,
      sym_integer,
  [263] = 2,
    ACTIONS(86), 1,
      sym_float,
    ACTIONS(88), 1,
      sym_integer,
  [270] = 2,
    ACTIONS(90), 1,
      sym_float,
    ACTIONS(92), 1,
      sym_integer,
  [277] = 2,
    ACTIONS(70), 1,
      sym_close_parenthesis,
    ACTIONS(94), 1,
      anon_sym_SPACE,
  [284] = 2,
    ACTIONS(96), 1,
      sym_float,
    ACTIONS(98), 1,
      sym_integer,
  [291] = 2,
    ACTIONS(100), 1,
      sym_open_parenthesis,
    STATE(18), 1,
      sym_pitches,
  [298] = 2,
    ACTIONS(90), 1,
      anon_sym_SPACE,
    ACTIONS(92), 1,
      sym_close_parenthesis,
  [305] = 2,
    ACTIONS(78), 1,
      anon_sym_SPACE,
    ACTIONS(80), 1,
      sym_close_parenthesis,
  [312] = 2,
    ACTIONS(86), 1,
      anon_sym_SPACE,
    ACTIONS(88), 1,
      sym_close_parenthesis,
  [319] = 1,
    ACTIONS(102), 1,
      sym_octave,
  [323] = 1,
    ACTIONS(104), 1,
      sym_octave,
  [327] = 1,
    ACTIONS(106), 1,
      ts_builtin_sym_end,
  [331] = 1,
    ACTIONS(108), 1,
      aux_sym_COMMENT_token1,
  [335] = 1,
    ACTIONS(110), 1,
      sym_octave,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 30,
  [SMALL_STATE(4)] = 60,
  [SMALL_STATE(5)] = 75,
  [SMALL_STATE(6)] = 84,
  [SMALL_STATE(7)] = 93,
  [SMALL_STATE(8)] = 102,
  [SMALL_STATE(9)] = 111,
  [SMALL_STATE(10)] = 120,
  [SMALL_STATE(11)] = 129,
  [SMALL_STATE(12)] = 138,
  [SMALL_STATE(13)] = 153,
  [SMALL_STATE(14)] = 166,
  [SMALL_STATE(15)] = 179,
  [SMALL_STATE(16)] = 192,
  [SMALL_STATE(17)] = 202,
  [SMALL_STATE(18)] = 212,
  [SMALL_STATE(19)] = 222,
  [SMALL_STATE(20)] = 232,
  [SMALL_STATE(21)] = 242,
  [SMALL_STATE(22)] = 249,
  [SMALL_STATE(23)] = 256,
  [SMALL_STATE(24)] = 263,
  [SMALL_STATE(25)] = 270,
  [SMALL_STATE(26)] = 277,
  [SMALL_STATE(27)] = 284,
  [SMALL_STATE(28)] = 291,
  [SMALL_STATE(29)] = 298,
  [SMALL_STATE(30)] = 305,
  [SMALL_STATE(31)] = 312,
  [SMALL_STATE(32)] = 319,
  [SMALL_STATE(33)] = 323,
  [SMALL_STATE(34)] = 327,
  [SMALL_STATE(35)] = 331,
  [SMALL_STATE(36)] = 335,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [15] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(23),
  [18] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(35),
  [21] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(15),
  [24] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(28),
  [27] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [35] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_NOTE, 3, 0, 0),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_duration, 1, 0, 0),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_TRILL, 3, 0, 0),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_CONFIG, 1, 0, 0),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_EVENT, 1, 0, 0),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_BPM, 2, 0, 0),
  [47] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_COMMENT, 2, 0, 0),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [53] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [55] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [57] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [59] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [61] = {.entry = {.count = 1, .reusable = false}}, SHIFT(6),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [65] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [67] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(14),
  [70] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0),
  [72] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [74] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitches, 3, 0, 0),
  [76] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitches, 3, 0, 0),
  [78] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchname, 2, 0, 0),
  [80] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitchname, 2, 0, 0),
  [82] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [84] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [86] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchname, 3, 0, 0),
  [88] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitchname, 3, 0, 0),
  [90] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitch, 1, 0, 0),
  [92] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitch, 1, 0, 0),
  [94] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitches, 4, 0, 0),
  [98] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitches, 4, 0, 0),
  [100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [102] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [104] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alteration, 1, 0, 0),
  [106] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [108] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
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
