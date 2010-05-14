//  $Id$
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

#include <libguile.h>
#include <guile/gh.h>
#include <string.h>
#include "Advent.hh"
#include "AdventObj.hh"
#include "GuileAdventObj.hh"
#include "AdventObjSmob.hh"
#include "Scenario.hh"

long AdventObjSmob::tag;

struct AdventObjP
{
  int i;
  GuileAdventObj* obj;
};

void AdventObjSmob::init ()
{
  tag = scm_make_smob_type ("AdventObj", sizeof (AdventObjP));
  scm_set_smob_mark (tag,  &AdventObjSmob::mark_obj);
  scm_set_smob_free (tag,  &AdventObjSmob::free_obj);
  scm_set_smob_print (tag, &AdventObjSmob::print_obj);

  gh_new_procedure5_0("advent:makeobj", AdventObjSmob::make_obj);
  gh_new_procedure2_0("advent:set-surface", AdventObjSmob::set_surface);
}

SCM       
AdventObjSmob::mark_obj (SCM smob)
{
  return SCM_UNSPECIFIED;
}

scm_sizet 
AdventObjSmob::free_obj (SCM smob)
{
  std::cout << "Freeing object..." << std::endl;

  //AdventObjP* obj = reinterpret_cast<AdventObjP*>(SCM_CDR (smob));

  // delete obj;

  // do nothing
  return 0;
}

int       
AdventObjSmob::print_obj (SCM smob, SCM port, scm_print_state *pstate)
{
  std::cout << "Printing object..." << std::endl;

  AdventObjP* obj = reinterpret_cast<AdventObjP*>(SCM_CDR (smob));
  if (obj)
    {
      std::cout << "STR: " << obj->obj->get_name () << std::endl;
      scm_puts ("#<AdventObj ", port);
      scm_puts (">", port);
    }
  else
    {
      scm_puts ("#<AdventObj -- unknown -->", port);
    }
  /* non-zero means success */
  return 1;  
}

SCM
AdventObjSmob::make_obj (SCM name, SCM surface, 
			 SCM x_pos, SCM y_pos, SCM z_pos)
{
  AdventObjP* obj = (AdventObjP*)scm_must_malloc (sizeof (AdventObjP), "AdventObjP");

  obj->obj = new GuileAdventObj (0, SCM_CHARS(name), 1,
				 CL_Surface (SCM_CHARS(surface), app.get_resource ()),
				 CL_Vector (SCM_INUM(x_pos), SCM_INUM(y_pos),
					    SCM_INUM(z_pos)));

  obj->i = 42;
  std::cout << "Makeing object: " << obj << " "<< obj->obj << std::endl;
 
  current_scenario->add (obj->obj);
  SCM_RETURN_NEWSMOB (tag, obj);
}

SCM 
AdventObjSmob::set_surface (SCM smob, SCM name)
{
  std::cout << "Setting surface" << std::endl;
  
  AdventObjP* advobj = reinterpret_cast<AdventObjP*>(SCM_CDR (smob));
  
  if (advobj)
    {
      char* str = SCM_CHARS(name);
      puts ("set_surface...");
      puts (str);
      std::cout << "int: " << advobj->i << std::endl;
      std::cout << "Pointer: " << advobj << " " << advobj->obj << std::endl;
      advobj->obj->set_surface (str);
    }
  else
    {
      std::cout << "KAPUTT" << std::endl;
    }
  return SCM_UNSPECIFIED;
}

/* EOF */
