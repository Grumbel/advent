//  $Id: scenario.hxx,v 1.16 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef SCENARIO_HXX
#define SCENARIO_HXX

#include <libguile.h>
#include "adv_obj.hxx"
#include "drawable_display.hxx"
#include "layer.hxx"
#include "smob_tuple.hxx"

namespace Advent {

class ColMap;

/** Basically the visual representation of the guile-scenario object,
    it consist of a list of drawables, which itself are AdvObj's

    FIXME: This should probally be just an interface and the drawable
    FIXME: stuff should be go into DrawableScenario or something like
    FIXME: that.
 */
class Scenario
{
private:
  int width, height;
  SCMObj bind;
  typedef std::list<SmobTuple<Drawable> > DrawableList;
  typedef std::list<SmobTuple<AdvObj> > AdvObjList;

  /** AdvObj's in the scenario, they are keeped seperate of the
      drawables, 'cause the drawables remove themself from the
      scenario (they expire) and because the AdvObj's needs to handle
      input handling. */
  AdvObjList   advobjs;
  DrawableList drawables;
  SmobTuple<ColMap> colmap;

  DrawableDisplay* display;

  // FIXME: Hack, should be replaced with an update manager or so
  static std::list<Scenario*> scenarios;
  static bool lock_count;
  static void update_all (float);
public:
  Scenario (SCM);
  virtual ~Scenario ();

  int get_width ();
  int get_height ();

  void update (float delta);
  void draw (boost::dummy_ptr<View>);
  void add_advobj (SCM advObj);
  void add_drawable (SCM drawable);
  void remove_advobj (SCM drawable);
  void remove_drawable (SCM drawable);
  ColMap* get_colmap ();
  SCM  get_scm ();

  /** Return the which is at the given coordinates or NULL. x/y_pos
      are in world coordinates, not screen coordinates */
  AdvObj* get_object (int x_pos, int y_pos);

  // static functions for guile bindings
private:
  static long int tag;
public:
  static bool is_a (SCM smob);
  static long get_smob_tag () { return tag; }

  static void register_guile_bindings ();

  static SCM mark (SCM smob);
  static size_t free (SCM smob);
  static int print (SCM image_smob, SCM port, scm_print_state *pstate);

  static SCM scm_scenario_create (SCM arg_scenario);
  static SCM scm_scenario_set_colmap (SCM scenario, SCM colmap);
  static SCM scm_scenario_set_dimension (SCM scenario, SCM scm_width, SCM scm_height);

  static SCM scm_scenario_add_drawable (SCM arg_scenario, SCM arg_obj);
  static SCM scm_scenario_remove_drawable (SCM arg_scenario, SCM arg_obj);

  static SCM scm_scenario_add_advobj (SCM scenario, SCM obj);
  static SCM scm_scenario_remove_advobj (SCM scenario, SCM obj);
};

} // namespace Advent

#endif

/* EOF */
