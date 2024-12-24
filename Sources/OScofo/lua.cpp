#include <OScofo.hpp>

#if defined(OSCOFO_LUA)

namespace OScofo {

// ─────────────────────────────────────
static OScofo *getOScofo(lua_State *L) {
    lua_getglobal(L, "_OScofo");
    lua_getfield(L, -1, "pointer");
    OScofo *oscofo = (OScofo *)lua_touserdata(L, -1);
    if (!oscofo) {
        return nullptr;
    }
    return oscofo;
}

// ─────────────────────────────────────
static int oscofo_getPitchProb(lua_State *L) {
    OScofo *OScofo = getOScofo(L);
    if (!OScofo) {
        return luaL_error(L, "Invalid OScofo instance");
    }
    double Freq = luaL_checknumber(L, 1);
    double Prob = OScofo->GetPitchProb(Freq);
    lua_pushnumber(L, Prob);
    return 1;
}

// ─────────────────────────────────────
static int oscofo_getBPM(lua_State *L) {
    OScofo *OScofo = getOScofo(L);
    if (!OScofo) {
        return luaL_error(L, "Invalid OScofo instance");
    }
    double bpm = OScofo->GetLiveBPM();
    lua_pushnumber(L, bpm);
    return 1;
}

// ─────────────────────────────────────
static int oscofo_getKappa(lua_State *L) {
    OScofo *OScofo = getOScofo(L);
    if (!OScofo) {
        return luaL_error(L, "Invalid OScofo instance");
    }
    double Kappa = OScofo->GetKappa();
    lua_pushnumber(L, Kappa);
    return 1;
}

// ─────────────────────────────────────
static int oscofo_getSpectrum(lua_State *L) {
    OScofo *OScofo = getOScofo(L);
    if (!OScofo) {
        return luaL_error(L, "Invalid OScofo instance");
    }
    std::vector<double> SpectralPower = OScofo->GetSpectrumPower();
    lua_newtable(L);
    for (size_t i = 0; i < SpectralPower.size(); ++i) {
        lua_pushnumber(L, SpectralPower[i]);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

// ─────────────────────────────────────
static const luaL_Reg oscofo_funcs[] = {
    // Tempo
    {"getKappa", oscofo_getKappa},
    {"getBPM", oscofo_getBPM},

    // Audio Description
    {"getPitchProb", oscofo_getPitchProb},
    {"getSpectrumPower", oscofo_getSpectrum},

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
