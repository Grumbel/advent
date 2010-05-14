//  $Id: ScenarioSmob.hh,v 1.1 2000/12/29 10:15:32 grumbel Exp $
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

#ifndef SCENARIOSMOB_HH
#define SCENARIOSMOB_HH

class ScenarioSmob
{
private:
  /// The uniq id of this object type, only used by the guile internals
  static long tag;
public:
  /// Register the smob to guile
  static void init ();
  //static SCM       mark_obj (SCM smob);
  //static scm_sizet free_obj (SCM smob);
  //static int       print_obj (SCM smob, SCM port, scm_print_state *pstate);

  static SCM set_current_scenario (SCM scenario_bind);

  static SCM make_bind (SCM scenario_name, 
			SCM background_surface,
			SCM colmap_surface,
			SCM objects);
};

#endif

/* EOF */
