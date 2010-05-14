//  $Id: empty_adv_obj.hxx,v 1.4 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef EMPTYADVOBJ_HXX
#define EMPTYADVOBJ_HXX

#include <guile/gh.h>
#include "collideable.hxx"
#include "adv_obj.hxx"
#include "smob_tuple.hxx"

namespace Advent {

/** An not-drawable advobj, it consist only of a collideable */
class EmptyAdvObj : public AdvObj
{
private:
  SmobTuple<Collideable> collideable;
  
public:
  EmptyAdvObj (SCM bind, SCM collideable);
  
  void  update (float delta) {}
  void  draw (boost::dummy_ptr<View> view) {}
  
  /** FIXME: This function is useless here, but must be here cause
      FIXME: AdvObj is a Drawable */
  float get_z_pos () { return 0.0f; }
  
  bool is_over (int x_pos, int y_pos);

  // static guile stuff
  // FIXME: This code is duplicated over and over again, should
  // FIXME: probally become a template<> or something.
public:
  static void register_guile_bindings ();
  
  static SCM scm_empty_advobj_create (SCM bind, SCM scm_collideable);
};

} // namespace Advent

#endif

/* EOF */
