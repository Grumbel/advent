//  $Id$
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <sstream>
#include <iostream>
#include "lua_value.hxx"

int LuaValue::uniq_num = 1;

LuaValue::LuaValue()
{
  state = 0;
}

LuaValue::LuaValue(lua_State *L, int index)
{
  state = L;

  // Get a value from the stack, create a uniq key for it and store it
  // in the registry
  std::stringstream str;
  str << "luavalue" << uniq_num++;
  id = str.str();
  std::cout << "LuaValue: id: " << id << std::endl;
  // key
  lua_pushstring(L, id.c_str());
  // value
  lua_pushvalue(L, index + 1);
  lua_settable (L, LUA_REGISTRYINDEX);
}

LuaValue::~LuaValue()
{
  
}

void
LuaValue::push(lua_State *L)
{
  if (state)
    lua_pushstring(L, id.c_str()); 
  else
    lua_pushnil(L);

  lua_gettable(L, LUA_REGISTRYINDEX); 
  //lua_call(L, 0, 0);
}

/* EOF */
