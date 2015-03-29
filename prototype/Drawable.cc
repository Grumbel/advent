//  $Id: Drawable.cc,v 1.4 2001/07/12 08:13:49 grumbel Exp $
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

#include "Advent.hh"
#include "Scenario.hh"
#include "Drawable.hh"

DrawableObj::DrawableObj (std::string sur_name, const CL_Vector arg_pos)
  : sur (sur_name.c_str (), app.get_resource ()),
    pos (arg_pos)
{

}

DrawableObj::~DrawableObj ()
{
}

void
DrawableObj::draw_world (int x_offset = 0, int y_offset = 0)
{
  sur.put_screen (pos.x + x_offset, pos.y + y_offset);
}


bool
DrawableFill::removeable ()
{
  return drawn > 2;
}

DrawableFill::DrawableFill (float arg_red, float arg_green, float arg_blue, float arg_alpha)
  : drawn (0),
    red (arg_red), green (arg_green), blue (arg_blue), alpha (arg_alpha)
{

}

void
DrawableFill::draw_world (int x_offset = 0, int y_offset = 0)
{
  ++drawn;
  CL_Display::fill_rect (0, 0, 640, 480,
			 red, green, blue, alpha);
}

float
DrawableFill::get_z_pos ()
{
 return 255.0;
}

void
DrawableSmob::add (std::string sur_name, const CL_Vector& vec)
{
  Scenario::get_current ()->add (new DrawableObj (sur_name, vec));
}

void
DrawableSmob::init ()
{
  gh_new_procedure2_0 ("c:draw", DrawableSmob::draw);
  gh_new_procedure4_0 ("c:fill-display", DrawableSmob::fill_display);
}

SCM
DrawableSmob::draw (SCM sur_name, SCM pos)
{
  int x_pos = SCM_INUM (SCM_CAR (pos));
  int y_pos = SCM_INUM (SCM_CADR (pos));
  int z_pos = SCM_INUM (SCM_CADDR (pos));

  //std::cout << "DRAWABLESMOB: " << x_pos << " " << y_pos << " " << z_pos << std::endl;

  add (SCM_CHARS (sur_name), CL_Vector (x_pos, y_pos, z_pos));

  return SCM_UNSPECIFIED;
}

SCM
DrawableSmob::fill_display (SCM arg_red, SCM arg_green, SCM arg_blue, SCM arg_alpha)
{
  assert(SCM_INUMP (arg_red));
  assert(SCM_INUMP (arg_green));
  assert(SCM_INUMP (arg_blue));
  assert(SCM_INUMP (arg_alpha));

  Scenario::get_current ()->add (new DrawableFill (SCM_INUM (arg_red)/255.0,
					    SCM_INUM (arg_green)/255.0,
					    SCM_INUM (arg_blue)/255.0,
					    SCM_INUM (arg_alpha)/255.0));
  return SCM_UNSPECIFIED;
}

/* EOF */
