//  $Id: adv_obj.cxx,v 1.9 2004/01/14 02:28:24 grumbel Exp $
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

#include "empty_adv_obj.hxx"
#include "drawable_adv_obj.hxx"
//nclude "EmptyRegionadv_obj.hxx"
#include "adv_obj.hxx"

namespace Advent {

void 
AdvObj::register_guile_bindings ()
{
  gh_new_procedure2_0 ("c:advobj:set-inventory-sprite", 
		       &AdvObj::scm_advobj_set_inventory_sprite);
}

SCM
AdvObj::scm_advobj_set_inventory_sprite (SCM scm_obj, SCM scm_sprite)
{
  smobbox_cast<AdvObj>(scm_obj)->inventory_sprite.set_scm (scm_sprite);
  return SCM_UNSPECIFIED;
}

void
AdvObj::on_click ()
{
  puts ("AdvObj::on_click ()");
  SCM func = gh_lookup("adv:on-click");
  if (func != SCM_BOOL_F)
    {
      gh_call1 (func, get_scm());
    }
  else
    {
      puts ("AdvObj: No adv:on-click-handler set");
    }
}

} // namespace Advent

/* EOF */
