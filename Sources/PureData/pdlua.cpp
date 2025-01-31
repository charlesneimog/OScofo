#include <OScofo.hpp>
#include <m_pd.h>

static int pd_Post(lua_State *L) {
    int num_args = lua_gettop(L);
    for (int i = 1; i <= num_args; i++) {
        if (lua_type(L, i) == LUA_TSTRING) {
            post("%s", lua_tostring(L, i));
        } else if (lua_type(L, i) == LUA_TNUMBER) {
            post("%f", lua_tonumber(L, i));
        } else if (lua_type(L, i) == LUA_TBOOLEAN) {
            if (lua_toboolean(L, i)) {
                post("true");
            } else {
                post("false");
            }
        } else {
            post("Unsupported type: %s", lua_typename(L, lua_type(L, i)));
        }
    }

    return 0;
}

// ─────────────────────────────────────
static int pd_Error(lua_State *L) {
    int num_args = lua_gettop(L);
    for (int i = 1; i <= num_args; i++) {
        if (lua_type(L, i) == LUA_TSTRING) {
            pd_error(nullptr, "%s", lua_tostring(L, i));
        } else if (lua_type(L, i) == LUA_TNUMBER) {
            pd_error(nullptr, "%f", lua_tonumber(L, i));
        } else if (lua_type(L, i) == LUA_TBOOLEAN) {
            if (lua_toboolean(L, i)) {
                pd_error(nullptr, "true");
            } else {
                pd_error(nullptr, "false");
            }
        } else {
            pd_error(nullptr, "Unsupported type: %s", lua_typename(L, lua_type(L, i)));
        }
    }
    return 0;
}

// ─────────────────────────────────────
static int pd_sendBang(lua_State *L) {
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
static int pd_sendFloat(lua_State *L) {
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
static int pd_sendSymbol(lua_State *L) {
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
static int pd_sendList(lua_State *L) {
    const char *r = luaL_checkstring(L, 1);
    luaL_checktype(L, 2, LUA_TTABLE);
    t_symbol *symbol = gensym(r);
    if (!symbol->s_thing) {
        return luaL_error(L, "Receiver not found");
    }

    const int listSize = luaL_len(L, 2);
    std::vector<t_atom> atomList(listSize);

    for (int i = 0; i < listSize; i++) {
        lua_rawgeti(L, 2, i + 1);
        if (lua_isnumber(L, -1)) {
            SETFLOAT(&atomList[i], lua_tonumber(L, -1));
        } else if (lua_isstring(L, -1)) {
            SETSYMBOL(&atomList[i], gensym(lua_tostring(L, -1)));
        } else {
            return luaL_error(L, "Table contains unsupported value type");
        }
        lua_pop(L, 1);
    }
    pd_list(symbol->s_thing, &s_list, listSize, atomList.data());
    return 0;
}

// ─────────────────────────────────────
static const luaL_Reg pd_funcs[] = {

    // Log
    {"print", pd_Post},
    {"post", pd_Post},
    {"error", pd_Error},

    // PureData
    {"sendBang", pd_sendBang},
    {"sendFloat", pd_sendFloat},
    {"sendSymbol", pd_sendSymbol},
    {"sendList", pd_sendList},

    // Sentinela
    {NULL, NULL}};

// ─────────────────────────────────────
int luaopen_pd(lua_State *L) {
    luaL_newlib(L, pd_funcs);
    return 1;
}
