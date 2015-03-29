//  $Id: inventory.hxx,v 1.10 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef INVENTORY_HXX
#define INVENTORY_HXX

#include "boost/dummy_ptr.hpp"
#include "boost/smart_ptr.hpp"
#include "layer.hxx"
#include "adv_obj.hxx"

namespace Advent {

/** FIXME: should probally be just an interface
    The graphical and input handling version of a scm_interface
*/
class Inventory : public Layer
{
private:
  /** FIXME: should contain a tuple of AdvObj and position in the
      inventory, or should be stored in a Field instead */
  std::list<SmobTuple<AdvObj> > objects;
  bool visible;

public:
  Inventory ();
  virtual ~Inventory ();

  void update (float delta);
  void draw (boost::dummy_ptr<View> view);

  void add (SCM obj);
  void remove (SCM obj);

  bool is_over (int x_pos, int y_pos);
  void on_button_press (const CL_InputEvent&);
  void on_button_release (const CL_InputEvent&);

  void set_visible (bool v);

  // Static functions for the guile bindings
public:
  static void register_guile_bindings ();

  static SCM scm_inventory_create ();
  static SCM scm_inventory_add_advobj (SCM inventory, SCM obj);
  static SCM scm_inventory_remove_advobj (SCM inventory, SCM obj);
  static SCM scm_inventory_set_visible (SCM inventory, SCM obj);
};

} // namespace Advent

#endif

/* EOF */
