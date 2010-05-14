//  $Id: AdventObj.hh,v 1.6 2001/04/27 20:42:57 grumbel Exp $
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

#ifndef ADVENTOBJ_HH
#define ADVENTOBJ_HH

#include <ClanLib/core.h>
#include "Position.hh"
#include "Drawable.hh"

class Scenario;

class AdventObj : public Drawable
{
protected:
  //Scenario* scenario;
  
public:
  /// Empty default constructor
  AdventObj () {}
  AdventObj (Scenario* s) {
    //scenario = s;
  }

  /// Empty default destructor
  virtual ~AdventObj () {}

  /// Update the status of the object, this function is called once an
  /// event loop
  virtual void update (float delta) {}

  /// Draw the object into the inventory
  virtual void draw_inventory (int x, int y) {}

  virtual bool is_at (int x, int y) { return false; }
  
  virtual std::string get_name () { return "-- unset --"; }
};

// Little helper class for sort()
struct AdventObj_less : public std::binary_function<Drawable*, Drawable*, bool>
{
  bool operator() (Drawable* a, Drawable* b) const
    {
      return a->get_z_pos () < b->get_z_pos ();
    }
};

class SurfaceAdvObj : public AdventObj
{
private:
  CL_Vector pos;
  CL_Surface sur;

public:
  SurfaceAdvObj (Scenario* s, const CL_Surface& arg_sur, const CL_Vector& arg_pos);
  ~SurfaceAdvObj () {}

  void  draw_world (int x_offset = 0, int y_offset = 0);
  float get_z_pos () { return pos.z; }
};

#endif

/* EOF */
