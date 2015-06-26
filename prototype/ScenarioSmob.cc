//  $Id: ScenarioSmob.cc,v 1.16 2001/07/15 21:00:31 grumbel Exp $
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

#include <guile/gh.h>
#include <assert.h>
#include "helper.hh"
#include "Advent.hh"
#include "GuileAdventObj.hh"
#include "Scenario.hh"
#include "AdventObjSmob.hh"
#include "ScenarioSmob.hh"

long ScenarioSmob::tag;

void
ScenarioSmob::init ()
{
  tag = scm_make_smob_type ("ScenarioSmob", // How is this used?
			    sizeof (ScenarioSmobStruct));

  scm_set_smob_mark (tag, ScenarioSmob::mark);
  scm_set_smob_free (tag, ScenarioSmob::free);
  scm_set_smob_print (tag, ScenarioSmob::print);

  gh_new_procedure5_0("c:scenario:make-bind", &ScenarioSmob::make_bind);
  //gh_new_procedure1_0("c:scenario:set-current", &ScenarioSmob::set_current_scenario);
  gh_new_procedure1_0("c:scenario:remove", &ScenarioSmob::remove);
  gh_new_procedure1_0("c:scenario:add", &ScenarioSmob::add);
}

SCM
ScenarioSmob::mark (SCM smob)
{
  //std::cout << ">>ScenarioSmob: Marking...<<" << std::endl;
  //  std::cout << "Marking: " << obj->get_name () << std::endl;

  return SCM_UNSPECIFIED;
}

scm_sizet
ScenarioSmob::free (SCM smob)
{
  //std::cout << ">>ScenarioSmob: Freeing...<<" << std::endl;
  return 0;
}

int
ScenarioSmob::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  //std::cout << ">>ScenarioSmob: Printing...<<" << std::endl;
  return 1;
}

SCM
ScenarioSmob::make_bind (SCM scenario_name,
			 SCM background_surface,
			 SCM colmap_surface,
			 SCM objects,
			 SCM with_guy)
{
  ScenarioSmobStruct* obj = (ScenarioSmobStruct*)scm_must_malloc (sizeof (ScenarioSmobStruct),
								  "ScenarioSmobStruct");
  std::list<AdventObj*> objs;

  while (objects != SCM_EOL)
    {
      //std::cout << "Adding object..." << std::endl;
      AdventObj* advobj = reinterpret_cast<AdventObjP*>(SCM_CDAR (objects))->obj;

      //std::cout << "ScenarioSmob: adding object" << std::endl;
      //std::cout << "SCenarioSmob: ObjName: " << advobj->get_name () << std::endl;

      objs.push_back (advobj);
      objects = SCM_CDR (objects);
    }

  assert(SCM_STRINGP (background_surface));

  std::string colmap;
  if (!SCM_FALSEP (colmap_surface))
    colmap = SCM_CHARS (colmap_surface);

  obj->scenario = new Scenario (scenario_name,
				SCM_CHARS (background_surface),
				colmap,
				objs,
				!SCM_FALSEP (with_guy));
  obj->i = 42;
  //std::cout << "Scenario Pointer: " << obj->scenario
  //    << " " << obj->i << std::endl;

  Scenario::scenario_list.push_back (obj->scenario);
  //Scenario::current = obj->scenario;
  //  std::cout << "Returning new smob" << std::endl;
  SCM_RETURN_NEWSMOB (tag, obj);
}
/*
SCM
ScenarioSmob::set_current_scenario (SCM scenario_bind)
{
  //char* str = SCM_CHARS (scenario_name);
  ScenarioSmobStruct* p = reinterpret_cast<ScenarioSmobStruct*>(SCM_CDR(scenario_bind));
  //std::cout << "+++ Scenario Pointer: " << p->scenario
  //	    << " " << p->i << std::endl;
  Scenario::set_current_scenario (p->scenario);
  Guy::get_current ()->scenario = p->scenario;
  return SCM_UNSPECIFIED;
}
*/
SCM
ScenarioSmob::remove (SCM obj)
{
  Scenario::get_current ()->remove (scm2AdventObj (obj));
  return SCM_UNSPECIFIED;
}

SCM
ScenarioSmob::add (SCM obj)
{
  Scenario::get_current ()->add (scm2AdventObj (obj));
  return SCM_UNSPECIFIED;
}

/* EOF */
