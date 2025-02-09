#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <charconv>

#include "score.hpp"
#include "tree_sitter/api.h"

extern "C" TSLanguage *tree_sitter_scofo();

namespace OScofo {

// ╭─────────────────────────────────────╮
// │               Errors                │
// ╰─────────────────────────────────────╯
bool Score::HasErrors() {
    return m_HasErrors;
}

// ─────────────────────────────────────
std::vector<std::string> Score::GetErrorMessage() {
    return m_Errors;
}

// ─────────────────────────────────────
void Score::SetError(const std::string &message) {
    m_HasErrors = true;
    m_Errors.push_back(message);
}

// ─────────────────────────────────────
void Score::ClearError() {
    m_HasErrors = false;
    m_Errors.clear();
}

// ─────────────────────────────────────
void Score::PrintTreeSitterNode(TSNode node, int indent) {
    const char *type = ts_node_type(node);
    std::string text = ts_node_string(node);
    if (indent != 0) {
        std::cout << std::string(indent, ' ') << type << ": " << text << std::endl;
    }
    uint32_t child_count = ts_node_child_count(node);
    for (uint32_t i = 0; i < child_count; i++) {
        PrintTreeSitterNode(ts_node_child(node, i), indent + 4);
    }
}

// ─────────────────────────────────────
TSNode Score::GetField(TSNode Node, std::string s) {
    int strLen = s.length();
    TSNode field = ts_node_child_by_field_name(Node, s.c_str(), strLen);
    return field;
}

// ─────────────────────────────────────
std::string Score::GetLuaCode() {
    return m_LuaCode;
}

// ─────────────────────────────────────
void Score::SetTunning(double Tunning) {
    m_Tunning = Tunning;
}

// ─────────────────────────────────────
double Score::GetFFTSize() {
    return m_FFTSize;
}

// ─────────────────────────────────────
double Score::GetHopSize() {
    return m_HopSize;
}

// ─────────────────────────────────────
double Score::GetPitchTemplateSigma() {
    return m_PitchTemplateSigma;
}

// ─────────────────────────────────────
double Score::GetPhaseCoupling() {
    return m_PhaseCoupling;
}

// ─────────────────────────────────────
double Score::GetSyncStrength() {
    return m_SyncStrength;
}

// ─────────────────────────────────────
bool Score::ScoreIsLoaded() {
    return m_ScoreLoaded;
}

// ─────────────────────────────────────
bool Score::isNumber(std::string str) {
    if (str.empty()) {
        return false;
    }

    if (std::isspace(static_cast<unsigned char>(str[0]))) {
        return false;
    }

    const char* start = str.c_str();
    char* endptr;
    errno = 0; 

    std::strtof(start, &endptr);

    if (endptr == start || errno == ERANGE || endptr != start + str.size()) {
        return false;
    }

    return true;
}

// ─────────────────────────────────────
double Score::PitchNode2Freq(const std::string ScoreStr, TSNode node) {
    TSNode pitch = ts_node_child(node, 0);
    std::string type = ts_node_type(pitch);
    if (type == "midi") {
        int midi = std::stof(GetCodeStr(ScoreStr, pitch));
        return m_Tunning * pow(2, (midi - 69.0) / 12);

    } else if (type != "noteName") {
        TSPoint Pos = ts_node_start_point(pitch);
        SetError("Invalid pitch type on line " + std::to_string(Pos.row + 1));
        return 0;
    }

    char pitchName = GetChildStringFromField(ScoreStr, pitch, "pitchname")[0];
    std::string alt = GetChildStringFromField(ScoreStr, pitch, "alteration");
    std::string octave = GetChildStringFromField(ScoreStr, pitch, "octave");

    int classNote = -1;
    switch (pitchName) {
    case 'C':
        classNote = 0;
        break;
    case 'D':
        classNote = 2;
        break;
    case 'E':
        classNote = 4;
        break;
    case 'F':
        classNote = 5;
        break;
    case 'G':
        classNote = 7;
        break;
    case 'A':
        classNote = 9;
        break;
    case 'B':
        classNote = 11;
        break;
    default:
        TSPoint Pos = ts_node_start_point(pitch);
        SetError("Invalid note name on line " + std::to_string(Pos.row + 1));
        return 0;
    }

    if (alt != "") {
        if (alt == "#") {
            classNote++;
        } else if (alt == "b") {
            classNote--;
        } else if (alt == "##") {
            classNote += 2;
        } else if (alt == "bb") {
            classNote -= 2;
        }
    }
    int midi = classNote + 12 + (12 * std::stoi(octave));

    midi = midi + m_Transpose;

    return m_Tunning * pow(2, (midi - 69.0) / 12);
}

// ─────────────────────────────────────
double Score::ModPhases(double Phase) {
    // Following Cont (2010) conventions
    double NewPhase = fmod(Phase + M_PI, TWO_PI);
    if (NewPhase < 0) {
        NewPhase += TWO_PI;
    }
    return NewPhase - M_PI;
}

// ╭─────────────────────────────────────╮
// │       Parse File of the Score       │
// ╰─────────────────────────────────────╯
std::string Score::GetCodeStr(const std::string &ScoreStr, TSNode Node) {
    int start = ts_node_start_byte(Node);
    int end = ts_node_end_byte(Node);
    return std::string(std::string_view(ScoreStr.data() + start, end - start));
}

// ─────────────────────────────────────
double Score::GetDurationFromNode(const std::string &ScoreStr, TSNode Node) {
    uint32_t count = ts_node_child_count(Node);
    if (count != 1) {
        TSPoint Pos = ts_node_start_point(Node);
        SetError("Invalid duration count on line " + std::to_string(Pos.row + 1));
        return 0;
    }

    TSNode dur = ts_node_child(Node, 0);
    std::string dur_type = ts_node_type(dur);
    if (dur_type == "number") {
        std::string dur_str = GetCodeStr(ScoreStr, dur);
        return std::stof(dur_str);
    }
    TSPoint Pos = ts_node_start_point(dur);
    SetError("Invalid duration type on line " + std::to_string(Pos.row + 1));
    return 0;
}

// ─────────────────────────────────────
MacroState Score::PitchEvent(const std::string &ScoreStr, TSNode Node) {
    m_ScorePosition++;

    MacroState Event;
    Event.Line = m_LineCount;
    Event.Markov = SEMIMARKOV;
    Event.Index = m_ScoreStates.size();
    Event.ScorePos = m_ScorePosition;
    Event.Entropy = m_Entropy;

    uint32_t child_count = ts_node_child_count(Node);
    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(Node, i);
        std::string type = ts_node_type(child);
        if (type == "pitchEventId") {
            std::string id = GetCodeStr(ScoreStr, child);
            if (id == "NOTE") {
                Event.Type = NOTE;
            } else if (id == "TRILL") {
                Event.Type = TRILL;
            } else if (id == "CHORD") {
                Event.Type = CHORD;
            } else {
                TSPoint Pos = ts_node_start_point(child);
                SetError("Invalid pitch event on line " + std::to_string(Pos.row + 1));
                return Event;
            }

        } else if (type == "pitch") {
            AudioState SubState;
            SubState.Markov = MARKOV;
            SubState.Type = NOTE;
            SubState.Freq = PitchNode2Freq(ScoreStr, child);
            Event.SubStates.push_back(SubState);
        } else if (type == "pitches") {
            uint32_t pitchCount = ts_node_child_count(child);
            for (size_t j = 0; j < pitchCount; j++) {
                TSNode eventPitch = ts_node_child(child, j);
                std::string eventPitchId = ts_node_type(eventPitch);
                if (eventPitchId == "pitch") {
                    AudioState SubState;
                    SubState.Markov = MARKOV;
                    SubState.Type = NOTE;
                    SubState.Freq = PitchNode2Freq(ScoreStr, eventPitch);
                    Event.SubStates.push_back(SubState);
                }
            }

        } else if (type == "duration") {
            double duration = GetDurationFromNode(ScoreStr, child);
            Event.Duration = duration;
        } else if (type == "ACTION") {
            ProcessAction(ScoreStr, child, Event);
        } else {
            TSPoint Pos = ts_node_start_point(child);
            SetError("Invalid note event on line " + std::to_string(Pos.row + 1));
            return Event;
        }
    }
    ProcessEventTime(Event);
    return Event;
}

// ─────────────────────────────────────
void Score::ProcessEventTime(MacroState &Event) {
    // Time
    if (Event.Index != 0) {
        int Index = Event.Index;
        double PsiK = 60.0f / m_ScoreStates[Index - 1].BPMExpected;
        double Tn = m_ScoreStates[Index - 1].OnsetExpected;
        double Tn1 = Event.OnsetExpected;
        double PhiN0 = Event.PhaseExpected;
        double PhiN1 = PhiN0 + ((Tn1 - Tn) / PsiK);
        PhiN1 = ModPhases(PhiN1);
        Event.PhaseExpected = PhiN1;
        Event.IOIHatPhiN = (Tn1 - Tn) / PsiK;
        Event.IOIPhiN = (Tn1 - Tn) / PsiK;
    } else {
        Event.PhaseExpected = 0;
        Event.IOIHatPhiN = 0;
        Event.IOIPhiN = 0;
    }
    Event.PhaseCoupling = m_PhaseCoupling;
    Event.SyncStrength = m_SyncStrength;
    Event.BPMExpected = m_CurrentBPM;
}

// ─────────────────────────────────────
std::string Score::GetChildStringFromField(const std::string &ScoreStr, TSNode node, std::string id) {
    int child_count = ts_node_child_count(node);
    for (int i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(node, i);
        const char *type = ts_node_type(child);
        if (id == type) {
            return GetCodeStr(ScoreStr, child);
        }
    }
    return "";
}

// ─────────────────────────────────────
void Score::ProcessEvent(const std::string &ScoreStr, TSNode Node) {
    uint32_t child_count = ts_node_child_count(Node);
    for (uint32_t i = 0; i < child_count; i++) {
        MacroState Event;
        TSNode child = ts_node_child(Node, i);
        std::string type = ts_node_type(child);
        TSPoint Pos = ts_node_start_point(child);
        Event.Line = Pos.row + 1;
        if (type == "pitchEvent") {
            Event = PitchEvent(ScoreStr, child);
            m_PrevDuration = Event.Duration;
            m_LastOnset = Event.OnsetExpected;
            m_ScoreStates.push_back(Event);
        }
    }
}

// ─────────────────────────────────────
void Score::ProcessConfig(const std::string &ScoreStr, TSNode Node) {
    MacroState Event;
    uint32_t child_count = ts_node_child_count(Node);
    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(Node, i);
        std::string type = ts_node_type(child);
        if (type == "numberConfig") {
            std::string configType = GetChildStringFromField(ScoreStr, child, "configId");
            std::string number = GetChildStringFromField(ScoreStr, child, "numberSet");
            TSPoint Pos = ts_node_start_point(child);
            if (configType == "BPM") {
                m_CurrentBPM = std::stof(number);
            } else if (configType == "TRANSPOSE") {
                m_Transpose = std::stof(number);
                if (m_Transpose < -36 || m_Transpose > 36) {
                    SetError("Invalid transpose value, must be between -36 and 36 on line " + std::to_string(Pos.row + 1));
                    return;
                }
            } else if (configType == "ENTROPY" || configType == "Entropy") {
                m_Entropy = std::stof(number);
            } else if (configType == "PhaseCoupling") {
                m_PhaseCoupling = std::stof(number);
            } else if (configType == "SyncStrength") {
                m_SyncStrength = std::stof(number);
            } else if (configType == "PitchTemplateSigma" || configType == "VARIANCE") {
                m_PitchTemplateSigma = std::stof(number);
            } else if (configType == "FFTSize") {
                m_FFTSize = std::stof(number);
            } else if (configType == "HopSize") {
                m_HopSize = std::stof(number);
            }
        }
    }
}
// ─────────────────────────────────────
void Score::ProcessAction(const std::string &ScoreStr, TSNode Node, MacroState &Event) {
    Action NewAction;
    NewAction.AbsoluteTime = true;
    NewAction.Time = 0;

    TSNode actionKeyNode = GetField(Node, "timedAction");
    if (!ts_node_is_null(actionKeyNode)) {
        TSNode key = GetField(actionKeyNode, "actionKey");
        TSNode number = GetField(actionKeyNode, "value");
        TSNode timeUnit = GetField(actionKeyNode, "timeUnit");

        if (!ts_node_is_null(key)) {
            std::string keyStr = GetCodeStr(ScoreStr, key);
            TSPoint pos = ts_node_start_point(key);
            if (keyStr != "delay") {
                SetError("Invalid action key on line " + std::to_string(pos.row + 1));
                return;
            }
        }

        if (!ts_node_is_null(number)) {
            NewAction.Time = std::stof(GetCodeStr(ScoreStr, number));
        }

        if (!ts_node_is_null(timeUnit)) {
            std::string unit = GetCodeStr(ScoreStr, timeUnit);
            if (unit == "sec") {
                NewAction.Time *= 1000;
                NewAction.AbsoluteTime = true;
            } else if (unit == "ms") {
                NewAction.AbsoluteTime = true;
            } else if (unit == "tempo") {
                NewAction.AbsoluteTime = false;
            }
        }
    }

    TSNode execNode = GetField(Node, "exec");
    if (!ts_node_is_null(execNode)) {
        TSNode key = GetField(execNode, "keyword");
        if (!ts_node_is_null(key)) {
            std::string keyStr = GetCodeStr(ScoreStr, key);
            if (keyStr == "luacall") {
                std::string luacall = GetChildStringFromField(ScoreStr, execNode, "lua_call");
                NewAction.Lua = luacall;
                NewAction.isLua = true;
            } else if (keyStr == "sendto") {
                std::string receiver = GetChildStringFromField(ScoreStr, execNode, "receiver");
                NewAction.Receiver = receiver;
                NewAction.isLua = false;
            }

            // Arguments
            TSNode args = GetField(execNode, "pdargs");
            if (!ts_node_is_null(args)) {
                int argsCount = ts_node_child_count(args);
                for (int i = 0; i < argsCount; i++) {
                    TSNode arg = ts_node_child(args, i);
                    std::string argType = ts_node_type(arg);
                    if (argType == "pdarg") {
                        TSNode pdarg = ts_node_child(arg, 0);
                        std::string pdargType = ts_node_type(pdarg);
                        std::string token = GetCodeStr(ScoreStr, pdarg);
                        if (pdargType == "number") {
                            // cechk if it is a number
                            if (isNumber(token)) {
                                float number = std::stof(token);
                                NewAction.PdArgs.push_back((float)number);
                            } else {
                                SetError("Invalid number argument on line " + std::to_string(ts_node_start_point(pdarg).row + 1));
                                return;
                            }
                        } else if (pdargType == "symbol") {
                            NewAction.PdArgs.push_back(token);
                        }
                    }
                }
            }
        }
    }
    Event.Actions.push_back(NewAction);
}

// ─────────────────────────────────────
void Score::ParseInput(const std::string &ScoreStr) {
    TSParser *parser = ts_parser_new();
    ts_parser_set_language(parser, tree_sitter_scofo());
    TSTree *tree = ts_parser_parse_string(parser, nullptr, ScoreStr.c_str(), ScoreStr.size());
    TSNode rootNode = ts_tree_root_node(tree);

    uint32_t child_count = ts_node_child_count(rootNode);
    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(rootNode, i);
        std::string type = ts_node_type(child);
        if (type == "EVENT") {
            if (m_CurrentBPM == -1) {
                SetError("BPM is not defined");
                return;
            }
            ProcessEvent(ScoreStr, child);
        } else if (type == "CONFIG") {
            ProcessConfig(ScoreStr, child);
        } else if (type == "LUA") {
            std::string lua_body = GetChildStringFromField(ScoreStr, child, "lua_body");
            lua_body += "\n\n";
            m_LuaCode += lua_body;
        }
    }

    // Cleanup
    ts_tree_delete(tree);
    ts_parser_delete(parser);
}

// ─────────────────────────────────────
States Score::Parse(std::string ScoreFile) {
    m_ScoreStates.clear();
    m_LuaCode.clear();

    // Open the score file for reading
    std::ifstream File(ScoreFile);
    if (!File) {
        SetError("Score File not found");
        return m_ScoreStates;
    }

    // Config Values
    m_CurrentBPM = 60;
    m_Transpose = 0;
    m_Entropy = 0;
    m_PitchTemplateSigma = 0.5;

    m_LineCount = 0;
    m_MarkovIndex = 0;
    m_ScorePosition = 0;
    m_LastOnset = 0;
    m_PrevDuration = 0;
    std::string Line;

    // read and process score
    std::string ScoreStr = std::string((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
    ParseInput(ScoreStr);

    if (!HasErrors()) {
        m_ScoreLoaded = true;
    }

    return m_ScoreStates;
}
} // namespace OScofo
