//  $Id: sprite.hxx,v 1.14 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef SPRITE_HXX
#define SPRITE_HXX

#include <ClanLib/core.h>
#include "view.hxx"
#include "boost/dummy_ptr.hpp"
#include "boost/smart_ptr.hpp"

#include "sprite_smob.hxx"

namespace Advent {

/** -- Interface --
    Wrapper around CL_Surface for the moment */
class Sprite
{
private:

public:
  virtual void update (float delta) =0;
  virtual void draw (boost::dummy_ptr<View> view, const CL_Vector& pos) =0;

  // FIXME: Am I poluting the interface here?
  virtual void draw (boost::dummy_ptr<View> view, const CL_Vector& pos, float zoom) {
    draw (view, pos);
  }

  virtual int get_width () const =0;
  virtual int get_height () const =0;

  /** FIXME: Do we need this here? I guess not since the aligment can be
      FIXME: handled with get_width () and get_height() */
  virtual void set_align (int, int) {}
  virtual void set_align_center_bottom () {}
  virtual void set_align_center () {}

  virtual bool  removable () { return false; }

  static SpriteSmob* cast (SCM);

  // static guile bindings
public:
  static void register_guile_bindings ();
  static SCM scm_sprite_get_width (SCM scm_sprite);
  static SCM scm_sprite_get_height (SCM scm_sprite);
};

typedef Sprite* SpritePtr;

} // namespace Advent

#endif

/* EOF */
