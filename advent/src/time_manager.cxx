//  $Id: time_manager.cxx,v 1.9 2004/01/14 02:28:24 grumbel Exp $
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

#include <ClanLib/core.h>
#include "scm_converter.hxx"
#include "scm_obj.hxx"
#include "time_manager.hxx"

namespace Advent {

struct TimedLambda
{
  unsigned int trigger_time;
  SCMObj lambda;

  TimedLambda (int arg_triger_time, SCM arg_lambda)
    : trigger_time (arg_triger_time),
      lambda (arg_lambda)
  {
    //std::cout << "TimedLambda ()" << std::endl;
  }

  TimedLambda (const TimedLambda& l)
    : trigger_time (l.trigger_time),
      lambda (l.lambda)
  {
    //std::cout << "TimedLambda (const TimedLambda&)" << std::endl;
  }

  ~TimedLambda ()
  {
    //std::cout << "~TimedLambda" << std::endl;
  }

  TimedLambda& operator=(const TimedLambda& l)
  {
    //std::cout << "TimedLambda::operator=()" << std::endl;
    trigger_time = l.trigger_time;
    lambda = l.lambda;
    return *this;
  }
};

struct TimeManager_to_old
{
  unsigned int current_time;

  TimeManager_to_old (unsigned int arg_current_time) {
    current_time = arg_current_time;
  }

  bool operator () (boost::shared_ptr<TimedLambda> & lambda) {
    return (lambda->trigger_time <= current_time);
  }
};

TimeManager::TimeManager ()
{
}

TimeManager::~TimeManager ()
{
}

void
TimeManager::add (int activation_time, SCM lambda)
{
  lambdas.push_back(boost::shared_ptr<TimedLambda>(new TimedLambda (CL_System::get_time () + activation_time,
								    lambda)));
}

void
TimeManager::update (float delta)
{
  unsigned int current_time = CL_System::get_time ();

  TimedList tmp_lambdas (lambdas);

  for (TimedList::iterator i = tmp_lambdas.begin ();
       i != tmp_lambdas.end (); ++i)
    {
      if ((*i)->trigger_time <= current_time)
	{
	  scm_call_0 ((*i)->lambda.get_scm ());
	}
    }

  lambdas.remove_if (TimeManager_to_old (current_time));
}

void
TimeManager::register_guile_bindings ()
{
  puts ("TimeManager::register_guile_bindings ()");

  scm_c_define_gsubr("c:timemanager:create", 0, 0, 0, reinterpret_cast<scm_t_subr>(&TimeManager::scm_timemanager_create));
  scm_c_define_gsubr("c:timemanager:add", 3, 0, 0, reinterpret_cast<scm_t_subr>(&TimeManager::scm_timemanager_add));
}
/*
SCM
TimeManager::mark (SCM smob)
{
  if (gc_mark_enabled)
    {
      TimeManager* time_manager = smob_cast<TimeManager>(smob);
      for (TimedList::iterator i = time_manager->lambdas.begin ();
	   i != time_manager->lambdas.end (); ++i)
	{
	  scm_gc_mark ((*i)->lambda.get_scm ());
	}
      return SCM_UNSPECIFIED;
    }
  else
    return SCM_BOOL_F;
}

size_t
TimeManager::free (SCM smob)
{
  if (gc_free_enabled)
    {
      delete smob_cast<TimeManager>(smob);
      return 0; //sizeof (TimeManager);
    }
  else
    return 0;
}

int
TimeManager::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:TimeManager>", port);
  return 1;
}
*/
SCM
TimeManager::scm_timemanager_create ()
{
  return LayerSmob::create (new TimeManager ());
}

SCM
TimeManager::scm_timemanager_add (SCM scm_manager, SCM scm_time, SCM scm_func)
{
  TimeManager* manager (smobbox_cast<TimeManager>(scm_manager));
  manager->add (scm_to_int (scm_time), scm_func);
  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
