#include <OScofo.hpp>

#if defined(OSCOFO_LUA)

namespace OScofo {

static int oscofo_getPitchProb(lua_State *L) {
    lua_getglobal(L, "_OScofo");
    lua_getfield(L, -1, "pointer");
    OScofo *oscofo = (OScofo *)lua_touserdata(L, -1);
    if (!oscofo) {
        return luaL_error(L, "Invalid OScofo instance");
    }
    double frequency = luaL_checknumber(L, 1);
    double prob = oscofo->GetPitchProb(frequency);
    lua_pushnumber(L, prob);
    return 1;
}

// ─────────────────────────────────────
static int oscofo_getBPM(lua_State *L) {
    lua_getglobal(L, "_OScofo");
    lua_getfield(L, -1, "pointer");
    OScofo *oscofo = (OScofo *)lua_touserdata(L, -1);
    if (!oscofo) {
        return luaL_error(L, "Invalid OScofo instance");
    }
    double bpm = oscofo->GetLiveBPM();
    lua_pushnumber(L, bpm);
    return 1;
}

// ─────────────────────────────────────
static int oscofo_getKappa(lua_State *L) {
    lua_getglobal(L, "_OScofo");
    lua_getfield(L, -1, "pointer");
    OScofo *oscofo = (OScofo *)lua_touserdata(L, -1);
    if (!oscofo) {
        return luaL_error(L, "Invalid OScofo instance");
    }
    double kappa = oscofo->GetKappa();
    lua_pushnumber(L, kappa);
    return 1;
}

// ─────────────────────────────────────
static const luaL_Reg oscofo_funcs[] = {
    // Tempo
    {"getKappa", oscofo_getKappa},
    {"getBPM", oscofo_getBPM},

    // Audio Description
    {"getPitchProb", oscofo_getPitchProb},

    {NULL, NULL}
    // Sentinela
};

// ─────────────────────────────────────
int luaopen_oscofo(lua_State *L) {
    luaL_newlib(L, oscofo_funcs);
    return 1;
}
} // namespace OScofo
//
#endif
