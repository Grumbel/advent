//  $Id: View.cc,v 1.4 2001/07/12 08:13:49 grumbel Exp $
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

#include "Scenario.hh"
#include "ScenarioSmob.hh"
#include "View.hh"

View* the_view;

View::View ()
{
  scenario = 0;
  guy = 0;
}

View::~View ()
{
}

void
View::draw ()
{
  if (scenario)
    {
      scenario->draw (this);
    }
}

void
View::update (float delta)
{
  guy = Guy::get_current ();
  scenario = Scenario::get_current ();

  if (guy)
    {
      scenario = guy->get_scenario ();
    }
  else
    {
      std::cout << "View: Guy not set" << std::endl;
    }

  //std::cout << "View:update: G:" << guy
  //

  if (scenario)
    {
      scenario->update (delta);
    }
}

void
View::look_at (CL_Vector pos)
{
}

void
View::scroll_to (CL_Vector pos)
{
}

void
View::follow (Guy* g)
{
  std::cout << "View: following guy: " << guy << std::endl;
  guy = g;
}

/*
void
View::fade_out ()
{
}*/

/***************/
/* Guile Stuff */
/***************/

/** Init guile functions and smob staff */
void
View::init ()
{
  gh_new_procedure2_0 ("c:view:look-at", &View::look_at);
  gh_new_procedure2_0 ("c:view:scroll-to", &View::scroll_to);
  gh_new_procedure1_0 ("c:view:set-scenario", &View::set_scenario);
  gh_new_procedure1_0 ("c:view:follow", &View::follow);
  gh_new_procedure0_0 ("c:view:fade-out", &View::fade_out);
}

/** Set the view to the given position */
SCM
View::look_at (SCM x, SCM y)
{
  return SCM_UNSPECIFIED;
}

/** Scroll slowly to the given coordinates */
SCM
View::scroll_to (SCM x, SCM y)
{
  return SCM_UNSPECIFIED;
}

/** Set the viem onto the given scenario */
SCM
View::set_scenario (SCM smob)
{
  //Scenario* scenario
    //  = ((ScenarioSmobStruct*)(SCM_CDR(smob)))->scenario;

  // FIXME..

  return SCM_UNSPECIFIED;
}

/** Follow a person */
SCM
View::follow (SCM person)
{
  return SCM_UNSPECIFIED;
}

/** Fadeout the screen */
SCM
View::fade_out ()
{
  return SCM_UNSPECIFIED;
}

/* EOF */
