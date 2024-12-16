#include <OScofo.hpp>

#include "pdlua.hpp"

namespace OScofo {

// ╭─────────────────────────────────────╮
// │          OScofo Lua Module          │
// ╰─────────────────────────────────────╯
static int oscofo_Post(lua_State *L) {
    const char *r = luaL_checkstring(L, 1);
    post("%s", r);
    return 0;
}

// ─────────────────────────────────────
static int oscofo_Error(lua_State *L) {
    const char *r = luaL_checkstring(L, 1);
    post("%s", r);
    return 0;
}

// ─────────────────────────────────────
static int oscofo_sendBang(lua_State *L) {
    const char *r = luaL_checkstring(L, 1);
    t_symbol *symbol = gensym(r);
    if (symbol->s_thing) {
        pd_bang(symbol->s_thing);
    } else {
        luaL_error(L, "Receiver not found");
    }
    return 0;
}

// ─────────────────────────────────────
static int oscofo_sendFloat(lua_State *L) {
    const char *r = luaL_checkstring(L, 1);
    const double f = luaL_checknumber(L, 2);
    t_symbol *symbol = gensym(r);
    if (symbol->s_thing) {
        pd_float(symbol->s_thing, f);
    } else {
        luaL_error(L, "Receiver not found");
    }
    return 0;
}

// ─────────────────────────────────────
static int oscofo_sendSymbol(lua_State *L) {
    const char *r = luaL_checkstring(L, 1);
    const char *s = luaL_checkstring(L, 2);
    t_symbol *symbol = gensym(r);
    if (symbol->s_thing) {
        pd_symbol(symbol->s_thing, gensym(s));
    } else {
        luaL_error(L, "Receiver not found");
    }
    return 0;
}

// ─────────────────────────────────────
static int oscofo_sendList(lua_State *L) {
    const char *r = luaL_checkstring(L, 1);
    luaL_checktype(L, 2, LUA_TTABLE);
    t_symbol *symbol = gensym(r);
    if (!symbol->s_thing) {
        return luaL_error(L, "Receiver not found");
    }

    int listSize = luaL_len(L, 2);
    t_atom list[listSize];

    for (int i = 0; i < listSize; i++) {
        lua_rawgeti(L, 2, i + 1);
        if (lua_isnumber(L, -1)) {
            SETFLOAT(&list[i], lua_tonumber(L, -1));
        } else if (lua_isstring(L, -1)) {
            SETSYMBOL(&list[i], gensym(lua_tostring(L, -1)));
        } else {
            return luaL_error(L, "Table contains unsupported value type");
        }
        lua_pop(L, 1);
    }

    pd_list(symbol->s_thing, &s_list, listSize, list);

    return 0;
}

// ─────────────────────────────────────
static int oscofo_getPitchProb(lua_State *L) {
    const double freq = luaL_checknumber(L, 1);
    double probability = 0;
    lua_pushnumber(L, probability);
    return 1;
}

// ─────────────────────────────────────
static const luaL_Reg oscofo_funcs[] = {

    // Log
    {"getPitchProb", oscofo_getPitchProb},

    // Sentinela
    {NULL, NULL}};

// ─────────────────────────────────────
static const luaL_Reg pd_funcs[] = {

    // Log
    {"post", oscofo_Post},
    {"error", oscofo_Error},

    // PureData
    {"sendBang", oscofo_sendBang},
    {"sendFloat", oscofo_sendFloat},
    {"sendSymbol", oscofo_sendSymbol},
    {"sendList", oscofo_sendList},

    // Sentinela
    {NULL, NULL}};

// ─────────────────────────────────────
int luaopen_oscofo(lua_State *L) {
    luaL_newlib(L, oscofo_funcs);
    return 1;
}

// ─────────────────────────────────────
int luaopen_pd(lua_State *L) {
    luaL_newlib(L, pd_funcs);
    return 1;
}

// ╭─────────────────────────────────────╮
// │           OScofo Lua API            │
// ╰─────────────────────────────────────╯
PdLua::PdLua() {
    m_L = luaL_newstate();
    luaL_openlibs(m_L);
    luaL_requiref(m_L, "oscofo", luaopen_oscofo, 1);
    luaL_requiref(m_L, "pd", luaopen_pd, 1);
}

// ─────────────────────────────────────
bool PdLua::execute(std::string code) {
    int status = luaL_loadstring(m_L, code.c_str());
    if (status == LUA_OK) {
        status = lua_pcall(m_L, 0, LUA_MULTRET, 0);
        if (status != LUA_OK) {
            return false;
        }
        return true;
    } else {
        return false;
    }
}

// ─────────────────────────────────────
std::string PdLua::getError() {
    if (lua_isstring(m_L, -1)) {
        std::string errorMsg = lua_tostring(m_L, -1);
        lua_pop(m_L, 1);
        return errorMsg;
    }
    return "Unknown error";
}

} // namespace OScofo
