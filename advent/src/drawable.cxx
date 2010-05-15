//  $Id: drawable.cxx,v 1.6 2004/01/14 02:28:24 grumbel Exp $
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

#include "sprite_drawable.hxx"
#include "person.hxx"
#include "drawable_smob.hxx"
#include "drawable.hxx"

namespace Advent {

DrawableSmob*
Drawable::cast (SCM smob)
{
  if (SCM_NIMP (smob))
    {
      if (DrawableSmob::get_smob_tag () == long(SCM_CAR(smob)))
	{
	  return reinterpret_cast<DrawableSmob*>(SCM_CDR (smob));
	}
      else
	{
	  //FIXME:
	  std::cout << "Error: Drawable::cast (SCM smob): tag = " << SCM_CAR (smob) << std::endl;
	  return 0;
	}
    }
  else
    {
      std::cout << "Error: Drawable::cast (): not a smob" << std::endl;
      gh_display (smob);gh_newline ();
      return 0;
    }
}

void 
Drawable::register_guile_bindings ()
{
  gh_new_procedure1_0("c:drawable:remove", &Drawable::scm_drawable_remove);
}

SCM 
Drawable::scm_drawable_remove (SCM scm_drawable)
{
  //std::cout << "Drawable::scm_drawable_remove" << std::endl;
  checked_smob_cast<DrawableSmob>(scm_drawable)->get_child ()->removable_ = true;
  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
