//  $Id: layer_screen.hxx,v 1.15 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef LAYERSCREEN_HXX
#define LAYERSCREEN_HXX

#include <list>
#include <guile/gh.h>
#include "boost/dummy_ptr.hpp"
#include "boost/smart_ptr.hpp"

#include "scm_obj.hxx"
#include "smob_tuple.hxx"
#include "layer.hxx"
#include "screen.hxx"

namespace Advent {

class View;

/** A screen setup which is build out ouf different layers. Most stuff
    should be done this way. */
class LayerScreen : public Screen
{
private:
  typedef std::list<SmobTuple<Layer> > LayerList;
  LayerList layers;

  int lock_count;

  /** Refcounter for disabling the input handling */
  int input_enabled;

  /** FIXME: should use real hooks */
  SCMObj input_enabled_hook;
  SCMObj input_disabled_hook;
public:
  LayerScreen ();
  virtual ~LayerScreen ();

  void update (float delta);
  void draw (boost::dummy_ptr<View> view);

  bool is_over (int x_pos, int y_pos);

  void on_button_press (const CL_InputEvent&);
  void on_button_release (const CL_InputEvent&);

  void pop ();
  void remove (SCM);
  void push (SCM);

  // static guile bindings
public:
  static void register_guile_bindings ();

  static SCM layerscreen_enable_input (SCM);
  static SCM layerscreen_disable_input (SCM);

  static SCM layerscreen_set_input_enabled_hook (SCM, SCM);
  static SCM layerscreen_set_input_disabled_hook (SCM, SCM);

  static SCM layerscreen_create ();
  static SCM layerscreen_push (SCM, SCM);
  static SCM layerscreen_remove (SCM, SCM);
  static SCM layerscreen_pop (SCM);
};

} // namespace Advent

#endif

/* EOF */
