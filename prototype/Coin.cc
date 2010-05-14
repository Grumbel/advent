//  $Id: Coin.cc,v 1.17 2001/07/02 10:27:13 grumbel Exp $
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

#include <guile/gh.h>
#include "GuileAdventObj.hh"
#include "Font.hh"
#include "AdventObj.hh"
#include "Advent.hh"
#include "Coin.hh"

Coin* coin;

Coin::Coin ()
{
  visible = false;
  sur = CL_Surface ("retriever_coin", app.get_resource ());
  q_mark = CL_Surface ("q_mark", app.get_resource ());
  marked_obj = 0;
  current_obj = 0;
  ignore_press = false;
}

void 
Coin::draw ()
{
  if (current_obj)
    {
      current_obj->draw_inventory (CL_Mouse::get_x (), CL_Mouse::get_y ());
    }

  if (visible)
    {
      sur.put_screen (x_pos - sur.get_width ()/2,
		      y_pos - sur.get_height ()/2);
    }

  AdventObj* obj = Scenario::current->get_object (CL_Mouse::get_x (), CL_Mouse::get_y ());

  if (obj)
    {
      font ("font")->print_center (320, 460, obj->get_name ().c_str ());
      if (!visible)
	q_mark.put_screen (CL_Mouse::get_x () - q_mark.get_width ()/2,
			   CL_Mouse::get_y () - q_mark.get_height ()/2);
    }
}

void
Coin::update (float delta)
{

}

void 
Coin::set_current_obj (AdventObj* obj)
{
  std::cout << "Setting current_obj" << std::endl;
  current_obj = obj;
}

bool
Coin::on_mouse_press(const CL_Key& key)
{
  if (key.id == CL_MOUSE_RIGHTBUTTON || key.id == 2)
    {
      marked_obj = Scenario::current->get_object (CL_Mouse::get_x (), CL_Mouse::get_y ());
      if (marked_obj)
	{
	  visible = true;
	  x_pos = (int) key.x;
	  y_pos = (int)key.y;
	}
      return true;
    }
  return false;
}

bool 
Coin::on_mouse_release (const CL_Key& key)
{
  if ((key.id == 2 || key.id == CL_MOUSE_RIGHTBUTTON) 
      && current_obj)
    {
      if (ignore_press)
	ignore_press = false;
      else
	{
	  AdventObj* marked_obj = Scenario::current->get_object (CL_Mouse::get_x (), CL_Mouse::get_y ());
	  if (marked_obj)
	    {
	      GuileAdventObj* obj = dynamic_cast<GuileAdventObj*>(marked_obj);
	      GuileAdventObj* cobj = dynamic_cast<GuileAdventObj*>(current_obj);

	      if (!obj)
		{
		  std::cout << "Don't know what to do with non GuileObj." << std::endl;
		  current_obj = 0;
		}
	      else
		{
		  std::cout << "Use: " << current_obj->get_name () << " with " << obj->get_name () << std::endl;
		  gh_call2 (gh_lookup ("adv:combine"), 
			    cobj->get_scm (),  // Object from the inventory
			    obj->get_scm ()); // the object somewhere in the scenario
		  
			    
		  current_obj = 0;
		}
	    }
	  else
	    {
	      current_obj = 0;
	    }
	}
      return true;
    }
  else if (key.id == 2 || key.id == CL_MOUSE_RIGHTBUTTON)
    {
      visible = false;

      GuileAdventObj* obj = dynamic_cast<GuileAdventObj*>(marked_obj);

      if (!obj)
	{
	  std::cout << "Don't know what to do with non GuileObj." << std::endl;
	}
      else
	{
	  /*std::cout << "Action on: " << marked_obj->get_name () << std::endl;
	  std::cout << "Key: " << key.x << " " << key.y << std::endl;
	  std::cout << "Pos: " << x_pos << " " << y_pos << std::endl;
	  std::cout << "Width: " << sur.get_width () << " "
	  << "Height: " << sur.get_height() << std::endl;*/

	  if (key.x > x_pos - ((int)sur.get_width ()/2)
	      && key.x < x_pos + ((int) sur.get_width ()/2)
	      && key.y > y_pos - ((int) sur.get_height ()/2)
	      && key.y < y_pos + ((int) sur.get_height ()/2))
	    {
	      if (key.x < x_pos && key.y < y_pos)
		{
		  gh_call1 (gh_lookup ("adv:use"), obj->get_scm ());
		}
	      else if (key.x > x_pos && key.y < y_pos)
		{
		  gh_call1 (gh_lookup ("adv:look"), obj->get_scm ());
		}
	      else if (key.x < x_pos && key.y > y_pos)
		{
		  gh_call1 (gh_lookup("adv:pickup"), obj->get_scm ());
		}
	      else if (key.x > x_pos && key.y > y_pos)
		{
		  gh_call1 (gh_lookup("adv:speak"), obj->get_scm ());
		}
	      else
		{
		  std::cout << "Coin: don't know what to do, !@#$" << std::endl;
		}
	    }
	  else
	    {
	      std::cout << "Coin: left coin region" << std::endl;
	    }
	}
      return true;
    }
  return false;
}

float
Coin::priority ()
{
  return 0.5;
}

/* EOF */
