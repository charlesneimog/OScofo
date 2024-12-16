#pragma once

#include <OScofo.hpp>

extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <m_pd.h>
}

namespace OScofo {

class PdLua {
  public:
    PdLua();
    bool execute(std::string code);
    std::string getError();

  private:
    lua_State *m_L;
};

} // namespace OScofo
