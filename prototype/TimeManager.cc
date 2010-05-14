//  $Id: TimeManager.cc,v 1.2 2001/04/27 20:42:57 grumbel Exp $
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

#include <ClanLib/core.h>
#include "TimeManager.hh"

std::list<TimedLambda> TimeManager::lambdas;

void
TimeManager::init ()
{
  gh_new_procedure2_0 ("c:add-timed", TimeManager::add);
}

SCM
TimeManager::add (SCM time, SCM lambda)
{
  lambdas.push_back(TimedLambda (CL_System::get_time () + SCM_INUM (time),
				 lambda));
  return SCM_UNSPECIFIED;
}

struct to_old
{
  unsigned int current_time;

  to_old (unsigned int arg_current_time) {
    current_time = arg_current_time;
  }

  bool operator () (const TimedLambda& lambda) {
    return (lambda.triger_time <= current_time);
  }
};

void
TimeManager::update (float delta)
{
  unsigned int current_time = CL_System::get_time ();
  
  for (std::list<TimedLambda>::iterator i = lambdas.begin ();
       i != lambdas.end (); ++i)
    {
      if (i->triger_time <= current_time)
	gh_call0 (i->lambda);
    }

  lambdas.remove_if (to_old (current_time));
}

/* EOF */
