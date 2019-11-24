//  $Id: rect_sprite.cxx,v 1.10 2004/01/14 02:28:24 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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
#include <ClanLib/display.h>
#include "scm_converter.hxx"
#include "rect_sprite.hxx"

namespace Advent {

RectSprite::RectSprite (int arg_width, int arg_height, const Color& c)
  : width (arg_width), height (arg_height), color (c)
{
  filled = true;
  //color = Color (0.0f, 0.0f, 0.0f);
}

RectSprite::~RectSprite ()
{
}

void
RectSprite::update (float delta)
{
}

void
RectSprite::draw (boost::dummy_ptr<View> view, const CL_Vector& pos)
{
  CL_Display::fill_rect (CL_Rect(int(pos.x), int(pos.y),
                                 int(pos.x + width), int(pos.y + height)),
			 CL_Color(int(255*color.r), int(255*color.g), int(255*color.b), int(255*color.a)));
}

int
RectSprite::get_width () const
{
  return width;
}

int
RectSprite::get_height () const
{
  return height;
}


void
RectSprite::register_guile_bindings ()
{
  puts ("RectSprite::register_guile_bindings ()");

  scm_c_define_gsubr("c:rect-sprite:create", 3, 0, 0, reinterpret_cast<scm_t_subr>(&RectSprite::scm_rect_sprite_create));
  scm_c_define_gsubr("c:rect-sprite:set-color", 2, 0, 0, reinterpret_cast<scm_t_subr>(&RectSprite::scm_rect_sprite_set_color));
}

/*
SCM
RectSprite::mark (SCM smob)
{
  return SCM_BOOL_F;
}

size_t
RectSprite::free (SCM smob)
{
  std::cout << "RectSprite::free" << std::endl;
  delete smob_cast<RectSprite>(smob);
  return 0; //sizeof (RectSprite);
}

int
RectSprite::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:SurfaseSprite>", port);
  return 1;
}
*/
SCM
RectSprite::scm_rect_sprite_create (SCM width, SCM height, SCM scm_color)
{
  return SpriteSmob::create(new RectSprite (scm_to_int (width), scm_to_int (height),
				     Color (scm_color)));
}

SCM
RectSprite::scm_rect_sprite_set_color (SCM scm_rect, SCM scm_color)
{
  RectSprite* rect = smobbox_cast<RectSprite>(scm_rect);
  rect->color = Color (scm_color);
  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
