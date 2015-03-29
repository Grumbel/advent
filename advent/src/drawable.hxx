//  $Id: drawable.hxx,v 1.7 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef DRAWABLE_HXX
#define DRAWABLE_HXX

#include <guile/gh.h>

#include "boost/dummy_ptr.hpp"
#include "boost/smart_ptr.hpp"

#include "drawable_smob.hxx"

namespace Advent {

class View;

/** A Drawable is a high level version of a surface, it gets
    putted/added to a DrawableDisplay and draws on request to a View.
    Subclasses can be used for simple Surfaces, animated Surfaces or
    more complex effects (fade in/out).
 */
class Drawable
{
private:
  bool removable_;
public:
  Drawable () : removable_ (false) {}

  static bool is_a (SCM);

  virtual void  update (float delta) =0;
  virtual void  draw (boost::dummy_ptr<View> view) =0;

  /** Return the z_pos of the drawable, it is used to sort a list of
      drawables */
  virtual float get_z_pos () =0;
  virtual bool is_removable () { return removable() || removable_; }

  static DrawableSmob* cast (SCM);

  static void register_guile_bindings ();
  static SCM scm_drawable_remove (SCM scm_drawable);
protected:
  virtual bool removable () { return false; }
};

typedef boost::shared_ptr<Drawable> DrawablePtr;

} // namespace Advent

#endif

/* EOF */
