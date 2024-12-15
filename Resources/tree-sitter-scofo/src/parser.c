#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 95
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 79
#define ALIAS_COUNT 0
#define TOKEN_COUNT 42
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
  anon_sym_EVENT = 17,
  anon_sym_timed = 18,
  anon_sym_internal = 19,
  sym_midi = 20,
  sym_pitchname = 21,
  anon_sym_POUND = 22,
  anon_sym_b = 23,
  sym_octave = 24,
  anon_sym_ACTION = 25,
  anon_sym_COMMA = 26,
  anon_sym_delay = 27,
  anon_sym_send = 28,
  anon_sym_sendto = 29,
  anon_sym_LBRACK = 30,
  anon_sym_RBRACK = 31,
  anon_sym_call = 32,
  aux_sym_actionKey_token1 = 33,
  aux_sym_number_token1 = 34,
  aux_sym_number_token2 = 35,
  sym_comment = 36,
  anon_sym_tempo = 37,
  anon_sym_s = 38,
  anon_sym_ms = 39,
  anon_sym_us = 40,
  anon_sym_ns = 41,
  sym_score = 42,
  sym__statement = 43,
  sym_LUA = 44,
  sym_lua_body = 45,
  sym_lua_call = 46,
  sym_CONFIG = 47,
  sym_configId = 48,
  sym_numberConfig = 49,
  sym_numberSet = 50,
  sym_EVENT = 51,
  sym_pitchEventId = 52,
  sym_restEventId = 53,
  sym_timeEventId = 54,
  sym_pitchEvent = 55,
  sym_restEvent = 56,
  sym_freeEvent = 57,
  sym_eventId = 58,
  sym_pitches = 59,
  sym_pitch = 60,
  sym_noteName = 61,
  sym_alteration = 62,
  sym_duration = 63,
  sym_ACTION = 64,
  sym_timedAction = 65,
  sym_exec = 66,
  sym_pdargs = 67,
  sym_receiver = 68,
  sym_number = 69,
  sym_symbol = 70,
  sym_timeUnit = 71,
  aux_sym_score_repeat1 = 72,
  aux_sym_lua_body_repeat1 = 73,
  aux_sym_lua_call_repeat1 = 74,
  aux_sym_pitchEvent_repeat1 = 75,
  aux_sym_pitches_repeat1 = 76,
  aux_sym_ACTION_repeat1 = 77,
  aux_sym_exec_repeat1 = 78,
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
  [anon_sym_EVENT] = "keyword",
  [anon_sym_timed] = "timed",
  [anon_sym_internal] = "internal",
  [sym_midi] = "midi",
  [sym_pitchname] = "pitchname",
  [anon_sym_POUND] = "#",
  [anon_sym_b] = "b",
  [sym_octave] = "octave",
  [anon_sym_ACTION] = "keyword",
  [anon_sym_COMMA] = ",",
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
  [sym_timeEventId] = "timeEventId",
  [sym_pitchEvent] = "pitchEvent",
  [sym_restEvent] = "restEvent",
  [sym_freeEvent] = "freeEvent",
  [sym_eventId] = "eventId",
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
  [aux_sym_pitchEvent_repeat1] = "pitchEvent_repeat1",
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
  [anon_sym_EVENT] = sym_keyword,
  [anon_sym_timed] = anon_sym_timed,
  [anon_sym_internal] = anon_sym_internal,
  [sym_midi] = sym_midi,
  [sym_pitchname] = sym_pitchname,
  [anon_sym_POUND] = anon_sym_POUND,
  [anon_sym_b] = anon_sym_b,
  [sym_octave] = sym_octave,
  [anon_sym_ACTION] = sym_keyword,
  [anon_sym_COMMA] = anon_sym_COMMA,
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
  [sym_timeEventId] = sym_timeEventId,
  [sym_pitchEvent] = sym_pitchEvent,
  [sym_restEvent] = sym_restEvent,
  [sym_freeEvent] = sym_freeEvent,
  [sym_eventId] = sym_eventId,
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
  [aux_sym_pitchEvent_repeat1] = aux_sym_pitchEvent_repeat1,
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
  [anon_sym_EVENT] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_timed] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_internal] = {
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
  [anon_sym_ACTION] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
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
  [sym_timeEventId] = {
    .visible = true,
    .named = true,
  },
  [sym_pitchEvent] = {
    .visible = true,
    .named = true,
  },
  [sym_restEvent] = {
    .visible = true,
    .named = true,
  },
  [sym_freeEvent] = {
    .visible = true,
    .named = true,
  },
  [sym_eventId] = {
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
  [aux_sym_pitchEvent_repeat1] = {
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
  [27] = 24,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 23,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 49,
  [51] = 24,
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
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 69,
  [78] = 78,
  [79] = 72,
  [80] = 80,
  [81] = 81,
  [82] = 68,
  [83] = 83,
  [84] = 84,
  [85] = 85,
  [86] = 86,
  [87] = 87,
  [88] = 88,
  [89] = 89,
  [90] = 90,
  [91] = 91,
  [92] = 92,
  [93] = 93,
  [94] = 90,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(93);
      ADVANCE_MAP(
        '#', 144,
        '(', 120,
        ')', 121,
        ',', 149,
        '-', 15,
        '/', 12,
        '0', 133,
        '1', 134,
        'A', 138,
        'B', 141,
        'C', 139,
        'E', 140,
        'L', 56,
        'N', 39,
        'R', 24,
        'T', 45,
        '[', 153,
      );
      if (lookahead == '\\') SKIP(89);
      if (lookahead == ']') ADVANCE(154);
      if (lookahead == 'b') ADVANCE(145);
      if (lookahead == 'c') ADVANCE(142);
      if (lookahead == 'd') ADVANCE(143);
      if (lookahead == 'i') ADVANCE(75);
      if (lookahead == 'm') ADVANCE(82);
      if (lookahead == 'n') ADVANCE(83);
      if (lookahead == 's') ADVANCE(165);
      if (lookahead == 't') ADVANCE(64);
      if (lookahead == 'u') ADVANCE(84);
      if (lookahead == '{') ADVANCE(96);
      if (lookahead == '}') ADVANCE(97);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('D' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(137);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(136);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(17);
      END_STATE();
    case 2:
      if (lookahead == '\n') SKIP(17);
      if (lookahead == '\r') SKIP(1);
      END_STATE();
    case 3:
      if (lookahead == '\n') SKIP(18);
      END_STATE();
    case 4:
      if (lookahead == '\n') SKIP(18);
      if (lookahead == '\r') SKIP(3);
      END_STATE();
    case 5:
      if (lookahead == '\n') SKIP(10);
      END_STATE();
    case 6:
      if (lookahead == '\n') SKIP(10);
      if (lookahead == '\r') SKIP(5);
      END_STATE();
    case 7:
      if (lookahead == '\n') SKIP(19);
      END_STATE();
    case 8:
      if (lookahead == '\n') SKIP(19);
      if (lookahead == '\r') SKIP(7);
      END_STATE();
    case 9:
      if (lookahead == '\r') ADVANCE(162);
      if (lookahead == '\\') ADVANCE(160);
      if (lookahead != 0) ADVANCE(161);
      END_STATE();
    case 10:
      if (lookahead == '(') ADVANCE(120);
      if (lookahead == ')') ADVANCE(121);
      if (lookahead == '/') ADVANCE(12);
      if (lookahead == '0') ADVANCE(133);
      if (lookahead == '1') ADVANCE(134);
      if (lookahead == '\\') SKIP(6);
      if (lookahead == 'm') ADVANCE(82);
      if (lookahead == 'n') ADVANCE(83);
      if (lookahead == 's') ADVANCE(164);
      if (lookahead == 't') ADVANCE(63);
      if (lookahead == 'u') ADVANCE(84);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(10);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(136);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(137);
      END_STATE();
    case 11:
      if (lookahead == '(') ADVANCE(120);
      if (lookahead == ')') ADVANCE(121);
      if (lookahead == '/') ADVANCE(114);
      if (lookahead == '\\') ADVANCE(110);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(117);
      if (lookahead != 0 &&
          lookahead != '`') ADVANCE(119);
      END_STATE();
    case 12:
      if (lookahead == '*') ADVANCE(14);
      if (lookahead == '/') ADVANCE(161);
      END_STATE();
    case 13:
      if (lookahead == '*') ADVANCE(13);
      if (lookahead == '/') ADVANCE(159);
      if (lookahead != 0) ADVANCE(14);
      END_STATE();
    case 14:
      if (lookahead == '*') ADVANCE(13);
      if (lookahead != 0) ADVANCE(14);
      END_STATE();
    case 15:
      if (lookahead == '-') ADVANCE(122);
      END_STATE();
    case 16:
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '/') ADVANCE(103);
      if (lookahead == '\\') ADVANCE(98);
      if (lookahead == '{') ADVANCE(96);
      if (lookahead == '}') ADVANCE(97);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(106);
      if (lookahead != 0 &&
          lookahead != '`') ADVANCE(109);
      END_STATE();
    case 17:
      if (lookahead == '/') ADVANCE(12);
      if (lookahead == 'A') ADVANCE(22);
      if (lookahead == '\\') SKIP(2);
      if (lookahead == 'c') ADVANCE(58);
      if (lookahead == 'd') ADVANCE(67);
      if (lookahead == 'm') ADVANCE(82);
      if (lookahead == 'n') ADVANCE(83);
      if (lookahead == 's') ADVANCE(165);
      if (lookahead == 't') ADVANCE(63);
      if (lookahead == 'u') ADVANCE(84);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(17);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(157);
      END_STATE();
    case 18:
      if (lookahead == '/') ADVANCE(12);
      if (lookahead == '\\') SKIP(4);
      if (lookahead == ']') ADVANCE(154);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(18);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(157);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(156);
      END_STATE();
    case 19:
      if (lookahead == '/') ADVANCE(12);
      if (lookahead == '\\') SKIP(8);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(19);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 20:
      if (lookahead == 'A') ADVANCE(95);
      END_STATE();
    case 21:
      if (lookahead == 'A') ADVANCE(35);
      if (lookahead == 'I') ADVANCE(31);
      END_STATE();
    case 22:
      if (lookahead == 'C') ADVANCE(51);
      END_STATE();
    case 23:
      if (lookahead == 'D') ADVANCE(128);
      END_STATE();
    case 24:
      if (lookahead == 'E') ADVANCE(50);
      END_STATE();
    case 25:
      if (lookahead == 'E') ADVANCE(36);
      END_STATE();
    case 26:
      if (lookahead == 'E') ADVANCE(126);
      END_STATE();
    case 27:
      if (lookahead == 'E') ADVANCE(124);
      END_STATE();
    case 28:
      if (lookahead == 'H') ADVANCE(38);
      END_STATE();
    case 29:
      if (lookahead == 'I') ADVANCE(41);
      END_STATE();
    case 30:
      if (lookahead == 'L') ADVANCE(127);
      END_STATE();
    case 31:
      if (lookahead == 'L') ADVANCE(30);
      END_STATE();
    case 32:
      if (lookahead == 'M') ADVANCE(123);
      END_STATE();
    case 33:
      if (lookahead == 'N') ADVANCE(148);
      END_STATE();
    case 34:
      if (lookahead == 'N') ADVANCE(55);
      if (lookahead == 'V') ADVANCE(25);
      END_STATE();
    case 35:
      if (lookahead == 'N') ADVANCE(48);
      END_STATE();
    case 36:
      if (lookahead == 'N') ADVANCE(53);
      END_STATE();
    case 37:
      if (lookahead == 'O') ADVANCE(43);
      END_STATE();
    case 38:
      if (lookahead == 'O') ADVANCE(46);
      END_STATE();
    case 39:
      if (lookahead == 'O') ADVANCE(54);
      END_STATE();
    case 40:
      if (lookahead == 'O') ADVANCE(49);
      END_STATE();
    case 41:
      if (lookahead == 'O') ADVANCE(33);
      END_STATE();
    case 42:
      if (lookahead == 'P') ADVANCE(32);
      END_STATE();
    case 43:
      if (lookahead == 'P') ADVANCE(57);
      END_STATE();
    case 44:
      if (lookahead == 'P') ADVANCE(40);
      END_STATE();
    case 45:
      if (lookahead == 'R') ADVANCE(21);
      END_STATE();
    case 46:
      if (lookahead == 'R') ADVANCE(23);
      END_STATE();
    case 47:
      if (lookahead == 'R') ADVANCE(37);
      END_STATE();
    case 48:
      if (lookahead == 'S') ADVANCE(44);
      END_STATE();
    case 49:
      if (lookahead == 'S') ADVANCE(27);
      END_STATE();
    case 50:
      if (lookahead == 'S') ADVANCE(52);
      END_STATE();
    case 51:
      if (lookahead == 'T') ADVANCE(29);
      END_STATE();
    case 52:
      if (lookahead == 'T') ADVANCE(129);
      END_STATE();
    case 53:
      if (lookahead == 'T') ADVANCE(130);
      END_STATE();
    case 54:
      if (lookahead == 'T') ADVANCE(26);
      END_STATE();
    case 55:
      if (lookahead == 'T') ADVANCE(47);
      END_STATE();
    case 56:
      if (lookahead == 'U') ADVANCE(20);
      END_STATE();
    case 57:
      if (lookahead == 'Y') ADVANCE(125);
      END_STATE();
    case 58:
      if (lookahead == 'a') ADVANCE(72);
      END_STATE();
    case 59:
      if (lookahead == 'a') ADVANCE(86);
      END_STATE();
    case 60:
      if (lookahead == 'a') ADVANCE(71);
      END_STATE();
    case 61:
      if (lookahead == 'd') ADVANCE(151);
      END_STATE();
    case 62:
      if (lookahead == 'd') ADVANCE(131);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(73);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(73);
      if (lookahead == 'i') ADVANCE(74);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(81);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(76);
      END_STATE();
    case 67:
      if (lookahead == 'e') ADVANCE(69);
      END_STATE();
    case 68:
      if (lookahead == 'e') ADVANCE(62);
      END_STATE();
    case 69:
      if (lookahead == 'l') ADVANCE(59);
      END_STATE();
    case 70:
      if (lookahead == 'l') ADVANCE(155);
      END_STATE();
    case 71:
      if (lookahead == 'l') ADVANCE(132);
      END_STATE();
    case 72:
      if (lookahead == 'l') ADVANCE(70);
      END_STATE();
    case 73:
      if (lookahead == 'm') ADVANCE(80);
      END_STATE();
    case 74:
      if (lookahead == 'm') ADVANCE(68);
      END_STATE();
    case 75:
      if (lookahead == 'n') ADVANCE(85);
      END_STATE();
    case 76:
      if (lookahead == 'n') ADVANCE(61);
      END_STATE();
    case 77:
      if (lookahead == 'n') ADVANCE(60);
      END_STATE();
    case 78:
      if (lookahead == 'o') ADVANCE(163);
      END_STATE();
    case 79:
      if (lookahead == 'o') ADVANCE(152);
      END_STATE();
    case 80:
      if (lookahead == 'p') ADVANCE(78);
      END_STATE();
    case 81:
      if (lookahead == 'r') ADVANCE(77);
      END_STATE();
    case 82:
      if (lookahead == 's') ADVANCE(166);
      END_STATE();
    case 83:
      if (lookahead == 's') ADVANCE(168);
      END_STATE();
    case 84:
      if (lookahead == 's') ADVANCE(167);
      END_STATE();
    case 85:
      if (lookahead == 't') ADVANCE(65);
      END_STATE();
    case 86:
      if (lookahead == 'y') ADVANCE(150);
      END_STATE();
    case 87:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(158);
      END_STATE();
    case 88:
      if (eof) ADVANCE(93);
      if (lookahead == '\n') SKIP(0);
      END_STATE();
    case 89:
      if (eof) ADVANCE(93);
      if (lookahead == '\n') SKIP(0);
      if (lookahead == '\r') SKIP(88);
      END_STATE();
    case 90:
      if (eof) ADVANCE(93);
      if (lookahead == '\n') SKIP(92);
      END_STATE();
    case 91:
      if (eof) ADVANCE(93);
      if (lookahead == '\n') SKIP(92);
      if (lookahead == '\r') SKIP(90);
      END_STATE();
    case 92:
      if (eof) ADVANCE(93);
      ADVANCE_MAP(
        '#', 144,
        ',', 149,
        '/', 12,
        '1', 147,
        'A', 22,
        'B', 42,
        'C', 28,
        'E', 34,
        'L', 56,
        'N', 39,
        'R', 24,
        'T', 45,
        '[', 153,
      );
      if (lookahead == '\\') SKIP(91);
      if (lookahead == 'b') ADVANCE(145);
      if (lookahead == 'c') ADVANCE(58);
      if (lookahead == 'd') ADVANCE(67);
      if (lookahead == 's') ADVANCE(66);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(92);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(146);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(sym_keyword);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(94);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(anon_sym_LUA);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(106);
      if (lookahead == '\r') ADVANCE(99);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(109);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(106);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(109);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(109);
      if (lookahead == '\\') ADVANCE(102);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(161);
      if (lookahead != 0) ADVANCE(100);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(109);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(122);
      if (lookahead != 0) ADVANCE(101);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\r') ADVANCE(108);
      if (lookahead == '\\') ADVANCE(102);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(161);
      if (lookahead != 0) ADVANCE(100);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '*') ADVANCE(105);
      if (lookahead == '/') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(109);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '*') ADVANCE(104);
      if (lookahead == '/') ADVANCE(109);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(14);
      if (lookahead != 0) ADVANCE(105);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '*') ADVANCE(104);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(14);
      if (lookahead != 0) ADVANCE(105);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '/') ADVANCE(103);
      if (lookahead == '\\') ADVANCE(98);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(106);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(109);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '-') ADVANCE(101);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(109);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\\') ADVANCE(102);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(161);
      if (lookahead != 0) ADVANCE(100);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(109);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\n') ADVANCE(117);
      if (lookahead == '\r') ADVANCE(111);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(119);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\n') ADVANCE(117);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(119);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\n') ADVANCE(119);
      if (lookahead == '\\') ADVANCE(113);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(161);
      if (lookahead != 0) ADVANCE(112);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\r') ADVANCE(118);
      if (lookahead == '\\') ADVANCE(113);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(161);
      if (lookahead != 0) ADVANCE(112);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '*') ADVANCE(116);
      if (lookahead == '/') ADVANCE(112);
      if (lookahead != 0 &&
          (lookahead < '(' || '*' < lookahead) &&
          lookahead != '`') ADVANCE(119);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '*') ADVANCE(115);
      if (lookahead == '/') ADVANCE(119);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(14);
      if (lookahead != 0) ADVANCE(116);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '*') ADVANCE(115);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(14);
      if (lookahead != 0) ADVANCE(116);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '/') ADVANCE(114);
      if (lookahead == '\\') ADVANCE(110);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(117);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(119);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\\') ADVANCE(113);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(161);
      if (lookahead != 0) ADVANCE(112);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(119);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(sym_lua_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(122);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(anon_sym_BPM);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(anon_sym_TRANSPOSE);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_ENTROPY);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(anon_sym_NOTE);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(anon_sym_TRILL);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(anon_sym_CHORD);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(anon_sym_REST);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(anon_sym_EVENT);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(anon_sym_timed);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(anon_sym_internal);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_midi);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(sym_midi);
      if (lookahead == '2') ADVANCE(135);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(136);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(133);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(133);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(133);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym_pitchname);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'C') ADVANCE(51);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'H') ADVANCE(38);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'N') ADVANCE(55);
      if (lookahead == 'V') ADVANCE(25);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'P') ADVANCE(32);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'a') ADVANCE(72);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'e') ADVANCE(69);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(anon_sym_b);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(sym_octave);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(sym_octave);
      if (('0' <= lookahead && lookahead <= '2')) ADVANCE(146);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(anon_sym_ACTION);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(anon_sym_delay);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(anon_sym_send);
      if (lookahead == 't') ADVANCE(79);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(anon_sym_sendto);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(anon_sym_call);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(aux_sym_actionKey_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(156);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(87);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(157);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(aux_sym_number_token2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(158);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\r') ADVANCE(162);
      if (lookahead == '\\') ADVANCE(160);
      if (lookahead != 0) ADVANCE(161);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(9);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(161);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(9);
      if (lookahead != 0) ADVANCE(161);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(anon_sym_tempo);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(anon_sym_s);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(anon_sym_s);
      if (lookahead == 'e') ADVANCE(76);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(anon_sym_ms);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(anon_sym_us);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(anon_sym_ns);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 92},
  [2] = {.lex_state = 92},
  [3] = {.lex_state = 92},
  [4] = {.lex_state = 92},
  [5] = {.lex_state = 92},
  [6] = {.lex_state = 92},
  [7] = {.lex_state = 92},
  [8] = {.lex_state = 92},
  [9] = {.lex_state = 92},
  [10] = {.lex_state = 92},
  [11] = {.lex_state = 92},
  [12] = {.lex_state = 92},
  [13] = {.lex_state = 92},
  [14] = {.lex_state = 92},
  [15] = {.lex_state = 92},
  [16] = {.lex_state = 92},
  [17] = {.lex_state = 92},
  [18] = {.lex_state = 92},
  [19] = {.lex_state = 92},
  [20] = {.lex_state = 92},
  [21] = {.lex_state = 92},
  [22] = {.lex_state = 92},
  [23] = {.lex_state = 92},
  [24] = {.lex_state = 92},
  [25] = {.lex_state = 92},
  [26] = {.lex_state = 92},
  [27] = {.lex_state = 17},
  [28] = {.lex_state = 92},
  [29] = {.lex_state = 92},
  [30] = {.lex_state = 92},
  [31] = {.lex_state = 92},
  [32] = {.lex_state = 92},
  [33] = {.lex_state = 18},
  [34] = {.lex_state = 18},
  [35] = {.lex_state = 18},
  [36] = {.lex_state = 10},
  [37] = {.lex_state = 92},
  [38] = {.lex_state = 10},
  [39] = {.lex_state = 10},
  [40] = {.lex_state = 16},
  [41] = {.lex_state = 10},
  [42] = {.lex_state = 16},
  [43] = {.lex_state = 16},
  [44] = {.lex_state = 10},
  [45] = {.lex_state = 16},
  [46] = {.lex_state = 92},
  [47] = {.lex_state = 11},
  [48] = {.lex_state = 16},
  [49] = {.lex_state = 92},
  [50] = {.lex_state = 92},
  [51] = {.lex_state = 18},
  [52] = {.lex_state = 11},
  [53] = {.lex_state = 92},
  [54] = {.lex_state = 92},
  [55] = {.lex_state = 18},
  [56] = {.lex_state = 18},
  [57] = {.lex_state = 17},
  [58] = {.lex_state = 17},
  [59] = {.lex_state = 11},
  [60] = {.lex_state = 11},
  [61] = {.lex_state = 92},
  [62] = {.lex_state = 17},
  [63] = {.lex_state = 17},
  [64] = {.lex_state = 16},
  [65] = {.lex_state = 10},
  [66] = {.lex_state = 92},
  [67] = {.lex_state = 92},
  [68] = {.lex_state = 10},
  [69] = {.lex_state = 10},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 17},
  [72] = {.lex_state = 10},
  [73] = {.lex_state = 11},
  [74] = {.lex_state = 11},
  [75] = {.lex_state = 17},
  [76] = {.lex_state = 17},
  [77] = {.lex_state = 17},
  [78] = {.lex_state = 17},
  [79] = {.lex_state = 17},
  [80] = {.lex_state = 19},
  [81] = {.lex_state = 19},
  [82] = {.lex_state = 17},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 17},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 92},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 92},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 92},
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
    [anon_sym_EVENT] = ACTIONS(1),
    [anon_sym_timed] = ACTIONS(1),
    [anon_sym_internal] = ACTIONS(1),
    [sym_midi] = ACTIONS(1),
    [sym_pitchname] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [anon_sym_b] = ACTIONS(1),
    [sym_octave] = ACTIONS(1),
    [anon_sym_ACTION] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
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
    [sym_score] = STATE(87),
    [sym__statement] = STATE(2),
    [sym_LUA] = STATE(2),
    [sym_CONFIG] = STATE(2),
    [sym_configId] = STATE(57),
    [sym_numberConfig] = STATE(31),
    [sym_EVENT] = STATE(2),
    [sym_pitchEventId] = STATE(36),
    [sym_restEventId] = STATE(58),
    [sym_timeEventId] = STATE(70),
    [sym_pitchEvent] = STATE(25),
    [sym_restEvent] = STATE(25),
    [sym_freeEvent] = STATE(25),
    [aux_sym_score_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_LUA] = ACTIONS(7),
    [anon_sym_BPM] = ACTIONS(9),
    [anon_sym_TRANSPOSE] = ACTIONS(9),
    [anon_sym_ENTROPY] = ACTIONS(9),
    [anon_sym_NOTE] = ACTIONS(11),
    [anon_sym_TRILL] = ACTIONS(11),
    [anon_sym_CHORD] = ACTIONS(11),
    [anon_sym_REST] = ACTIONS(13),
    [anon_sym_EVENT] = ACTIONS(15),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_LUA,
    ACTIONS(13), 1,
      anon_sym_REST,
    ACTIONS(15), 1,
      anon_sym_EVENT,
    ACTIONS(17), 1,
      ts_builtin_sym_end,
    STATE(31), 1,
      sym_numberConfig,
    STATE(36), 1,
      sym_pitchEventId,
    STATE(57), 1,
      sym_configId,
    STATE(58), 1,
      sym_restEventId,
    STATE(70), 1,
      sym_timeEventId,
    ACTIONS(9), 3,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
    ACTIONS(11), 3,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
    STATE(25), 3,
      sym_pitchEvent,
      sym_restEvent,
      sym_freeEvent,
    STATE(3), 5,
      sym__statement,
      sym_LUA,
      sym_CONFIG,
      sym_EVENT,
      aux_sym_score_repeat1,
  [53] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      ts_builtin_sym_end,
    ACTIONS(21), 1,
      anon_sym_LUA,
    ACTIONS(30), 1,
      anon_sym_REST,
    ACTIONS(33), 1,
      anon_sym_EVENT,
    STATE(31), 1,
      sym_numberConfig,
    STATE(36), 1,
      sym_pitchEventId,
    STATE(57), 1,
      sym_configId,
    STATE(58), 1,
      sym_restEventId,
    STATE(70), 1,
      sym_timeEventId,
    ACTIONS(24), 3,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
    ACTIONS(27), 3,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
    STATE(25), 3,
      sym_pitchEvent,
      sym_restEvent,
      sym_freeEvent,
    STATE(3), 5,
      sym__statement,
      sym_LUA,
      sym_CONFIG,
      sym_EVENT,
      aux_sym_score_repeat1,
  [106] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_send,
    ACTIONS(44), 1,
      anon_sym_sendto,
    ACTIONS(46), 1,
      anon_sym_call,
    STATE(10), 1,
      sym_exec,
    STATE(53), 1,
      sym_timedAction,
    STATE(5), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(36), 10,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [147] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_send,
    ACTIONS(44), 1,
      anon_sym_sendto,
    ACTIONS(46), 1,
      anon_sym_call,
    STATE(10), 1,
      sym_exec,
    STATE(53), 1,
      sym_timedAction,
    STATE(8), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(48), 10,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [188] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_send,
    ACTIONS(44), 1,
      anon_sym_sendto,
    ACTIONS(46), 1,
      anon_sym_call,
    STATE(10), 1,
      sym_exec,
    STATE(53), 1,
      sym_timedAction,
    STATE(8), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(50), 10,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [229] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_send,
    ACTIONS(44), 1,
      anon_sym_sendto,
    ACTIONS(46), 1,
      anon_sym_call,
    STATE(10), 1,
      sym_exec,
    STATE(53), 1,
      sym_timedAction,
    STATE(6), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(52), 10,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [270] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(56), 1,
      anon_sym_ACTION,
    ACTIONS(59), 1,
      anon_sym_delay,
    ACTIONS(62), 1,
      anon_sym_send,
    ACTIONS(65), 1,
      anon_sym_sendto,
    ACTIONS(68), 1,
      anon_sym_call,
    STATE(10), 1,
      sym_exec,
    STATE(53), 1,
      sym_timedAction,
    STATE(8), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(54), 10,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [311] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_send,
    ACTIONS(44), 1,
      anon_sym_sendto,
    ACTIONS(46), 1,
      anon_sym_call,
    STATE(10), 1,
      sym_exec,
    STATE(53), 1,
      sym_timedAction,
    STATE(8), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(71), 10,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [352] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(75), 1,
      anon_sym_COMMA,
    ACTIONS(77), 1,
      anon_sym_send,
    STATE(16), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(73), 14,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [381] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(75), 1,
      anon_sym_COMMA,
    ACTIONS(81), 1,
      anon_sym_send,
    STATE(18), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(79), 14,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [410] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(85), 1,
      anon_sym_send,
    ACTIONS(83), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_COMMA,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_LBRACK,
      anon_sym_call,
  [435] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(75), 1,
      anon_sym_COMMA,
    ACTIONS(89), 1,
      anon_sym_send,
    STATE(15), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(87), 14,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [464] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      anon_sym_send,
    ACTIONS(95), 1,
      anon_sym_LBRACK,
    ACTIONS(91), 15,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_COMMA,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [491] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(99), 1,
      anon_sym_COMMA,
    ACTIONS(102), 1,
      anon_sym_send,
    STATE(15), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(97), 14,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [520] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(75), 1,
      anon_sym_COMMA,
    ACTIONS(81), 1,
      anon_sym_send,
    STATE(15), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(79), 14,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [549] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(75), 1,
      anon_sym_COMMA,
    ACTIONS(106), 1,
      anon_sym_send,
    STATE(13), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(104), 14,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [578] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(75), 1,
      anon_sym_COMMA,
    ACTIONS(106), 1,
      anon_sym_send,
    STATE(15), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(104), 14,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [607] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      anon_sym_send,
    ACTIONS(97), 15,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_COMMA,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [631] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(110), 1,
      anon_sym_send,
    ACTIONS(108), 15,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_COMMA,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [655] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(114), 1,
      anon_sym_send,
    ACTIONS(112), 15,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_COMMA,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [679] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      anon_sym_send,
    ACTIONS(91), 15,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_COMMA,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [703] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_send,
    ACTIONS(116), 14,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [726] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(122), 1,
      anon_sym_send,
    ACTIONS(120), 14,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [749] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(124), 10,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [765] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(126), 10,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [781] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(122), 2,
      anon_sym_send,
      anon_sym_s,
    ACTIONS(120), 8,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
      anon_sym_tempo,
      anon_sym_ms,
      anon_sym_us,
      anon_sym_ns,
  [799] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(128), 10,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [815] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(130), 10,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [831] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(132), 10,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [847] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(134), 10,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [863] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_send,
    ACTIONS(44), 1,
      anon_sym_sendto,
    ACTIONS(46), 1,
      anon_sym_call,
    STATE(10), 1,
      sym_exec,
    STATE(53), 1,
      sym_timedAction,
    STATE(9), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
  [892] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(136), 1,
      anon_sym_RBRACK,
    ACTIONS(138), 1,
      aux_sym_actionKey_token1,
    ACTIONS(140), 1,
      aux_sym_number_token1,
    ACTIONS(142), 1,
      aux_sym_number_token2,
    STATE(34), 2,
      sym_pdargs,
      aux_sym_exec_repeat1,
    STATE(55), 2,
      sym_number,
      sym_symbol,
  [916] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(144), 1,
      anon_sym_RBRACK,
    ACTIONS(146), 1,
      aux_sym_actionKey_token1,
    ACTIONS(149), 1,
      aux_sym_number_token1,
    ACTIONS(152), 1,
      aux_sym_number_token2,
    STATE(34), 2,
      sym_pdargs,
      aux_sym_exec_repeat1,
    STATE(55), 2,
      sym_number,
      sym_symbol,
  [940] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(138), 1,
      aux_sym_actionKey_token1,
    ACTIONS(140), 1,
      aux_sym_number_token1,
    ACTIONS(142), 1,
      aux_sym_number_token2,
    ACTIONS(155), 1,
      anon_sym_RBRACK,
    STATE(33), 2,
      sym_pdargs,
      aux_sym_exec_repeat1,
    STATE(55), 2,
      sym_number,
      sym_symbol,
  [964] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(157), 1,
      anon_sym_LPAREN,
    ACTIONS(159), 1,
      sym_midi,
    ACTIONS(161), 1,
      sym_pitchname,
    STATE(79), 1,
      sym_noteName,
    STATE(62), 2,
      sym_pitches,
      sym_pitch,
  [984] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_send,
    ACTIONS(44), 1,
      anon_sym_sendto,
    ACTIONS(46), 1,
      anon_sym_call,
    STATE(11), 1,
      sym_exec,
    STATE(54), 1,
      sym_timedAction,
  [1006] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 1,
      anon_sym_RPAREN,
    ACTIONS(165), 1,
      sym_midi,
    ACTIONS(167), 1,
      sym_pitchname,
    STATE(72), 1,
      sym_noteName,
    STATE(41), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [1026] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(67), 1,
      sym_timeUnit,
    ACTIONS(169), 5,
      anon_sym_tempo,
      anon_sym_s,
      anon_sym_ms,
      anon_sym_us,
      anon_sym_ns,
  [1040] = 6,
    ACTIONS(171), 1,
      anon_sym_LBRACE,
    ACTIONS(173), 1,
      anon_sym_RBRACE,
    ACTIONS(177), 1,
      sym_comment,
    STATE(45), 1,
      aux_sym_lua_body_repeat1,
    STATE(91), 1,
      sym_lua_body,
    ACTIONS(175), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1060] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(179), 1,
      anon_sym_RPAREN,
    ACTIONS(181), 1,
      sym_midi,
    ACTIONS(184), 1,
      sym_pitchname,
    STATE(72), 1,
      sym_noteName,
    STATE(41), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [1080] = 6,
    ACTIONS(171), 1,
      anon_sym_LBRACE,
    ACTIONS(177), 1,
      sym_comment,
    ACTIONS(187), 1,
      anon_sym_RBRACE,
    STATE(45), 1,
      aux_sym_lua_body_repeat1,
    STATE(93), 1,
      sym_lua_body,
    ACTIONS(175), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1100] = 5,
    ACTIONS(177), 1,
      sym_comment,
    ACTIONS(189), 1,
      anon_sym_LBRACE,
    ACTIONS(192), 1,
      anon_sym_RBRACE,
    STATE(43), 1,
      aux_sym_lua_body_repeat1,
    ACTIONS(194), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1117] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(165), 1,
      sym_midi,
    ACTIONS(167), 1,
      sym_pitchname,
    STATE(72), 1,
      sym_noteName,
    STATE(38), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [1134] = 5,
    ACTIONS(171), 1,
      anon_sym_LBRACE,
    ACTIONS(177), 1,
      sym_comment,
    ACTIONS(197), 1,
      anon_sym_RBRACE,
    STATE(43), 1,
      aux_sym_lua_body_repeat1,
    ACTIONS(199), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1151] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_send,
    ACTIONS(116), 4,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_call,
  [1164] = 6,
    ACTIONS(177), 1,
      sym_comment,
    ACTIONS(201), 1,
      aux_sym_lua_call_token1,
    ACTIONS(203), 1,
      anon_sym_LPAREN,
    ACTIONS(205), 1,
      anon_sym_RPAREN,
    STATE(59), 1,
      aux_sym_lua_call_repeat1,
    STATE(86), 1,
      sym_lua_call,
  [1183] = 2,
    ACTIONS(177), 1,
      sym_comment,
    ACTIONS(192), 4,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1193] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(209), 1,
      sym_octave,
    STATE(90), 1,
      sym_alteration,
    ACTIONS(207), 2,
      anon_sym_POUND,
      anon_sym_b,
  [1207] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(211), 1,
      sym_octave,
    STATE(94), 1,
      sym_alteration,
    ACTIONS(207), 2,
      anon_sym_POUND,
      anon_sym_b,
  [1221] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(122), 1,
      aux_sym_number_token1,
    ACTIONS(120), 3,
      anon_sym_RBRACK,
      aux_sym_actionKey_token1,
      aux_sym_number_token2,
  [1233] = 5,
    ACTIONS(177), 1,
      sym_comment,
    ACTIONS(213), 1,
      aux_sym_lua_call_token1,
    ACTIONS(216), 1,
      anon_sym_LPAREN,
    ACTIONS(219), 1,
      anon_sym_RPAREN,
    STATE(52), 1,
      aux_sym_lua_call_repeat1,
  [1249] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(42), 1,
      anon_sym_send,
    ACTIONS(44), 1,
      anon_sym_sendto,
    ACTIONS(46), 1,
      anon_sym_call,
    STATE(11), 1,
      sym_exec,
  [1265] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(42), 1,
      anon_sym_send,
    ACTIONS(44), 1,
      anon_sym_sendto,
    ACTIONS(46), 1,
      anon_sym_call,
    STATE(17), 1,
      sym_exec,
  [1281] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(223), 1,
      aux_sym_number_token1,
    ACTIONS(221), 3,
      anon_sym_RBRACK,
      aux_sym_actionKey_token1,
      aux_sym_number_token2,
  [1293] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(227), 1,
      aux_sym_number_token1,
    ACTIONS(225), 3,
      anon_sym_RBRACK,
      aux_sym_actionKey_token1,
      aux_sym_number_token2,
  [1305] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(229), 1,
      aux_sym_number_token1,
    ACTIONS(231), 1,
      aux_sym_number_token2,
    STATE(28), 1,
      sym_numberSet,
    STATE(29), 1,
      sym_number,
  [1321] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(229), 1,
      aux_sym_number_token1,
    ACTIONS(231), 1,
      aux_sym_number_token2,
    STATE(4), 1,
      sym_duration,
    STATE(23), 1,
      sym_number,
  [1337] = 5,
    ACTIONS(177), 1,
      sym_comment,
    ACTIONS(203), 1,
      anon_sym_LPAREN,
    ACTIONS(233), 1,
      aux_sym_lua_call_token1,
    ACTIONS(235), 1,
      anon_sym_RPAREN,
    STATE(52), 1,
      aux_sym_lua_call_repeat1,
  [1353] = 5,
    ACTIONS(177), 1,
      sym_comment,
    ACTIONS(201), 1,
      aux_sym_lua_call_token1,
    ACTIONS(203), 1,
      anon_sym_LPAREN,
    STATE(59), 1,
      aux_sym_lua_call_repeat1,
    STATE(85), 1,
      sym_lua_call,
  [1369] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(42), 1,
      anon_sym_send,
    ACTIONS(44), 1,
      anon_sym_sendto,
    ACTIONS(46), 1,
      anon_sym_call,
    STATE(19), 1,
      sym_exec,
  [1385] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(229), 1,
      aux_sym_number_token1,
    ACTIONS(231), 1,
      aux_sym_number_token2,
    STATE(7), 1,
      sym_duration,
    STATE(23), 1,
      sym_number,
  [1401] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(237), 1,
      aux_sym_number_token1,
    ACTIONS(239), 1,
      aux_sym_number_token2,
    STATE(32), 1,
      sym_duration,
    STATE(46), 1,
      sym_number,
  [1417] = 2,
    ACTIONS(177), 1,
      sym_comment,
    ACTIONS(241), 4,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1427] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(243), 3,
      anon_sym_LPAREN,
      sym_midi,
      sym_pitchname,
  [1436] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(245), 1,
      anon_sym_send,
    ACTIONS(247), 2,
      anon_sym_sendto,
      anon_sym_call,
  [1447] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(249), 1,
      anon_sym_send,
    ACTIONS(251), 2,
      anon_sym_sendto,
      anon_sym_call,
  [1458] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(253), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [1467] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(255), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [1476] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(63), 1,
      sym_eventId,
    ACTIONS(257), 2,
      anon_sym_timed,
      anon_sym_internal,
  [1487] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(237), 1,
      aux_sym_number_token1,
    ACTIONS(239), 1,
      aux_sym_number_token2,
    STATE(39), 1,
      sym_number,
  [1500] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(259), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [1509] = 2,
    ACTIONS(177), 1,
      sym_comment,
    ACTIONS(219), 3,
      aux_sym_lua_call_token1,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [1518] = 2,
    ACTIONS(177), 1,
      sym_comment,
    ACTIONS(261), 3,
      aux_sym_lua_call_token1,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [1527] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(263), 1,
      aux_sym_number_token1,
    ACTIONS(265), 1,
      aux_sym_number_token2,
  [1537] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(267), 1,
      aux_sym_number_token1,
    ACTIONS(269), 1,
      aux_sym_number_token2,
  [1547] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(255), 1,
      aux_sym_number_token2,
    ACTIONS(271), 1,
      aux_sym_number_token1,
  [1557] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      aux_sym_number_token1,
    ACTIONS(275), 1,
      aux_sym_number_token2,
  [1567] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(259), 1,
      aux_sym_number_token2,
    ACTIONS(277), 1,
      aux_sym_number_token1,
  [1577] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_keyword,
    STATE(22), 1,
      sym_receiver,
  [1587] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 1,
      sym_keyword,
    STATE(14), 1,
      sym_receiver,
  [1597] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(253), 1,
      aux_sym_number_token2,
    ACTIONS(281), 1,
      aux_sym_number_token1,
  [1607] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(283), 2,
      anon_sym_timed,
      anon_sym_internal,
  [1615] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(285), 1,
      aux_sym_number_token1,
    ACTIONS(287), 1,
      aux_sym_number_token2,
  [1625] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(155), 1,
      anon_sym_RPAREN,
  [1632] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(289), 1,
      anon_sym_RPAREN,
  [1639] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 1,
      ts_builtin_sym_end,
  [1646] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(293), 1,
      sym_octave,
  [1653] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(295), 1,
      anon_sym_LPAREN,
  [1660] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(297), 1,
      sym_octave,
  [1667] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(299), 1,
      anon_sym_RBRACE,
  [1674] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(301), 1,
      anon_sym_LBRACE,
  [1681] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      anon_sym_RBRACE,
  [1688] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(305), 1,
      sym_octave,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 53,
  [SMALL_STATE(4)] = 106,
  [SMALL_STATE(5)] = 147,
  [SMALL_STATE(6)] = 188,
  [SMALL_STATE(7)] = 229,
  [SMALL_STATE(8)] = 270,
  [SMALL_STATE(9)] = 311,
  [SMALL_STATE(10)] = 352,
  [SMALL_STATE(11)] = 381,
  [SMALL_STATE(12)] = 410,
  [SMALL_STATE(13)] = 435,
  [SMALL_STATE(14)] = 464,
  [SMALL_STATE(15)] = 491,
  [SMALL_STATE(16)] = 520,
  [SMALL_STATE(17)] = 549,
  [SMALL_STATE(18)] = 578,
  [SMALL_STATE(19)] = 607,
  [SMALL_STATE(20)] = 631,
  [SMALL_STATE(21)] = 655,
  [SMALL_STATE(22)] = 679,
  [SMALL_STATE(23)] = 703,
  [SMALL_STATE(24)] = 726,
  [SMALL_STATE(25)] = 749,
  [SMALL_STATE(26)] = 765,
  [SMALL_STATE(27)] = 781,
  [SMALL_STATE(28)] = 799,
  [SMALL_STATE(29)] = 815,
  [SMALL_STATE(30)] = 831,
  [SMALL_STATE(31)] = 847,
  [SMALL_STATE(32)] = 863,
  [SMALL_STATE(33)] = 892,
  [SMALL_STATE(34)] = 916,
  [SMALL_STATE(35)] = 940,
  [SMALL_STATE(36)] = 964,
  [SMALL_STATE(37)] = 984,
  [SMALL_STATE(38)] = 1006,
  [SMALL_STATE(39)] = 1026,
  [SMALL_STATE(40)] = 1040,
  [SMALL_STATE(41)] = 1060,
  [SMALL_STATE(42)] = 1080,
  [SMALL_STATE(43)] = 1100,
  [SMALL_STATE(44)] = 1117,
  [SMALL_STATE(45)] = 1134,
  [SMALL_STATE(46)] = 1151,
  [SMALL_STATE(47)] = 1164,
  [SMALL_STATE(48)] = 1183,
  [SMALL_STATE(49)] = 1193,
  [SMALL_STATE(50)] = 1207,
  [SMALL_STATE(51)] = 1221,
  [SMALL_STATE(52)] = 1233,
  [SMALL_STATE(53)] = 1249,
  [SMALL_STATE(54)] = 1265,
  [SMALL_STATE(55)] = 1281,
  [SMALL_STATE(56)] = 1293,
  [SMALL_STATE(57)] = 1305,
  [SMALL_STATE(58)] = 1321,
  [SMALL_STATE(59)] = 1337,
  [SMALL_STATE(60)] = 1353,
  [SMALL_STATE(61)] = 1369,
  [SMALL_STATE(62)] = 1385,
  [SMALL_STATE(63)] = 1401,
  [SMALL_STATE(64)] = 1417,
  [SMALL_STATE(65)] = 1427,
  [SMALL_STATE(66)] = 1436,
  [SMALL_STATE(67)] = 1447,
  [SMALL_STATE(68)] = 1458,
  [SMALL_STATE(69)] = 1467,
  [SMALL_STATE(70)] = 1476,
  [SMALL_STATE(71)] = 1487,
  [SMALL_STATE(72)] = 1500,
  [SMALL_STATE(73)] = 1509,
  [SMALL_STATE(74)] = 1518,
  [SMALL_STATE(75)] = 1527,
  [SMALL_STATE(76)] = 1537,
  [SMALL_STATE(77)] = 1547,
  [SMALL_STATE(78)] = 1557,
  [SMALL_STATE(79)] = 1567,
  [SMALL_STATE(80)] = 1577,
  [SMALL_STATE(81)] = 1587,
  [SMALL_STATE(82)] = 1597,
  [SMALL_STATE(83)] = 1607,
  [SMALL_STATE(84)] = 1615,
  [SMALL_STATE(85)] = 1625,
  [SMALL_STATE(86)] = 1632,
  [SMALL_STATE(87)] = 1639,
  [SMALL_STATE(88)] = 1646,
  [SMALL_STATE(89)] = 1653,
  [SMALL_STATE(90)] = 1660,
  [SMALL_STATE(91)] = 1667,
  [SMALL_STATE(92)] = 1674,
  [SMALL_STATE(93)] = 1681,
  [SMALL_STATE(94)] = 1688,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_score, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_score, 1, 0, 0),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0),
  [21] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(92),
  [24] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(78),
  [27] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(65),
  [30] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(84),
  [33] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(83),
  [36] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_restEvent, 2, 0, 0),
  [38] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [40] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [42] = {.entry = {.count = 1, .reusable = false}}, SHIFT(80),
  [44] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [46] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_restEvent, 3, 0, 0),
  [50] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEvent, 4, 0, 0),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEvent, 3, 0, 0),
  [54] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0),
  [56] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(37),
  [59] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(71),
  [62] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(80),
  [65] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(81),
  [68] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(89),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_freeEvent, 4, 0, 0),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 1, 0, 0),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [77] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ACTION, 1, 0, 0),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 2, 0, 0),
  [81] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ACTION, 2, 0, 0),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_receiver, 1, 0, 0),
  [85] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_receiver, 1, 0, 0),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 4, 0, 0),
  [89] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ACTION, 4, 0, 0),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exec, 2, 0, 0),
  [93] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_exec, 2, 0, 0),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_ACTION_repeat1, 2, 0, 0),
  [99] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_ACTION_repeat1, 2, 0, 0), SHIFT_REPEAT(61),
  [102] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_ACTION_repeat1, 2, 0, 0),
  [104] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 3, 0, 0),
  [106] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ACTION, 3, 0, 0),
  [108] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exec, 5, 0, 0),
  [110] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_exec, 5, 0, 0),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exec, 4, 0, 0),
  [114] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_exec, 4, 0, 0),
  [116] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_duration, 1, 0, 0),
  [118] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_duration, 1, 0, 0),
  [120] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_number, 1, 0, 0),
  [122] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_number, 1, 0, 0),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_EVENT, 1, 0, 0),
  [126] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_LUA, 4, 0, 0),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberConfig, 2, 0, 0),
  [130] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberSet, 1, 0, 0),
  [132] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_LUA, 3, 0, 0),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_CONFIG, 1, 0, 0),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [140] = {.entry = {.count = 1, .reusable = false}}, SHIFT(51),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [144] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_exec_repeat1, 2, 0, 0),
  [146] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_exec_repeat1, 2, 0, 0), SHIFT_REPEAT(56),
  [149] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_exec_repeat1, 2, 0, 0), SHIFT_REPEAT(51),
  [152] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_exec_repeat1, 2, 0, 0), SHIFT_REPEAT(51),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [161] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [171] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [173] = {.entry = {.count = 1, .reusable = false}}, SHIFT(30),
  [175] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [177] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [179] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0),
  [181] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(72),
  [184] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(50),
  [187] = {.entry = {.count = 1, .reusable = false}}, SHIFT(48),
  [189] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 2, 0, 0), SHIFT_REPEAT(42),
  [192] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 2, 0, 0),
  [194] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 2, 0, 0), SHIFT_REPEAT(43),
  [197] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lua_body, 1, 0, 0),
  [199] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [201] = {.entry = {.count = 1, .reusable = false}}, SHIFT(59),
  [203] = {.entry = {.count = 1, .reusable = false}}, SHIFT(47),
  [205] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [207] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [209] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [211] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [213] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 2, 0, 0), SHIFT_REPEAT(52),
  [216] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 2, 0, 0), SHIFT_REPEAT(47),
  [219] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 2, 0, 0),
  [221] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pdargs, 1, 0, 0),
  [223] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pdargs, 1, 0, 0),
  [225] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_symbol, 1, 0, 0),
  [227] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_symbol, 1, 0, 0),
  [229] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [231] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [233] = {.entry = {.count = 1, .reusable = false}}, SHIFT(52),
  [235] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lua_call, 1, 0, 0),
  [237] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [239] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [241] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 3, 0, 0),
  [243] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEventId, 1, 0, 0),
  [245] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_timeUnit, 1, 0, 0),
  [247] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_timeUnit, 1, 0, 0),
  [249] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_timedAction, 3, 0, 0),
  [251] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_timedAction, 3, 0, 0),
  [253] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_noteName, 3, 0, 0),
  [255] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_noteName, 2, 0, 0),
  [257] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [259] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitch, 1, 0, 0),
  [261] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 3, 0, 0),
  [263] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitches, 3, 0, 0),
  [265] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitches, 3, 0, 0),
  [267] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_eventId, 1, 0, 0),
  [269] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_eventId, 1, 0, 0),
  [271] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_noteName, 2, 0, 0),
  [273] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_configId, 1, 0, 0),
  [275] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_configId, 1, 0, 0),
  [277] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitch, 1, 0, 0),
  [279] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [281] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_noteName, 3, 0, 0),
  [283] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_timeEventId, 1, 0, 0),
  [285] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_restEventId, 1, 0, 0),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_restEventId, 1, 0, 0),
  [289] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [291] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [293] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alteration, 1, 0, 0),
  [295] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [297] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [299] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [301] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [303] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [305] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
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
