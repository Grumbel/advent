//  $Id: coin_layer.hxx,v 1.9 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef COINLAYER_HXX
#define COINLAYER_HXX

#include <guile/gh.h>
#include "layer.hxx"
#include "sprite.hxx"
#include "scm_obj.hxx"

namespace Advent {

class CoinLayer : public Layer
{
private:
  SpritePtr sprite;
  CL_Vector pos;
  bool is_enabled;

  /** Closure that is called once an icon on the coin has been
      clicked: FIXME: CoinIcon should be a seperate class */
  SCMObj click_func;

  /** The current object (AdvObj) on which the CoinLayer acts */
  SCMObj object;

public:
  CoinLayer ();
  virtual ~CoinLayer ();

  void update (float delta);
  void draw (boost::dummy_ptr<View> view);

  bool is_over(int, int);
  void on_button_press(const CL_InputEvent&);
  void on_button_release(const CL_InputEvent&);

  /** Switch the coin visible, obj is the object to which the action
      is applied */
  void enable (SCM obj);
  void disable ();

  void call_action (const CL_Vector& offset);

  void set_click_func (SCM func);
  // static guile stuff
private:
  static long tag;

  static SCM mark (SCM smob);
  static scm_sizet free (SCM smob);
  static int print (SCM image_smob, SCM port, scm_print_state *pstate);

public:
  static long get_smob_tag () { return tag; }
  static void register_guile_bindings ();
  static SCM scm_coinlayer_create ();
  static SCM scm_coinlayer_enable (SCM layer, SCM obj);
  static SCM scm_coinlayer_disable (SCM layer);
  static SCM scm_coinlayer_set_click_func (SCM layer, SCM func);
};

} // namespace Advent

#endif

/* EOF */
