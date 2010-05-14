//  $Id: AdventObj.cc,v 1.1 2000/12/28 20:00:49 grumbel Exp $
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

#include <ClanLib/core.h>
#include "Scenario.hh"
#include "Advent.hh"
#include "AdventObj.hh"

SurfaceAdvObj::SurfaceAdvObj (Scenario* s, const CL_Surface& arg_sur, const CL_Vector& arg_pos)
  : AdventObj (s)
{
  sur = arg_sur;
  pos = arg_pos;
}

void 
SurfaceAdvObj::draw_world ()
{
  sur.put_screen (pos.x, pos.y);
}

Mogli::Mogli (Scenario* s) : AdventObj (s)
{
  sur_front = CL_Surface ("mogli_front", app.get_resource ());
  sur_back  = CL_Surface ("mogli_back", app.get_resource ());
  sur_left  = CL_Surface ("mogli_left", app.get_resource ());
  sur_right = CL_Surface ("mogli_right", app.get_resource ());

  counter = 0;
  pos.x = 320;
  pos.y = 400;
  delta = 4.0;

  on_button_press_slot = CL_Input::sig_button_press.connect (thCreateSlot(this, &Mogli::on_button_press));
}

Mogli::~Mogli ()
{
}

void 
Mogli::update ()
{
  // update animation
  if (target != pos)
    {
      counter++;
      if (counter > 7)
	counter = 0;

      if (on_target ())
	{
	  target = pos;
	}
      else
	{
	  CL_Vector tmp_pos = pos + direction;
	  if (scenario->get_colmap ()->get_pixel (tmp_pos.x, tmp_pos.y) != 0)
	    {
	      pos = tmp_pos;
	      pos.z = scenario->get_colmap ()->get_pixel (pos.x, pos.y);
	    }
	  else
	    {
	      target = pos;
	    }
	}
    }
  else
    {
      counter = 0;
    }
}

bool
Mogli::on_target ()
{
  if (pos.x - delta < target.x 
      && pos.x + delta > target.x
      && pos.y - delta < target.y 
      && pos.y + delta > target.y)
    {
      return true;
    }
  return false;
}

void 
Mogli::draw_world ()
{
  float zoom = scenario->get_colmap ()->get_pixel (pos.x, pos.y) / 255.0;

  CL_Surface* sur;
  
  if (fabs(direction.x) < fabs(direction.y))
    {
      if (direction.y > 0)
	  sur = &sur_front;
	  else 
	  sur = &sur_back;
    }
  else
    {
      if (direction.x > 0)
	sur = &sur_right;
      else 
	sur = &sur_left;
    }

  sur->put_screen (pos.x - (sur->get_width ()/2 * zoom), 
		   pos.y - (sur->get_height () * zoom),
		   zoom, zoom, counter % sur->get_num_frames ());
  //std::cout << "Zoom: " << zoom << std::endl;
}

void 
Mogli::on_button_press(CL_InputDevice *device, const CL_Key &key)
{
  if (key.id == 0)
    {
      direction = CL_Vector (key.x - pos.x, key.y - pos.y);
      direction.normalize ();
      direction *= 5.0;
      target = CL_Vector (key.x, key.y);
    }
}

bool 
Mogli::is_at (int x, int y)
{
  if (pos.x - sur_left.get_width()/2 < x
      && pos.x + sur_left.get_width()/2 > x
      && pos.y > y
      && pos.y - sur_left.get_height () < y)
    {
      return true;
    }
  return false;
}

/* EOF */
