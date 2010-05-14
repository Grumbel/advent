//  $Id: button_layer.hxx,v 1.14 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef BUTTONLAYER_HXX
#define BUTTONLAYER_HXX

#include <guile/gh.h>
#include <ClanLib/display.h>
#include "boost/smart_ptr.hpp"
#include "boost/dummy_ptr.hpp"
#include "smob_tuple.hxx"
#include "layer.hxx"
#include "scm_obj.hxx"

namespace Advent {

class View;
class Sprite;

/** A layer which represens a simple button (like the one used for the
    inventory) 

    FIXME: mouse_over and button_press sprites should be possible */
class ButtonLayer : public Layer
{
private:
  SmobTuple<Sprite> sprite;
  SmobTuple<Sprite> pressed_sprite;
  SmobTuple<Sprite> mouse_over_sprite;

  int x_pos, y_pos;
  SCMObj scm_on_press;
  SCMObj scm_on_release;
public:
  ButtonLayer (SCM scm_sprite, SCM, SCM, int, int);
  virtual ~ButtonLayer ();

  void update (float delta);
  void draw (boost::dummy_ptr<View> view);
  
  bool is_over (int x_pos, int y_pos);
  void on_button_press (const CL_InputEvent&);
  void on_button_release (const CL_InputEvent&);

public:
  // static guile stuff
  static void register_guile_bindings ();

  static SCM scm_buttonlayer_create (SCM filename, SCM, SCM, SCM x_pos, SCM y_pos);
  static SCM scm_buttonlayer_set_press_callback (SCM button, SCM func);
  static SCM scm_buttonlayer_set_release_callback (SCM button, SCM func);
};

} // namespace Advent

#endif

/* EOF */
