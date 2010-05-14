//  $Id: Scenariolayer.hxx,v 1.13 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef SCENARIOLAYER_HXX
#define SCENARIOLAYER_HXX

#include "layer.hxx"
#include "person.hxx"
#include "scenario.hxx"
#include "display_view.hxx"

namespace Advent {

/** A layer which shows the current scenario. Should probally get
    plugable follow modules (follow person, scroll left, ...)
 */
class ScenarioLayer : public Layer
{
private:
  DisplayView* current_view;
  Person* current_person;
  SCM callback;
  SCMObj mouse_over_callback;
  AdvObj* last_obj;
public:
  ScenarioLayer ();
  virtual ~ScenarioLayer () {}

  void update (float delta);
  void draw (boost::dummy_ptr<View> view);
  void set_person (Person* person);

  bool is_over (int x_pos, int y_pos);
  void on_button_press (const CL_InputEvent&);
  void on_button_release (const CL_InputEvent&);

  // static guile stuff
public:
  static void register_guile_bindings ();
  static SCM scm_scenariolayer_create ();
  static SCM scm_scenariolayer_set_person (SCM layer, SCM person);
  static SCM scm_scenariolayer_set_callback (SCM layer, SCM c);
  static SCM scm_scenariolayer_set_mouse_over_callback (SCM layer, SCM c);
  static SCM scm_scenariolayer_mouse_update (SCM layer);
};

} // namespace Advent

#endif

/* EOF */
