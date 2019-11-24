//  $Id: Spritedrawable.cxx,v 1.14 2004/01/14 02:28:24 grumbel Exp $
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

#include "drawable_smob.hxx"
#include "scm_converter.hxx"
#include "debug.hxx"
#include "sprite_drawable.hxx"

//long SpriteDrawable::tag;

namespace Advent {

SpriteDrawable::SpriteDrawable (SCM arg_sprite, CL_Vector arg_pos)
  : sprite (arg_sprite), pos (arg_pos), uncrop (false)
{
  //std::cout << "SpriteDrawable::SpriteDrawable()" << std::endl;
}

SpriteDrawable::~SpriteDrawable ()
{
  //std::cout << "SpriteDrawable::~SpriteDrawable()" << std::endl;
}

void
SpriteDrawable::draw (boost::dummy_ptr<View> view)
{
  if (uncrop)
    {
      std::cout << "SpriteDrawable::draw(): uncrop not implemented" << std::endl;
      sprite.get()->draw(view, pos);
    }
  else
    {
      sprite.get()->draw(view, pos);
    }
}

void
SpriteDrawable::update (float delta)
{
  //std::cout << "SpriteDrawable::update" << std::endl;
  sprite.get ()->update (delta);
}

SmobTuple<Sprite>
SpriteDrawable::get_sprite ()
{
  return SmobTuple<Sprite> (sprite);
}

/*
bool
SpriteDrawable::is_a (SCM smob)
{
  //std::cout << "Drawable::is_a" << std::endl;
  return (SCM_CAR (smob) == get_smob_tag ());
}*/

void
SpriteDrawable::register_guile_bindings ()
{
  puts ("SpriteDrawable::register_guile_bindings ()");

  scm_c_define_gsubr("c:sprite-drawable:create", 4, 0, 0,  reinterpret_cast<scm_t_subr>(&SpriteDrawable::scm_sprite_drawable_create));
  scm_c_define_gsubr("c:sprite-drawable:set-position", 4, 0, 0, reinterpret_cast<scm_t_subr>(&SpriteDrawable::scm_sprite_drawable_set_pos));
  scm_c_define_gsubr("c:sprite-drawable:get-position", 1, 0, 0, reinterpret_cast<scm_t_subr>(&SpriteDrawable::scm_sprite_drawable_get_pos));
  scm_c_define_gsubr("c:sprite-drawable:get-sprite", 1, 0, 0, reinterpret_cast<scm_t_subr>(&SpriteDrawable::scm_sprite_drawable_get_sprite));
  scm_c_define_gsubr("c:sprite-drawable:set-uncrop", 2, 0, 0, reinterpret_cast<scm_t_subr>(&SpriteDrawable::scm_sprite_drawable_set_uncrop));
}
/*
SCM
SpriteDrawable::mark (SCM smob)
{
  return smob_cast<SpriteDrawable>(smob)->sprite.get_scm ();
}

size_t
SpriteDrawable::free (SCM smob)
{
  SpriteDrawable* drawable = smob_cast<SpriteDrawable>(smob);
  delete drawable;

  return 0; //sizeof (SpriteDrawable);
}

int
SpriteDrawable::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:SpriteDrawable>", port);
  return 1;
}*/

SCM
SpriteDrawable::scm_sprite_drawable_create (SCM scm_sprite, SCM x_align, SCM y_align, SCM z_align)
{
  SpriteDrawable* drawable;
  drawable = new SpriteDrawable (scm_sprite,
				 CL_Vector (scm_to_double (x_align),
					    scm_to_double (y_align),
					    scm_to_double (z_align)));
  return DrawableSmob::create (drawable);
}

SCM
SpriteDrawable::scm_sprite_drawable_set_uncrop (SCM scm_drawable, SCM scm_uncrop)
{
  smobbox_cast<SpriteDrawable>(scm_drawable)->uncrop = scm_to_bool(scm_uncrop);
  return SCM_UNSPECIFIED;
}

SCM
SpriteDrawable::scm_sprite_drawable_set_pos (SCM drawable, SCM x_pos, SCM y_pos, SCM z_pos)
{
  smobbox_cast<SpriteDrawable>(drawable)->pos = CL_Vector (scm_to_double (x_pos),
                                                           scm_to_double (y_pos),
                                                           scm_to_double (z_pos));
  return SCM_UNSPECIFIED;
}

SCM
SpriteDrawable::scm_sprite_drawable_get_pos (SCM scm_drawable)
{
  CL_Vector& pos = smobbox_cast<SpriteDrawable>(scm_drawable)->pos;
  return scm_list_3(scm_from_double(pos.x), scm_from_double(pos.y), scm_from_double(pos.z));
}

SCM
SpriteDrawable::scm_sprite_drawable_get_sprite (SCM scm_drawable)
{
  return smobbox_cast<SpriteDrawable>(scm_drawable)->sprite.get_scm ();
}

} // namespace Advent

/* EOF */
