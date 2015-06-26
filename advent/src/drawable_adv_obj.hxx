//  $Id: drawable_adv_obj.hxx,v 1.7 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef DRAWABLEADVOBJ_HXX
#define DRAWABLEADVOBJ_HXX

#include "boost/dummy_ptr.hpp"
#include "adv_obj.hxx"
#include "drawable.hxx"
#include "smob_tuple.hxx"
#include "collideable.hxx"

namespace Advent {

class DrawableAdvObj : public AdvObj
{
private:
  SmobTuple<Drawable>    drawable;
  SmobTuple<Collideable> collideable;

public:
  DrawableAdvObj (SCM bind, SCM scm_drawable, SCM scm_collideable);

  void  update (float delta);
  void  draw (boost::dummy_ptr<View> view);
  bool is_over (int x_pos, int y_pos);

  /** Return the z_pos of the drawable, it is used to sort a list of
      drawables */
  float get_z_pos ();

  // static guile stuff
public:
  static void register_guile_bindings ();

  static SCM drawable_advobj_create (SCM bind, SCM scm_drawable, SCM scm_collideable);
  static SCM drawable_advobj_set_drawable (SCM obj, SCM scm_drawable);
};

} // namespace Advent

#endif

/* EOF */
