//  $Id: adv_obj.hxx,v 1.11 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef ADVOBJ_HXX
#define ADVOBJ_HXX

#include <list>
#include "boost/dummy_ptr.hpp"
#include "boost/smart_ptr.hpp"

#include <guile/gh.h>
#include "smob_tuple.hxx"
#include "scm_obj.hxx"
#include "sprite.hxx"
#include "drawable.hxx"

namespace Advent {

/** An AdvObj 'is a' a Drawable (a visible gfx object) and some kind
    of collision detection */
class AdvObj : public Advent::Drawable
{
private:
  /** 'Pointer' to the guile object */
  SCMObj obj;

  /** The sprite that is shown in the inventory when the object is
      inside the inventory */
  SmobTuple<Sprite> inventory_sprite;

public:
  /** Binds an C++ object to an object in the guile world */
  AdvObj (SCM new_obj) : obj (new_obj) {
  }

  virtual ~AdvObj () {
  }

  /** FIXME: bad function name */
  virtual bool is_over (int x_pos, int y_pos) =0;

  void on_click ();

  SCM get_scm () { return obj.get_scm (); }
  SmobTuple<Sprite> get_inventory_sprite () { return inventory_sprite; }


  // static guile stuff
  static bool is_a (SCM scm);
  static void register_guile_bindings ();
  static SCM scm_advobj_set_inventory_sprite (SCM, SCM);
};

typedef boost::shared_ptr<AdvObj> AdvObjPtr;
typedef std::list<AdvObjPtr> AdvObjList;

} // namespace Advent

#endif

/* EOF */
