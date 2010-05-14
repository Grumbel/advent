//  $Id: GuileAdventObj.cc,v 1.1 2000/12/28 20:00:49 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include <string.h>
#include <guile/gh.h>
#include "Advent.hh"
#include "GuileAdventObj.hh"

GuileAdventObj::GuileAdventObj (Scenario* s, std::string arg_name, int arg_id,
				CL_Surface arg_sur, CL_Vector arg_pos)
  : AdventObj (s)
{
  name = arg_name;
  id = arg_id;

  sur = arg_sur;
  pos = arg_pos;
}

void 
GuileAdventObj::call (std::string func, std::string id)
{
  std::string call = "(advent:eval \"";
  call += func;
  call += " ";
  call += id;
  call += "\")";
  std::cout << "Call: " << call << std::endl;
  char* str = strdup (call.c_str ());
  
  gh_eval_str (str);
  
  free (str);
}

void
GuileAdventObj::draw_world ()
{
  sur.put_screen (pos.x, pos.y);
}

bool 
GuileAdventObj::is_at (int x, int y)
{
  if (pos.x < x
      && pos.x + sur.get_width() > x
      && pos.y < y
      && pos.y + sur.get_height () > y)
    {
      return true;
    }
  return false;
}

void
GuileAdventObj::set_surface (std::string str)
{
  std::cout << "GuileAdventObj: set_surface: " << str << std::endl;
  sur = CL_Surface (str.c_str (), app.get_resource ()); 
}

/* EOF */
