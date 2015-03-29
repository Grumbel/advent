//  $Id: Animation.cc,v 1.5 2001/07/12 08:13:49 grumbel Exp $
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

#include "Scenario.hh"
#include "Advent.hh"
#include "Animation.hh"

Frame::Frame (SCM frame)
{
  SCM surname = gh_call1 (gh_lookup ("surface-name"), frame);
  assert (SCM_STRINGP (surname));
  //std::cout << "Surfacename: " << SCM_CHARS(surname) << std::endl;
  sur = CL_Surface (SCM_CHARS(surname), app.get_resource ());

  SCM disp_time = gh_call1 (gh_lookup ("display-time"), frame);
  assert (SCM_INUMP (disp_time));
  display_time = SCM_INUM (disp_time);

  SCM sframe = gh_call1 (gh_lookup ("sub-frame"), frame);
  assert (SCM_INUMP (sframe));
  sub_frame = SCM_INUM (sframe);
  assert (sub_frame < sur.get_num_frames ());

  SCM position = gh_call1 (gh_lookup ("position"), frame);
  pos.x = SCM_INUM(SCM_CAR (position));
  pos.y = SCM_INUM(SCM_CADR (position));
  pos.z = SCM_INUM(SCM_CADDR (position));
}

Frame::~Frame () {}

float
Frame::get_z_pos () { return pos.z; }

void
Frame::draw_world (int x_offset = 0, int y_offset = 0)
{
  sur.put_screen (int(pos.x + x_offset), int(pos.y + y_offset), sub_frame);
}

Animation::Animation (SCM animation)
  : remove_me (false),
    display_start (0)
{
  SCM frame_objs = gh_call1 (gh_lookup("frames"), animation);

  std::cout << "Creating animations..." << std::endl;
  while (frame_objs != SCM_EOL)
    {
      frames.push_back (new Frame (SCM_CAR (frame_objs)));

      frame_objs = SCM_CDR (frame_objs);
    }
  std::cout << "Creating animations done" << std::endl;
  assert (!frames.empty ());
  current_frame = frames.begin ();
  display_start = CL_System::get_time ();
}

Animation::~Animation ()
{
  std::cout << "Deleting animation" << std::endl;
}

void
Animation::update (float delta)
{
  if (display_start + (*current_frame)->display_time < CL_System::get_time ())
    {
      ++current_frame;
      display_start = CL_System::get_time ();
      if (current_frame == frames.end ())
	{
	  current_frame = frames.begin ();
	  remove_me = true;
	}
    }
}

void
Animation::draw_world (int x_offset, int y_offset)
{
  return (*current_frame)->draw_world ();
}

float
Animation::get_z_pos ()
{
  return (*current_frame)->get_z_pos ();
}

void
Animation::init ()
{
  gh_new_procedure1_0 ("c:animation-play", Animation::play);
}

SCM
Animation::play (SCM animation)
{
  Scenario::get_current ()->add (new Animation (animation));
  return SCM_UNSPECIFIED;
}


/* EOF */
