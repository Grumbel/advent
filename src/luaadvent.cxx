extern "C" {
#include "lua.h"
}

#include "tolua++.h"

int tolua_advent_open (lua_State* tolua_S);

int main(int argc, char** argv)
{
  lua_State* state = lua_open();
  tolua_advent_open(state);
  lua_dofile(state, "test.lua");
  lua_close(state);
}

// EOF //

