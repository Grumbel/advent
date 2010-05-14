//  $Id: Scenario.hh,v 1.2 2000/12/29 10:08:16 grumbel Exp $
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

#ifndef SCENARIO_HH
#define SCENARIO_HH

#include "AdventObj.hh"
#include "Background.hh"
#include "CollisionMap.hh"
#include <list>

class AdventObj;

class Scenario
{
protected:
  std::list<AdventObj*> objects;
  Background* background;
  CollisionMap* colmap;
  std::string name;

public:
  ///
  static std::list<Scenario*> scenario_list;
  ///
  static Scenario* current;

  Scenario (std::string name, 
	    std::string background, std::string colmap,
	    std::list<AdventObj*> objects);
  virtual ~Scenario ();
  
  static void set_current_scenario (std::string name);
  static void set_current_scenario (Scenario* scenario);

  virtual std::string get_name () { return name; }

  virtual void draw ();
  virtual void update ();
  virtual CollisionMap* get_colmap ();
  virtual AdventObj* get_object (int x, int y);
  virtual void add (AdventObj* obj);
};

#endif

/* EOF */
