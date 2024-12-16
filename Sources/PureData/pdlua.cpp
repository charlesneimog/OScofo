#include <OScofo.hpp>

#include "pdlua.hpp"

namespace OScofo {

// ╭─────────────────────────────────────╮
// │          OScofo Lua Module          │
// ╰─────────────────────────────────────╯
// ─────────────────────────────────────
static int oscofo_Post(lua_State *L) {
    const char *r = luaL_checkstring(L, 1);
    post("%s", r);
    return 1;
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
    return 1;
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
    return 1;
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
    {"post", oscofo_Post},

    // PureData
    {"sendFloat", oscofo_sendFloat},
    {"sendSymbol", oscofo_sendSymbol},

    // OScofo
    {"getPitchProb", oscofo_getPitchProb},

    // Sentinela
    {NULL, NULL}};

// ─────────────────────────────────────
int luaopen_oscofo(lua_State *L) {
    luaL_newlib(L, oscofo_funcs);
    return 1;
}

// ╭─────────────────────────────────────╮
// │           OScofo Lua API            │
// ╰─────────────────────────────────────╯
PdLua::PdLua() {
    m_L = luaL_newstate();
    luaL_openlibs(m_L);
    luaL_requiref(m_L, "oscofo", luaopen_oscofo, 1);
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
