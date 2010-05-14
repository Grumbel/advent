//  $Id: GuileAdventObj.cc,v 1.3 2000/12/30 14:56:04 grumbel Exp $
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

GuileAdventObj::GuileAdventObj (std::string arg_name,
				CL_Surface arg_sur, CL_Vector arg_pos)
{
  name = arg_name;
  surface_visible = true;
  sur = arg_sur;
  pos = arg_pos;

  width = sur.get_width ();
  height = sur.get_height ();
}

GuileAdventObj::GuileAdventObj (std::string arg_name, 
				CL_Vector arg_pos, 
				int arg_width, int arg_height)
  : name (arg_name), pos (arg_pos), width (arg_width), height (arg_height)
{
  surface_visible = true;
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
  if (sur && surface_visible)
    sur.put_screen (pos.x, pos.y);
}

bool 
GuileAdventObj::is_at (int x, int y)
{
  if (pos.x <= x
      && pos.x + width > x
      && pos.y <= y
      && pos.y + height > y)
    {
      return true;
    }
  return false;
}

void
GuileAdventObj::set_surface (std::string str)
{
  if (!str.empty ())
    {
      try
	{
	  std::cout << "GuileAdventObj: set_surface: " << str << std::endl;
	  sur = CL_Surface (str.c_str (), app.get_resource ()); 
	  surface_visible = true;
	  width = sur.get_width ();
	  height = sur.get_height ();
	}
      catch (CL_Error err)
	{
	  std::cout << "CL_Error: " << err.message << std::endl;
	}
    }
  else
    {
      surface_visible = false;
      // ClanLib BUG
      // sur = CL_Surface ();
    }
}

/* EOF */
