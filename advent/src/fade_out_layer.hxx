//  $Id: fade_out_layer.hxx,v 1.6 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef FADEOUTLAYER_HH
#define FADEOUTLAYER_HH

#include <guile/gh.h>

#include "scm_obj.hxx"
#include "layer.hxx"

namespace Advent {

class FadeOutLayer : public Layer
{
private:
  /** Called once the screen is fadeout */
  SCMObj lambda;

  /** Called once the screen is faded back in */
  SCMObj hook;

  float progress;
  int running;
  bool is_blackout;

public:
  FadeOutLayer ();
  virtual ~FadeOutLayer ();

  void update (float delta);
  void draw (boost::dummy_ptr<View>);

  // FIXME: This should be moved into a Layer Subclass,
  // FIXME: NonInteractiveLayer or something like that
  bool is_over (int, int) { return false; }
  void on_button_press (const CL_InputEvent&) {}
  void on_button_release (const CL_InputEvent&) {}

  static void register_guile_bindings ();
  static SCM  scm_fadeout_layer_create   ();
  static SCM  scm_fadeout_layer_blackout (SCM scm_layer);
  static SCM  scm_fadeout_layer_fade     (SCM scm_layer, SCM l);
  static SCM  scm_fadeout_layer_fade_in  (SCM scm_layer);
};

} // namespace Advent

#endif

/* EOF */
