//  $Id: Spritecollideable.cxx,v 1.8 2004/01/14 02:28:24 grumbel Exp $
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

#include "scm_converter.hxx"
#include "sprite_drawable.hxx"
#include "sprite_collideable.hxx"
#include "util.hxx"

namespace Advent {

bool
SpriteCollideable::is_over (int x_pos, int y_pos)
{
  return (pos.x <= x_pos && pos.x + sprite->get_width () > x_pos
	  && pos.y <= y_pos && pos.y + sprite->get_height () > y_pos);
}

void
SpriteCollideable::update (float delta)
{
  // do nothing
}

void
SpriteCollideable::register_guile_bindings ()
{
  puts ("SpriteCollideable::register_guile_bindings ()");

  gh_c_define_public_gsubr("c:sprite-collideable:create", 1, 0, 0,
		       reinterpret_cast<scm_t_subr>(&SpriteCollideable::scm_sprite_collideable_create));
}

/*
SCM
SpriteCollideable::mark (SCM smob)
{
  return SCM_BOOL_F;
}

size_t
SpriteCollideable::free (SCM smob)
{
  std::cout << "SpriteCollideable::free" << std::endl;
  delete smob_cast<SpriteCollideable>(smob);
  return 0; //sizeof (SpriteCollideable);
}

int
SpriteCollideable::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  return 1;
}
*/
SCM
SpriteCollideable::scm_sprite_collideable_create (SCM sprite_drawable)
{
  SpriteDrawable* drawable = smobbox_cast<SpriteDrawable>(sprite_drawable);
  SpriteCollideable* obj = new SpriteCollideable (drawable->get_sprite ().get (),
						  drawable->get_pos ());
  return CollideableSmob::create (obj);
}

} // namespace Advent

/* EOF */
