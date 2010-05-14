//  $Id: Scenario.cc,v 1.1 2000/12/28 20:00:48 grumbel Exp $
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

#include "Advent.hh"
#include "GuileAdventObj.hh"
#include "Position.hh"
#include "Scenario.hh"

Scenario::Scenario ()
{
  objects.push_back (new Mogli (this));
  /*
  objects.push_back (new GuileAdventObj (this, "odd" , 3,
					CL_Surface ("odd", app.get_resource ()),
					CL_Vector (340, 216, 230)));
  objects.push_back (new GuileAdventObj (this, "tree", 2,
					 CL_Surface ("tree", app.get_resource ()),
					 CL_Vector (0, 211, 255)));
  objects.push_back (new GuileAdventObj (this, "takeme", 1,
					 CL_Surface ("takeme", app.get_resource ()),
					 CL_Vector (236, 300, 240)));
  */
}

Scenario::~Scenario ()
{
}
  
void
Scenario::draw ()
{
  background.draw ();
  // CL_Display::clear_display ();
  objects.sort (AdventObj_less ());

  for (std::list<AdventObj*>::iterator i = objects.begin (); 
       i != objects.end (); i++)
    {
      (*i)->draw_world ();
    }
}

void
Scenario::update ()
{
  for (std::list<AdventObj*>::iterator i = objects.begin (); 
       i != objects.end (); i++)
    {
      (*i)->update ();
    }
  background.update ();
  colmap.update ();
}

CollisionMap* 
Scenario::get_colmap ()
{
  return &colmap;
}

AdventObj* 
Scenario::get_object (int x, int y)
{
  AdventObj* obj = 0;
  for (std::list<AdventObj*>::iterator i = objects.begin (); 
       i != objects.end (); i++)
    {
      if ((*i)->is_at (x, y))
	obj = (*i);
    }
  return obj;
}

void 
Scenario::add (AdventObj* obj)
{
  objects.push_back (obj);
}

/* EOF */
