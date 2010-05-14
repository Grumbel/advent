//  $Id$
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

Coin::Coin (Scenario* s)
{
  scenario = s;  
  visible = false;
  sur = CL_Surface ("coin", app.get_resource ());
  on_button_press_slot = CL_Input::sig_button_press.connect (thCreateSlot(this, &Coin::on_button_press));
  on_button_release_slot = CL_Input::sig_button_release.connect (thCreateSlot(this, &Coin::on_button_release));
  marked_obj = 0;
}

void 
Coin::draw ()
{
  if (visible)
    {
      //std::cout << "Drawing..." << x_pos << " " << y_pos << std::endl;
      sur.put_screen (x_pos - sur.get_width ()/2,
		      y_pos - sur.get_height ()/2);
    }

  AdventObj* obj = scenario->get_object (CL_Mouse::get_x (), CL_Mouse::get_y ());

  if (obj)
    {
      font ("font")->print_center (320, 460, obj->get_name ().c_str ());
    }
}

void
Coin::update ()
{

}

void
Coin::on_button_press(CL_InputDevice *device, const CL_Key &key)
{
  std::cout << "Coin pressed: " << key.id << std::endl;	
  if (key.id == 1)
    {
      std::cout << "Point Color: " << scenario->get_colmap ()->get_pixel (key.x, key.y) 
		<< " " << key.x << "x" << key.y << std::endl;
    }
  else if (key.id == 2)
    {
      marked_obj = scenario->get_object (CL_Mouse::get_x (), CL_Mouse::get_y ());
      if (marked_obj)
	{
	  visible = true;
	  x_pos = (int) key.x;
	  y_pos = (int)key.y;
	}
    }
}

void 
Coin::on_button_release (CL_InputDevice *device, const CL_Key &key)
{
  //std::cout << "Coin released: " << key.id << std::endl;
  if (key.id == 2)
    {
      visible = false;

      if (marked_obj)
	{
	  std::cout << "Action on: " << marked_obj->get_name () << std::endl;
	  
	  if (key.x > x_pos - sur.get_width ()/2
	      && key.x < x_pos + sur.get_width ()/2
	      && key.y > y_pos - sur.get_height ()/2
	      && key.y < y_pos + sur.get_height ()/2)
	    {
	      if (key.x < x_pos && key.y < y_pos)
		{
		  std::cout << "Use" << std::endl;
		  //gh_eval_str ("(advent:eval \"use whip\")");
		  GuileAdventObj* obj = dynamic_cast<GuileAdventObj*>(marked_obj);
		  obj->call ("use", obj->get_name ());
		}
	      else if (key.x > x_pos && key.y < y_pos)
		{
		  std::cout << "Open/Close" << std::endl;
		  //gh_eval_str ("(advent:eval \"use whip box\")");
		  GuileAdventObj* obj = dynamic_cast<GuileAdventObj*>(marked_obj);
		  obj->call ("open", obj->get_name ());
		}
	      else if (key.x < x_pos && key.y > y_pos)
		{
		  std::cout << "Pickup" << std::endl;
		  //gh_eval_str ("(advent:eval \"pickup whip\")");
		  GuileAdventObj* obj = dynamic_cast<GuileAdventObj*>(marked_obj);
		  obj->call ("pickup", obj->get_name ());
		}
	      else if (key.x > x_pos && key.y > y_pos)
		{
		  std::cout << "Inventory" << std::endl;
		  gh_eval_str ("(advent:eval \"inventory\")");
		  //obj->call ("pickup", obj->get_name ());
		}
	    }
	}
    }
}

/* EOF */
