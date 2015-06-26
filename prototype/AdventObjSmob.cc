//  $Id: AdventObjSmob.cc,v 1.16 2001/07/16 17:44:10 grumbel Exp $
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

#include <libguile.h>
#include <guile/gh.h>
#include <string.h>

#include "helper.hh"
#include "Advent.hh"
#include "AdventObj.hh"
#include "GuileAdventObj.hh"
#include "AdventObjSmob.hh"
#include "Scenario.hh"

long AdventObjSmob::tag;

void AdventObjSmob::init ()
{
  tag = scm_make_smob_type ("AdventObj", sizeof (AdventObjP));
  scm_set_smob_mark (tag,  &AdventObjSmob::mark);
  scm_set_smob_free (tag,  &AdventObjSmob::free);
  scm_set_smob_print (tag, &AdventObjSmob::print);

  gh_new_procedure5_0("advent:makeobj-surface", AdventObjSmob::makeobj_surface);
  gh_new_procedure5_0 ("advent:makeobj-empty", AdventObjSmob::makeobj_empty);
  gh_new_procedure5_0 ("c:adv:makeobj-empty", AdventObjSmob::makeobj_empty);
  gh_new_procedure2_0("advent:set-surface", AdventObjSmob::set_surface);
  gh_new_procedure4_0("c:advent:set-surface-pos", AdventObjSmob::set_surface_pos);
  gh_new_procedure2_0("advent:set-inventory-surface", AdventObjSmob::set_inventory_surface);
  gh_new_procedure1_0("c:adv:mark-empty", AdventObjSmob::mark_empty);
}

SCM
AdventObjSmob::mark (SCM smob)
{
  //std::cout << ">>Marking AdventObjSmob<<" << std::endl;
  return SCM_UNSPECIFIED;
}

scm_sizet
AdventObjSmob::free (SCM smob)
{
  GuileAdventObj* obj = scm2GuileAdventObj (smob);
  std::cout << ">>Freeing AdventObjSmob: " << obj->get_name () << "<<"<< std::endl;


  return 0;
}

int
AdventObjSmob::print (SCM smob, SCM port, scm_print_state *pstate)
{
  std::cout << ">>Printing AdventObjSmob<<" << std::endl;

  AdventObjP* obj = reinterpret_cast<AdventObjP*>(SCM_CDR (smob));
  if (obj)
    {
      //std::cout << "STR: " << obj->obj->get_name () << std::endl;
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
AdventObjSmob::makeobj_empty (SCM arg_name, SCM arg_x_pos, SCM arg_y_pos,
			      SCM arg_width, SCM arg_height)
{
  // FIXMME: Error checking is missing
  //AdventObjP* obj = (AdventObjP*)scm_must_malloc (sizeof (AdventObjP), "AdventObjP");
  AdventObjP* obj = new AdventObjP ();

  obj->obj = new GuileAdventObj (arg_name,
				 CL_Vector (SCM_INUM(arg_x_pos), SCM_INUM(arg_y_pos)),
				 SCM_INUM (arg_width), SCM_INUM (arg_height));
  SCM_RETURN_NEWSMOB (tag, obj);
}

SCM
AdventObjSmob::scm_makeobj_empty (SCM obj, SCM arg_x_pos, SCM arg_y_pos,
				  SCM arg_width, SCM arg_height)
{
  AdventObjP* advobj = new AdventObjP ();
  advobj->obj = new GuileAdventObj (obj,
				    CL_Vector (SCM_INUM(arg_x_pos), SCM_INUM(arg_y_pos)),
				    SCM_INUM (arg_width), SCM_INUM (arg_height));
  SCM_RETURN_NEWSMOB (tag, advobj);
}

SCM
AdventObjSmob::makeobj_surface (SCM arg_name, SCM arg_surface,
				SCM arg_x_pos, SCM arg_y_pos, SCM arg_z_pos)
{
  // FIXMME: Error checking is missing
  //AdventObjP* obj = (AdventObjP*)scm_must_malloc (sizeof (AdventObjP), "AdventObjP");

  AdventObjP* obj = new AdventObjP ();

  if (strcmp(SCM_CHARS (arg_surface), "") != 0)
    {
      obj->obj = new GuileAdventObj (arg_name,
				     SCM_CHARS(arg_surface),
				     CL_Vector (SCM_INUM(arg_x_pos), SCM_INUM(arg_y_pos),
						SCM_INUM(arg_z_pos)));
    }
  else
    {
      assert (false);
    }

  SCM_RETURN_NEWSMOB (tag, obj);
}

SCM
AdventObjSmob::set_surface_pos (SCM smob, SCM x_pos, SCM y_pos, SCM z_pos)
{
  // GuileAdventObj* obj = scm2GuileAdventObj(smob);

  AdventObjP* advobj = reinterpret_cast<AdventObjP*>(SCM_CDR (smob));

  std::cout << "POINTER: " << advobj->obj << std::endl;

  GuileAdventObj* obj = dynamic_cast<GuileAdventObj*>(advobj->obj);


  std::cout << "SET_SURFACE_POS" << std::endl;

  if (obj)
    {
      obj->set_surface_pos (SCM_INUM(x_pos), SCM_INUM(y_pos), SCM_INUM(z_pos));
    }
  else
    {
      std::cout << "KAPUTT@2" << std::endl;
    }
  return SCM_UNSPECIFIED;
}

SCM
AdventObjSmob::set_surface (SCM smob, SCM name)
{
  //std::cout << "Setting surface" << std::endl;

  //  AdventObjP* advobj = reinterpret_cast<AdventObjP*>(SCM_CDR (smob));
  //GuileAdventObj* obj = dynamic_cast<GuileAdventObj*>(advobj->obj);
  GuileAdventObj* obj = scm2GuileAdventObj (smob);

  if (obj)
    {
      char* str = SCM_CHARS(name);
      puts ("set_surface...");
      puts (str);
      //std::cout << "Pointer: " << obj << " " << obj->obj << std::endl;
      obj->set_surface (str);
    }
  else
    {
      std::cout << "KAPUTT" << std::endl;
    }
  return SCM_UNSPECIFIED;
}

SCM
AdventObjSmob::set_inventory_surface (SCM smob, SCM name)
{
  std::cout << "AdventObjSmob::set_inventory_surface" << std::endl;

  std::cout << "name: " << SCM_CHARS (name) << std::endl;
  //std::cout << "Pointer: " << SCM_CDR(smob) << std::endl;
  GuileAdventObj* advobj = scm2GuileAdventObj (smob);
  std::cout << "Pointer: " << advobj << std::endl;
  advobj->set_inventory_surface (SCM_CHARS (name));
  return SCM_UNSPECIFIED;
}

SCM
AdventObjSmob::mark_empty (SCM smob)
{
  GuileAdventObj* obj = scm2GuileAdventObj (smob);

  obj->empty_object = true;

  return SCM_UNSPECIFIED;
}

/* EOF */
