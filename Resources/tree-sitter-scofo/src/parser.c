#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 96
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 77
#define ALIAS_COUNT 0
#define TOKEN_COUNT 39
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 13
#define MAX_ALIAS_SEQUENCE_LENGTH 4
#define PRODUCTION_ID_COUNT 13

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
  anon_sym_sendto = 28,
  anon_sym_luacall = 29,
  anon_sym_LBRACK = 30,
  anon_sym_RBRACK = 31,
  aux_sym_actionKey_token1 = 32,
  aux_sym_number_token1 = 33,
  aux_sym_number_token2 = 34,
  sym_comment = 35,
  anon_sym_tempo = 36,
  anon_sym_sec = 37,
  anon_sym_ms = 38,
  sym_score = 39,
  sym__statement = 40,
  sym_LUA = 41,
  sym_lua_body = 42,
  sym_lua_call = 43,
  sym_CONFIG = 44,
  sym_configId = 45,
  sym_numberConfig = 46,
  sym_numberSet = 47,
  sym_EVENT = 48,
  sym_pitchEventId = 49,
  sym_restEventId = 50,
  sym_timeEventId = 51,
  sym_pitchEvent = 52,
  sym_restEvent = 53,
  sym_freeEvent = 54,
  sym_eventId = 55,
  sym_pitches = 56,
  sym_pitch = 57,
  sym_noteName = 58,
  sym_alteration = 59,
  sym_duration = 60,
  sym_ACTION = 61,
  sym_timedAction = 62,
  sym_exec = 63,
  sym_pdargs = 64,
  sym_pdarg = 65,
  sym_receiver = 66,
  sym_number = 67,
  sym_symbol = 68,
  sym_timeUnit = 69,
  aux_sym_score_repeat1 = 70,
  aux_sym_lua_body_repeat1 = 71,
  aux_sym_lua_call_repeat1 = 72,
  aux_sym_pitchEvent_repeat1 = 73,
  aux_sym_pitches_repeat1 = 74,
  aux_sym_ACTION_repeat1 = 75,
  aux_sym_pdargs_repeat1 = 76,
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
  [anon_sym_delay] = "delay",
  [anon_sym_sendto] = "sendto",
  [anon_sym_luacall] = "luacall",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [aux_sym_actionKey_token1] = "actionKey_token1",
  [aux_sym_number_token1] = "number_token1",
  [aux_sym_number_token2] = "number_token2",
  [sym_comment] = "comment",
  [anon_sym_tempo] = "tempo",
  [anon_sym_sec] = "sec",
  [anon_sym_ms] = "ms",
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
  [sym_pdarg] = "pdarg",
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
  [aux_sym_pdargs_repeat1] = "pdargs_repeat1",
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
  [anon_sym_sendto] = anon_sym_sendto,
  [anon_sym_luacall] = anon_sym_luacall,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [aux_sym_actionKey_token1] = aux_sym_actionKey_token1,
  [aux_sym_number_token1] = aux_sym_number_token1,
  [aux_sym_number_token2] = aux_sym_number_token2,
  [sym_comment] = sym_comment,
  [anon_sym_tempo] = anon_sym_tempo,
  [anon_sym_sec] = anon_sym_sec,
  [anon_sym_ms] = anon_sym_ms,
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
  [sym_pdarg] = sym_pdarg,
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
  [aux_sym_pdargs_repeat1] = aux_sym_pdargs_repeat1,
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
    .named = false,
  },
  [anon_sym_sendto] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_luacall] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
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
  [anon_sym_sec] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ms] = {
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
  [sym_pdarg] = {
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
  [aux_sym_pdargs_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_actionKey = 1,
  field_configId = 2,
  field_exec = 3,
  field_keyword = 4,
  field_lua_call = 5,
  field_luabody = 6,
  field_pdarg = 7,
  field_pdargs = 8,
  field_pitchEventId = 9,
  field_receiver = 10,
  field_timeUnit = 11,
  field_timedAction = 12,
  field_value = 13,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_actionKey] = "actionKey",
  [field_configId] = "configId",
  [field_exec] = "exec",
  [field_keyword] = "keyword",
  [field_lua_call] = "lua_call",
  [field_luabody] = "luabody",
  [field_pdarg] = "pdarg",
  [field_pdargs] = "pdargs",
  [field_pitchEventId] = "pitchEventId",
  [field_receiver] = "receiver",
  [field_timeUnit] = "timeUnit",
  [field_timedAction] = "timedAction",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 1},
  [4] = {.index = 3, .length = 1},
  [5] = {.index = 4, .length = 2},
  [6] = {.index = 6, .length = 2},
  [7] = {.index = 8, .length = 1},
  [8] = {.index = 9, .length = 3},
  [9] = {.index = 12, .length = 3},
  [10] = {.index = 15, .length = 1},
  [11] = {.index = 16, .length = 1},
  [12] = {.index = 17, .length = 4},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_configId, 0},
  [1] =
    {field_pitchEventId, 0},
  [2] =
    {field_exec, 0},
  [3] =
    {field_exec, 1},
  [4] =
    {field_exec, 1},
    {field_timedAction, 0},
  [6] =
    {field_exec, 2},
    {field_timedAction, 1},
  [8] =
    {field_timeUnit, 0},
  [9] =
    {field_actionKey, 0},
    {field_timeUnit, 2},
    {field_value, 1},
  [12] =
    {field_keyword, 0},
    {field_pdargs, 2},
    {field_receiver, 1},
  [15] =
    {field_lua_call, 0},
  [16] =
    {field_pdarg, 0},
  [17] =
    {field_keyword, 0},
    {field_luabody, 1},
    {field_luabody, 2},
    {field_luabody, 3},
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
  [34] = 34,
  [35] = 23,
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
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 23,
  [50] = 50,
  [51] = 47,
  [52] = 24,
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
  [74] = 62,
  [75] = 69,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 72,
  [81] = 81,
  [82] = 82,
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
  [94] = 94,
  [95] = 90,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(92);
      ADVANCE_MAP(
        '#', 142,
        '(', 119,
        ')', 120,
        ',', 147,
        '-', 13,
        '/', 10,
        '0', 132,
        '1', 133,
        'A', 137,
        'B', 140,
        'C', 138,
        'E', 139,
        'L', 53,
        'N', 36,
        'R', 21,
        'T', 42,
        '[', 151,
      );
      if (lookahead == '\\') SKIP(88);
      if (lookahead == ']') ADVANCE(152);
      if (lookahead == 'b') ADVANCE(143);
      if (lookahead == 'd') ADVANCE(141);
      if (lookahead == 'i') ADVANCE(75);
      if (lookahead == 'l') ADVANCE(84);
      if (lookahead == 'm') ADVANCE(81);
      if (lookahead == 's') ADVANCE(64);
      if (lookahead == 't') ADVANCE(66);
      if (lookahead == '{') ADVANCE(95);
      if (lookahead == '}') ADVANCE(96);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('D' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(136);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(135);
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
      if (lookahead == '\r') ADVANCE(159);
      if (lookahead == '\\') ADVANCE(157);
      if (lookahead != 0) ADVANCE(158);
      END_STATE();
    case 8:
      if (lookahead == '(') ADVANCE(119);
      if (lookahead == ')') ADVANCE(120);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '0') ADVANCE(132);
      if (lookahead == '1') ADVANCE(133);
      if (lookahead == '\\') SKIP(4);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(8);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(135);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(136);
      END_STATE();
    case 9:
      if (lookahead == '(') ADVANCE(119);
      if (lookahead == ')') ADVANCE(120);
      if (lookahead == '/') ADVANCE(113);
      if (lookahead == '\\') ADVANCE(109);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(116);
      if (lookahead != 0 &&
          lookahead != '`') ADVANCE(118);
      END_STATE();
    case 10:
      if (lookahead == '*') ADVANCE(12);
      if (lookahead == '/') ADVANCE(158);
      END_STATE();
    case 11:
      if (lookahead == '*') ADVANCE(11);
      if (lookahead == '/') ADVANCE(156);
      if (lookahead != 0) ADVANCE(12);
      END_STATE();
    case 12:
      if (lookahead == '*') ADVANCE(11);
      if (lookahead != 0) ADVANCE(12);
      END_STATE();
    case 13:
      if (lookahead == '-') ADVANCE(121);
      END_STATE();
    case 14:
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '/') ADVANCE(102);
      if (lookahead == '\\') ADVANCE(97);
      if (lookahead == '{') ADVANCE(95);
      if (lookahead == '}') ADVANCE(96);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(105);
      if (lookahead != 0 &&
          lookahead != '`') ADVANCE(108);
      END_STATE();
    case 15:
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '\\') SKIP(2);
      if (lookahead == ']') ADVANCE(152);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(15);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(153);
      END_STATE();
    case 16:
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '\\') SKIP(6);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 17:
      if (lookahead == 'A') ADVANCE(94);
      END_STATE();
    case 18:
      if (lookahead == 'A') ADVANCE(32);
      if (lookahead == 'I') ADVANCE(28);
      END_STATE();
    case 19:
      if (lookahead == 'C') ADVANCE(48);
      END_STATE();
    case 20:
      if (lookahead == 'D') ADVANCE(127);
      END_STATE();
    case 21:
      if (lookahead == 'E') ADVANCE(47);
      END_STATE();
    case 22:
      if (lookahead == 'E') ADVANCE(33);
      END_STATE();
    case 23:
      if (lookahead == 'E') ADVANCE(125);
      END_STATE();
    case 24:
      if (lookahead == 'E') ADVANCE(123);
      END_STATE();
    case 25:
      if (lookahead == 'H') ADVANCE(35);
      END_STATE();
    case 26:
      if (lookahead == 'I') ADVANCE(38);
      END_STATE();
    case 27:
      if (lookahead == 'L') ADVANCE(126);
      END_STATE();
    case 28:
      if (lookahead == 'L') ADVANCE(27);
      END_STATE();
    case 29:
      if (lookahead == 'M') ADVANCE(122);
      END_STATE();
    case 30:
      if (lookahead == 'N') ADVANCE(146);
      END_STATE();
    case 31:
      if (lookahead == 'N') ADVANCE(52);
      if (lookahead == 'V') ADVANCE(22);
      END_STATE();
    case 32:
      if (lookahead == 'N') ADVANCE(45);
      END_STATE();
    case 33:
      if (lookahead == 'N') ADVANCE(50);
      END_STATE();
    case 34:
      if (lookahead == 'O') ADVANCE(40);
      END_STATE();
    case 35:
      if (lookahead == 'O') ADVANCE(43);
      END_STATE();
    case 36:
      if (lookahead == 'O') ADVANCE(51);
      END_STATE();
    case 37:
      if (lookahead == 'O') ADVANCE(46);
      END_STATE();
    case 38:
      if (lookahead == 'O') ADVANCE(30);
      END_STATE();
    case 39:
      if (lookahead == 'P') ADVANCE(29);
      END_STATE();
    case 40:
      if (lookahead == 'P') ADVANCE(54);
      END_STATE();
    case 41:
      if (lookahead == 'P') ADVANCE(37);
      END_STATE();
    case 42:
      if (lookahead == 'R') ADVANCE(18);
      END_STATE();
    case 43:
      if (lookahead == 'R') ADVANCE(20);
      END_STATE();
    case 44:
      if (lookahead == 'R') ADVANCE(34);
      END_STATE();
    case 45:
      if (lookahead == 'S') ADVANCE(41);
      END_STATE();
    case 46:
      if (lookahead == 'S') ADVANCE(24);
      END_STATE();
    case 47:
      if (lookahead == 'S') ADVANCE(49);
      END_STATE();
    case 48:
      if (lookahead == 'T') ADVANCE(26);
      END_STATE();
    case 49:
      if (lookahead == 'T') ADVANCE(128);
      END_STATE();
    case 50:
      if (lookahead == 'T') ADVANCE(129);
      END_STATE();
    case 51:
      if (lookahead == 'T') ADVANCE(23);
      END_STATE();
    case 52:
      if (lookahead == 'T') ADVANCE(44);
      END_STATE();
    case 53:
      if (lookahead == 'U') ADVANCE(17);
      END_STATE();
    case 54:
      if (lookahead == 'Y') ADVANCE(124);
      END_STATE();
    case 55:
      if (lookahead == 'a') ADVANCE(60);
      END_STATE();
    case 56:
      if (lookahead == 'a') ADVANCE(85);
      END_STATE();
    case 57:
      if (lookahead == 'a') ADVANCE(72);
      END_STATE();
    case 58:
      if (lookahead == 'a') ADVANCE(70);
      END_STATE();
    case 59:
      if (lookahead == 'c') ADVANCE(161);
      if (lookahead == 'n') ADVANCE(62);
      END_STATE();
    case 60:
      if (lookahead == 'c') ADVANCE(57);
      END_STATE();
    case 61:
      if (lookahead == 'd') ADVANCE(130);
      END_STATE();
    case 62:
      if (lookahead == 'd') ADVANCE(83);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(71);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(59);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(73);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(73);
      if (lookahead == 'i') ADVANCE(74);
      END_STATE();
    case 67:
      if (lookahead == 'e') ADVANCE(80);
      END_STATE();
    case 68:
      if (lookahead == 'e') ADVANCE(61);
      END_STATE();
    case 69:
      if (lookahead == 'l') ADVANCE(150);
      END_STATE();
    case 70:
      if (lookahead == 'l') ADVANCE(131);
      END_STATE();
    case 71:
      if (lookahead == 'l') ADVANCE(56);
      END_STATE();
    case 72:
      if (lookahead == 'l') ADVANCE(69);
      END_STATE();
    case 73:
      if (lookahead == 'm') ADVANCE(79);
      END_STATE();
    case 74:
      if (lookahead == 'm') ADVANCE(68);
      END_STATE();
    case 75:
      if (lookahead == 'n') ADVANCE(82);
      END_STATE();
    case 76:
      if (lookahead == 'n') ADVANCE(58);
      END_STATE();
    case 77:
      if (lookahead == 'o') ADVANCE(160);
      END_STATE();
    case 78:
      if (lookahead == 'o') ADVANCE(149);
      END_STATE();
    case 79:
      if (lookahead == 'p') ADVANCE(77);
      END_STATE();
    case 80:
      if (lookahead == 'r') ADVANCE(76);
      END_STATE();
    case 81:
      if (lookahead == 's') ADVANCE(162);
      END_STATE();
    case 82:
      if (lookahead == 't') ADVANCE(67);
      END_STATE();
    case 83:
      if (lookahead == 't') ADVANCE(78);
      END_STATE();
    case 84:
      if (lookahead == 'u') ADVANCE(55);
      END_STATE();
    case 85:
      if (lookahead == 'y') ADVANCE(148);
      END_STATE();
    case 86:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(155);
      END_STATE();
    case 87:
      if (eof) ADVANCE(92);
      if (lookahead == '\n') SKIP(0);
      END_STATE();
    case 88:
      if (eof) ADVANCE(92);
      if (lookahead == '\n') SKIP(0);
      if (lookahead == '\r') SKIP(87);
      END_STATE();
    case 89:
      if (eof) ADVANCE(92);
      if (lookahead == '\n') SKIP(91);
      END_STATE();
    case 90:
      if (eof) ADVANCE(92);
      if (lookahead == '\n') SKIP(91);
      if (lookahead == '\r') SKIP(89);
      END_STATE();
    case 91:
      if (eof) ADVANCE(92);
      ADVANCE_MAP(
        '#', 142,
        ',', 147,
        '/', 10,
        '1', 145,
        'A', 19,
        'B', 39,
        'C', 25,
        'E', 31,
        'L', 53,
        'N', 36,
        'R', 21,
        'T', 42,
      );
      if (lookahead == '\\') SKIP(90);
      if (lookahead == 'b') ADVANCE(143);
      if (lookahead == 'd') ADVANCE(63);
      if (lookahead == 'l') ADVANCE(84);
      if (lookahead == 'm') ADVANCE(81);
      if (lookahead == 's') ADVANCE(64);
      if (lookahead == 't') ADVANCE(65);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(91);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(144);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(sym_keyword);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(anon_sym_LUA);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(105);
      if (lookahead == '\r') ADVANCE(98);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(108);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(105);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(108);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(108);
      if (lookahead == '\\') ADVANCE(101);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(158);
      if (lookahead != 0) ADVANCE(99);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(108);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(121);
      if (lookahead != 0) ADVANCE(100);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\r') ADVANCE(107);
      if (lookahead == '\\') ADVANCE(101);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(158);
      if (lookahead != 0) ADVANCE(99);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '*') ADVANCE(104);
      if (lookahead == '/') ADVANCE(99);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(108);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '*') ADVANCE(103);
      if (lookahead == '/') ADVANCE(108);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(12);
      if (lookahead != 0) ADVANCE(104);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '*') ADVANCE(103);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(12);
      if (lookahead != 0) ADVANCE(104);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '/') ADVANCE(102);
      if (lookahead == '\\') ADVANCE(97);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(105);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(108);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '-') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(108);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\\') ADVANCE(101);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(158);
      if (lookahead != 0) ADVANCE(99);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(108);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\n') ADVANCE(116);
      if (lookahead == '\r') ADVANCE(110);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(118);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\n') ADVANCE(116);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(118);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\n') ADVANCE(118);
      if (lookahead == '\\') ADVANCE(112);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(158);
      if (lookahead != 0) ADVANCE(111);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\r') ADVANCE(117);
      if (lookahead == '\\') ADVANCE(112);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(158);
      if (lookahead != 0) ADVANCE(111);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '*') ADVANCE(115);
      if (lookahead == '/') ADVANCE(111);
      if (lookahead != 0 &&
          (lookahead < '(' || '*' < lookahead) &&
          lookahead != '`') ADVANCE(118);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '*') ADVANCE(114);
      if (lookahead == '/') ADVANCE(118);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(12);
      if (lookahead != 0) ADVANCE(115);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '*') ADVANCE(114);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(12);
      if (lookahead != 0) ADVANCE(115);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '/') ADVANCE(113);
      if (lookahead == '\\') ADVANCE(109);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(116);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(118);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\\') ADVANCE(112);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(158);
      if (lookahead != 0) ADVANCE(111);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(118);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(sym_lua_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(121);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(anon_sym_BPM);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(anon_sym_TRANSPOSE);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(anon_sym_ENTROPY);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_NOTE);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(anon_sym_TRILL);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(anon_sym_CHORD);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(anon_sym_REST);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(anon_sym_EVENT);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(anon_sym_timed);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(anon_sym_internal);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(sym_midi);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_midi);
      if (lookahead == '2') ADVANCE(134);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(135);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(132);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(132);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(132);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(sym_pitchname);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'C') ADVANCE(48);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'H') ADVANCE(35);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'N') ADVANCE(52);
      if (lookahead == 'V') ADVANCE(22);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'P') ADVANCE(29);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'e') ADVANCE(71);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(anon_sym_b);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(sym_octave);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(sym_octave);
      if (('0' <= lookahead && lookahead <= '2')) ADVANCE(144);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(anon_sym_ACTION);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(anon_sym_delay);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(anon_sym_sendto);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(anon_sym_luacall);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(aux_sym_actionKey_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(153);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(86);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(aux_sym_number_token2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(155);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\r') ADVANCE(159);
      if (lookahead == '\\') ADVANCE(157);
      if (lookahead != 0) ADVANCE(158);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(7);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(158);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(7);
      if (lookahead != 0) ADVANCE(158);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(anon_sym_tempo);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(anon_sym_sec);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(anon_sym_ms);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 91},
  [2] = {.lex_state = 91},
  [3] = {.lex_state = 91},
  [4] = {.lex_state = 91},
  [5] = {.lex_state = 91},
  [6] = {.lex_state = 91},
  [7] = {.lex_state = 91},
  [8] = {.lex_state = 91},
  [9] = {.lex_state = 91},
  [10] = {.lex_state = 91},
  [11] = {.lex_state = 91},
  [12] = {.lex_state = 91},
  [13] = {.lex_state = 91},
  [14] = {.lex_state = 91},
  [15] = {.lex_state = 91},
  [16] = {.lex_state = 91},
  [17] = {.lex_state = 91},
  [18] = {.lex_state = 91},
  [19] = {.lex_state = 91},
  [20] = {.lex_state = 91},
  [21] = {.lex_state = 91},
  [22] = {.lex_state = 91},
  [23] = {.lex_state = 91},
  [24] = {.lex_state = 91},
  [25] = {.lex_state = 91},
  [26] = {.lex_state = 91},
  [27] = {.lex_state = 91},
  [28] = {.lex_state = 91},
  [29] = {.lex_state = 91},
  [30] = {.lex_state = 91},
  [31] = {.lex_state = 91},
  [32] = {.lex_state = 15},
  [33] = {.lex_state = 15},
  [34] = {.lex_state = 15},
  [35] = {.lex_state = 91},
  [36] = {.lex_state = 8},
  [37] = {.lex_state = 14},
  [38] = {.lex_state = 8},
  [39] = {.lex_state = 14},
  [40] = {.lex_state = 8},
  [41] = {.lex_state = 14},
  [42] = {.lex_state = 8},
  [43] = {.lex_state = 9},
  [44] = {.lex_state = 91},
  [45] = {.lex_state = 14},
  [46] = {.lex_state = 14},
  [47] = {.lex_state = 91},
  [48] = {.lex_state = 14},
  [49] = {.lex_state = 15},
  [50] = {.lex_state = 9},
  [51] = {.lex_state = 91},
  [52] = {.lex_state = 91},
  [53] = {.lex_state = 15},
  [54] = {.lex_state = 15},
  [55] = {.lex_state = 15},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 15},
  [58] = {.lex_state = 9},
  [59] = {.lex_state = 9},
  [60] = {.lex_state = 15},
  [61] = {.lex_state = 15},
  [62] = {.lex_state = 8},
  [63] = {.lex_state = 9},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 8},
  [67] = {.lex_state = 9},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 8},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 15},
  [72] = {.lex_state = 8},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 15},
  [75] = {.lex_state = 15},
  [76] = {.lex_state = 15},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 16},
  [79] = {.lex_state = 15},
  [80] = {.lex_state = 15},
  [81] = {.lex_state = 15},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 15},
  [85] = {.lex_state = 91},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 91},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 91},
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
    [anon_sym_sendto] = ACTIONS(1),
    [anon_sym_luacall] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [anon_sym_tempo] = ACTIONS(1),
    [anon_sym_sec] = ACTIONS(1),
    [anon_sym_ms] = ACTIONS(1),
  },
  [1] = {
    [sym_score] = STATE(91),
    [sym__statement] = STATE(2),
    [sym_LUA] = STATE(2),
    [sym_CONFIG] = STATE(2),
    [sym_configId] = STATE(54),
    [sym_numberConfig] = STATE(30),
    [sym_EVENT] = STATE(2),
    [sym_pitchEventId] = STATE(40),
    [sym_restEventId] = STATE(53),
    [sym_timeEventId] = STATE(70),
    [sym_pitchEvent] = STATE(29),
    [sym_restEvent] = STATE(29),
    [sym_freeEvent] = STATE(29),
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
    STATE(30), 1,
      sym_numberConfig,
    STATE(40), 1,
      sym_pitchEventId,
    STATE(53), 1,
      sym_restEventId,
    STATE(54), 1,
      sym_configId,
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
    STATE(29), 3,
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
    STATE(30), 1,
      sym_numberConfig,
    STATE(40), 1,
      sym_pitchEventId,
    STATE(53), 1,
      sym_restEventId,
    STATE(54), 1,
      sym_configId,
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
    STATE(29), 3,
      sym_pitchEvent,
      sym_restEvent,
      sym_freeEvent,
    STATE(3), 5,
      sym__statement,
      sym_LUA,
      sym_CONFIG,
      sym_EVENT,
      aux_sym_score_repeat1,
  [106] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_sendto,
    ACTIONS(44), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(65), 1,
      sym_timedAction,
    STATE(9), 2,
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
  [144] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_sendto,
    ACTIONS(44), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(65), 1,
      sym_timedAction,
    STATE(8), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(46), 10,
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
  [182] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_sendto,
    ACTIONS(44), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(65), 1,
      sym_timedAction,
    STATE(9), 2,
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
  [220] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_sendto,
    ACTIONS(44), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(65), 1,
      sym_timedAction,
    STATE(4), 2,
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
  [258] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_sendto,
    ACTIONS(44), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(65), 1,
      sym_timedAction,
    STATE(9), 2,
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
  [296] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(56), 1,
      anon_sym_ACTION,
    ACTIONS(59), 1,
      anon_sym_delay,
    ACTIONS(62), 1,
      anon_sym_sendto,
    ACTIONS(65), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(65), 1,
      sym_timedAction,
    STATE(9), 2,
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
  [334] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_COMMA,
    STATE(15), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(68), 14,
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
      anon_sym_luacall,
  [360] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_COMMA,
    STATE(15), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(72), 14,
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
      anon_sym_luacall,
  [386] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_COMMA,
    STATE(11), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(74), 14,
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
      anon_sym_luacall,
  [412] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_COMMA,
    STATE(10), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(76), 14,
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
      anon_sym_luacall,
  [438] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_COMMA,
    STATE(16), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(78), 14,
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
      anon_sym_luacall,
  [464] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(82), 1,
      anon_sym_COMMA,
    STATE(15), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(80), 14,
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
      anon_sym_luacall,
  [490] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_COMMA,
    STATE(15), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(85), 14,
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
      anon_sym_luacall,
  [516] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_COMMA,
    STATE(18), 1,
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
      anon_sym_luacall,
  [542] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_COMMA,
    STATE(15), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(89), 14,
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
      anon_sym_luacall,
  [568] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(80), 15,
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
      anon_sym_luacall,
  [589] = 2,
    ACTIONS(3), 1,
      sym_comment,
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
      anon_sym_luacall,
  [610] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 15,
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
      anon_sym_luacall,
  [631] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(95), 15,
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
      anon_sym_luacall,
  [652] = 2,
    ACTIONS(3), 1,
      sym_comment,
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
      anon_sym_luacall,
  [672] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(99), 14,
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
      anon_sym_luacall,
  [692] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(101), 10,
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
  [708] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 10,
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
  [724] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(105), 10,
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
  [740] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 10,
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
  [756] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(109), 10,
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
  [772] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(111), 10,
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
  [788] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_sendto,
    ACTIONS(44), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(65), 1,
      sym_timedAction,
    STATE(6), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
  [814] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(113), 1,
      anon_sym_RBRACK,
    ACTIONS(115), 1,
      aux_sym_actionKey_token1,
    ACTIONS(118), 1,
      aux_sym_number_token1,
    ACTIONS(121), 1,
      aux_sym_number_token2,
    STATE(32), 2,
      sym_pdarg,
      aux_sym_pdargs_repeat1,
    STATE(60), 2,
      sym_number,
      sym_symbol,
  [838] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(124), 1,
      anon_sym_RBRACK,
    ACTIONS(126), 1,
      aux_sym_actionKey_token1,
    ACTIONS(128), 1,
      aux_sym_number_token1,
    ACTIONS(130), 1,
      aux_sym_number_token2,
    STATE(32), 2,
      sym_pdarg,
      aux_sym_pdargs_repeat1,
    STATE(60), 2,
      sym_number,
      sym_symbol,
  [862] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(126), 1,
      aux_sym_actionKey_token1,
    ACTIONS(128), 1,
      aux_sym_number_token1,
    ACTIONS(130), 1,
      aux_sym_number_token2,
    STATE(33), 2,
      sym_pdarg,
      aux_sym_pdargs_repeat1,
    STATE(60), 2,
      sym_number,
      sym_symbol,
  [883] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 7,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
      anon_sym_tempo,
      anon_sym_sec,
      anon_sym_ms,
  [896] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(132), 1,
      anon_sym_RPAREN,
    ACTIONS(134), 1,
      sym_midi,
    ACTIONS(137), 1,
      sym_pitchname,
    STATE(69), 1,
      sym_noteName,
    STATE(36), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [916] = 6,
    ACTIONS(140), 1,
      anon_sym_LBRACE,
    ACTIONS(142), 1,
      anon_sym_RBRACE,
    ACTIONS(146), 1,
      sym_comment,
    STATE(45), 1,
      aux_sym_lua_body_repeat1,
    STATE(94), 1,
      sym_lua_body,
    ACTIONS(144), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [936] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(148), 1,
      anon_sym_RPAREN,
    ACTIONS(150), 1,
      sym_midi,
    ACTIONS(152), 1,
      sym_pitchname,
    STATE(69), 1,
      sym_noteName,
    STATE(36), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [956] = 6,
    ACTIONS(140), 1,
      anon_sym_LBRACE,
    ACTIONS(146), 1,
      sym_comment,
    ACTIONS(154), 1,
      anon_sym_RBRACE,
    STATE(45), 1,
      aux_sym_lua_body_repeat1,
    STATE(88), 1,
      sym_lua_body,
    ACTIONS(144), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [976] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(156), 1,
      anon_sym_LPAREN,
    ACTIONS(158), 1,
      sym_midi,
    ACTIONS(160), 1,
      sym_pitchname,
    STATE(75), 1,
      sym_noteName,
    STATE(55), 2,
      sym_pitches,
      sym_pitch,
  [996] = 5,
    ACTIONS(146), 1,
      sym_comment,
    ACTIONS(162), 1,
      anon_sym_LBRACE,
    ACTIONS(165), 1,
      anon_sym_RBRACE,
    STATE(41), 1,
      aux_sym_lua_body_repeat1,
    ACTIONS(167), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1013] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(150), 1,
      sym_midi,
    ACTIONS(152), 1,
      sym_pitchname,
    STATE(69), 1,
      sym_noteName,
    STATE(38), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [1030] = 6,
    ACTIONS(146), 1,
      sym_comment,
    ACTIONS(170), 1,
      aux_sym_lua_call_token1,
    ACTIONS(172), 1,
      anon_sym_LPAREN,
    ACTIONS(174), 1,
      anon_sym_RPAREN,
    STATE(50), 1,
      aux_sym_lua_call_repeat1,
    STATE(86), 1,
      sym_lua_call,
  [1049] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(40), 1,
      anon_sym_delay,
    ACTIONS(42), 1,
      anon_sym_sendto,
    ACTIONS(44), 1,
      anon_sym_luacall,
    STATE(14), 1,
      sym_exec,
    STATE(68), 1,
      sym_timedAction,
  [1068] = 5,
    ACTIONS(140), 1,
      anon_sym_LBRACE,
    ACTIONS(146), 1,
      sym_comment,
    ACTIONS(176), 1,
      anon_sym_RBRACE,
    STATE(41), 1,
      aux_sym_lua_body_repeat1,
    ACTIONS(178), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1085] = 2,
    ACTIONS(146), 1,
      sym_comment,
    ACTIONS(180), 4,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1095] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(184), 1,
      sym_octave,
    STATE(95), 1,
      sym_alteration,
    ACTIONS(182), 2,
      anon_sym_POUND,
      anon_sym_b,
  [1109] = 2,
    ACTIONS(146), 1,
      sym_comment,
    ACTIONS(165), 4,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1119] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(186), 1,
      aux_sym_number_token1,
    ACTIONS(97), 3,
      anon_sym_RBRACK,
      aux_sym_actionKey_token1,
      aux_sym_number_token2,
  [1131] = 5,
    ACTIONS(146), 1,
      sym_comment,
    ACTIONS(172), 1,
      anon_sym_LPAREN,
    ACTIONS(188), 1,
      aux_sym_lua_call_token1,
    ACTIONS(190), 1,
      anon_sym_RPAREN,
    STATE(58), 1,
      aux_sym_lua_call_repeat1,
  [1147] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(192), 1,
      sym_octave,
    STATE(90), 1,
      sym_alteration,
    ACTIONS(182), 2,
      anon_sym_POUND,
      anon_sym_b,
  [1161] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(99), 4,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [1171] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(194), 1,
      aux_sym_number_token1,
    ACTIONS(196), 1,
      aux_sym_number_token2,
    STATE(7), 1,
      sym_duration,
    STATE(24), 1,
      sym_number,
  [1187] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(194), 1,
      aux_sym_number_token1,
    ACTIONS(196), 1,
      aux_sym_number_token2,
    STATE(25), 1,
      sym_number,
    STATE(27), 1,
      sym_numberSet,
  [1203] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(194), 1,
      aux_sym_number_token1,
    ACTIONS(196), 1,
      aux_sym_number_token2,
    STATE(5), 1,
      sym_duration,
    STATE(24), 1,
      sym_number,
  [1219] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(77), 1,
      sym_timeUnit,
    ACTIONS(198), 3,
      anon_sym_tempo,
      anon_sym_sec,
      anon_sym_ms,
  [1231] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(202), 1,
      aux_sym_number_token1,
    ACTIONS(200), 3,
      anon_sym_RBRACK,
      aux_sym_actionKey_token1,
      aux_sym_number_token2,
  [1243] = 5,
    ACTIONS(146), 1,
      sym_comment,
    ACTIONS(204), 1,
      aux_sym_lua_call_token1,
    ACTIONS(207), 1,
      anon_sym_LPAREN,
    ACTIONS(210), 1,
      anon_sym_RPAREN,
    STATE(58), 1,
      aux_sym_lua_call_repeat1,
  [1259] = 5,
    ACTIONS(146), 1,
      sym_comment,
    ACTIONS(170), 1,
      aux_sym_lua_call_token1,
    ACTIONS(172), 1,
      anon_sym_LPAREN,
    STATE(50), 1,
      aux_sym_lua_call_repeat1,
    STATE(89), 1,
      sym_lua_call,
  [1275] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(214), 1,
      aux_sym_number_token1,
    ACTIONS(212), 3,
      anon_sym_RBRACK,
      aux_sym_actionKey_token1,
      aux_sym_number_token2,
  [1287] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(216), 1,
      aux_sym_number_token1,
    ACTIONS(218), 1,
      aux_sym_number_token2,
    STATE(31), 1,
      sym_duration,
    STATE(52), 1,
      sym_number,
  [1303] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(220), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [1312] = 2,
    ACTIONS(146), 1,
      sym_comment,
    ACTIONS(210), 3,
      aux_sym_lua_call_token1,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [1321] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(42), 1,
      anon_sym_sendto,
    ACTIONS(44), 1,
      anon_sym_luacall,
    STATE(19), 1,
      sym_exec,
  [1334] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(42), 1,
      anon_sym_sendto,
    ACTIONS(44), 1,
      anon_sym_luacall,
    STATE(12), 1,
      sym_exec,
  [1347] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 3,
      anon_sym_LPAREN,
      sym_midi,
      sym_pitchname,
  [1356] = 2,
    ACTIONS(146), 1,
      sym_comment,
    ACTIONS(224), 3,
      aux_sym_lua_call_token1,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [1365] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(42), 1,
      anon_sym_sendto,
    ACTIONS(44), 1,
      anon_sym_luacall,
    STATE(17), 1,
      sym_exec,
  [1378] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(226), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [1387] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(61), 1,
      sym_eventId,
    ACTIONS(228), 2,
      anon_sym_timed,
      anon_sym_internal,
  [1398] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(216), 1,
      aux_sym_number_token1,
    ACTIONS(218), 1,
      aux_sym_number_token2,
    STATE(56), 1,
      sym_number,
  [1411] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(230), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [1420] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(232), 2,
      anon_sym_sendto,
      anon_sym_luacall,
  [1428] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(220), 1,
      aux_sym_number_token2,
    ACTIONS(234), 1,
      aux_sym_number_token1,
  [1438] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(226), 1,
      aux_sym_number_token2,
    ACTIONS(236), 1,
      aux_sym_number_token1,
  [1448] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(238), 1,
      aux_sym_number_token1,
    ACTIONS(240), 1,
      aux_sym_number_token2,
  [1458] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 2,
      anon_sym_sendto,
      anon_sym_luacall,
  [1466] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(244), 1,
      sym_keyword,
    STATE(82), 1,
      sym_receiver,
  [1476] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(246), 1,
      aux_sym_number_token1,
    ACTIONS(248), 1,
      aux_sym_number_token2,
  [1486] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(230), 1,
      aux_sym_number_token2,
    ACTIONS(250), 1,
      aux_sym_number_token1,
  [1496] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(252), 1,
      aux_sym_number_token1,
    ACTIONS(254), 1,
      aux_sym_number_token2,
  [1506] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(256), 1,
      anon_sym_LBRACK,
    STATE(21), 1,
      sym_pdargs,
  [1516] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 2,
      anon_sym_timed,
      anon_sym_internal,
  [1524] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(260), 1,
      aux_sym_number_token1,
    ACTIONS(262), 1,
      aux_sym_number_token2,
  [1534] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(264), 1,
      sym_octave,
  [1541] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(266), 1,
      anon_sym_RPAREN,
  [1548] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(268), 1,
      anon_sym_LBRACK,
  [1555] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(270), 1,
      anon_sym_RBRACE,
  [1562] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      anon_sym_RPAREN,
  [1569] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(274), 1,
      sym_octave,
  [1576] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(276), 1,
      ts_builtin_sym_end,
  [1583] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(278), 1,
      anon_sym_LPAREN,
  [1590] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(280), 1,
      anon_sym_LBRACE,
  [1597] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(282), 1,
      anon_sym_RBRACE,
  [1604] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(284), 1,
      sym_octave,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 53,
  [SMALL_STATE(4)] = 106,
  [SMALL_STATE(5)] = 144,
  [SMALL_STATE(6)] = 182,
  [SMALL_STATE(7)] = 220,
  [SMALL_STATE(8)] = 258,
  [SMALL_STATE(9)] = 296,
  [SMALL_STATE(10)] = 334,
  [SMALL_STATE(11)] = 360,
  [SMALL_STATE(12)] = 386,
  [SMALL_STATE(13)] = 412,
  [SMALL_STATE(14)] = 438,
  [SMALL_STATE(15)] = 464,
  [SMALL_STATE(16)] = 490,
  [SMALL_STATE(17)] = 516,
  [SMALL_STATE(18)] = 542,
  [SMALL_STATE(19)] = 568,
  [SMALL_STATE(20)] = 589,
  [SMALL_STATE(21)] = 610,
  [SMALL_STATE(22)] = 631,
  [SMALL_STATE(23)] = 652,
  [SMALL_STATE(24)] = 672,
  [SMALL_STATE(25)] = 692,
  [SMALL_STATE(26)] = 708,
  [SMALL_STATE(27)] = 724,
  [SMALL_STATE(28)] = 740,
  [SMALL_STATE(29)] = 756,
  [SMALL_STATE(30)] = 772,
  [SMALL_STATE(31)] = 788,
  [SMALL_STATE(32)] = 814,
  [SMALL_STATE(33)] = 838,
  [SMALL_STATE(34)] = 862,
  [SMALL_STATE(35)] = 883,
  [SMALL_STATE(36)] = 896,
  [SMALL_STATE(37)] = 916,
  [SMALL_STATE(38)] = 936,
  [SMALL_STATE(39)] = 956,
  [SMALL_STATE(40)] = 976,
  [SMALL_STATE(41)] = 996,
  [SMALL_STATE(42)] = 1013,
  [SMALL_STATE(43)] = 1030,
  [SMALL_STATE(44)] = 1049,
  [SMALL_STATE(45)] = 1068,
  [SMALL_STATE(46)] = 1085,
  [SMALL_STATE(47)] = 1095,
  [SMALL_STATE(48)] = 1109,
  [SMALL_STATE(49)] = 1119,
  [SMALL_STATE(50)] = 1131,
  [SMALL_STATE(51)] = 1147,
  [SMALL_STATE(52)] = 1161,
  [SMALL_STATE(53)] = 1171,
  [SMALL_STATE(54)] = 1187,
  [SMALL_STATE(55)] = 1203,
  [SMALL_STATE(56)] = 1219,
  [SMALL_STATE(57)] = 1231,
  [SMALL_STATE(58)] = 1243,
  [SMALL_STATE(59)] = 1259,
  [SMALL_STATE(60)] = 1275,
  [SMALL_STATE(61)] = 1287,
  [SMALL_STATE(62)] = 1303,
  [SMALL_STATE(63)] = 1312,
  [SMALL_STATE(64)] = 1321,
  [SMALL_STATE(65)] = 1334,
  [SMALL_STATE(66)] = 1347,
  [SMALL_STATE(67)] = 1356,
  [SMALL_STATE(68)] = 1365,
  [SMALL_STATE(69)] = 1378,
  [SMALL_STATE(70)] = 1387,
  [SMALL_STATE(71)] = 1398,
  [SMALL_STATE(72)] = 1411,
  [SMALL_STATE(73)] = 1420,
  [SMALL_STATE(74)] = 1428,
  [SMALL_STATE(75)] = 1438,
  [SMALL_STATE(76)] = 1448,
  [SMALL_STATE(77)] = 1458,
  [SMALL_STATE(78)] = 1466,
  [SMALL_STATE(79)] = 1476,
  [SMALL_STATE(80)] = 1486,
  [SMALL_STATE(81)] = 1496,
  [SMALL_STATE(82)] = 1506,
  [SMALL_STATE(83)] = 1516,
  [SMALL_STATE(84)] = 1524,
  [SMALL_STATE(85)] = 1534,
  [SMALL_STATE(86)] = 1541,
  [SMALL_STATE(87)] = 1548,
  [SMALL_STATE(88)] = 1555,
  [SMALL_STATE(89)] = 1562,
  [SMALL_STATE(90)] = 1569,
  [SMALL_STATE(91)] = 1576,
  [SMALL_STATE(92)] = 1583,
  [SMALL_STATE(93)] = 1590,
  [SMALL_STATE(94)] = 1597,
  [SMALL_STATE(95)] = 1604,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_score, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_score, 1, 0, 0),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0),
  [21] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(93),
  [24] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(81),
  [27] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(66),
  [30] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(84),
  [33] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(83),
  [36] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_restEvent, 3, 0, 0),
  [38] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [40] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [42] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [44] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [46] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEvent, 3, 0, 0),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_freeEvent, 4, 0, 0),
  [50] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_restEvent, 2, 0, 0),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEvent, 4, 0, 0),
  [54] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0),
  [56] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(44),
  [59] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(71),
  [62] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(78),
  [65] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(92),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 2, 0, 3),
  [70] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 3, 0, 5),
  [74] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 2, 0, 5),
  [76] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 1, 0, 3),
  [78] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 2, 0, 4),
  [80] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_ACTION_repeat1, 2, 0, 0),
  [82] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_ACTION_repeat1, 2, 0, 0), SHIFT_REPEAT(64),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 3, 0, 4),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 3, 0, 6),
  [89] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 4, 0, 6),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pdargs, 3, 0, 0),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exec, 3, 0, 9),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exec, 4, 0, 12),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_number, 1, 0, 0),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_duration, 1, 0, 0),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberSet, 1, 0, 0),
  [103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_LUA, 3, 0, 0),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberConfig, 2, 0, 0),
  [107] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_LUA, 4, 0, 0),
  [109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_EVENT, 1, 0, 0),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_CONFIG, 1, 0, 0),
  [113] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pdargs_repeat1, 2, 0, 0),
  [115] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pdargs_repeat1, 2, 0, 0), SHIFT_REPEAT(57),
  [118] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_pdargs_repeat1, 2, 0, 0), SHIFT_REPEAT(49),
  [121] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pdargs_repeat1, 2, 0, 0), SHIFT_REPEAT(49),
  [124] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [126] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [128] = {.entry = {.count = 1, .reusable = false}}, SHIFT(49),
  [130] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [132] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0),
  [134] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(69),
  [137] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(47),
  [140] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [142] = {.entry = {.count = 1, .reusable = false}}, SHIFT(48),
  [144] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [146] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [150] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [154] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [162] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 2, 0, 0), SHIFT_REPEAT(37),
  [165] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 2, 0, 0),
  [167] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 2, 0, 0), SHIFT_REPEAT(41),
  [170] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [172] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [174] = {.entry = {.count = 1, .reusable = false}}, SHIFT(63),
  [176] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lua_body, 1, 0, 0),
  [178] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [180] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 3, 0, 0),
  [182] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [184] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [186] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_number, 1, 0, 0),
  [188] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [190] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lua_call, 1, 0, 10),
  [192] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [194] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [196] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [198] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [200] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_symbol, 1, 0, 0),
  [202] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_symbol, 1, 0, 0),
  [204] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 2, 0, 0), SHIFT_REPEAT(58),
  [207] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 2, 0, 0), SHIFT_REPEAT(43),
  [210] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 2, 0, 0),
  [212] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pdarg, 1, 0, 11),
  [214] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pdarg, 1, 0, 11),
  [216] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [218] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [220] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_noteName, 2, 0, 0),
  [222] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEventId, 1, 0, 2),
  [224] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 3, 0, 0),
  [226] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitch, 1, 0, 0),
  [228] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [230] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_noteName, 3, 0, 0),
  [232] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_timeUnit, 1, 0, 7),
  [234] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_noteName, 2, 0, 0),
  [236] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitch, 1, 0, 0),
  [238] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitches, 3, 0, 0),
  [240] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitches, 3, 0, 0),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_timedAction, 3, 0, 8),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [246] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_eventId, 1, 0, 0),
  [248] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_eventId, 1, 0, 0),
  [250] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_noteName, 3, 0, 0),
  [252] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_configId, 1, 0, 1),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_configId, 1, 0, 1),
  [256] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [258] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_timeEventId, 1, 0, 0),
  [260] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_restEventId, 1, 0, 0),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_restEventId, 1, 0, 0),
  [264] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alteration, 1, 0, 0),
  [266] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [268] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_receiver, 1, 0, 0),
  [270] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [272] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [274] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [276] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [284] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
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
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
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
