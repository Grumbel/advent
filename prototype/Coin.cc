//  $Id: Coin.cc,v 1.28 2001/08/22 10:19:10 grumbel Exp $
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
#include "ClickManager.hh"
#include "Font.hh"
#include "AdventObj.hh"
#include "Advent.hh"
#include "Coin.hh"
#include "Guy.hh"

Coin* coin;

Coin::Coin ()
{
  sur = CL_Surface ("retriever_coin", app.get_resource ());
  highlight = CL_Surface ("retriever_coin_hl", app.get_resource ());
  disabled_mark = CL_Surface ("disabled_mark", app.get_resource ());

  q_mark = CL_Surface ("q_mark", app.get_resource ());
  marked_obj = 0;
  current_obj = 0;
  ignore_press = false;
}

void 
Coin::draw ()
{
  if (input_mode == MODE_OBJECT)
    {
      // We want to use the current_object with something else
      if (current_obj)
	current_obj->draw_inventory (CL_Mouse::get_x (), CL_Mouse::get_y ());
    }
     
  if (input_mode == MODE_NORMAL || input_mode == MODE_OBJECT)
    {
      // Print the object name
      AdventObj* obj = Scenario::get_current ()->get_object (CL_Mouse::get_x (), CL_Mouse::get_y ());
  
      if (obj)
	{
	  font ("font")->print_center (320, 460, obj->get_name ().c_str ());
	  if (ClickManager::input_enabled)
	    q_mark.put_screen (CL_Mouse::get_x () - q_mark.get_width ()/2,
			       CL_Mouse::get_y () - q_mark.get_height ()/2);
	}
    }
  else
    {
      if (!ClickManager::input_enabled)
	disabled_mark.put_screen (CL_Mouse::get_x () - q_mark.get_width ()/2,
				  CL_Mouse::get_y () - q_mark.get_height ()/2);
    }

  // Draw the coin 
  if (input_mode == MODE_COIN)
    {
      sur.put_screen (click_pos.x - sur.get_width ()/2,
		      click_pos.y - sur.get_height ()/2);

      switch (current_action)
	{
	case USE:
	  highlight.put_screen (click_pos.x - 45,
				click_pos.y - 45);
	  break;
      
	case LOOK:
	  highlight.put_screen (click_pos.x - 5,
				click_pos.y - 45);
	  break;
      
	case PICKUP:
	  highlight.put_screen (click_pos.x - 45,
				click_pos.y - 5 );
	  break;
      
	case SPEAK:
	  highlight.put_screen (click_pos.x - 5 ,
				click_pos.y -  5);
	  break;
	default:
	  break;
	}
    }
}

void
Coin::update (float delta)
{
  if (input_mode == MODE_NORMAL && CL_Mouse::left_pressed ())
    {
      if (click_time + 250 < CL_System::get_time ())
	{
	  input_mode = MODE_COIN;
	}
    }

  CL_Vector key;

  key.x = CL_Mouse::get_x ();
  key.y = CL_Mouse::get_y ();
  
  float distance = (key - click_pos).norm ();

  if (input_mode == MODE_COIN && distance > 100.0f)
    {
      // Hide the coin
      input_mode = MODE_NORMAL;
    }
  else if (input_mode == MODE_COIN && distance < 10.0f)
    {
      current_action = NONE;
    }
  else if (input_mode == MODE_COIN)
    {
      if (key.x > click_pos.x - ((int)sur.get_width ()/2)
	  && key.x < click_pos.x + ((int) sur.get_width ()/2)
	  && key.y > click_pos.y - ((int) sur.get_height ()/2)
	  && key.y < click_pos.y + ((int) sur.get_height ()/2))
	{
	  if (key.x < click_pos.x && key.y < click_pos.y)
	    {
	      current_action = USE;
	    }
	  else if (key.x > click_pos.x && key.y < click_pos.y)
	    {
	      current_action = LOOK;
	    }
	  else if (key.x < click_pos.x && key.y > click_pos.y)
	    {
	      current_action = PICKUP;
	    }
	  else if (key.x > click_pos.x && key.y > click_pos.y)
	    {
	      current_action = SPEAK;
	    }
	  else
	    {
	      current_action = NONE;
	    }
	}
      else
	{
	  current_action = NONE;
	}
    }
}

void 
Coin::set_current_obj (AdventObj* obj)
{
  std::cout << "Setting current_obj" << std::endl;
  current_obj = obj;
}

void 
Coin::call_current_action ()
{
  if (click_obj == NULL)
    {
      std::cout << "BUG: click_obj is NULL, this shouldn't happen." << std::endl;
      return;
    }
  
  switch (current_action)
    {
    case USE:
      std::cout << "Calling: use" << std::endl;
      gh_call2 (gh_lookup ("adv:use"), 
		Guy::get_current ()->get_scm (), 
		click_obj->get_scm ());
      break;
    case LOOK:
      gh_call2 (gh_lookup ("adv:look"), 
		Guy::get_current ()->get_scm (), 
		click_obj->get_scm ());
      break;
    case PICKUP:
      gh_call2 (gh_lookup("adv:pickup"), 
		Guy::get_current ()->get_scm (), 
		click_obj->get_scm ());
      break;
    case SPEAK:
      gh_call2 (gh_lookup("adv:speak"),
		Guy::get_current ()->get_scm (), 
		click_obj->get_scm ());
      break;
    default:
      std::cout << "Action selection abort" << std::endl;
    }
}

bool
Coin::on_mouse_press(const CL_Key& key)
{
  if (input_mode == MODE_NORMAL || input_mode == MODE_OBJECT)
    {
      if (key.id == CL_MOUSE_LEFTBUTTON)
	{
	  click_pos = CL_Vector (key.x, key.y);
	  click_obj = Scenario::get_current ()->get_object (CL_Mouse::get_x (), CL_Mouse::get_y ());
	  click_time = CL_System::get_time ();

	  return true;
	}
      if (input_mode == MODE_OBJECT && key.id == CL_MOUSE_RIGHTBUTTON)
	{
	  input_mode = MODE_NORMAL;
	  return true;
	}
    }
  
  return false;
}

bool 
Coin::on_mouse_release (const CL_Key& key)
{
  if (input_mode == MODE_NORMAL && key.id == CL_MOUSE_LEFTBUTTON)
    {
      //std::cout << "Got Walk" << std::endl;
      Guy::get_current ()->walk_to_mouse ();
      if (click_time + 250 >= CL_System::get_time ())
	{
	  input_mode = MODE_NORMAL;
	}
      return true;
    }

  if (input_mode == MODE_COIN && key.id == CL_MOUSE_RIGHTBUTTON)
    {
      input_mode = MODE_NORMAL;
      return true;
    }

  if (input_mode == MODE_COIN && key.id == CL_MOUSE_LEFTBUTTON 
      && current_action != NONE)
    {
      std::cout << "Call_current_action" << std::endl;
      input_mode = MODE_NORMAL;
      call_current_action ();
      return true;
    }

  if (input_mode == MODE_OBJECT && key.id == CL_MOUSE_LEFTBUTTON && current_obj)
    {      
      AdventObj* marked_obj = Scenario::get_current ()->get_object (CL_Mouse::get_x (),
								    CL_Mouse::get_y ());
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
	      input_mode = MODE_NORMAL;
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
