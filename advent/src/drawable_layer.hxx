//  $Id: drawable_layer.hxx,v 1.9 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef DRAWABLELAYER_HXX
#define DRAWABLELAYER_HXX

#include <guile/gh.h>
#include "smob_tuple.hxx"
#include "drawable.hxx"
#include "layer.hxx"

namespace Advent {

/** Wrapper to get a drawable into a layer */
class DrawableLayer : public Layer
{
private:
  SmobTuple<Drawable> drawable;
  
public:
  DrawableLayer (SCM d);
  virtual ~DrawableLayer ();
 
  void update (float delta) { drawable.get ()->update (delta); }
  void draw (boost::dummy_ptr<View> view) { drawable.get ()->draw (view); }

  bool is_over (int x_pos, int y_pos) { return false; }
  void on_button_press (const CL_InputEvent&) {}
  void on_button_release (const CL_InputEvent&) {}

  // static guile bindings
public:
  static void register_guile_bindings ();

  static SCM scm_drawable_layer_create (SCM scm_drawable);
  static SCM scm_drawable_layer_get_drawable (SCM scm_drawable);
};

} // namespace Advent

#endif

/* EOF */
