//  $Id: Scenariolayer.cxx,v 1.26 2004/01/14 02:28:24 grumbel Exp $
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

#include "colmap.hxx"
#include "person.hxx"
#include "scm_converter.hxx"
#include "scenario_layer.hxx"

namespace Advent {

// FIXME: Memory Leak
ScenarioLayer::ScenarioLayer ()
  : current_view (new DisplayView (0, 0, 639, 480, -320, -240)),
    current_person (0),
    callback (SCM_BOOL_F),
    last_obj (0)
{
  z_pos = 0;
}

void
ScenarioLayer::update (float delta)
{
  assert (current_person);
  current_person->get_scenario ()->update (delta);

  CL_Vector pos = current_view->display_to_view (CL_Vector(CL_Mouse::get_x (),
							   CL_Mouse::get_y ()));
  AdvObj* obj = current_person->get_scenario ()->get_object ((int) pos.x, (int) pos.y);
  if (obj != last_obj && mouse_over_callback.get_scm () != SCM_BOOL_F)
    {
      //std::cout << "Trying to call callback" << std::endl;
      if (obj)
	gh_call1 (mouse_over_callback.get_scm (), obj->get_scm ());
      else
	gh_call1 (mouse_over_callback.get_scm (), SCM_BOOL_F);

      last_obj = obj;
      //std::cout << "Trying to call callback: done" << std::endl;
    }
}

void
ScenarioLayer::draw (boost::dummy_ptr<View> view)
{
  CL_Vector pos = current_person->get_pos ();
  Scenario* scenario = current_person->get_scenario ();

  if (pos.x > scenario->get_width () - CL_Display::get_width ()/2)
    pos.x = scenario->get_width () - CL_Display::get_width ()/2;

  if (pos.y > scenario->get_height () - CL_Display::get_height ()/2)
    pos.y = scenario->get_height () - CL_Display::get_height ()/2;

  if (pos.x < CL_Display::get_width ()/2)
    pos.x = CL_Display::get_width ()/2;

  if (pos.y < CL_Display::get_height ()/2)
    pos.y = CL_Display::get_height ()/2;

  current_view->set_view(pos);

  assert (current_person);
  scenario->draw (current_view);
  //std::cout << "ScenarioLayer::draw: done" << std::endl;
}

void
ScenarioLayer::set_person (Person* p)
{
  current_person = p;
}

bool
ScenarioLayer::is_over (int x_pos, int y_pos)
{
  //std::cout << "isover" << std::endl;
  return true;
}

void
ScenarioLayer::on_button_press (const CL_InputEvent& key)
{
  assert (current_person);
  CL_Vector pos (key.mouse_pos.x, key.mouse_pos.y);
  pos = current_view->display_to_view (pos);
  AdvObj* obj = current_person->get_scenario ()->get_object ((int) pos.x, (int) pos.y);

  if (key.id == CL_MOUSE_LEFT)
    {
      if (obj)
	{
          obj->on_click ();
	}
      else
	{
	  if (callback != SCM_BOOL_F)
	    gh_call2 (callback, gh_double2scm (pos.x), gh_double2scm (pos.y));
	}
    }
  else if (key.id == CL_MOUSE_MIDDLE)
    {
      ColMap* colmap = current_person->get_scenario ()->get_colmap ();
      if (colmap)
	std::cout << "Press at: " << pos.x << " " << pos.y << " "
		  << colmap->get_depth (pos.x, pos.y) << std::endl;
      else
	std::cout << "Press at: " << pos.x << " " << pos.y << std::endl;
    }
}

void
ScenarioLayer::on_button_release (const CL_InputEvent&)
{
}

void
ScenarioLayer::register_guile_bindings ()
{
  puts ("ScenarioLayer::register_guile_bindings ()");

  gh_new_procedure2_0 ("c:scenariolayer:set-person",
		       &ScenarioLayer::scm_scenariolayer_set_person);
  gh_new_procedure0_0 ("c:scenariolayer:create",
		       &ScenarioLayer::scm_scenariolayer_create);
  gh_new_procedure2_0 ("c:scenariolayer:set-callback",
		       scm_scenariolayer_set_callback);
  gh_new_procedure2_0 ("c:scenariolayer:set-mouse-over-callback",
		       scm_scenariolayer_set_mouse_over_callback);
  gh_new_procedure1_0 ("c:scenariolayer:mouse-update",
		       scm_scenariolayer_mouse_update);
}
/*
SCM
ScenarioLayer::mark (SCM smob)
{
  return SCM_BOOL_F; //FIXME:smob_cast<ScenarioLayer>(smob)->callback;
}

scm_sizet
ScenarioLayer::free (SCM smob)
{
  //FIXME:delete smob_cast<ScenarioLayer>(smob);
  return 0; //sizeof (ScenarioLayer);
}

int
ScenarioLayer::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:ScenarioLayer>", port);
  return 1;
}
*/
SCM
ScenarioLayer::scm_scenariolayer_create ()
{
  ScenarioLayer* layer = new ScenarioLayer ();
  return LayerSmob::create (layer);
}

SCM
ScenarioLayer::scm_scenariolayer_set_person (SCM scm_layer, SCM scm_person)
{
  smobbox_cast<ScenarioLayer>(scm_layer)->set_person(smobbox_cast<Person>(scm_person));
  return SCM_UNSPECIFIED;
}

SCM
ScenarioLayer::scm_scenariolayer_set_callback (SCM scm_layer, SCM c)
{
  Guile::protect_object (c);
  smobbox_cast<ScenarioLayer>(scm_layer)->callback = c;
  return SCM_UNSPECIFIED;
}

SCM
ScenarioLayer::scm_scenariolayer_set_mouse_over_callback (SCM scm_layer, SCM c)
{
  smobbox_cast<ScenarioLayer>(scm_layer)->mouse_over_callback.set_scm (c);
  return SCM_UNSPECIFIED;
}

SCM
ScenarioLayer::scm_scenariolayer_mouse_update (SCM scm_layer)
{
  ScenarioLayer* layer = smobbox_cast<ScenarioLayer>(scm_layer);

  CL_Vector pos = layer->current_view->display_to_view (CL_Vector(CL_Mouse::get_x (),
								  CL_Mouse::get_y ()));
  AdvObj* obj = layer->current_person->get_scenario ()->get_object ((int) pos.x, (int) pos.y);
  if (layer->mouse_over_callback.get_scm () != SCM_BOOL_F)
    {
      if (obj)
	gh_call1 (layer->mouse_over_callback.get_scm (), obj->get_scm ());
      else
	gh_call1 (layer->mouse_over_callback.get_scm (), SCM_BOOL_F);

      layer->last_obj = obj;
    }
  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
