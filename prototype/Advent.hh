//  $Id: Advent.hh,v 1.1 2000/12/28 20:00:48 grumbel Exp $
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

#ifndef ADVENT_HH
#define ADVENT_HH

#include <ClanLib/core.h>
#include "Inventory.hh"

extern Scenario* current_scenario;

void inner_main (void* closure, int argc, char* argv[]);

class Advent : public CL_ClanApplication
{
private:
  CL_ResourceManager* resource;
public:
  Advent ();
  char* get_title ();
  CL_ResourceManager* get_resource () { return resource; }
  void   inner_main (void* closure, int argc, char* argv[]);
  int   main (int argc, char* argv[]);
};

extern Inventory inventory;
extern Advent app;

#endif

/* EOF */
