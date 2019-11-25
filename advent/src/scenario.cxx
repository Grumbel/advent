//  $Id: scenario.cxx,v 1.28 2004/01/14 02:28:24 grumbel Exp $
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

#include "colmap.hxx"
#include "scm_converter.hxx"
#include "view.hxx"
#include "drawable_display.hxx"
#include "scenario.hxx"
#include "util.hxx"

namespace Advent {

long int Scenario::tag;

std::list<Scenario*> Scenario::scenarios;
bool Scenario::lock_count = false;

struct drawable_removable
{
  bool operator() (SmobTuple<Drawable>& a)
  {
    // FIXME: This doesn't work, probally a dynamic_cast problem
    // FIXME: inside SmobTuple
    //return a.get ()->removable ();
    return checked_smob_cast<DrawableSmob>(a.get_scm ())->get_child ()->is_removable ();
  }
};

Scenario::Scenario (SCM arg_scm)
  : width (800), height (600),
    bind (arg_scm),
    display (new DrawableDisplay ())
{
  scenarios.push_back (this);
}

Scenario::~Scenario ()
{
  delete display;
}

void
Scenario::add_advobj (SCM obj)
{
  // Don't add objects multiple times
  AdvObjList::iterator i = find(advobjs.begin(), advobjs.end(), SmobTuple<AdvObj>(obj));
  if (i == advobjs.end ())
    advobjs.push_back (SmobTuple<AdvObj>(obj));
  else
    std::cout << "Scenario::add_drawable:duplicated found" << std::endl;
}

void
Scenario::remove_advobj (SCM obj)
{
  std::cout << "Scenario::remove_advobj" << std::endl;
  advobjs.remove (SmobTuple<AdvObj>(obj));
}

void
Scenario::add_drawable (SCM drawable)
{
  DrawableList::iterator i = find(drawables.begin(), drawables.end(),
				  SmobTuple<Drawable>(drawable));
  if (i == drawables.end ())
    drawables.push_back (SmobTuple<Drawable>(drawable));
  else
    std::cout << "Scenario::add_drawable:duplicated found" << std::endl;
}

void
Scenario::remove_drawable (SCM drawable)
{
  drawables.remove (SmobTuple<Drawable>(drawable));
}

ColMap*
Scenario::get_colmap ()
{
  //std::cout << "ColMap: " << colmap << std::endl;
  return colmap.get ();
}

void
Scenario::update_all (float delta)
{
  for (std::list<Scenario*>::iterator i = scenarios.begin (); i != scenarios.end (); ++i)
    {
      (*i)->update (delta);
    }
}

void
Scenario::update (float delta)
{
  if (lock_count == false)
    {
      lock_count = true;
      update_all (delta);
      lock_count = false;
      //std::cout << "updating_all: " << this << std::endl;
    }
  else
    {
      //std::cout << "updating: " << this << std::endl;
      // FIXME: Probally a bit slow, especially the protect/unprotect in
      // FIXME: DrawableDisplay could become a bottleneck
      display->update (delta);
      drawables.remove_if (drawable_removable ());
      display->clear ();
      for (AdvObjList::iterator i = advobjs.begin (); i != advobjs.end (); ++i)
	{
	  display->add (i->get_scm ());
	}
      for (DrawableList::iterator i = drawables.begin (); i != drawables.end (); ++i)
	{
	  display->add (i->get_scm ());
	}
      display->update (delta);
      // FIXME:
      //get_object (CL_Mouse::get_x (), CL_Mouse::get_y ());
    }
  get_object (CL_Mouse::get_x (), CL_Mouse::get_y ());
}

int
Scenario::get_width ()
{
  // FIXME: BUG: unimplemented
  return width;
}

int
Scenario::get_height ()
{
  // FIXME: BUG: unimplemented
  return height;
}

void
Scenario::draw (boost::dummy_ptr<View> view)
{
  // std::cout << "Scenario::draw" << std::endl;
  display->draw (view);
}

SCM
Scenario::get_scm ()
{
  return bind.get_scm ();
}

AdvObj*
Scenario::get_object (int x_pos, int y_pos)
{
  AdvObj* obj = NULL;

  for (AdvObjList::iterator i = advobjs.begin (); i != advobjs.end (); ++i)
    {
      if (i->get()->is_over (x_pos, y_pos))
	{
  	  obj = i->get ();
	}
    }

  return obj;
}

bool
Scenario::is_a (SCM smob)
{
  puts ("304950: Crash expected"); //Sun Feb 23 17:05:34 2003
  //return (SCM_CAR (smob) == get_smob_tag ());
  return true;
}

void
Scenario::register_guile_bindings ()
{
  puts ("Scenario::register_guile_bindings ()");
  tag = scm_make_smob_type ("Scenario", 0);

  scm_set_smob_mark  (tag, Scenario::mark);
  scm_set_smob_free  (tag, Scenario::free);
  scm_set_smob_print (tag, Scenario::print);

  gh_c_define_public_gsubr("c:scenario:create", 1, 0, 0, reinterpret_cast<scm_t_subr>(&Scenario::scm_scenario_create));
  gh_c_define_public_gsubr("c:scenario:add-drawable", 2, 0, 0, reinterpret_cast<scm_t_subr>(&Scenario::scm_scenario_add_drawable));
  gh_c_define_public_gsubr("c:scenario:remove-drawable", 2, 0, 0, reinterpret_cast<scm_t_subr>(&Scenario::scm_scenario_remove_drawable));

  gh_c_define_public_gsubr("c:scenario:add-advobj", 2, 0, 0,    reinterpret_cast<scm_t_subr>(&Scenario::scm_scenario_add_advobj));
  gh_c_define_public_gsubr("c:scenario:remove-advobj", 2, 0, 0, reinterpret_cast<scm_t_subr>(&Scenario::scm_scenario_remove_advobj));

  gh_c_define_public_gsubr("c:scenario:set-colmap", 2, 0, 0, reinterpret_cast<scm_t_subr>(&Scenario::scm_scenario_set_colmap));
  gh_c_define_public_gsubr("c:scenario:set-dimension", 3, 0, 0, reinterpret_cast<scm_t_subr>(&Scenario::scm_scenario_set_dimension));
}

SCM
Scenario::mark (SCM smob)
{
  /* FIXME:
  Scenario* scenario = smob_cast<Scenario>(smob);

  for (AdvObjList::iterator i = scenario->advobjs.begin ();
       i != scenario->advobjs.end (); ++i)
    i->mark ();

  for (DrawableList::iterator i = scenario->drawables.begin ();
       i != scenario->drawables.end (); ++i)
    i->mark ();

  scenario->display->mark ();

  return scenario->colmap.get_scm ();*/
  return SCM_BOOL_F;
}

size_t
Scenario::free (SCM smob)
{
  //FIXME:delete smob_cast<Scenario>(smob);
  return 0; //sizeof (Scenario);
}

int
Scenario::print (SCM scm_scenario, SCM port, scm_print_state *pstate)
{
  //Scenario* scenario = checked_smob_cast<Scenario>(scm_scenario);
  scm_puts ("#<c:Scenario>", port);
  return 1;
}

SCM
Scenario::scm_scenario_set_colmap (SCM scm_scenario, SCM scm_colmap)
{
  Scenario* scenario = checked_smob_cast<Scenario>(scm_scenario);
  scenario->colmap.set_scm(scm_colmap);
  return SCM_UNSPECIFIED;
}

SCM
Scenario::scm_scenario_create (SCM arg_scenario)
{
  Scenario* scenario = new Scenario (arg_scenario);
  SCM_RETURN_NEWSMOB (tag, scenario);
}

SCM
Scenario::scm_scenario_add_drawable (SCM arg_scenario, SCM arg_obj)
{
  //std::cout << "Scenario::scm_scenario_add_drawable" << std::endl;
  Scenario* scenario = checked_smob_cast<Scenario>(arg_scenario);
  scenario->add_drawable (arg_obj);
  return SCM_UNSPECIFIED;
}

SCM
Scenario::scm_scenario_remove_drawable (SCM arg_scenario, SCM arg_obj)
{
  checked_smob_cast<Scenario>(arg_scenario)->remove_drawable(arg_obj);
  return SCM_UNSPECIFIED;
}

SCM
Scenario::scm_scenario_add_advobj (SCM arg_scenario, SCM arg_obj)
{
  Scenario* scenario = checked_smob_cast<Scenario>(arg_scenario);
  scenario->add_advobj (arg_obj);

  return SCM_UNSPECIFIED;
}

SCM
Scenario::scm_scenario_set_dimension (SCM arg_scenario, SCM scm_width, SCM scm_height)
{
  Scenario* scenario = checked_smob_cast<Scenario>(arg_scenario);
  scenario->width = scm_to_int(scm_width);
  scenario->height = scm_to_int(scm_height);
  return SCM_UNSPECIFIED;
}

SCM
Scenario::scm_scenario_remove_advobj (SCM arg_scenario, SCM arg_obj)
{
  Scenario* scenario = checked_smob_cast<Scenario>(arg_scenario);
  scenario->remove_advobj (arg_obj);

  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
