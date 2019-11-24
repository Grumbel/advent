//  $Id: inventory.cxx,v 1.12 2004/01/14 02:28:24 grumbel Exp $
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

#include "scm_converter.hxx"
#include "inventory.hxx"

namespace Advent {

Inventory::Inventory ()
  : visible (true)
{
}

Inventory::~Inventory ()
{
}

void
Inventory::update (float delta)
{
  if (visible)
    {
    }
}

void
Inventory::draw (boost::dummy_ptr<View> view)
{
  if (visible)
    {
      CL_Display::fill_rect (CL_Rect(40, 40, 600, 440),
                             CL_Color(0, 0, 0, 127));
      int x = 40;
      for (std::list<SmobTuple<AdvObj> >::iterator i = objects.begin ();
	   i != objects.end (); ++i)
	{
	  SmobTuple<Sprite> sprite = i->get ()->get_inventory_sprite ();
	  if (sprite.get ())
	    {
	      sprite.get ()->draw (view, CL_Vector (x, 60));
	    }
	  else
	    {
	      std::cout << "Inventory: No inventory sprite available" << std::endl;
	    }
	  x += 40;
	}
    }
}

void
Inventory::add (SCM obj)
{
  objects.push_back (SmobTuple<AdvObj>(obj));
}

void
Inventory::remove (SCM obj)
{
  // FIXME: slow
  objects.remove (SmobTuple<AdvObj>(obj));
}

void
Inventory::set_visible (bool v)
{
  visible = v;
}

bool
Inventory::is_over (int x_pos, int y_pos)
{
  if (visible)
    {
      return true;
    }
  else
    {
      return false;
    }
}

void
Inventory::on_button_press (const CL_InputEvent&)
{

}

void
Inventory::on_button_release (const CL_InputEvent&)
{

}

void
Inventory::register_guile_bindings ()
{
  puts ("Inventory::register_guile_bindings ()");

  scm_c_define_gsubr("c:inventory:create", 0, 0, 0, reinterpret_cast<scm_t_subr>(&Inventory::scm_inventory_create));
  scm_c_define_gsubr("c:inventory:add-advobj", 2, 0, 0, reinterpret_cast<scm_t_subr>(&Inventory::scm_inventory_add_advobj));
  scm_c_define_gsubr("c:inventory:remove-advobj", 2, 0, 0, reinterpret_cast<scm_t_subr>(&Inventory::scm_inventory_remove_advobj));
  scm_c_define_gsubr("c:inventory:set-visible", 2, 0, 0, reinterpret_cast<scm_t_subr>(&Inventory::scm_inventory_set_visible));
}

/*
SCM
Inventory::mark (SCM smob)
{
  // FIXME: Unimplemented, could crash
  return SCM_BOOL_F;
}

size_t
Inventory::free (SCM smob)
{
  delete smob_cast<Inventory> (smob);
  return 0; // sizeof (Inventory);
}

int
Inventory::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:Inventory>", port);
  return 1;
}

bool
Inventory::is_a (SCM smob)
{
  return (SCM_CAR (smob) == get_smob_tag ());
}
*/
SCM
Inventory::scm_inventory_create ()
{
  return LayerSmob::create (new Inventory ());
}

SCM
Inventory::scm_inventory_add_advobj (SCM scm_inventory, SCM scm_obj)
{
  Inventory* inventory = smobbox_cast<Inventory>(scm_inventory);
  inventory->add (scm_obj);
  return SCM_UNSPECIFIED;
}

SCM
Inventory::scm_inventory_remove_advobj (SCM scm_inventory, SCM scm_obj)
{
  Inventory* inventory = smobbox_cast<Inventory>(scm_inventory);
  inventory->remove (scm_obj);

  return SCM_UNSPECIFIED;
}

SCM
Inventory::scm_inventory_set_visible (SCM scm_inventory, SCM obj)
{
  smobbox_cast<Inventory>(scm_inventory)->set_visible (scm_to_bool (obj));
  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
