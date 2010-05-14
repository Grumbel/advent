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

#include "Inventory.hh"

Inventory::Inventory ()
{
}

void 
Inventory::add (AdventObj* obj)
{
  objects.push_back (obj);
}

void 
Inventory::remove (AdventObj* obj)
{
  objects.remove (obj);
}

void 
Inventory::draw ()
{
  int x = 0;
  for (std::list<AdventObj*>::iterator i = objects.begin (); 
       i != objects.end (); i++)
    {
      (*i)->draw_inventory (x, 0);
      x += 50;
    }
}

/* EOF */
