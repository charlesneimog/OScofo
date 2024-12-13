#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 81
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 71
#define ALIAS_COUNT 0
#define TOKEN_COUNT 38
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  sym_keyword = 1,
  anon_sym_LUA = 2,
  anon_sym_LBRACE = 3,
  anon_sym_RBRACE = 4,
  aux_sym_lua_body_token1 = 5,
  aux_sym_lua_call_token1 = 6,
  anon_sym_LPAREN = 7,
  anon_sym_RPAREN = 8,
  sym_lua_comment = 9,
  anon_sym_BPM = 10,
  anon_sym_TRANSPOSE = 11,
  anon_sym_ENTROPY = 12,
  anon_sym_NOTE = 13,
  anon_sym_TRILL = 14,
  anon_sym_CHORD = 15,
  anon_sym_REST = 16,
  sym_midi = 17,
  sym_pitchname = 18,
  anon_sym_POUND = 19,
  anon_sym_b = 20,
  sym_octave = 21,
  anon_sym_ACTION = 22,
  anon_sym_delay = 23,
  anon_sym_send = 24,
  anon_sym_sendto = 25,
  anon_sym_LBRACK = 26,
  anon_sym_RBRACK = 27,
  anon_sym_call = 28,
  aux_sym_actionKey_token1 = 29,
  aux_sym_number_token1 = 30,
  aux_sym_number_token2 = 31,
  sym_comment = 32,
  anon_sym_tempo = 33,
  anon_sym_s = 34,
  anon_sym_ms = 35,
  anon_sym_us = 36,
  anon_sym_ns = 37,
  sym_score = 38,
  sym__statement = 39,
  sym_LUA = 40,
  sym_lua_body = 41,
  sym_lua_call = 42,
  sym_CONFIG = 43,
  sym_configId = 44,
  sym_numberConfig = 45,
  sym_numberSet = 46,
  sym_EVENT = 47,
  sym_pitchEventId = 48,
  sym_restEventId = 49,
  sym_pitchEvent = 50,
  sym_rest = 51,
  sym_pitches = 52,
  sym_pitch = 53,
  sym_noteName = 54,
  sym_alteration = 55,
  sym_duration = 56,
  sym_ACTION = 57,
  sym_timedAction = 58,
  sym_exec = 59,
  sym_pdargs = 60,
  sym_receiver = 61,
  sym_number = 62,
  sym_symbol = 63,
  sym_timeUnit = 64,
  aux_sym_score_repeat1 = 65,
  aux_sym_lua_body_repeat1 = 66,
  aux_sym_lua_call_repeat1 = 67,
  aux_sym_pitches_repeat1 = 68,
  aux_sym_ACTION_repeat1 = 69,
  aux_sym_exec_repeat1 = 70,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_keyword] = "keyword",
  [anon_sym_LUA] = "identifier",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [aux_sym_lua_body_token1] = "lua_body_token1",
  [aux_sym_lua_call_token1] = "lua_call_token1",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_lua_comment] = "lua_comment",
  [anon_sym_BPM] = "keyword",
  [anon_sym_TRANSPOSE] = "keyword",
  [anon_sym_ENTROPY] = "keyword",
  [anon_sym_NOTE] = "keyword",
  [anon_sym_TRILL] = "keyword",
  [anon_sym_CHORD] = "keyword",
  [anon_sym_REST] = "keyword",
  [sym_midi] = "midi",
  [sym_pitchname] = "pitchname",
  [anon_sym_POUND] = "#",
  [anon_sym_b] = "b",
  [sym_octave] = "octave",
  [anon_sym_ACTION] = "keyword",
  [anon_sym_delay] = "actionKey",
  [anon_sym_send] = "keyword",
  [anon_sym_sendto] = "keyword",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_call] = "keyword",
  [aux_sym_actionKey_token1] = "actionKey_token1",
  [aux_sym_number_token1] = "number_token1",
  [aux_sym_number_token2] = "number_token2",
  [sym_comment] = "comment",
  [anon_sym_tempo] = "tempo",
  [anon_sym_s] = "s",
  [anon_sym_ms] = "ms",
  [anon_sym_us] = "us",
  [anon_sym_ns] = "ns",
  [sym_score] = "score",
  [sym__statement] = "_statement",
  [sym_LUA] = "LUA",
  [sym_lua_body] = "lua_body",
  [sym_lua_call] = "lua_call",
  [sym_CONFIG] = "CONFIG",
  [sym_configId] = "configId",
  [sym_numberConfig] = "numberConfig",
  [sym_numberSet] = "numberSet",
  [sym_EVENT] = "EVENT",
  [sym_pitchEventId] = "pitchEventId",
  [sym_restEventId] = "restEventId",
  [sym_pitchEvent] = "pitchEvent",
  [sym_rest] = "rest",
  [sym_pitches] = "pitches",
  [sym_pitch] = "pitch",
  [sym_noteName] = "noteName",
  [sym_alteration] = "alteration",
  [sym_duration] = "duration",
  [sym_ACTION] = "ACTION",
  [sym_timedAction] = "timedAction",
  [sym_exec] = "exec",
  [sym_pdargs] = "pdargs",
  [sym_receiver] = "receiver",
  [sym_number] = "number",
  [sym_symbol] = "symbol",
  [sym_timeUnit] = "timeUnit",
  [aux_sym_score_repeat1] = "score_repeat1",
  [aux_sym_lua_body_repeat1] = "lua_body_repeat1",
  [aux_sym_lua_call_repeat1] = "lua_call_repeat1",
  [aux_sym_pitches_repeat1] = "pitches_repeat1",
  [aux_sym_ACTION_repeat1] = "ACTION_repeat1",
  [aux_sym_exec_repeat1] = "exec_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_keyword] = sym_keyword,
  [anon_sym_LUA] = anon_sym_LUA,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [aux_sym_lua_body_token1] = aux_sym_lua_body_token1,
  [aux_sym_lua_call_token1] = aux_sym_lua_call_token1,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_lua_comment] = sym_lua_comment,
  [anon_sym_BPM] = sym_keyword,
  [anon_sym_TRANSPOSE] = sym_keyword,
  [anon_sym_ENTROPY] = sym_keyword,
  [anon_sym_NOTE] = sym_keyword,
  [anon_sym_TRILL] = sym_keyword,
  [anon_sym_CHORD] = sym_keyword,
  [anon_sym_REST] = sym_keyword,
  [sym_midi] = sym_midi,
  [sym_pitchname] = sym_pitchname,
  [anon_sym_POUND] = anon_sym_POUND,
  [anon_sym_b] = anon_sym_b,
  [sym_octave] = sym_octave,
  [anon_sym_ACTION] = sym_keyword,
  [anon_sym_delay] = anon_sym_delay,
  [anon_sym_send] = sym_keyword,
  [anon_sym_sendto] = sym_keyword,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_call] = sym_keyword,
  [aux_sym_actionKey_token1] = aux_sym_actionKey_token1,
  [aux_sym_number_token1] = aux_sym_number_token1,
  [aux_sym_number_token2] = aux_sym_number_token2,
  [sym_comment] = sym_comment,
  [anon_sym_tempo] = anon_sym_tempo,
  [anon_sym_s] = anon_sym_s,
  [anon_sym_ms] = anon_sym_ms,
  [anon_sym_us] = anon_sym_us,
  [anon_sym_ns] = anon_sym_ns,
  [sym_score] = sym_score,
  [sym__statement] = sym__statement,
  [sym_LUA] = sym_LUA,
  [sym_lua_body] = sym_lua_body,
  [sym_lua_call] = sym_lua_call,
  [sym_CONFIG] = sym_CONFIG,
  [sym_configId] = sym_configId,
  [sym_numberConfig] = sym_numberConfig,
  [sym_numberSet] = sym_numberSet,
  [sym_EVENT] = sym_EVENT,
  [sym_pitchEventId] = sym_pitchEventId,
  [sym_restEventId] = sym_restEventId,
  [sym_pitchEvent] = sym_pitchEvent,
  [sym_rest] = sym_rest,
  [sym_pitches] = sym_pitches,
  [sym_pitch] = sym_pitch,
  [sym_noteName] = sym_noteName,
  [sym_alteration] = sym_alteration,
  [sym_duration] = sym_duration,
  [sym_ACTION] = sym_ACTION,
  [sym_timedAction] = sym_timedAction,
  [sym_exec] = sym_exec,
  [sym_pdargs] = sym_pdargs,
  [sym_receiver] = sym_receiver,
  [sym_number] = sym_number,
  [sym_symbol] = sym_symbol,
  [sym_timeUnit] = sym_timeUnit,
  [aux_sym_score_repeat1] = aux_sym_score_repeat1,
  [aux_sym_lua_body_repeat1] = aux_sym_lua_body_repeat1,
  [aux_sym_lua_call_repeat1] = aux_sym_lua_call_repeat1,
  [aux_sym_pitches_repeat1] = aux_sym_pitches_repeat1,
  [aux_sym_ACTION_repeat1] = aux_sym_ACTION_repeat1,
  [aux_sym_exec_repeat1] = aux_sym_exec_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_keyword] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LUA] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_lua_body_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_lua_call_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [sym_lua_comment] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_BPM] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_TRANSPOSE] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_ENTROPY] = {
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
  [anon_sym_ACTION] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_delay] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_send] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_sendto] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_call] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_actionKey_token1] = {
    .visible = false,
    .named = false,
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
  [anon_sym_tempo] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_s] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ms] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_us] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ns] = {
    .visible = true,
    .named = false,
  },
  [sym_score] = {
    .visible = true,
    .named = true,
  },
  [sym__statement] = {
    .visible = false,
    .named = true,
  },
  [sym_LUA] = {
    .visible = true,
    .named = true,
  },
  [sym_lua_body] = {
    .visible = true,
    .named = true,
  },
  [sym_lua_call] = {
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
  [sym_EVENT] = {
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
  [sym_ACTION] = {
    .visible = true,
    .named = true,
  },
  [sym_timedAction] = {
    .visible = true,
    .named = true,
  },
  [sym_exec] = {
    .visible = true,
    .named = true,
  },
  [sym_pdargs] = {
    .visible = true,
    .named = true,
  },
  [sym_receiver] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_symbol] = {
    .visible = true,
    .named = true,
  },
  [sym_timeUnit] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_score_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_lua_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_lua_call_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_pitches_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_ACTION_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_exec_repeat1] = {
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
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 10,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 41,
  [44] = 10,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 61,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 54,
  [68] = 68,
  [69] = 69,
  [70] = 56,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 76,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(76);
      ADVANCE_MAP(
        '#', 124,
        '(', 103,
        ')', 104,
        '-', 13,
        '/', 10,
        '0', 113,
        '1', 114,
        'A', 118,
        'B', 121,
        'C', 119,
        'E', 120,
        'L', 50,
        'N', 35,
        'R', 21,
        'T', 40,
        '[', 132,
      );
      if (lookahead == '\\') SKIP(72);
      if (lookahead == ']') ADVANCE(133);
      if (lookahead == 'b') ADVANCE(125);
      if (lookahead == 'c') ADVANCE(122);
      if (lookahead == 'd') ADVANCE(123);
      if (lookahead == 'm') ADVANCE(66);
      if (lookahead == 'n') ADVANCE(67);
      if (lookahead == 's') ADVANCE(144);
      if (lookahead == 't') ADVANCE(56);
      if (lookahead == 'u') ADVANCE(68);
      if (lookahead == '{') ADVANCE(79);
      if (lookahead == '}') ADVANCE(80);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('D' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(117);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(116);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(15);
      END_STATE();
    case 2:
      if (lookahead == '\n') SKIP(15);
      if (lookahead == '\r') SKIP(1);
      END_STATE();
    case 3:
      if (lookahead == '\n') SKIP(8);
      END_STATE();
    case 4:
      if (lookahead == '\n') SKIP(8);
      if (lookahead == '\r') SKIP(3);
      END_STATE();
    case 5:
      if (lookahead == '\n') SKIP(16);
      END_STATE();
    case 6:
      if (lookahead == '\n') SKIP(16);
      if (lookahead == '\r') SKIP(5);
      END_STATE();
    case 7:
      if (lookahead == '\r') ADVANCE(141);
      if (lookahead == '\\') ADVANCE(139);
      if (lookahead != 0) ADVANCE(140);
      END_STATE();
    case 8:
      if (lookahead == '(') ADVANCE(103);
      if (lookahead == ')') ADVANCE(104);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '0') ADVANCE(113);
      if (lookahead == '1') ADVANCE(114);
      if (lookahead == '\\') SKIP(4);
      if (lookahead == 'm') ADVANCE(66);
      if (lookahead == 'n') ADVANCE(67);
      if (lookahead == 's') ADVANCE(143);
      if (lookahead == 't') ADVANCE(56);
      if (lookahead == 'u') ADVANCE(68);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(8);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(116);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(117);
      END_STATE();
    case 9:
      if (lookahead == '(') ADVANCE(103);
      if (lookahead == ')') ADVANCE(104);
      if (lookahead == '/') ADVANCE(97);
      if (lookahead == '\\') ADVANCE(93);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '`') ADVANCE(102);
      END_STATE();
    case 10:
      if (lookahead == '*') ADVANCE(12);
      if (lookahead == '/') ADVANCE(140);
      END_STATE();
    case 11:
      if (lookahead == '*') ADVANCE(11);
      if (lookahead == '/') ADVANCE(138);
      if (lookahead != 0) ADVANCE(12);
      END_STATE();
    case 12:
      if (lookahead == '*') ADVANCE(11);
      if (lookahead != 0) ADVANCE(12);
      END_STATE();
    case 13:
      if (lookahead == '-') ADVANCE(105);
      END_STATE();
    case 14:
      if (lookahead == '-') ADVANCE(90);
      if (lookahead == '/') ADVANCE(86);
      if (lookahead == '\\') ADVANCE(81);
      if (lookahead == '{') ADVANCE(79);
      if (lookahead == '}') ADVANCE(80);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(89);
      if (lookahead != 0 &&
          lookahead != '`') ADVANCE(92);
      END_STATE();
    case 15:
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '\\') SKIP(2);
      if (lookahead == ']') ADVANCE(133);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(15);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(136);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(135);
      END_STATE();
    case 16:
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '\\') SKIP(6);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(77);
      END_STATE();
    case 17:
      if (lookahead == 'A') ADVANCE(78);
      END_STATE();
    case 18:
      if (lookahead == 'A') ADVANCE(31);
      if (lookahead == 'I') ADVANCE(27);
      END_STATE();
    case 19:
      if (lookahead == 'C') ADVANCE(46);
      END_STATE();
    case 20:
      if (lookahead == 'D') ADVANCE(111);
      END_STATE();
    case 21:
      if (lookahead == 'E') ADVANCE(45);
      END_STATE();
    case 22:
      if (lookahead == 'E') ADVANCE(109);
      END_STATE();
    case 23:
      if (lookahead == 'E') ADVANCE(107);
      END_STATE();
    case 24:
      if (lookahead == 'H') ADVANCE(33);
      END_STATE();
    case 25:
      if (lookahead == 'I') ADVANCE(34);
      END_STATE();
    case 26:
      if (lookahead == 'L') ADVANCE(110);
      END_STATE();
    case 27:
      if (lookahead == 'L') ADVANCE(26);
      END_STATE();
    case 28:
      if (lookahead == 'M') ADVANCE(106);
      END_STATE();
    case 29:
      if (lookahead == 'N') ADVANCE(128);
      END_STATE();
    case 30:
      if (lookahead == 'N') ADVANCE(49);
      END_STATE();
    case 31:
      if (lookahead == 'N') ADVANCE(43);
      END_STATE();
    case 32:
      if (lookahead == 'O') ADVANCE(38);
      END_STATE();
    case 33:
      if (lookahead == 'O') ADVANCE(41);
      END_STATE();
    case 34:
      if (lookahead == 'O') ADVANCE(29);
      END_STATE();
    case 35:
      if (lookahead == 'O') ADVANCE(48);
      END_STATE();
    case 36:
      if (lookahead == 'O') ADVANCE(44);
      END_STATE();
    case 37:
      if (lookahead == 'P') ADVANCE(28);
      END_STATE();
    case 38:
      if (lookahead == 'P') ADVANCE(51);
      END_STATE();
    case 39:
      if (lookahead == 'P') ADVANCE(36);
      END_STATE();
    case 40:
      if (lookahead == 'R') ADVANCE(18);
      END_STATE();
    case 41:
      if (lookahead == 'R') ADVANCE(20);
      END_STATE();
    case 42:
      if (lookahead == 'R') ADVANCE(32);
      END_STATE();
    case 43:
      if (lookahead == 'S') ADVANCE(39);
      END_STATE();
    case 44:
      if (lookahead == 'S') ADVANCE(23);
      END_STATE();
    case 45:
      if (lookahead == 'S') ADVANCE(47);
      END_STATE();
    case 46:
      if (lookahead == 'T') ADVANCE(25);
      END_STATE();
    case 47:
      if (lookahead == 'T') ADVANCE(112);
      END_STATE();
    case 48:
      if (lookahead == 'T') ADVANCE(22);
      END_STATE();
    case 49:
      if (lookahead == 'T') ADVANCE(42);
      END_STATE();
    case 50:
      if (lookahead == 'U') ADVANCE(17);
      END_STATE();
    case 51:
      if (lookahead == 'Y') ADVANCE(108);
      END_STATE();
    case 52:
      if (lookahead == 'a') ADVANCE(60);
      END_STATE();
    case 53:
      if (lookahead == 'a') ADVANCE(69);
      END_STATE();
    case 54:
      if (lookahead == 'd') ADVANCE(130);
      END_STATE();
    case 55:
      if (lookahead == 'e') ADVANCE(62);
      END_STATE();
    case 56:
      if (lookahead == 'e') ADVANCE(61);
      END_STATE();
    case 57:
      if (lookahead == 'e') ADVANCE(58);
      END_STATE();
    case 58:
      if (lookahead == 'l') ADVANCE(53);
      END_STATE();
    case 59:
      if (lookahead == 'l') ADVANCE(134);
      END_STATE();
    case 60:
      if (lookahead == 'l') ADVANCE(59);
      END_STATE();
    case 61:
      if (lookahead == 'm') ADVANCE(65);
      END_STATE();
    case 62:
      if (lookahead == 'n') ADVANCE(54);
      END_STATE();
    case 63:
      if (lookahead == 'o') ADVANCE(142);
      END_STATE();
    case 64:
      if (lookahead == 'o') ADVANCE(131);
      END_STATE();
    case 65:
      if (lookahead == 'p') ADVANCE(63);
      END_STATE();
    case 66:
      if (lookahead == 's') ADVANCE(145);
      END_STATE();
    case 67:
      if (lookahead == 's') ADVANCE(147);
      END_STATE();
    case 68:
      if (lookahead == 's') ADVANCE(146);
      END_STATE();
    case 69:
      if (lookahead == 'y') ADVANCE(129);
      END_STATE();
    case 70:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(137);
      END_STATE();
    case 71:
      if (eof) ADVANCE(76);
      if (lookahead == '\n') SKIP(0);
      END_STATE();
    case 72:
      if (eof) ADVANCE(76);
      if (lookahead == '\n') SKIP(0);
      if (lookahead == '\r') SKIP(71);
      END_STATE();
    case 73:
      if (eof) ADVANCE(76);
      if (lookahead == '\n') SKIP(75);
      END_STATE();
    case 74:
      if (eof) ADVANCE(76);
      if (lookahead == '\n') SKIP(75);
      if (lookahead == '\r') SKIP(73);
      END_STATE();
    case 75:
      if (eof) ADVANCE(76);
      ADVANCE_MAP(
        '#', 124,
        '/', 10,
        '1', 127,
        'A', 19,
        'B', 37,
        'C', 24,
        'E', 30,
        'L', 50,
        'N', 35,
        'R', 21,
        'T', 40,
        '[', 132,
      );
      if (lookahead == '\\') SKIP(74);
      if (lookahead == 'b') ADVANCE(125);
      if (lookahead == 'c') ADVANCE(52);
      if (lookahead == 'd') ADVANCE(57);
      if (lookahead == 's') ADVANCE(55);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(75);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(126);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(sym_keyword);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(77);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_LUA);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(89);
      if (lookahead == '\r') ADVANCE(82);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(92);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(89);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(92);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(92);
      if (lookahead == '\\') ADVANCE(85);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(140);
      if (lookahead != 0) ADVANCE(83);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(92);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(105);
      if (lookahead != 0) ADVANCE(84);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\r') ADVANCE(91);
      if (lookahead == '\\') ADVANCE(85);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(140);
      if (lookahead != 0) ADVANCE(83);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '*') ADVANCE(88);
      if (lookahead == '/') ADVANCE(83);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(92);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '*') ADVANCE(87);
      if (lookahead == '/') ADVANCE(92);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(12);
      if (lookahead != 0) ADVANCE(88);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '*') ADVANCE(87);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(12);
      if (lookahead != 0) ADVANCE(88);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '-') ADVANCE(90);
      if (lookahead == '/') ADVANCE(86);
      if (lookahead == '\\') ADVANCE(81);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(89);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(92);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '-') ADVANCE(84);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(92);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\\') ADVANCE(85);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(140);
      if (lookahead != 0) ADVANCE(83);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(92);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\n') ADVANCE(100);
      if (lookahead == '\r') ADVANCE(94);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(102);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\n') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(102);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\n') ADVANCE(102);
      if (lookahead == '\\') ADVANCE(96);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(140);
      if (lookahead != 0) ADVANCE(95);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\r') ADVANCE(101);
      if (lookahead == '\\') ADVANCE(96);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(140);
      if (lookahead != 0) ADVANCE(95);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '*') ADVANCE(99);
      if (lookahead == '/') ADVANCE(95);
      if (lookahead != 0 &&
          (lookahead < '(' || '*' < lookahead) &&
          lookahead != '`') ADVANCE(102);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '*') ADVANCE(98);
      if (lookahead == '/') ADVANCE(102);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(12);
      if (lookahead != 0) ADVANCE(99);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '*') ADVANCE(98);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(12);
      if (lookahead != 0) ADVANCE(99);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '/') ADVANCE(97);
      if (lookahead == '\\') ADVANCE(93);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(102);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\\') ADVANCE(96);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(140);
      if (lookahead != 0) ADVANCE(95);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(102);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(sym_lua_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(105);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(anon_sym_BPM);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(anon_sym_TRANSPOSE);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_ENTROPY);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_NOTE);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_TRILL);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(anon_sym_CHORD);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(anon_sym_REST);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(sym_midi);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(sym_midi);
      if (lookahead == '2') ADVANCE(115);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(116);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(113);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(113);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(113);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(sym_pitchname);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'C') ADVANCE(46);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'H') ADVANCE(33);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'N') ADVANCE(49);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'P') ADVANCE(28);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'a') ADVANCE(60);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'e') ADVANCE(58);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_b);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(sym_octave);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(sym_octave);
      if (('0' <= lookahead && lookahead <= '2')) ADVANCE(126);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(anon_sym_ACTION);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(anon_sym_delay);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(anon_sym_send);
      if (lookahead == 't') ADVANCE(64);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(anon_sym_sendto);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(anon_sym_call);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(aux_sym_actionKey_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(135);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(70);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(136);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(aux_sym_number_token2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(137);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\r') ADVANCE(141);
      if (lookahead == '\\') ADVANCE(139);
      if (lookahead != 0) ADVANCE(140);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(7);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(140);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(7);
      if (lookahead != 0) ADVANCE(140);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(anon_sym_tempo);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(anon_sym_s);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(anon_sym_s);
      if (lookahead == 'e') ADVANCE(62);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(anon_sym_ms);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(anon_sym_us);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(anon_sym_ns);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 75},
  [2] = {.lex_state = 75},
  [3] = {.lex_state = 75},
  [4] = {.lex_state = 75},
  [5] = {.lex_state = 75},
  [6] = {.lex_state = 75},
  [7] = {.lex_state = 75},
  [8] = {.lex_state = 75},
  [9] = {.lex_state = 75},
  [10] = {.lex_state = 75},
  [11] = {.lex_state = 75},
  [12] = {.lex_state = 75},
  [13] = {.lex_state = 75},
  [14] = {.lex_state = 75},
  [15] = {.lex_state = 75},
  [16] = {.lex_state = 75},
  [17] = {.lex_state = 75},
  [18] = {.lex_state = 75},
  [19] = {.lex_state = 75},
  [20] = {.lex_state = 75},
  [21] = {.lex_state = 75},
  [22] = {.lex_state = 75},
  [23] = {.lex_state = 75},
  [24] = {.lex_state = 15},
  [25] = {.lex_state = 15},
  [26] = {.lex_state = 15},
  [27] = {.lex_state = 75},
  [28] = {.lex_state = 8},
  [29] = {.lex_state = 14},
  [30] = {.lex_state = 8},
  [31] = {.lex_state = 14},
  [32] = {.lex_state = 8},
  [33] = {.lex_state = 8},
  [34] = {.lex_state = 8},
  [35] = {.lex_state = 75},
  [36] = {.lex_state = 75},
  [37] = {.lex_state = 14},
  [38] = {.lex_state = 14},
  [39] = {.lex_state = 9},
  [40] = {.lex_state = 8},
  [41] = {.lex_state = 75},
  [42] = {.lex_state = 9},
  [43] = {.lex_state = 75},
  [44] = {.lex_state = 15},
  [45] = {.lex_state = 9},
  [46] = {.lex_state = 15},
  [47] = {.lex_state = 15},
  [48] = {.lex_state = 14},
  [49] = {.lex_state = 15},
  [50] = {.lex_state = 15},
  [51] = {.lex_state = 14},
  [52] = {.lex_state = 15},
  [53] = {.lex_state = 9},
  [54] = {.lex_state = 8},
  [55] = {.lex_state = 9},
  [56] = {.lex_state = 8},
  [57] = {.lex_state = 8},
  [58] = {.lex_state = 75},
  [59] = {.lex_state = 75},
  [60] = {.lex_state = 9},
  [61] = {.lex_state = 8},
  [62] = {.lex_state = 15},
  [63] = {.lex_state = 15},
  [64] = {.lex_state = 16},
  [65] = {.lex_state = 16},
  [66] = {.lex_state = 15},
  [67] = {.lex_state = 15},
  [68] = {.lex_state = 15},
  [69] = {.lex_state = 15},
  [70] = {.lex_state = 15},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 75},
  [76] = {.lex_state = 75},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 75},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_LUA] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym_lua_comment] = ACTIONS(1),
    [anon_sym_BPM] = ACTIONS(1),
    [anon_sym_TRANSPOSE] = ACTIONS(1),
    [anon_sym_ENTROPY] = ACTIONS(1),
    [anon_sym_NOTE] = ACTIONS(1),
    [anon_sym_TRILL] = ACTIONS(1),
    [anon_sym_CHORD] = ACTIONS(1),
    [anon_sym_REST] = ACTIONS(1),
    [sym_midi] = ACTIONS(1),
    [sym_pitchname] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [anon_sym_b] = ACTIONS(1),
    [sym_octave] = ACTIONS(1),
    [anon_sym_ACTION] = ACTIONS(1),
    [anon_sym_delay] = ACTIONS(1),
    [anon_sym_send] = ACTIONS(1),
    [anon_sym_sendto] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_call] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [anon_sym_tempo] = ACTIONS(1),
    [anon_sym_s] = ACTIONS(1),
    [anon_sym_ms] = ACTIONS(1),
    [anon_sym_us] = ACTIONS(1),
    [anon_sym_ns] = ACTIONS(1),
  },
  [1] = {
    [sym_score] = STATE(72),
    [sym__statement] = STATE(3),
    [sym_LUA] = STATE(3),
    [sym_CONFIG] = STATE(3),
    [sym_configId] = STATE(47),
    [sym_numberConfig] = STATE(22),
    [sym_EVENT] = STATE(3),
    [sym_pitchEventId] = STATE(28),
    [sym_restEventId] = STATE(46),
    [sym_pitchEvent] = STATE(16),
    [sym_rest] = STATE(16),
    [aux_sym_score_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_LUA] = ACTIONS(7),
    [anon_sym_BPM] = ACTIONS(9),
    [anon_sym_TRANSPOSE] = ACTIONS(9),
    [anon_sym_ENTROPY] = ACTIONS(9),
    [anon_sym_NOTE] = ACTIONS(11),
    [anon_sym_TRILL] = ACTIONS(11),
    [anon_sym_CHORD] = ACTIONS(11),
    [anon_sym_REST] = ACTIONS(13),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      ts_builtin_sym_end,
    ACTIONS(17), 1,
      anon_sym_LUA,
    ACTIONS(26), 1,
      anon_sym_REST,
    STATE(22), 1,
      sym_numberConfig,
    STATE(28), 1,
      sym_pitchEventId,
    STATE(46), 1,
      sym_restEventId,
    STATE(47), 1,
      sym_configId,
    STATE(16), 2,
      sym_pitchEvent,
      sym_rest,
    ACTIONS(20), 3,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
    ACTIONS(23), 3,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
    STATE(2), 5,
      sym__statement,
      sym_LUA,
      sym_CONFIG,
      sym_EVENT,
      aux_sym_score_repeat1,
  [46] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_LUA,
    ACTIONS(13), 1,
      anon_sym_REST,
    ACTIONS(29), 1,
      ts_builtin_sym_end,
    STATE(22), 1,
      sym_numberConfig,
    STATE(28), 1,
      sym_pitchEventId,
    STATE(46), 1,
      sym_restEventId,
    STATE(47), 1,
      sym_configId,
    STATE(16), 2,
      sym_pitchEvent,
      sym_rest,
    ACTIONS(9), 3,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
    ACTIONS(11), 3,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
    STATE(2), 5,
      sym__statement,
      sym_LUA,
      sym_CONFIG,
      sym_EVENT,
      aux_sym_score_repeat1,
  [92] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 1,
      anon_sym_ACTION,
    ACTIONS(35), 1,
      anon_sym_delay,
    ACTIONS(37), 1,
      anon_sym_send,
    ACTIONS(39), 1,
      anon_sym_sendto,
    ACTIONS(41), 1,
      anon_sym_call,
    STATE(17), 1,
      sym_ACTION,
    STATE(35), 1,
      sym_timedAction,
    STATE(5), 2,
      sym_exec,
      aux_sym_ACTION_repeat1,
    ACTIONS(31), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [132] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_send,
    ACTIONS(39), 1,
      anon_sym_sendto,
    ACTIONS(41), 1,
      anon_sym_call,
    STATE(8), 2,
      sym_exec,
      aux_sym_ACTION_repeat1,
    ACTIONS(43), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [160] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_send,
    ACTIONS(39), 1,
      anon_sym_sendto,
    ACTIONS(41), 1,
      anon_sym_call,
    STATE(8), 2,
      sym_exec,
      aux_sym_ACTION_repeat1,
    ACTIONS(45), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [188] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      anon_sym_send,
    ACTIONS(47), 13,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [210] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(53), 1,
      anon_sym_send,
    ACTIONS(56), 1,
      anon_sym_sendto,
    ACTIONS(59), 1,
      anon_sym_call,
    STATE(8), 2,
      sym_exec,
      aux_sym_ACTION_repeat1,
    ACTIONS(51), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [238] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_send,
    ACTIONS(39), 1,
      anon_sym_sendto,
    ACTIONS(41), 1,
      anon_sym_call,
    STATE(8), 2,
      sym_exec,
      aux_sym_ACTION_repeat1,
    ACTIONS(62), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [266] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(66), 1,
      anon_sym_send,
    ACTIONS(64), 13,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [288] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_send,
    ACTIONS(68), 12,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_sendto,
      anon_sym_LBRACK,
      anon_sym_call,
  [309] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 1,
      anon_sym_send,
    ACTIONS(76), 1,
      anon_sym_LBRACK,
    ACTIONS(72), 11,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_sendto,
      anon_sym_call,
  [332] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(80), 1,
      anon_sym_send,
    ACTIONS(78), 11,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_sendto,
      anon_sym_call,
  [352] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(84), 1,
      anon_sym_send,
    ACTIONS(82), 11,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_sendto,
      anon_sym_call,
  [372] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 1,
      anon_sym_send,
    ACTIONS(72), 11,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_sendto,
      anon_sym_call,
  [392] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(86), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [407] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(88), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [422] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(90), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [437] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(92), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [452] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(94), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [467] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(96), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [482] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(98), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [497] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(100), 9,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
  [512] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      anon_sym_RBRACK,
    ACTIONS(104), 1,
      aux_sym_actionKey_token1,
    ACTIONS(106), 1,
      aux_sym_number_token1,
    ACTIONS(108), 1,
      aux_sym_number_token2,
    STATE(26), 2,
      sym_pdargs,
      aux_sym_exec_repeat1,
    STATE(52), 2,
      sym_number,
      sym_symbol,
  [536] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(110), 1,
      anon_sym_RBRACK,
    ACTIONS(112), 1,
      aux_sym_actionKey_token1,
    ACTIONS(115), 1,
      aux_sym_number_token1,
    ACTIONS(118), 1,
      aux_sym_number_token2,
    STATE(25), 2,
      sym_pdargs,
      aux_sym_exec_repeat1,
    STATE(52), 2,
      sym_number,
      sym_symbol,
  [560] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(104), 1,
      aux_sym_actionKey_token1,
    ACTIONS(106), 1,
      aux_sym_number_token1,
    ACTIONS(108), 1,
      aux_sym_number_token2,
    ACTIONS(121), 1,
      anon_sym_RBRACK,
    STATE(25), 2,
      sym_pdargs,
      aux_sym_exec_repeat1,
    STATE(52), 2,
      sym_number,
      sym_symbol,
  [584] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(35), 1,
      anon_sym_delay,
    ACTIONS(37), 1,
      anon_sym_send,
    ACTIONS(39), 1,
      anon_sym_sendto,
    ACTIONS(41), 1,
      anon_sym_call,
    STATE(36), 1,
      sym_timedAction,
    STATE(6), 2,
      sym_exec,
      aux_sym_ACTION_repeat1,
  [607] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_LPAREN,
    ACTIONS(125), 1,
      sym_midi,
    ACTIONS(127), 1,
      sym_pitchname,
    STATE(63), 1,
      sym_noteName,
    STATE(50), 2,
      sym_pitches,
      sym_pitch,
  [627] = 6,
    ACTIONS(129), 1,
      anon_sym_LBRACE,
    ACTIONS(131), 1,
      anon_sym_RBRACE,
    ACTIONS(135), 1,
      sym_comment,
    STATE(37), 1,
      aux_sym_lua_body_repeat1,
    STATE(73), 1,
      sym_lua_body,
    ACTIONS(133), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [647] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(137), 1,
      anon_sym_RPAREN,
    ACTIONS(139), 1,
      sym_midi,
    ACTIONS(142), 1,
      sym_pitchname,
    STATE(61), 1,
      sym_noteName,
    STATE(30), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [667] = 6,
    ACTIONS(129), 1,
      anon_sym_LBRACE,
    ACTIONS(135), 1,
      sym_comment,
    ACTIONS(145), 1,
      anon_sym_RBRACE,
    STATE(37), 1,
      aux_sym_lua_body_repeat1,
    STATE(77), 1,
      sym_lua_body,
    ACTIONS(133), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [687] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(147), 1,
      anon_sym_RPAREN,
    ACTIONS(149), 1,
      sym_midi,
    ACTIONS(151), 1,
      sym_pitchname,
    STATE(61), 1,
      sym_noteName,
    STATE(30), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [707] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(59), 1,
      sym_timeUnit,
    ACTIONS(153), 5,
      anon_sym_tempo,
      anon_sym_s,
      anon_sym_ms,
      anon_sym_us,
      anon_sym_ns,
  [721] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(64), 5,
      anon_sym_tempo,
      anon_sym_s,
      anon_sym_ms,
      anon_sym_us,
      anon_sym_ns,
  [732] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_send,
    ACTIONS(39), 1,
      anon_sym_sendto,
    ACTIONS(41), 1,
      anon_sym_call,
    STATE(6), 2,
      sym_exec,
      aux_sym_ACTION_repeat1,
  [749] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_send,
    ACTIONS(39), 1,
      anon_sym_sendto,
    ACTIONS(41), 1,
      anon_sym_call,
    STATE(9), 2,
      sym_exec,
      aux_sym_ACTION_repeat1,
  [766] = 5,
    ACTIONS(129), 1,
      anon_sym_LBRACE,
    ACTIONS(135), 1,
      sym_comment,
    ACTIONS(155), 1,
      anon_sym_RBRACE,
    STATE(38), 1,
      aux_sym_lua_body_repeat1,
    ACTIONS(157), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [783] = 5,
    ACTIONS(135), 1,
      sym_comment,
    ACTIONS(159), 1,
      anon_sym_LBRACE,
    ACTIONS(162), 1,
      anon_sym_RBRACE,
    STATE(38), 1,
      aux_sym_lua_body_repeat1,
    ACTIONS(164), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [800] = 6,
    ACTIONS(135), 1,
      sym_comment,
    ACTIONS(167), 1,
      aux_sym_lua_call_token1,
    ACTIONS(169), 1,
      anon_sym_LPAREN,
    ACTIONS(171), 1,
      anon_sym_RPAREN,
    STATE(45), 1,
      aux_sym_lua_call_repeat1,
    STATE(74), 1,
      sym_lua_call,
  [819] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(149), 1,
      sym_midi,
    ACTIONS(151), 1,
      sym_pitchname,
    STATE(61), 1,
      sym_noteName,
    STATE(32), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [836] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(175), 1,
      sym_octave,
    STATE(76), 1,
      sym_alteration,
    ACTIONS(173), 2,
      anon_sym_POUND,
      anon_sym_b,
  [850] = 5,
    ACTIONS(135), 1,
      sym_comment,
    ACTIONS(167), 1,
      aux_sym_lua_call_token1,
    ACTIONS(169), 1,
      anon_sym_LPAREN,
    STATE(45), 1,
      aux_sym_lua_call_repeat1,
    STATE(71), 1,
      sym_lua_call,
  [866] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(177), 1,
      sym_octave,
    STATE(80), 1,
      sym_alteration,
    ACTIONS(173), 2,
      anon_sym_POUND,
      anon_sym_b,
  [880] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(66), 1,
      aux_sym_number_token1,
    ACTIONS(64), 3,
      anon_sym_RBRACK,
      aux_sym_actionKey_token1,
      aux_sym_number_token2,
  [892] = 5,
    ACTIONS(135), 1,
      sym_comment,
    ACTIONS(169), 1,
      anon_sym_LPAREN,
    ACTIONS(179), 1,
      aux_sym_lua_call_token1,
    ACTIONS(181), 1,
      anon_sym_RPAREN,
    STATE(53), 1,
      aux_sym_lua_call_repeat1,
  [908] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(183), 1,
      aux_sym_number_token1,
    ACTIONS(185), 1,
      aux_sym_number_token2,
    STATE(7), 1,
      sym_number,
    STATE(20), 1,
      sym_duration,
  [924] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(183), 1,
      aux_sym_number_token1,
    ACTIONS(185), 1,
      aux_sym_number_token2,
    STATE(18), 1,
      sym_number,
    STATE(21), 1,
      sym_numberSet,
  [940] = 2,
    ACTIONS(135), 1,
      sym_comment,
    ACTIONS(187), 4,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [950] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(191), 1,
      aux_sym_number_token1,
    ACTIONS(189), 3,
      anon_sym_RBRACK,
      aux_sym_actionKey_token1,
      aux_sym_number_token2,
  [962] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(183), 1,
      aux_sym_number_token1,
    ACTIONS(185), 1,
      aux_sym_number_token2,
    STATE(4), 1,
      sym_duration,
    STATE(7), 1,
      sym_number,
  [978] = 2,
    ACTIONS(135), 1,
      sym_comment,
    ACTIONS(162), 4,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [988] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 1,
      aux_sym_number_token1,
    ACTIONS(193), 3,
      anon_sym_RBRACK,
      aux_sym_actionKey_token1,
      aux_sym_number_token2,
  [1000] = 5,
    ACTIONS(135), 1,
      sym_comment,
    ACTIONS(197), 1,
      aux_sym_lua_call_token1,
    ACTIONS(200), 1,
      anon_sym_LPAREN,
    ACTIONS(203), 1,
      anon_sym_RPAREN,
    STATE(53), 1,
      aux_sym_lua_call_repeat1,
  [1016] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(205), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [1025] = 2,
    ACTIONS(135), 1,
      sym_comment,
    ACTIONS(203), 3,
      aux_sym_lua_call_token1,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [1034] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(207), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [1043] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(209), 3,
      anon_sym_LPAREN,
      sym_midi,
      sym_pitchname,
  [1052] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(211), 1,
      anon_sym_send,
    ACTIONS(213), 2,
      anon_sym_sendto,
      anon_sym_call,
  [1063] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(215), 1,
      anon_sym_send,
    ACTIONS(217), 2,
      anon_sym_sendto,
      anon_sym_call,
  [1074] = 2,
    ACTIONS(135), 1,
      sym_comment,
    ACTIONS(219), 3,
      aux_sym_lua_call_token1,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [1083] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(221), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [1092] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(223), 1,
      aux_sym_number_token1,
    ACTIONS(225), 1,
      aux_sym_number_token2,
    STATE(33), 1,
      sym_number,
  [1105] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(221), 1,
      aux_sym_number_token2,
    ACTIONS(227), 1,
      aux_sym_number_token1,
  [1115] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(229), 1,
      sym_keyword,
    STATE(12), 1,
      sym_receiver,
  [1125] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(229), 1,
      sym_keyword,
    STATE(15), 1,
      sym_receiver,
  [1135] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(231), 1,
      aux_sym_number_token1,
    ACTIONS(233), 1,
      aux_sym_number_token2,
  [1145] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(205), 1,
      aux_sym_number_token2,
    ACTIONS(235), 1,
      aux_sym_number_token1,
  [1155] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(237), 1,
      aux_sym_number_token1,
    ACTIONS(239), 1,
      aux_sym_number_token2,
  [1165] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(241), 1,
      aux_sym_number_token1,
    ACTIONS(243), 1,
      aux_sym_number_token2,
  [1175] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(207), 1,
      aux_sym_number_token2,
    ACTIONS(245), 1,
      aux_sym_number_token1,
  [1185] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      anon_sym_RPAREN,
  [1192] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(247), 1,
      ts_builtin_sym_end,
  [1199] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(249), 1,
      anon_sym_RBRACE,
  [1206] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(251), 1,
      anon_sym_RPAREN,
  [1213] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(253), 1,
      sym_octave,
  [1220] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(255), 1,
      sym_octave,
  [1227] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(257), 1,
      anon_sym_RBRACE,
  [1234] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(259), 1,
      anon_sym_LBRACE,
  [1241] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(261), 1,
      anon_sym_LPAREN,
  [1248] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(263), 1,
      sym_octave,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 46,
  [SMALL_STATE(4)] = 92,
  [SMALL_STATE(5)] = 132,
  [SMALL_STATE(6)] = 160,
  [SMALL_STATE(7)] = 188,
  [SMALL_STATE(8)] = 210,
  [SMALL_STATE(9)] = 238,
  [SMALL_STATE(10)] = 266,
  [SMALL_STATE(11)] = 288,
  [SMALL_STATE(12)] = 309,
  [SMALL_STATE(13)] = 332,
  [SMALL_STATE(14)] = 352,
  [SMALL_STATE(15)] = 372,
  [SMALL_STATE(16)] = 392,
  [SMALL_STATE(17)] = 407,
  [SMALL_STATE(18)] = 422,
  [SMALL_STATE(19)] = 437,
  [SMALL_STATE(20)] = 452,
  [SMALL_STATE(21)] = 467,
  [SMALL_STATE(22)] = 482,
  [SMALL_STATE(23)] = 497,
  [SMALL_STATE(24)] = 512,
  [SMALL_STATE(25)] = 536,
  [SMALL_STATE(26)] = 560,
  [SMALL_STATE(27)] = 584,
  [SMALL_STATE(28)] = 607,
  [SMALL_STATE(29)] = 627,
  [SMALL_STATE(30)] = 647,
  [SMALL_STATE(31)] = 667,
  [SMALL_STATE(32)] = 687,
  [SMALL_STATE(33)] = 707,
  [SMALL_STATE(34)] = 721,
  [SMALL_STATE(35)] = 732,
  [SMALL_STATE(36)] = 749,
  [SMALL_STATE(37)] = 766,
  [SMALL_STATE(38)] = 783,
  [SMALL_STATE(39)] = 800,
  [SMALL_STATE(40)] = 819,
  [SMALL_STATE(41)] = 836,
  [SMALL_STATE(42)] = 850,
  [SMALL_STATE(43)] = 866,
  [SMALL_STATE(44)] = 880,
  [SMALL_STATE(45)] = 892,
  [SMALL_STATE(46)] = 908,
  [SMALL_STATE(47)] = 924,
  [SMALL_STATE(48)] = 940,
  [SMALL_STATE(49)] = 950,
  [SMALL_STATE(50)] = 962,
  [SMALL_STATE(51)] = 978,
  [SMALL_STATE(52)] = 988,
  [SMALL_STATE(53)] = 1000,
  [SMALL_STATE(54)] = 1016,
  [SMALL_STATE(55)] = 1025,
  [SMALL_STATE(56)] = 1034,
  [SMALL_STATE(57)] = 1043,
  [SMALL_STATE(58)] = 1052,
  [SMALL_STATE(59)] = 1063,
  [SMALL_STATE(60)] = 1074,
  [SMALL_STATE(61)] = 1083,
  [SMALL_STATE(62)] = 1092,
  [SMALL_STATE(63)] = 1105,
  [SMALL_STATE(64)] = 1115,
  [SMALL_STATE(65)] = 1125,
  [SMALL_STATE(66)] = 1135,
  [SMALL_STATE(67)] = 1145,
  [SMALL_STATE(68)] = 1155,
  [SMALL_STATE(69)] = 1165,
  [SMALL_STATE(70)] = 1175,
  [SMALL_STATE(71)] = 1185,
  [SMALL_STATE(72)] = 1192,
  [SMALL_STATE(73)] = 1199,
  [SMALL_STATE(74)] = 1206,
  [SMALL_STATE(75)] = 1213,
  [SMALL_STATE(76)] = 1220,
  [SMALL_STATE(77)] = 1227,
  [SMALL_STATE(78)] = 1234,
  [SMALL_STATE(79)] = 1241,
  [SMALL_STATE(80)] = 1248,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_score, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0),
  [17] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(78),
  [20] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(68),
  [23] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(57),
  [26] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(66),
  [29] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_score, 1, 0, 0),
  [31] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEvent, 3, 0, 0),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(65),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 1, 0, 0),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 2, 0, 0),
  [47] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_duration, 1, 0, 0),
  [49] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_duration, 1, 0, 0),
  [51] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_ACTION_repeat1, 2, 0, 0),
  [53] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_ACTION_repeat1, 2, 0, 0), SHIFT_REPEAT(65),
  [56] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_ACTION_repeat1, 2, 0, 0), SHIFT_REPEAT(64),
  [59] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_ACTION_repeat1, 2, 0, 0), SHIFT_REPEAT(79),
  [62] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 3, 0, 0),
  [64] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_number, 1, 0, 0),
  [66] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_number, 1, 0, 0),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_receiver, 1, 0, 0),
  [70] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_receiver, 1, 0, 0),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exec, 2, 0, 0),
  [74] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_exec, 2, 0, 0),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [78] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exec, 5, 0, 0),
  [80] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_exec, 5, 0, 0),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exec, 4, 0, 0),
  [84] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_exec, 4, 0, 0),
  [86] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_EVENT, 1, 0, 0),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEvent, 4, 0, 0),
  [90] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberSet, 1, 0, 0),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_LUA, 3, 0, 0),
  [94] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rest, 2, 0, 0),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberConfig, 2, 0, 0),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_CONFIG, 1, 0, 0),
  [100] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_LUA, 4, 0, 0),
  [102] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [106] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [108] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [110] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_exec_repeat1, 2, 0, 0),
  [112] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_exec_repeat1, 2, 0, 0), SHIFT_REPEAT(49),
  [115] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_exec_repeat1, 2, 0, 0), SHIFT_REPEAT(44),
  [118] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_exec_repeat1, 2, 0, 0), SHIFT_REPEAT(44),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [129] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [131] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [133] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [135] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0),
  [139] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(61),
  [142] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(43),
  [145] = {.entry = {.count = 1, .reusable = false}}, SHIFT(51),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [155] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lua_body, 1, 0, 0),
  [157] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [159] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 2, 0, 0), SHIFT_REPEAT(31),
  [162] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 2, 0, 0),
  [164] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 2, 0, 0), SHIFT_REPEAT(38),
  [167] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [169] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [171] = {.entry = {.count = 1, .reusable = false}}, SHIFT(55),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [177] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [179] = {.entry = {.count = 1, .reusable = false}}, SHIFT(53),
  [181] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lua_call, 1, 0, 0),
  [183] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [185] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [187] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 3, 0, 0),
  [189] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_symbol, 1, 0, 0),
  [191] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_symbol, 1, 0, 0),
  [193] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pdargs, 1, 0, 0),
  [195] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pdargs, 1, 0, 0),
  [197] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 2, 0, 0), SHIFT_REPEAT(53),
  [200] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 2, 0, 0), SHIFT_REPEAT(39),
  [203] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 2, 0, 0),
  [205] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_noteName, 2, 0, 0),
  [207] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_noteName, 3, 0, 0),
  [209] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEventId, 1, 0, 0),
  [211] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_timeUnit, 1, 0, 0),
  [213] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_timeUnit, 1, 0, 0),
  [215] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_timedAction, 3, 0, 0),
  [217] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_timedAction, 3, 0, 0),
  [219] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 3, 0, 0),
  [221] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitch, 1, 0, 0),
  [223] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [225] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [227] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitch, 1, 0, 0),
  [229] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [231] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_restEventId, 1, 0, 0),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_restEventId, 1, 0, 0),
  [235] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_noteName, 2, 0, 0),
  [237] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_configId, 1, 0, 0),
  [239] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_configId, 1, 0, 0),
  [241] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitches, 3, 0, 0),
  [243] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitches, 3, 0, 0),
  [245] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_noteName, 3, 0, 0),
  [247] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [249] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [251] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [253] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alteration, 1, 0, 0),
  [255] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [257] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [259] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [261] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [263] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
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
