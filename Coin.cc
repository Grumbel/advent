//  $Id: Coin.cc,v 1.4 2000/12/30 13:11:56 grumbel Exp $
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

Coin::Coin ()
{
  visible = false;
  sur = CL_Surface ("retriever_coin", app.get_resource ());
  q_mark = CL_Surface ("q_mark", app.get_resource ());
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
Coin::update ()
{

}

void
Coin::on_button_press(CL_InputDevice *device, const CL_Key &key)
{
  //std::cout << "Coin pressed: " << key.id << std::endl;	
  if (key.id == 1)
    {
      std::cout << "Point Color: " << Scenario::current->get_colmap ()->get_pixel (key.x, key.y) 
		<< " " << key.x << "x" << key.y << std::endl;
    }
  else if (key.id == 2)
    {
      marked_obj = Scenario::current->get_object (CL_Mouse::get_x (), CL_Mouse::get_y ());
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

      GuileAdventObj* obj = dynamic_cast<GuileAdventObj*>(marked_obj);

      if (!obj)
	{
	  std::cout << "Don't know what to do with non GuileObj." << std::endl;
	}
      else
	{
	  std::cout << "Action on: " << marked_obj->get_name () << std::endl;
	  std::cout << "Key: " << key.x << " " << key.y << std::endl;
	  std::cout << "Pos: " << x_pos << " " << y_pos << std::endl;
	  std::cout << "Width: " << sur.get_width () << " " << "Height: " << sur.get_height() << std::endl;

	  if (key.x > x_pos - (sur.get_width ()/2)
	      && key.x < x_pos + (sur.get_width ()/2)
	      && key.y > y_pos - (sur.get_height ()/2)
	      && key.y < y_pos + (sur.get_height ()/2))
	    {
	      if (key.x < x_pos && key.y < y_pos)
		{
		  std::cout << "Use" << std::endl;
		  obj->call ("use", obj->get_name ());
		}
	      else if (key.x > x_pos && key.y < y_pos)
		{
		  std::cout << "Open/Close" << std::endl;
		  obj->call ("open", obj->get_name ());
		}
	      else if (key.x < x_pos && key.y > y_pos)
		{
		  std::cout << "Pickup" << std::endl;
		  obj->call ("pickup", obj->get_name ());
		}
	      else if (key.x > x_pos && key.y > y_pos)
		{
		  std::cout << "Inventory" << std::endl;
		  gh_eval_str ("(advent:eval \"inventory\")");
		  //obj->call ("pickup", obj->get_name ());
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
    }
}

/* EOF */
