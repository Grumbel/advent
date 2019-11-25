//  $Id: person_gfx.cxx,v 1.11 2004/01/14 02:28:24 grumbel Exp $
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
#include <math.h>
#include "surface_sprite.hxx"
#include "person.hxx"
#include "person_gfx.hxx"
#include "util.hxx"

namespace Advent {

long PersonGfx::tag;

PersonGfx::PersonGfx (SCM lst)
{
  std::cout << "PersonGfx::PersonGfx (SCM lst)" << std::endl;
  SCM walk  = SCM_CAR (lst);
  SCM stand = SCM_CADR (lst);

  walking = new PersonGfxPack (scm_list_ref (walk, scm_from_int(0)),
			       scm_list_ref (walk, scm_from_int(1)),
			       scm_list_ref (walk, scm_from_int(2)),
			       scm_list_ref (walk, scm_from_int(3)));

  standing = new PersonGfxPack (scm_list_ref (stand, scm_from_int(0)),
				scm_list_ref (stand, scm_from_int(1)),
				scm_list_ref (stand, scm_from_int(2)),
				scm_list_ref (stand, scm_from_int(3)));

  //west  = new SurfaceSprite ("images/mogli_west.png");
  //east  = new SurfaceSprite ("images/mogli_east.png");
  //north = new SurfaceSprite ("images/mogli_north.png");
  //south = new SurfaceSprite ("images/mogli_south.png");

  /*
    walking.west  = new SurfaceSprite ("images/amogli_west.png", 8);
    walking.east  = new SurfaceSprite ("images/amogli_east.png", 8);
    walking.north = new SurfaceSprite ("images/amogli_north.png", 5);
    walking.south = new SurfaceSprite ("images/amogli_south.png", 8);

    walking.west->set_align_center_bottom ();
    walking.east->set_align_center_bottom ();
    walking.north->set_align_center_bottom ();
    walking.south->set_align_center_bottom ();
  */

  /*
    standing.west  = new SurfaceSprite ("images/mogli_west.png");
    standing.east  = new SurfaceSprite ("images/mogli_east.png");
    standing.north = new SurfaceSprite ("images/mogli_north.png");
    standing.south = new SurfaceSprite ("images/mogli_south.png");

    standing.west->set_align_center_bottom ();
    standing.east->set_align_center_bottom ();
    standing.north->set_align_center_bottom ();
    standing.south->set_align_center_bottom ();
  */

  /*
    walking.west  = new SurfaceSprite ("images/prof_west.png");
    walking.east  = new SurfaceSprite ("images/prof_east.png");
    walking.north = new SurfaceSprite ("images/prof_north.png");
    walking.south = new SurfaceSprite ("images/prof_south.png");

    walking.west->set_align (-45, -265);
    walking.east->set_align (-45, -265);
    walking.north->set_align (-62, -265);
    walking.south->set_align (-62, -265);

    standing.west  = new SurfaceSprite ("images/prof_west.png");
    standing.east  = new SurfaceSprite ("images/prof_east.png");
    standing.north = new SurfaceSprite ("images/prof_north.png");
    standing.south = new SurfaceSprite ("images/prof_south.png");

    standing.west->set_align (-45, -265);
    standing.east->set_align (-45, -265);
    standing.north->set_align (-62,-265);
    standing.south->set_align (-62, -265);
  */
}

PersonGfx::~PersonGfx ()
{
}

Sprite*
PersonGfx::get_sprite (Person* person)
{
  PersonGfxPack* pack;
  if (person->on_target ())
    pack = standing;
  else
    pack = walking;


  CL_Vector direction (person->get_direction ());

  if (direction == CL_Vector ())
    {
      return pack->west.get();
    }
  else
    {
      if (fabs(direction.x) > fabs(direction.y))
	{
	  if (direction.x < 0)
	    return pack->west.get();
	  else
	    return pack->east.get();
	}
      else
	{
	  if (direction.y < 0)
	    return pack->north.get();
	  else
	    return pack->south.get();
	}

      return pack->west.get();
    }
}

void
PersonGfx::update (float delta)
{
  standing->update (delta);
  walking->update (delta);
}

void
PersonGfx::register_guile_bindings ()
{
  puts ("PersonGfx::register_guile_bindings ()");
  tag = scm_make_smob_type ("PersonGfx", 0);

  scm_set_smob_mark  (tag, PersonGfx::mark);
  scm_set_smob_free  (tag, PersonGfx::free);
  scm_set_smob_print (tag, PersonGfx::print);

  gh_c_define_public_gsubr("c:persongfx:create", 1, 0, 0, reinterpret_cast<scm_t_subr>(&PersonGfx::scm_persongfx_create));
}

SCM
PersonGfx::mark (SCM smob)
{
  return SCM_BOOL_F;
}

size_t
PersonGfx::free (SCM smob)
{
  //FIXME:delete smob_cast<Scenario>(smob);
  return 0; //sizeof (Scenario);
}

int
PersonGfx::print (SCM scm_scenario, SCM port, scm_print_state *pstate)
{
  //Scenario* scenario = checked_smob_cast<Scenario>(scm_scenario);
  scm_puts ("#<c:PersonGfx>", port);
  return 1;
}

SCM
PersonGfx::scm_persongfx_create (SCM lst)
{
  std::cout << "PersonGfx::scm_persongfx_create (SCM lst)" << std::endl;
  PersonGfx* gfx = new PersonGfx (lst);
  SCM_RETURN_NEWSMOB (tag, gfx);
}

} // namespace Advent

/* EOF */
