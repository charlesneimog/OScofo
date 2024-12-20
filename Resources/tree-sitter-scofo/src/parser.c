#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 96
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 83
#define ALIAS_COUNT 0
#define TOKEN_COUNT 45
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 13
#define MAX_ALIAS_SEQUENCE_LENGTH 4
#define PRODUCTION_ID_COUNT 14

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
  anon_sym_PhaseCoupling = 11,
  anon_sym_SyncStrength = 12,
  anon_sym_TRANSPOSE = 13,
  anon_sym_ENTROPY = 14,
  anon_sym_Entropy = 15,
  anon_sym_PitchSigma = 16,
  anon_sym_FFTSize = 17,
  anon_sym_HopSize = 18,
  anon_sym_NOTE = 19,
  anon_sym_TRILL = 20,
  anon_sym_CHORD = 21,
  anon_sym_REST = 22,
  anon_sym_EVENT = 23,
  anon_sym_timed = 24,
  anon_sym_internal = 25,
  sym_midi = 26,
  sym_pitchname = 27,
  anon_sym_POUND = 28,
  anon_sym_b = 29,
  sym_octave = 30,
  anon_sym_ACTION = 31,
  anon_sym_COMMA = 32,
  anon_sym_delay = 33,
  anon_sym_sendto = 34,
  anon_sym_luacall = 35,
  anon_sym_LBRACK = 36,
  anon_sym_RBRACK = 37,
  aux_sym_actionKey_token1 = 38,
  aux_sym_number_token1 = 39,
  aux_sym_number_token2 = 40,
  sym_comment = 41,
  anon_sym_tempo = 42,
  anon_sym_sec = 43,
  anon_sym_ms = 44,
  sym_score = 45,
  sym__statement = 46,
  sym_LUA = 47,
  sym_lua_body = 48,
  sym_lua_call = 49,
  sym_CONFIG = 50,
  sym_configId = 51,
  sym_numberConfig = 52,
  sym_numberSet = 53,
  sym_EVENT = 54,
  sym_pitchEventId = 55,
  sym_restEventId = 56,
  sym_timeEventId = 57,
  sym_pitchEvent = 58,
  sym_restEvent = 59,
  sym_freeEvent = 60,
  sym_eventId = 61,
  sym_pitches = 62,
  sym_pitch = 63,
  sym_noteName = 64,
  sym_alteration = 65,
  sym_duration = 66,
  sym_ACTION = 67,
  sym_timedAction = 68,
  sym_exec = 69,
  sym_pdargs = 70,
  sym_pdarg = 71,
  sym_receiver = 72,
  sym_number = 73,
  sym_symbol = 74,
  sym_timeUnit = 75,
  aux_sym_score_repeat1 = 76,
  aux_sym_lua_body_repeat1 = 77,
  aux_sym_lua_call_repeat1 = 78,
  aux_sym_pitchEvent_repeat1 = 79,
  aux_sym_pitches_repeat1 = 80,
  aux_sym_ACTION_repeat1 = 81,
  aux_sym_pdargs_repeat1 = 82,
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
  [anon_sym_PhaseCoupling] = "keyword",
  [anon_sym_SyncStrength] = "keyword",
  [anon_sym_TRANSPOSE] = "keyword",
  [anon_sym_ENTROPY] = "keyword",
  [anon_sym_Entropy] = "keyword",
  [anon_sym_PitchSigma] = "keyword",
  [anon_sym_FFTSize] = "keyword",
  [anon_sym_HopSize] = "keyword",
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
  [anon_sym_PhaseCoupling] = sym_keyword,
  [anon_sym_SyncStrength] = sym_keyword,
  [anon_sym_TRANSPOSE] = sym_keyword,
  [anon_sym_ENTROPY] = sym_keyword,
  [anon_sym_Entropy] = sym_keyword,
  [anon_sym_PitchSigma] = sym_keyword,
  [anon_sym_FFTSize] = sym_keyword,
  [anon_sym_HopSize] = sym_keyword,
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
  [anon_sym_PhaseCoupling] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_SyncStrength] = {
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
  [anon_sym_Entropy] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_PitchSigma] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_FFTSize] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_HopSize] = {
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
  [7] = {.index = 8, .length = 2},
  [8] = {.index = 10, .length = 1},
  [9] = {.index = 11, .length = 3},
  [10] = {.index = 14, .length = 3},
  [11] = {.index = 17, .length = 1},
  [12] = {.index = 18, .length = 1},
  [13] = {.index = 19, .length = 4},
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
    {field_keyword, 0},
    {field_receiver, 1},
  [6] =
    {field_exec, 1},
    {field_timedAction, 0},
  [8] =
    {field_exec, 2},
    {field_timedAction, 1},
  [10] =
    {field_timeUnit, 0},
  [11] =
    {field_actionKey, 0},
    {field_timeUnit, 2},
    {field_value, 1},
  [14] =
    {field_keyword, 0},
    {field_pdargs, 2},
    {field_receiver, 1},
  [17] =
    {field_lua_call, 0},
  [18] =
    {field_pdarg, 0},
  [19] =
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
  [35] = 35,
  [36] = 36,
  [37] = 25,
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
  [49] = 49,
  [50] = 50,
  [51] = 25,
  [52] = 52,
  [53] = 26,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 50,
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
  [75] = 74,
  [76] = 64,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 66,
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
  [95] = 92,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(141);
      ADVANCE_MAP(
        '#', 198,
        '(', 168,
        ')', 169,
        ',', 203,
        '-', 13,
        '/', 10,
        '0', 187,
        '1', 188,
        'A', 192,
        'B', 196,
        'C', 194,
        'E', 195,
        'F', 193,
        'H', 107,
        'L', 60,
        'N', 39,
        'P', 87,
        'R', 22,
        'S', 131,
        'T', 44,
        '[', 207,
      );
      if (lookahead == '\\') SKIP(137);
      if (lookahead == ']') ADVANCE(208);
      if (lookahead == 'b') ADVANCE(199);
      if (lookahead == 'd') ADVANCE(197);
      if (lookahead == 'i') ADVANCE(104);
      if (lookahead == 'l') ADVANCE(127);
      if (lookahead == 'm') ADVANCE(119);
      if (lookahead == 's') ADVANCE(75);
      if (lookahead == 't') ADVANCE(77);
      if (lookahead == '{') ADVANCE(144);
      if (lookahead == '}') ADVANCE(145);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('D' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(191);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(190);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(14);
      END_STATE();
    case 2:
      if (lookahead == '\n') SKIP(14);
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
      if (lookahead == '\r') ADVANCE(215);
      if (lookahead == '\\') ADVANCE(213);
      if (lookahead != 0) ADVANCE(214);
      END_STATE();
    case 8:
      if (lookahead == '(') ADVANCE(168);
      if (lookahead == ')') ADVANCE(169);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '0') ADVANCE(187);
      if (lookahead == '1') ADVANCE(188);
      if (lookahead == '\\') SKIP(4);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(8);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(190);
      if (('A' <= lookahead && lookahead <= 'G') ||
          ('a' <= lookahead && lookahead <= 'g')) ADVANCE(191);
      END_STATE();
    case 9:
      if (lookahead == '(') ADVANCE(168);
      if (lookahead == ')') ADVANCE(169);
      if (lookahead == '/') ADVANCE(162);
      if (lookahead == '\\') ADVANCE(158);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(165);
      if (lookahead != 0 &&
          lookahead != '`') ADVANCE(167);
      END_STATE();
    case 10:
      if (lookahead == '*') ADVANCE(12);
      if (lookahead == '/') ADVANCE(214);
      END_STATE();
    case 11:
      if (lookahead == '*') ADVANCE(11);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead != 0) ADVANCE(12);
      END_STATE();
    case 12:
      if (lookahead == '*') ADVANCE(11);
      if (lookahead != 0) ADVANCE(12);
      END_STATE();
    case 13:
      if (lookahead == '-') ADVANCE(170);
      END_STATE();
    case 14:
      if (lookahead == '-') ADVANCE(134);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '\\') SKIP(2);
      if (lookahead == ']') ADVANCE(208);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(14);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(210);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(209);
      END_STATE();
    case 15:
      if (lookahead == '-') ADVANCE(155);
      if (lookahead == '/') ADVANCE(151);
      if (lookahead == '\\') ADVANCE(146);
      if (lookahead == '{') ADVANCE(144);
      if (lookahead == '}') ADVANCE(145);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(154);
      if (lookahead != 0 &&
          lookahead != '`') ADVANCE(157);
      END_STATE();
    case 16:
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '\\') SKIP(6);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(142);
      END_STATE();
    case 17:
      if (lookahead == 'A') ADVANCE(143);
      END_STATE();
    case 18:
      if (lookahead == 'A') ADVANCE(34);
      if (lookahead == 'I') ADVANCE(30);
      END_STATE();
    case 19:
      if (lookahead == 'C') ADVANCE(54);
      END_STATE();
    case 20:
      if (lookahead == 'C') ADVANCE(110);
      END_STATE();
    case 21:
      if (lookahead == 'D') ADVANCE(182);
      END_STATE();
    case 22:
      if (lookahead == 'E') ADVANCE(51);
      END_STATE();
    case 23:
      if (lookahead == 'E') ADVANCE(35);
      END_STATE();
    case 24:
      if (lookahead == 'E') ADVANCE(180);
      END_STATE();
    case 25:
      if (lookahead == 'E') ADVANCE(174);
      END_STATE();
    case 26:
      if (lookahead == 'F') ADVANCE(57);
      END_STATE();
    case 27:
      if (lookahead == 'H') ADVANCE(37);
      END_STATE();
    case 28:
      if (lookahead == 'I') ADVANCE(38);
      END_STATE();
    case 29:
      if (lookahead == 'L') ADVANCE(181);
      END_STATE();
    case 30:
      if (lookahead == 'L') ADVANCE(29);
      END_STATE();
    case 31:
      if (lookahead == 'M') ADVANCE(171);
      END_STATE();
    case 32:
      if (lookahead == 'N') ADVANCE(202);
      END_STATE();
    case 33:
      if (lookahead == 'N') ADVANCE(59);
      if (lookahead == 'V') ADVANCE(23);
      if (lookahead == 'n') ADVANCE(121);
      END_STATE();
    case 34:
      if (lookahead == 'N') ADVANCE(49);
      END_STATE();
    case 35:
      if (lookahead == 'N') ADVANCE(56);
      END_STATE();
    case 36:
      if (lookahead == 'O') ADVANCE(42);
      END_STATE();
    case 37:
      if (lookahead == 'O') ADVANCE(45);
      END_STATE();
    case 38:
      if (lookahead == 'O') ADVANCE(32);
      END_STATE();
    case 39:
      if (lookahead == 'O') ADVANCE(58);
      END_STATE();
    case 40:
      if (lookahead == 'O') ADVANCE(50);
      END_STATE();
    case 41:
      if (lookahead == 'P') ADVANCE(31);
      END_STATE();
    case 42:
      if (lookahead == 'P') ADVANCE(61);
      END_STATE();
    case 43:
      if (lookahead == 'P') ADVANCE(40);
      END_STATE();
    case 44:
      if (lookahead == 'R') ADVANCE(18);
      END_STATE();
    case 45:
      if (lookahead == 'R') ADVANCE(21);
      END_STATE();
    case 46:
      if (lookahead == 'R') ADVANCE(36);
      END_STATE();
    case 47:
      if (lookahead == 'S') ADVANCE(90);
      END_STATE();
    case 48:
      if (lookahead == 'S') ADVANCE(91);
      END_STATE();
    case 49:
      if (lookahead == 'S') ADVANCE(43);
      END_STATE();
    case 50:
      if (lookahead == 'S') ADVANCE(25);
      END_STATE();
    case 51:
      if (lookahead == 'S') ADVANCE(55);
      END_STATE();
    case 52:
      if (lookahead == 'S') ADVANCE(126);
      END_STATE();
    case 53:
      if (lookahead == 'S') ADVANCE(93);
      END_STATE();
    case 54:
      if (lookahead == 'T') ADVANCE(28);
      END_STATE();
    case 55:
      if (lookahead == 'T') ADVANCE(183);
      END_STATE();
    case 56:
      if (lookahead == 'T') ADVANCE(184);
      END_STATE();
    case 57:
      if (lookahead == 'T') ADVANCE(47);
      END_STATE();
    case 58:
      if (lookahead == 'T') ADVANCE(24);
      END_STATE();
    case 59:
      if (lookahead == 'T') ADVANCE(46);
      END_STATE();
    case 60:
      if (lookahead == 'U') ADVANCE(17);
      END_STATE();
    case 61:
      if (lookahead == 'Y') ADVANCE(175);
      END_STATE();
    case 62:
      if (lookahead == 'a') ADVANCE(177);
      END_STATE();
    case 63:
      if (lookahead == 'a') ADVANCE(129);
      END_STATE();
    case 64:
      if (lookahead == 'a') ADVANCE(120);
      END_STATE();
    case 65:
      if (lookahead == 'a') ADVANCE(97);
      END_STATE();
    case 66:
      if (lookahead == 'a') ADVANCE(71);
      END_STATE();
    case 67:
      if (lookahead == 'a') ADVANCE(95);
      END_STATE();
    case 68:
      if (lookahead == 'c') ADVANCE(217);
      if (lookahead == 'n') ADVANCE(73);
      END_STATE();
    case 69:
      if (lookahead == 'c') ADVANCE(89);
      END_STATE();
    case 70:
      if (lookahead == 'c') ADVANCE(52);
      END_STATE();
    case 71:
      if (lookahead == 'c') ADVANCE(65);
      END_STATE();
    case 72:
      if (lookahead == 'd') ADVANCE(185);
      END_STATE();
    case 73:
      if (lookahead == 'd') ADVANCE(125);
      END_STATE();
    case 74:
      if (lookahead == 'e') ADVANCE(96);
      END_STATE();
    case 75:
      if (lookahead == 'e') ADVANCE(68);
      END_STATE();
    case 76:
      if (lookahead == 'e') ADVANCE(99);
      END_STATE();
    case 77:
      if (lookahead == 'e') ADVANCE(99);
      if (lookahead == 'i') ADVANCE(100);
      END_STATE();
    case 78:
      if (lookahead == 'e') ADVANCE(20);
      END_STATE();
    case 79:
      if (lookahead == 'e') ADVANCE(178);
      END_STATE();
    case 80:
      if (lookahead == 'e') ADVANCE(179);
      END_STATE();
    case 81:
      if (lookahead == 'e') ADVANCE(116);
      END_STATE();
    case 82:
      if (lookahead == 'e') ADVANCE(72);
      END_STATE();
    case 83:
      if (lookahead == 'e') ADVANCE(103);
      END_STATE();
    case 84:
      if (lookahead == 'g') ADVANCE(172);
      END_STATE();
    case 85:
      if (lookahead == 'g') ADVANCE(101);
      END_STATE();
    case 86:
      if (lookahead == 'g') ADVANCE(124);
      END_STATE();
    case 87:
      if (lookahead == 'h') ADVANCE(64);
      if (lookahead == 'i') ADVANCE(122);
      END_STATE();
    case 88:
      if (lookahead == 'h') ADVANCE(173);
      END_STATE();
    case 89:
      if (lookahead == 'h') ADVANCE(48);
      END_STATE();
    case 90:
      if (lookahead == 'i') ADVANCE(132);
      END_STATE();
    case 91:
      if (lookahead == 'i') ADVANCE(85);
      END_STATE();
    case 92:
      if (lookahead == 'i') ADVANCE(105);
      END_STATE();
    case 93:
      if (lookahead == 'i') ADVANCE(133);
      END_STATE();
    case 94:
      if (lookahead == 'l') ADVANCE(206);
      END_STATE();
    case 95:
      if (lookahead == 'l') ADVANCE(186);
      END_STATE();
    case 96:
      if (lookahead == 'l') ADVANCE(63);
      END_STATE();
    case 97:
      if (lookahead == 'l') ADVANCE(94);
      END_STATE();
    case 98:
      if (lookahead == 'l') ADVANCE(92);
      END_STATE();
    case 99:
      if (lookahead == 'm') ADVANCE(112);
      END_STATE();
    case 100:
      if (lookahead == 'm') ADVANCE(82);
      END_STATE();
    case 101:
      if (lookahead == 'm') ADVANCE(62);
      END_STATE();
    case 102:
      if (lookahead == 'n') ADVANCE(70);
      END_STATE();
    case 103:
      if (lookahead == 'n') ADVANCE(86);
      END_STATE();
    case 104:
      if (lookahead == 'n') ADVANCE(123);
      END_STATE();
    case 105:
      if (lookahead == 'n') ADVANCE(84);
      END_STATE();
    case 106:
      if (lookahead == 'n') ADVANCE(67);
      END_STATE();
    case 107:
      if (lookahead == 'o') ADVANCE(115);
      END_STATE();
    case 108:
      if (lookahead == 'o') ADVANCE(216);
      END_STATE();
    case 109:
      if (lookahead == 'o') ADVANCE(205);
      END_STATE();
    case 110:
      if (lookahead == 'o') ADVANCE(128);
      END_STATE();
    case 111:
      if (lookahead == 'o') ADVANCE(113);
      END_STATE();
    case 112:
      if (lookahead == 'p') ADVANCE(108);
      END_STATE();
    case 113:
      if (lookahead == 'p') ADVANCE(130);
      END_STATE();
    case 114:
      if (lookahead == 'p') ADVANCE(98);
      END_STATE();
    case 115:
      if (lookahead == 'p') ADVANCE(53);
      END_STATE();
    case 116:
      if (lookahead == 'r') ADVANCE(106);
      END_STATE();
    case 117:
      if (lookahead == 'r') ADVANCE(83);
      END_STATE();
    case 118:
      if (lookahead == 'r') ADVANCE(111);
      END_STATE();
    case 119:
      if (lookahead == 's') ADVANCE(218);
      END_STATE();
    case 120:
      if (lookahead == 's') ADVANCE(78);
      END_STATE();
    case 121:
      if (lookahead == 't') ADVANCE(118);
      END_STATE();
    case 122:
      if (lookahead == 't') ADVANCE(69);
      END_STATE();
    case 123:
      if (lookahead == 't') ADVANCE(81);
      END_STATE();
    case 124:
      if (lookahead == 't') ADVANCE(88);
      END_STATE();
    case 125:
      if (lookahead == 't') ADVANCE(109);
      END_STATE();
    case 126:
      if (lookahead == 't') ADVANCE(117);
      END_STATE();
    case 127:
      if (lookahead == 'u') ADVANCE(66);
      END_STATE();
    case 128:
      if (lookahead == 'u') ADVANCE(114);
      END_STATE();
    case 129:
      if (lookahead == 'y') ADVANCE(204);
      END_STATE();
    case 130:
      if (lookahead == 'y') ADVANCE(176);
      END_STATE();
    case 131:
      if (lookahead == 'y') ADVANCE(102);
      END_STATE();
    case 132:
      if (lookahead == 'z') ADVANCE(79);
      END_STATE();
    case 133:
      if (lookahead == 'z') ADVANCE(80);
      END_STATE();
    case 134:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(210);
      END_STATE();
    case 135:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(211);
      END_STATE();
    case 136:
      if (eof) ADVANCE(141);
      if (lookahead == '\n') SKIP(0);
      END_STATE();
    case 137:
      if (eof) ADVANCE(141);
      if (lookahead == '\n') SKIP(0);
      if (lookahead == '\r') SKIP(136);
      END_STATE();
    case 138:
      if (eof) ADVANCE(141);
      if (lookahead == '\n') SKIP(140);
      END_STATE();
    case 139:
      if (eof) ADVANCE(141);
      if (lookahead == '\n') SKIP(140);
      if (lookahead == '\r') SKIP(138);
      END_STATE();
    case 140:
      if (eof) ADVANCE(141);
      ADVANCE_MAP(
        '#', 198,
        ',', 203,
        '/', 10,
        '1', 201,
        'A', 19,
        'B', 41,
        'C', 27,
        'E', 33,
        'F', 26,
        'H', 107,
        'L', 60,
        'N', 39,
        'P', 87,
        'R', 22,
        'S', 131,
        'T', 44,
        '[', 207,
      );
      if (lookahead == '\\') SKIP(139);
      if (lookahead == 'b') ADVANCE(199);
      if (lookahead == 'd') ADVANCE(74);
      if (lookahead == 'l') ADVANCE(127);
      if (lookahead == 'm') ADVANCE(119);
      if (lookahead == 's') ADVANCE(75);
      if (lookahead == 't') ADVANCE(76);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(140);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(200);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(sym_keyword);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(142);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(anon_sym_LUA);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(154);
      if (lookahead == '\r') ADVANCE(147);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(157);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(154);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(157);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(157);
      if (lookahead == '\\') ADVANCE(150);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(214);
      if (lookahead != 0) ADVANCE(148);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\n') ADVANCE(157);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(170);
      if (lookahead != 0) ADVANCE(149);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\r') ADVANCE(156);
      if (lookahead == '\\') ADVANCE(150);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(214);
      if (lookahead != 0) ADVANCE(148);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '*') ADVANCE(153);
      if (lookahead == '/') ADVANCE(148);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(157);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '*') ADVANCE(152);
      if (lookahead == '/') ADVANCE(157);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(12);
      if (lookahead != 0) ADVANCE(153);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '*') ADVANCE(152);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(12);
      if (lookahead != 0) ADVANCE(153);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '-') ADVANCE(155);
      if (lookahead == '/') ADVANCE(151);
      if (lookahead == '\\') ADVANCE(146);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(154);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(157);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '-') ADVANCE(149);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(157);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead == '\\') ADVANCE(150);
      if (lookahead == '`' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(214);
      if (lookahead != 0) ADVANCE(148);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(aux_sym_lua_body_token1);
      if (lookahead != 0 &&
          lookahead != '`' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(157);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\n') ADVANCE(165);
      if (lookahead == '\r') ADVANCE(159);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(167);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\n') ADVANCE(165);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(167);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\n') ADVANCE(167);
      if (lookahead == '\\') ADVANCE(161);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(214);
      if (lookahead != 0) ADVANCE(160);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\r') ADVANCE(166);
      if (lookahead == '\\') ADVANCE(161);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(214);
      if (lookahead != 0) ADVANCE(160);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '*') ADVANCE(164);
      if (lookahead == '/') ADVANCE(160);
      if (lookahead != 0 &&
          (lookahead < '(' || '*' < lookahead) &&
          lookahead != '`') ADVANCE(167);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '*') ADVANCE(163);
      if (lookahead == '/') ADVANCE(167);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(12);
      if (lookahead != 0) ADVANCE(164);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '*') ADVANCE(163);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(12);
      if (lookahead != 0) ADVANCE(164);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '/') ADVANCE(162);
      if (lookahead == '\\') ADVANCE(158);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(165);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(167);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead == '\\') ADVANCE(161);
      if (lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '`') ADVANCE(214);
      if (lookahead != 0) ADVANCE(160);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(aux_sym_lua_call_token1);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '`') ADVANCE(167);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(sym_lua_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(170);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(anon_sym_BPM);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(anon_sym_PhaseCoupling);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(anon_sym_SyncStrength);
      END_STATE();
    case 174:
      ACCEPT_TOKEN(anon_sym_TRANSPOSE);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(anon_sym_ENTROPY);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(anon_sym_Entropy);
      END_STATE();
    case 177:
      ACCEPT_TOKEN(anon_sym_PitchSigma);
      END_STATE();
    case 178:
      ACCEPT_TOKEN(anon_sym_FFTSize);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(anon_sym_HopSize);
      END_STATE();
    case 180:
      ACCEPT_TOKEN(anon_sym_NOTE);
      END_STATE();
    case 181:
      ACCEPT_TOKEN(anon_sym_TRILL);
      END_STATE();
    case 182:
      ACCEPT_TOKEN(anon_sym_CHORD);
      END_STATE();
    case 183:
      ACCEPT_TOKEN(anon_sym_REST);
      END_STATE();
    case 184:
      ACCEPT_TOKEN(anon_sym_EVENT);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(anon_sym_timed);
      END_STATE();
    case 186:
      ACCEPT_TOKEN(anon_sym_internal);
      END_STATE();
    case 187:
      ACCEPT_TOKEN(sym_midi);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(sym_midi);
      if (lookahead == '2') ADVANCE(189);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(190);
      if (('3' <= lookahead && lookahead <= '9')) ADVANCE(187);
      END_STATE();
    case 189:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(187);
      END_STATE();
    case 190:
      ACCEPT_TOKEN(sym_midi);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(187);
      END_STATE();
    case 191:
      ACCEPT_TOKEN(sym_pitchname);
      END_STATE();
    case 192:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'C') ADVANCE(54);
      END_STATE();
    case 193:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'F') ADVANCE(57);
      END_STATE();
    case 194:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'H') ADVANCE(37);
      END_STATE();
    case 195:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'N') ADVANCE(59);
      if (lookahead == 'V') ADVANCE(23);
      if (lookahead == 'n') ADVANCE(121);
      END_STATE();
    case 196:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'P') ADVANCE(31);
      END_STATE();
    case 197:
      ACCEPT_TOKEN(sym_pitchname);
      if (lookahead == 'e') ADVANCE(96);
      END_STATE();
    case 198:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 199:
      ACCEPT_TOKEN(anon_sym_b);
      END_STATE();
    case 200:
      ACCEPT_TOKEN(sym_octave);
      END_STATE();
    case 201:
      ACCEPT_TOKEN(sym_octave);
      if (('0' <= lookahead && lookahead <= '2')) ADVANCE(200);
      END_STATE();
    case 202:
      ACCEPT_TOKEN(anon_sym_ACTION);
      END_STATE();
    case 203:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 204:
      ACCEPT_TOKEN(anon_sym_delay);
      END_STATE();
    case 205:
      ACCEPT_TOKEN(anon_sym_sendto);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(anon_sym_luacall);
      END_STATE();
    case 207:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 208:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 209:
      ACCEPT_TOKEN(aux_sym_actionKey_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(209);
      END_STATE();
    case 210:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(135);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(210);
      END_STATE();
    case 211:
      ACCEPT_TOKEN(aux_sym_number_token2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(211);
      END_STATE();
    case 212:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 213:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\r') ADVANCE(215);
      if (lookahead == '\\') ADVANCE(213);
      if (lookahead != 0) ADVANCE(214);
      END_STATE();
    case 214:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(7);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(214);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(7);
      if (lookahead != 0) ADVANCE(214);
      END_STATE();
    case 216:
      ACCEPT_TOKEN(anon_sym_tempo);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(anon_sym_sec);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(anon_sym_ms);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 140},
  [2] = {.lex_state = 140},
  [3] = {.lex_state = 140},
  [4] = {.lex_state = 140},
  [5] = {.lex_state = 140},
  [6] = {.lex_state = 140},
  [7] = {.lex_state = 140},
  [8] = {.lex_state = 140},
  [9] = {.lex_state = 140},
  [10] = {.lex_state = 140},
  [11] = {.lex_state = 140},
  [12] = {.lex_state = 140},
  [13] = {.lex_state = 140},
  [14] = {.lex_state = 140},
  [15] = {.lex_state = 140},
  [16] = {.lex_state = 140},
  [17] = {.lex_state = 140},
  [18] = {.lex_state = 140},
  [19] = {.lex_state = 140},
  [20] = {.lex_state = 140},
  [21] = {.lex_state = 140},
  [22] = {.lex_state = 140},
  [23] = {.lex_state = 140},
  [24] = {.lex_state = 140},
  [25] = {.lex_state = 140},
  [26] = {.lex_state = 140},
  [27] = {.lex_state = 140},
  [28] = {.lex_state = 140},
  [29] = {.lex_state = 140},
  [30] = {.lex_state = 140},
  [31] = {.lex_state = 140},
  [32] = {.lex_state = 140},
  [33] = {.lex_state = 14},
  [34] = {.lex_state = 140},
  [35] = {.lex_state = 14},
  [36] = {.lex_state = 14},
  [37] = {.lex_state = 140},
  [38] = {.lex_state = 15},
  [39] = {.lex_state = 8},
  [40] = {.lex_state = 8},
  [41] = {.lex_state = 15},
  [42] = {.lex_state = 8},
  [43] = {.lex_state = 15},
  [44] = {.lex_state = 8},
  [45] = {.lex_state = 9},
  [46] = {.lex_state = 140},
  [47] = {.lex_state = 15},
  [48] = {.lex_state = 15},
  [49] = {.lex_state = 15},
  [50] = {.lex_state = 140},
  [51] = {.lex_state = 14},
  [52] = {.lex_state = 14},
  [53] = {.lex_state = 140},
  [54] = {.lex_state = 14},
  [55] = {.lex_state = 9},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 140},
  [58] = {.lex_state = 14},
  [59] = {.lex_state = 9},
  [60] = {.lex_state = 14},
  [61] = {.lex_state = 14},
  [62] = {.lex_state = 9},
  [63] = {.lex_state = 14},
  [64] = {.lex_state = 8},
  [65] = {.lex_state = 9},
  [66] = {.lex_state = 8},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 8},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 9},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 14},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 8},
  [75] = {.lex_state = 14},
  [76] = {.lex_state = 14},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 14},
  [81] = {.lex_state = 14},
  [82] = {.lex_state = 14},
  [83] = {.lex_state = 14},
  [84] = {.lex_state = 16},
  [85] = {.lex_state = 14},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 140},
  [92] = {.lex_state = 140},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 140},
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
    [anon_sym_PhaseCoupling] = ACTIONS(1),
    [anon_sym_SyncStrength] = ACTIONS(1),
    [anon_sym_TRANSPOSE] = ACTIONS(1),
    [anon_sym_ENTROPY] = ACTIONS(1),
    [anon_sym_Entropy] = ACTIONS(1),
    [anon_sym_PitchSigma] = ACTIONS(1),
    [anon_sym_FFTSize] = ACTIONS(1),
    [anon_sym_HopSize] = ACTIONS(1),
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
    [sym_score] = STATE(88),
    [sym__statement] = STATE(3),
    [sym_LUA] = STATE(3),
    [sym_CONFIG] = STATE(3),
    [sym_configId] = STATE(54),
    [sym_numberConfig] = STATE(27),
    [sym_EVENT] = STATE(3),
    [sym_pitchEventId] = STATE(42),
    [sym_restEventId] = STATE(52),
    [sym_timeEventId] = STATE(73),
    [sym_pitchEvent] = STATE(32),
    [sym_restEvent] = STATE(32),
    [sym_freeEvent] = STATE(32),
    [aux_sym_score_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_LUA] = ACTIONS(7),
    [anon_sym_BPM] = ACTIONS(9),
    [anon_sym_PhaseCoupling] = ACTIONS(9),
    [anon_sym_SyncStrength] = ACTIONS(9),
    [anon_sym_TRANSPOSE] = ACTIONS(9),
    [anon_sym_ENTROPY] = ACTIONS(9),
    [anon_sym_Entropy] = ACTIONS(9),
    [anon_sym_PitchSigma] = ACTIONS(9),
    [anon_sym_FFTSize] = ACTIONS(9),
    [anon_sym_HopSize] = ACTIONS(9),
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
    ACTIONS(17), 1,
      ts_builtin_sym_end,
    ACTIONS(19), 1,
      anon_sym_LUA,
    ACTIONS(28), 1,
      anon_sym_REST,
    ACTIONS(31), 1,
      anon_sym_EVENT,
    STATE(27), 1,
      sym_numberConfig,
    STATE(42), 1,
      sym_pitchEventId,
    STATE(52), 1,
      sym_restEventId,
    STATE(54), 1,
      sym_configId,
    STATE(73), 1,
      sym_timeEventId,
    ACTIONS(25), 3,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
    STATE(32), 3,
      sym_pitchEvent,
      sym_restEvent,
      sym_freeEvent,
    STATE(2), 5,
      sym__statement,
      sym_LUA,
      sym_CONFIG,
      sym_EVENT,
      aux_sym_score_repeat1,
    ACTIONS(22), 9,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
  [59] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_LUA,
    ACTIONS(13), 1,
      anon_sym_REST,
    ACTIONS(15), 1,
      anon_sym_EVENT,
    ACTIONS(34), 1,
      ts_builtin_sym_end,
    STATE(27), 1,
      sym_numberConfig,
    STATE(42), 1,
      sym_pitchEventId,
    STATE(52), 1,
      sym_restEventId,
    STATE(54), 1,
      sym_configId,
    STATE(73), 1,
      sym_timeEventId,
    ACTIONS(11), 3,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
    STATE(32), 3,
      sym_pitchEvent,
      sym_restEvent,
      sym_freeEvent,
    STATE(2), 5,
      sym__statement,
      sym_LUA,
      sym_CONFIG,
      sym_EVENT,
      aux_sym_score_repeat1,
    ACTIONS(9), 9,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
  [118] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 1,
      anon_sym_ACTION,
    ACTIONS(41), 1,
      anon_sym_delay,
    ACTIONS(44), 1,
      anon_sym_sendto,
    ACTIONS(47), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(69), 1,
      sym_timedAction,
    STATE(4), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(36), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [162] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(52), 1,
      anon_sym_ACTION,
    ACTIONS(54), 1,
      anon_sym_delay,
    ACTIONS(56), 1,
      anon_sym_sendto,
    ACTIONS(58), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(69), 1,
      sym_timedAction,
    STATE(4), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(50), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [206] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(52), 1,
      anon_sym_ACTION,
    ACTIONS(54), 1,
      anon_sym_delay,
    ACTIONS(56), 1,
      anon_sym_sendto,
    ACTIONS(58), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(69), 1,
      sym_timedAction,
    STATE(4), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(60), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [250] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(52), 1,
      anon_sym_ACTION,
    ACTIONS(54), 1,
      anon_sym_delay,
    ACTIONS(56), 1,
      anon_sym_sendto,
    ACTIONS(58), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(69), 1,
      sym_timedAction,
    STATE(9), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(62), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [294] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(52), 1,
      anon_sym_ACTION,
    ACTIONS(54), 1,
      anon_sym_delay,
    ACTIONS(56), 1,
      anon_sym_sendto,
    ACTIONS(58), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(69), 1,
      sym_timedAction,
    STATE(5), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(64), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [338] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(52), 1,
      anon_sym_ACTION,
    ACTIONS(54), 1,
      anon_sym_delay,
    ACTIONS(56), 1,
      anon_sym_sendto,
    ACTIONS(58), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(69), 1,
      sym_timedAction,
    STATE(4), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
    ACTIONS(66), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [382] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(70), 1,
      anon_sym_LBRACK,
    STATE(22), 1,
      sym_pdargs,
    ACTIONS(68), 21,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
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
  [415] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 1,
      anon_sym_COMMA,
    STATE(17), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(72), 20,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [447] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(76), 22,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
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
      anon_sym_LBRACK,
  [475] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 1,
      anon_sym_COMMA,
    STATE(16), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(78), 20,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [507] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 1,
      anon_sym_COMMA,
    STATE(18), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(80), 20,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [539] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 1,
      anon_sym_COMMA,
    STATE(11), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(82), 20,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [571] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 1,
      anon_sym_COMMA,
    STATE(17), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(84), 20,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [603] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(88), 1,
      anon_sym_COMMA,
    STATE(17), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(86), 20,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [635] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 1,
      anon_sym_COMMA,
    STATE(17), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(91), 20,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [667] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 1,
      anon_sym_COMMA,
    STATE(20), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(93), 20,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [699] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(74), 1,
      anon_sym_COMMA,
    STATE(17), 1,
      aux_sym_ACTION_repeat1,
    ACTIONS(95), 20,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [731] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(86), 21,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
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
  [758] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 21,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
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
  [785] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(99), 21,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
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
  [812] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(101), 21,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
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
  [839] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 20,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [865] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(105), 20,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [891] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [913] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(109), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [935] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(111), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [957] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(113), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [979] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(115), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [1001] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(117), 16,
      ts_builtin_sym_end,
      anon_sym_LUA,
      anon_sym_BPM,
      anon_sym_PhaseCoupling,
      anon_sym_SyncStrength,
      anon_sym_TRANSPOSE,
      anon_sym_ENTROPY,
      anon_sym_Entropy,
      anon_sym_PitchSigma,
      anon_sym_FFTSize,
      anon_sym_HopSize,
      anon_sym_NOTE,
      anon_sym_TRILL,
      anon_sym_CHORD,
      anon_sym_REST,
      anon_sym_EVENT,
  [1023] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(119), 1,
      anon_sym_RBRACK,
    ACTIONS(121), 1,
      aux_sym_actionKey_token1,
    ACTIONS(124), 1,
      aux_sym_number_token1,
    ACTIONS(127), 1,
      aux_sym_number_token2,
    STATE(33), 2,
      sym_pdarg,
      aux_sym_pdargs_repeat1,
    STATE(60), 2,
      sym_number,
      sym_symbol,
  [1047] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(52), 1,
      anon_sym_ACTION,
    ACTIONS(54), 1,
      anon_sym_delay,
    ACTIONS(56), 1,
      anon_sym_sendto,
    ACTIONS(58), 1,
      anon_sym_luacall,
    STATE(13), 1,
      sym_exec,
    STATE(69), 1,
      sym_timedAction,
    STATE(6), 2,
      sym_ACTION,
      aux_sym_pitchEvent_repeat1,
  [1073] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(130), 1,
      anon_sym_RBRACK,
    ACTIONS(132), 1,
      aux_sym_actionKey_token1,
    ACTIONS(134), 1,
      aux_sym_number_token1,
    ACTIONS(136), 1,
      aux_sym_number_token2,
    STATE(33), 2,
      sym_pdarg,
      aux_sym_pdargs_repeat1,
    STATE(60), 2,
      sym_number,
      sym_symbol,
  [1097] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(132), 1,
      aux_sym_actionKey_token1,
    ACTIONS(134), 1,
      aux_sym_number_token1,
    ACTIONS(136), 1,
      aux_sym_number_token2,
    STATE(35), 2,
      sym_pdarg,
      aux_sym_pdargs_repeat1,
    STATE(60), 2,
      sym_number,
      sym_symbol,
  [1118] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 7,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
      anon_sym_tempo,
      anon_sym_sec,
      anon_sym_ms,
  [1131] = 6,
    ACTIONS(138), 1,
      anon_sym_LBRACE,
    ACTIONS(140), 1,
      anon_sym_RBRACE,
    ACTIONS(144), 1,
      sym_comment,
    STATE(47), 1,
      aux_sym_lua_body_repeat1,
    STATE(87), 1,
      sym_lua_body,
    ACTIONS(142), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1151] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(146), 1,
      anon_sym_RPAREN,
    ACTIONS(148), 1,
      sym_midi,
    ACTIONS(151), 1,
      sym_pitchname,
    STATE(64), 1,
      sym_noteName,
    STATE(39), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [1171] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(154), 1,
      anon_sym_RPAREN,
    ACTIONS(156), 1,
      sym_midi,
    ACTIONS(158), 1,
      sym_pitchname,
    STATE(64), 1,
      sym_noteName,
    STATE(39), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [1191] = 6,
    ACTIONS(138), 1,
      anon_sym_LBRACE,
    ACTIONS(144), 1,
      sym_comment,
    ACTIONS(160), 1,
      anon_sym_RBRACE,
    STATE(47), 1,
      aux_sym_lua_body_repeat1,
    STATE(90), 1,
      sym_lua_body,
    ACTIONS(142), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1211] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(162), 1,
      anon_sym_LPAREN,
    ACTIONS(164), 1,
      sym_midi,
    ACTIONS(166), 1,
      sym_pitchname,
    STATE(76), 1,
      sym_noteName,
    STATE(61), 2,
      sym_pitches,
      sym_pitch,
  [1231] = 5,
    ACTIONS(144), 1,
      sym_comment,
    ACTIONS(168), 1,
      anon_sym_LBRACE,
    ACTIONS(171), 1,
      anon_sym_RBRACE,
    STATE(43), 1,
      aux_sym_lua_body_repeat1,
    ACTIONS(173), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1248] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(156), 1,
      sym_midi,
    ACTIONS(158), 1,
      sym_pitchname,
    STATE(64), 1,
      sym_noteName,
    STATE(40), 2,
      sym_pitch,
      aux_sym_pitches_repeat1,
  [1265] = 6,
    ACTIONS(144), 1,
      sym_comment,
    ACTIONS(176), 1,
      aux_sym_lua_call_token1,
    ACTIONS(178), 1,
      anon_sym_LPAREN,
    ACTIONS(180), 1,
      anon_sym_RPAREN,
    STATE(55), 1,
      aux_sym_lua_call_repeat1,
    STATE(89), 1,
      sym_lua_call,
  [1284] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(54), 1,
      anon_sym_delay,
    ACTIONS(56), 1,
      anon_sym_sendto,
    ACTIONS(58), 1,
      anon_sym_luacall,
    STATE(14), 1,
      sym_exec,
    STATE(71), 1,
      sym_timedAction,
  [1303] = 5,
    ACTIONS(138), 1,
      anon_sym_LBRACE,
    ACTIONS(144), 1,
      sym_comment,
    ACTIONS(182), 1,
      anon_sym_RBRACE,
    STATE(43), 1,
      aux_sym_lua_body_repeat1,
    ACTIONS(184), 2,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1320] = 2,
    ACTIONS(144), 1,
      sym_comment,
    ACTIONS(186), 4,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1330] = 2,
    ACTIONS(144), 1,
      sym_comment,
    ACTIONS(171), 4,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      aux_sym_lua_body_token1,
      sym_lua_comment,
  [1340] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(190), 1,
      sym_octave,
    STATE(95), 1,
      sym_alteration,
    ACTIONS(188), 2,
      anon_sym_POUND,
      anon_sym_b,
  [1354] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(192), 1,
      aux_sym_number_token1,
    ACTIONS(103), 3,
      anon_sym_RBRACK,
      aux_sym_actionKey_token1,
      aux_sym_number_token2,
  [1366] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(194), 1,
      aux_sym_number_token1,
    ACTIONS(196), 1,
      aux_sym_number_token2,
    STATE(7), 1,
      sym_duration,
    STATE(26), 1,
      sym_number,
  [1382] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(105), 4,
      anon_sym_ACTION,
      anon_sym_delay,
      anon_sym_sendto,
      anon_sym_luacall,
  [1392] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(194), 1,
      aux_sym_number_token1,
    ACTIONS(196), 1,
      aux_sym_number_token2,
    STATE(29), 1,
      sym_number,
    STATE(30), 1,
      sym_numberSet,
  [1408] = 5,
    ACTIONS(144), 1,
      sym_comment,
    ACTIONS(178), 1,
      anon_sym_LPAREN,
    ACTIONS(198), 1,
      aux_sym_lua_call_token1,
    ACTIONS(200), 1,
      anon_sym_RPAREN,
    STATE(62), 1,
      aux_sym_lua_call_repeat1,
  [1424] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(77), 1,
      sym_timeUnit,
    ACTIONS(202), 3,
      anon_sym_tempo,
      anon_sym_sec,
      anon_sym_ms,
  [1436] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(204), 1,
      sym_octave,
    STATE(92), 1,
      sym_alteration,
    ACTIONS(188), 2,
      anon_sym_POUND,
      anon_sym_b,
  [1450] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(208), 1,
      aux_sym_number_token1,
    ACTIONS(206), 3,
      anon_sym_RBRACK,
      aux_sym_actionKey_token1,
      aux_sym_number_token2,
  [1462] = 5,
    ACTIONS(144), 1,
      sym_comment,
    ACTIONS(176), 1,
      aux_sym_lua_call_token1,
    ACTIONS(178), 1,
      anon_sym_LPAREN,
    STATE(55), 1,
      aux_sym_lua_call_repeat1,
    STATE(86), 1,
      sym_lua_call,
  [1478] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(212), 1,
      aux_sym_number_token1,
    ACTIONS(210), 3,
      anon_sym_RBRACK,
      aux_sym_actionKey_token1,
      aux_sym_number_token2,
  [1490] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(194), 1,
      aux_sym_number_token1,
    ACTIONS(196), 1,
      aux_sym_number_token2,
    STATE(8), 1,
      sym_duration,
    STATE(26), 1,
      sym_number,
  [1506] = 5,
    ACTIONS(144), 1,
      sym_comment,
    ACTIONS(214), 1,
      aux_sym_lua_call_token1,
    ACTIONS(217), 1,
      anon_sym_LPAREN,
    ACTIONS(220), 1,
      anon_sym_RPAREN,
    STATE(62), 1,
      aux_sym_lua_call_repeat1,
  [1522] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      aux_sym_number_token1,
    ACTIONS(224), 1,
      aux_sym_number_token2,
    STATE(34), 1,
      sym_duration,
    STATE(53), 1,
      sym_number,
  [1538] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(226), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [1547] = 2,
    ACTIONS(144), 1,
      sym_comment,
    ACTIONS(220), 3,
      aux_sym_lua_call_token1,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [1556] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(228), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [1565] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(56), 1,
      anon_sym_sendto,
    ACTIONS(58), 1,
      anon_sym_luacall,
    STATE(21), 1,
      sym_exec,
  [1578] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(230), 3,
      anon_sym_LPAREN,
      sym_midi,
      sym_pitchname,
  [1587] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(56), 1,
      anon_sym_sendto,
    ACTIONS(58), 1,
      anon_sym_luacall,
    STATE(15), 1,
      sym_exec,
  [1600] = 2,
    ACTIONS(144), 1,
      sym_comment,
    ACTIONS(232), 3,
      aux_sym_lua_call_token1,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
  [1609] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(56), 1,
      anon_sym_sendto,
    ACTIONS(58), 1,
      anon_sym_luacall,
    STATE(19), 1,
      sym_exec,
  [1622] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      aux_sym_number_token1,
    ACTIONS(224), 1,
      aux_sym_number_token2,
    STATE(56), 1,
      sym_number,
  [1635] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(63), 1,
      sym_eventId,
    ACTIONS(234), 2,
      anon_sym_timed,
      anon_sym_internal,
  [1646] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(236), 3,
      anon_sym_RPAREN,
      sym_midi,
      sym_pitchname,
  [1655] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(236), 1,
      aux_sym_number_token2,
    ACTIONS(238), 1,
      aux_sym_number_token1,
  [1665] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(226), 1,
      aux_sym_number_token2,
    ACTIONS(240), 1,
      aux_sym_number_token1,
  [1675] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 2,
      anon_sym_sendto,
      anon_sym_luacall,
  [1683] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(244), 2,
      anon_sym_sendto,
      anon_sym_luacall,
  [1691] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(246), 2,
      anon_sym_timed,
      anon_sym_internal,
  [1699] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(248), 1,
      aux_sym_number_token1,
    ACTIONS(250), 1,
      aux_sym_number_token2,
  [1709] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(252), 1,
      aux_sym_number_token1,
    ACTIONS(254), 1,
      aux_sym_number_token2,
  [1719] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(256), 1,
      aux_sym_number_token1,
    ACTIONS(258), 1,
      aux_sym_number_token2,
  [1729] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(228), 1,
      aux_sym_number_token2,
    ACTIONS(260), 1,
      aux_sym_number_token1,
  [1739] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_keyword,
    STATE(10), 1,
      sym_receiver,
  [1749] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(264), 1,
      aux_sym_number_token1,
    ACTIONS(266), 1,
      aux_sym_number_token2,
  [1759] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(268), 1,
      anon_sym_RPAREN,
  [1766] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(270), 1,
      anon_sym_RBRACE,
  [1773] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      ts_builtin_sym_end,
  [1780] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(274), 1,
      anon_sym_RPAREN,
  [1787] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(276), 1,
      anon_sym_RBRACE,
  [1794] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(278), 1,
      sym_octave,
  [1801] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(280), 1,
      sym_octave,
  [1808] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(282), 1,
      anon_sym_LPAREN,
  [1815] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(284), 1,
      anon_sym_LBRACE,
  [1822] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(286), 1,
      sym_octave,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 59,
  [SMALL_STATE(4)] = 118,
  [SMALL_STATE(5)] = 162,
  [SMALL_STATE(6)] = 206,
  [SMALL_STATE(7)] = 250,
  [SMALL_STATE(8)] = 294,
  [SMALL_STATE(9)] = 338,
  [SMALL_STATE(10)] = 382,
  [SMALL_STATE(11)] = 415,
  [SMALL_STATE(12)] = 447,
  [SMALL_STATE(13)] = 475,
  [SMALL_STATE(14)] = 507,
  [SMALL_STATE(15)] = 539,
  [SMALL_STATE(16)] = 571,
  [SMALL_STATE(17)] = 603,
  [SMALL_STATE(18)] = 635,
  [SMALL_STATE(19)] = 667,
  [SMALL_STATE(20)] = 699,
  [SMALL_STATE(21)] = 731,
  [SMALL_STATE(22)] = 758,
  [SMALL_STATE(23)] = 785,
  [SMALL_STATE(24)] = 812,
  [SMALL_STATE(25)] = 839,
  [SMALL_STATE(26)] = 865,
  [SMALL_STATE(27)] = 891,
  [SMALL_STATE(28)] = 913,
  [SMALL_STATE(29)] = 935,
  [SMALL_STATE(30)] = 957,
  [SMALL_STATE(31)] = 979,
  [SMALL_STATE(32)] = 1001,
  [SMALL_STATE(33)] = 1023,
  [SMALL_STATE(34)] = 1047,
  [SMALL_STATE(35)] = 1073,
  [SMALL_STATE(36)] = 1097,
  [SMALL_STATE(37)] = 1118,
  [SMALL_STATE(38)] = 1131,
  [SMALL_STATE(39)] = 1151,
  [SMALL_STATE(40)] = 1171,
  [SMALL_STATE(41)] = 1191,
  [SMALL_STATE(42)] = 1211,
  [SMALL_STATE(43)] = 1231,
  [SMALL_STATE(44)] = 1248,
  [SMALL_STATE(45)] = 1265,
  [SMALL_STATE(46)] = 1284,
  [SMALL_STATE(47)] = 1303,
  [SMALL_STATE(48)] = 1320,
  [SMALL_STATE(49)] = 1330,
  [SMALL_STATE(50)] = 1340,
  [SMALL_STATE(51)] = 1354,
  [SMALL_STATE(52)] = 1366,
  [SMALL_STATE(53)] = 1382,
  [SMALL_STATE(54)] = 1392,
  [SMALL_STATE(55)] = 1408,
  [SMALL_STATE(56)] = 1424,
  [SMALL_STATE(57)] = 1436,
  [SMALL_STATE(58)] = 1450,
  [SMALL_STATE(59)] = 1462,
  [SMALL_STATE(60)] = 1478,
  [SMALL_STATE(61)] = 1490,
  [SMALL_STATE(62)] = 1506,
  [SMALL_STATE(63)] = 1522,
  [SMALL_STATE(64)] = 1538,
  [SMALL_STATE(65)] = 1547,
  [SMALL_STATE(66)] = 1556,
  [SMALL_STATE(67)] = 1565,
  [SMALL_STATE(68)] = 1578,
  [SMALL_STATE(69)] = 1587,
  [SMALL_STATE(70)] = 1600,
  [SMALL_STATE(71)] = 1609,
  [SMALL_STATE(72)] = 1622,
  [SMALL_STATE(73)] = 1635,
  [SMALL_STATE(74)] = 1646,
  [SMALL_STATE(75)] = 1655,
  [SMALL_STATE(76)] = 1665,
  [SMALL_STATE(77)] = 1675,
  [SMALL_STATE(78)] = 1683,
  [SMALL_STATE(79)] = 1691,
  [SMALL_STATE(80)] = 1699,
  [SMALL_STATE(81)] = 1709,
  [SMALL_STATE(82)] = 1719,
  [SMALL_STATE(83)] = 1729,
  [SMALL_STATE(84)] = 1739,
  [SMALL_STATE(85)] = 1749,
  [SMALL_STATE(86)] = 1759,
  [SMALL_STATE(87)] = 1766,
  [SMALL_STATE(88)] = 1773,
  [SMALL_STATE(89)] = 1780,
  [SMALL_STATE(90)] = 1787,
  [SMALL_STATE(91)] = 1794,
  [SMALL_STATE(92)] = 1801,
  [SMALL_STATE(93)] = 1808,
  [SMALL_STATE(94)] = 1815,
  [SMALL_STATE(95)] = 1822,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_score, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0),
  [19] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(94),
  [22] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(82),
  [25] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(68),
  [28] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(81),
  [31] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_score_repeat1, 2, 0, 0), SHIFT_REPEAT(79),
  [34] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_score, 1, 0, 0),
  [36] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0),
  [38] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(46),
  [41] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(72),
  [44] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(84),
  [47] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitchEvent_repeat1, 2, 0, 0), SHIFT_REPEAT(93),
  [50] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEvent, 4, 0, 0),
  [52] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [56] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [58] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [60] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_freeEvent, 4, 0, 0),
  [62] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_restEvent, 2, 0, 0),
  [64] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEvent, 3, 0, 0),
  [66] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_restEvent, 3, 0, 0),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exec, 2, 0, 5),
  [70] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 3, 0, 6),
  [74] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [76] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_receiver, 1, 0, 0),
  [78] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 1, 0, 3),
  [80] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 2, 0, 4),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 2, 0, 6),
  [84] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 2, 0, 3),
  [86] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_ACTION_repeat1, 2, 0, 0),
  [88] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_ACTION_repeat1, 2, 0, 0), SHIFT_REPEAT(67),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 3, 0, 4),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 3, 0, 7),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ACTION, 4, 0, 7),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exec, 3, 0, 10),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_exec, 4, 0, 13),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pdargs, 3, 0, 0),
  [103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_number, 1, 0, 0),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_duration, 1, 0, 0),
  [107] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_CONFIG, 1, 0, 0),
  [109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_LUA, 3, 0, 0),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberSet, 1, 0, 0),
  [113] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberConfig, 2, 0, 0),
  [115] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_LUA, 4, 0, 0),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_EVENT, 1, 0, 0),
  [119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pdargs_repeat1, 2, 0, 0),
  [121] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pdargs_repeat1, 2, 0, 0), SHIFT_REPEAT(58),
  [124] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_pdargs_repeat1, 2, 0, 0), SHIFT_REPEAT(51),
  [127] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pdargs_repeat1, 2, 0, 0), SHIFT_REPEAT(51),
  [130] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [134] = {.entry = {.count = 1, .reusable = false}}, SHIFT(51),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [138] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [140] = {.entry = {.count = 1, .reusable = false}}, SHIFT(49),
  [142] = {.entry = {.count = 1, .reusable = false}}, SHIFT(47),
  [144] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [146] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0),
  [148] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(64),
  [151] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pitches_repeat1, 2, 0, 0), SHIFT_REPEAT(50),
  [154] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [160] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [162] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [166] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [168] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 2, 0, 0), SHIFT_REPEAT(38),
  [171] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 2, 0, 0),
  [173] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 2, 0, 0), SHIFT_REPEAT(43),
  [176] = {.entry = {.count = 1, .reusable = false}}, SHIFT(55),
  [178] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [180] = {.entry = {.count = 1, .reusable = false}}, SHIFT(65),
  [182] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lua_body, 1, 0, 0),
  [184] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [186] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_body_repeat1, 3, 0, 0),
  [188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [190] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [192] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_number, 1, 0, 0),
  [194] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [196] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [198] = {.entry = {.count = 1, .reusable = false}}, SHIFT(62),
  [200] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lua_call, 1, 0, 11),
  [202] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_symbol, 1, 0, 0),
  [208] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_symbol, 1, 0, 0),
  [210] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pdarg, 1, 0, 12),
  [212] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pdarg, 1, 0, 12),
  [214] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 2, 0, 0), SHIFT_REPEAT(62),
  [217] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 2, 0, 0), SHIFT_REPEAT(45),
  [220] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 2, 0, 0),
  [222] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [226] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitch, 1, 0, 0),
  [228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_noteName, 3, 0, 0),
  [230] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitchEventId, 1, 0, 2),
  [232] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_lua_call_repeat1, 3, 0, 0),
  [234] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [236] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_noteName, 2, 0, 0),
  [238] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_noteName, 2, 0, 0),
  [240] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitch, 1, 0, 0),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_timedAction, 3, 0, 9),
  [244] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_timeUnit, 1, 0, 8),
  [246] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_timeEventId, 1, 0, 0),
  [248] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_eventId, 1, 0, 0),
  [250] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_eventId, 1, 0, 0),
  [252] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_restEventId, 1, 0, 0),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_restEventId, 1, 0, 0),
  [256] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_configId, 1, 0, 1),
  [258] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_configId, 1, 0, 1),
  [260] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_noteName, 3, 0, 0),
  [262] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [264] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_pitches, 3, 0, 0),
  [266] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pitches, 3, 0, 0),
  [268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [270] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [272] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [274] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [276] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [278] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alteration, 1, 0, 0),
  [280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [284] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [286] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
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
