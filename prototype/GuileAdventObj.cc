//  $Id: GuileAdventObj.cc,v 1.24 2001/07/16 17:44:10 grumbel Exp $
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
#include "View.hh"
#include "Advent.hh"
#include "GuileAdventObj.hh"

GuileAdventObj::GuileAdventObj (SCM arg_name,
				std::string arg_surname, CL_Vector arg_pos)
  : counter (0), is_init (false)
{
  empty_object = false;
  if (SCM_STRINGP (arg_name))
    {
      scm_object = SCM_BOOL_F;
      name = SCM_CHARS (arg_name);
    }
  else
    {
      scm_object = arg_name;
      name = SCM_CHARS (gh_call1 (gh_lookup ("name"), scm_object));
    }

  surface_visible = true;
  surname = arg_surname;
  pos = arg_pos;

}

void
GuileAdventObj::init ()
{
  if (is_init)
    {
      std::cout << "GuileAdventObj: Already init!" << std::endl;
    }
  else
    {
      sur = CL_Surface (surname.c_str (), app.get_resource ());
      width = sur.get_width ();
      height = sur.get_height ();
      is_init = true;
    }
}

GuileAdventObj::GuileAdventObj (SCM arg_name,
				CL_Vector arg_pos,
				int arg_width, int arg_height)
  : pos (arg_pos), width (arg_width), height (arg_height),
    counter (0), is_init (true)
{
  empty_object = false;
  if (SCM_STRINGP (arg_name))
    {
      scm_object = SCM_BOOL_F;
      name = SCM_CHARS(arg_name);
    }
  else
    {
      scm_object = arg_name;
      name = SCM_CHARS (gh_call1 (gh_lookup ("name"), scm_object));
    }

  surname = "";
  surface_visible = true;
  //std::cout << "name:"<< name <<": " << width << " " << height << std::endl;
}

SCM
GuileAdventObj::call (std::string func)
{
  if (SCM_BOOL_F == scm_object)
    {
      puts ("don't have scm object for call");
      return SCM_BOOL_F;
    }
  else
    {
      char* str = strdup (func.c_str ());
      SCM ret_val = gh_call1 (gh_lookup (str), scm_object);
      free (str);
      return ret_val;
    }
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
GuileAdventObj::update (float delta)
{
  //char command[1024];
  //  std::cout << "Updating..." << std::endl;
  //sprintf (command, "(println (name \"guile updating\")");
  //gh_eval_str (command);
  if (SCM_BOOL_F != scm_object)
    {
      //  printf ("bool: %d", scm_object);
      // printf ("GUILE: LOOKUP: %s\n", name.c_str ());
      //std::cout << "Calling update: " << scm_object << std::endl;
      gh_call1 (gh_lookup ("update"), scm_object);
      // puts ("GUILE: LOOKUP DONE");
    }
  else
    {
      //puts ("no");
    }
}

void
GuileAdventObj::draw_world (int x_offset = 0, int y_offset = 0)
{
  if (!is_init) init ();

  if (sur && surface_visible)
    {
      if (sur.get_num_frames () == 1)
	sur.put_screen (int(pos.x + x_offset), int(pos.y + y_offset));
      else
	{
	  // FIXME: HACK
	  if (counter >= ((int) sur.get_num_frames ()) * 10)
	    counter = 0;
	  sur.put_screen (int(pos.x + x_offset), int(pos.y + y_offset), counter/10);
	  counter++;
	}
    }
}

void
GuileAdventObj::draw_inventory (int x, int y)
{
  if (!is_init) init ();

  //std::cout << "Drawing Inv. Object: " << x << " " << y << std::endl;
  if (inventory_sur)
    inventory_sur.put_screen (x - inventory_sur.get_width ()/2,
			      y - inventory_sur.get_height ()/2);
}

bool
GuileAdventObj::is_at (int x, int y)
{
  if (empty_object) return false;

  if (!is_init) init ();

  if (pos.x + the_view->x_offset <= x
      && pos.x + width + the_view->x_offset > x
      && pos.y + the_view->y_offset  <= y
      && pos.y + the_view->y_offset  + height > y)
    {
      return true;
    }
  return false;
}

void
GuileAdventObj::set_inventory_surface (std::string str)
{
  //std::cout << "set_inventory_surface()" << std::endl;
  try {
    inventory_sur = CL_Surface (str.c_str (), app.get_resource ());
  } catch (CL_Error err) {
    std::cout << "CL_Error: " << err.message << std::endl;
  }
}

void
GuileAdventObj::set_surface_pos (int x_pos, int y_pos, int z_pos)
{
  pos = CL_Vector (x_pos, y_pos);
}

void
GuileAdventObj::set_surface (std::string str)
{
  if (!str.empty ())
    {
      try
	{
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
    }
}

/* EOF */
