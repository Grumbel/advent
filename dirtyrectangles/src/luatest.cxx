extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <assert.h>
#include <vector>
#include "lua_value.hxx"

#define lua_register(L,n,f) \
               (lua_pushstring(L, n), \
                lua_pushcfunction(L, f), \
                lua_settable(L, LUA_GLOBALSINDEX))

std::vector<LuaValue> my_callbacks;

int my_function(lua_State *L)
{
  int n = lua_gettop(L); 
  printf("You called my_function() with %d arguments\n", n);
  return 0;
}

int set_callback(lua_State *L)
{
  int n = lua_gettop(L); 
  assert(n == 1);
  printf("You called set_callback() with %d arguments\n", n);
  my_callbacks.push_back(LuaValue(L, 0));
  return 0;
}

int call_callback(lua_State *L)
{
  int n = lua_gettop(L); 
  printf("You called call_callback() with %d arguments\n", n);

  for (std::vector<LuaValue>::iterator i = my_callbacks.begin(); i != my_callbacks.end(); ++i)
    {
      lua_pushstring(L, "print");
      lua_gettable(L, LUA_GLOBALSINDEX);
      lua_pushstring(L, "MyCallback is: ");
      i->push(L);
      lua_call(L, 2, 1);

      i->push(L);
      lua_call(L, 0, 0);
      if (lua_isfunction(L, 0))
        puts("Its a function");
    }

  return 0;
}

int main(int argc, char** argv)
{
  lua_State* state = lua_open();
  luaopen_base(state);
  luaopen_string(state);
  luaopen_table(state);
  luaopen_math(state);
  luaopen_io(state);
  luaopen_debug(state);

  lua_register(state, "my_function", &my_function);
  lua_register(state, "set_callback", &set_callback);
  lua_register(state, "call_callback", &call_callback);

  lua_dofile(state, "luatest.lua");

  lua_close(state);
}

// EOF //
