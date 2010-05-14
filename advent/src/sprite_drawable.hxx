//  $Id: sprite_drawable.hxx,v 1.13 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef SPRITEDRAWABLE_HXX
#define SPRITEDRAWABLE_HXX

#include <guile/gh.h>
#include "drawable.hxx"
#include "surface_sprite.hxx"
#include "smob_tuple.hxx"
#include "scm_obj.hxx"
#include "view.hxx"

namespace Advent {

/** A drawable that be used for simple sprites */
class SpriteDrawable : public Drawable
{
private:
  SmobTuple<Sprite> sprite;
  CL_Vector pos;
  bool uncrop;
  
public:
  SpriteDrawable (SCM arg_sprite, CL_Vector arg_pos);
  virtual ~SpriteDrawable ();

  void  update (float delta);
  void  draw (boost::dummy_ptr<View> view);
  float get_z_pos () { return pos.z; }
  bool  removable () { return sprite.get ()->removable (); }

  CL_Vector get_pos () { return pos; }
  SmobTuple<Sprite> get_sprite ();
  
  // static guile bindings
private:
public:
  static void register_guile_bindings ();

  static SCM scm_sprite_drawable_create (SCM filename, SCM x_pos, SCM y_pos, SCM z_pos);
  static SCM scm_sprite_drawable_set_pos (SCM filename, SCM x_pos, SCM y_pos, SCM z_pos);
  static SCM scm_sprite_drawable_set_uncrop (SCM scm_drawable, SCM scm_uncrop);
  static SCM scm_sprite_drawable_get_sprite (SCM scm_drawable);
  static SCM scm_sprite_drawable_get_pos (SCM scm_drawable);
};

} // namespace Advent

#endif

/* EOF */
