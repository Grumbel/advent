//  $Id: GuileAdventObj.hh,v 1.1 2000/12/28 20:00:49 grumbel Exp $
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

#ifndef GUILEADVENTOBJ_HH
#define GUILEADVENTOBJ_HH

#include <ClanLib/core.h>
#include "AdventObj.hh"

class GuileAdventObj : public AdventObj
{
private: 
  std::string name;

  /// The uniq id of this object instance
  int id; 
  
  CL_Surface sur;
  CL_Vector pos;
public:
  /// Empty default constructor
  GuileAdventObj (Scenario* s, std::string arg_name, int arg_id,
		  CL_Surface arg_sur, CL_Vector pos);

  /// Empty default destructor
  virtual ~GuileAdventObj () {}

  /// Update the status of the object, this function is called once an
  /// event loop
  virtual void update () {}

  /// Draw the object to the world
  virtual void draw_world ();

  /// Draw the object into the inventory
  virtual void draw_inventory (int x, int y) {}

  virtual void call (std::string func, std::string id);

  virtual bool is_at (int x, int y);
  
  virtual std::string get_name () { return name; }

  virtual float get_z_pos () { return pos.z; }

  virtual void set_surface (std::string str);
};

#endif

/* EOF */
