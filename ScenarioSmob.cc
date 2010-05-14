//  $Id: ScenarioSmob.cc,v 1.3 2000/12/30 13:11:56 grumbel Exp $
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

#include <guile/gh.h>
#include "Advent.hh"
#include "GuileAdventObj.hh"
#include "Scenario.hh"
#include "AdventObjSmob.hh"
#include "ScenarioSmob.hh"

long ScenarioSmob::tag;

struct ScenarioSmobStruct
{
  int i;
  Scenario* scenario;
};

void 
ScenarioSmob::init ()
{
  tag = scm_make_smob_type ("ScenarioSmob", // How is this used?
			    sizeof (ScenarioSmobStruct));
  gh_new_procedure4_0("scenario:make-bind", &ScenarioSmob::make_bind);
  gh_new_procedure1_0("scenario:set-current", &ScenarioSmob::set_current_scenario);
}

SCM
ScenarioSmob::make_bind (SCM scenario_name, 
			 SCM background_surface,
			 SCM colmap_surface,
			 SCM objects)
{
  ScenarioSmobStruct* obj = (ScenarioSmobStruct*)scm_must_malloc (sizeof (ScenarioSmobStruct),
								  "ScenarioSmobStruct");
  std::list<AdventObj*> objs; 

  while (objects != SCM_EOL)
    {
      std::cout << "Adding object..." << std::endl;
      AdventObj* advobj = reinterpret_cast<AdventObjP*>(SCM_CDAR (objects))->obj;

      std::cout << "ScenarioSmob: adding object" << std::endl;
      std::cout << "SCenarioSmob: ObjName: " << advobj->get_name () << std::endl;

      objs.push_back (advobj);
      objects = SCM_CDR (objects);
    }

  obj->scenario = new Scenario (SCM_CHARS (scenario_name), 
				SCM_CHARS (background_surface),
				SCM_CHARS (colmap_surface),
				objs);
  obj->i = 42;
  std::cout << "Scenario Pointer: " << obj->scenario
	    << " " << obj->i << std::endl;

  Scenario::scenario_list.push_back (obj->scenario);
  Scenario::current = obj->scenario;
  std::cout << "Returning new smob" << std::endl;
  SCM_RETURN_NEWSMOB (tag, obj);
}

SCM
ScenarioSmob::set_current_scenario (SCM scenario_bind)
{
  //char* str = SCM_CHARS (scenario_name);
  ScenarioSmobStruct* p = reinterpret_cast<ScenarioSmobStruct*>(SCM_CDR(scenario_bind));
  std::cout << "+++ Scenario Pointer: " << p->scenario
	    << " " << p->i << std::endl;
  Scenario::set_current_scenario (p->scenario);
  return SCM_UNSPECIFIED;
}

/* EOF */
