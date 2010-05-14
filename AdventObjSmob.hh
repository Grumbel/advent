//  $Id$
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

#ifndef ADVENTOBJSMOB_HH
#define ADVENTOBJSMOB_HH

class AdventObjSmob
{
private:
  static long tag;
  
public:
  static void init ();
  static SCM       mark_obj (SCM smob);
  static scm_sizet free_obj (SCM smob);
  static int       print_obj (SCM smob, SCM port, scm_print_state *pstate);

  static SCM make_obj (SCM name, SCM surface, 
		       SCM x_pos, SCM y_pos, SCM z_pos);
  static SCM set_surface (SCM obj, SCM name);
};

#endif

/* EOF */
