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

#ifndef ADVENTOBJ_HH
#define ADVENTOBJ_HH

#include <ClanLib/core.h>
#include "Position.hh"

class Scenario;

class AdventObj
{
protected:
  Scenario* scenario;
  
public:
  /// Empty default constructor
  AdventObj (Scenario* s) {
    scenario = s;
  }

  /// Empty default destructor
  virtual ~AdventObj () {}

  /// Update the status of the object, this function is called once an
  /// event loop
  virtual void update () {}

  /// Draw the object to the world
  virtual void draw_world () {}

  /// Draw the object into the inventory
  virtual void draw_inventory (int x, int y) {}

  virtual bool is_at (int x, int y) { return false; }
  
  virtual std::string get_name () { return "-- unset --"; }

  virtual float get_z_pos () { return 0.0; }
};

// Little helper class for sort()
struct AdventObj_less : public binary_function<AdventObj*, AdventObj*, bool>
{
  bool operator() (AdventObj* a, AdventObj* b) const
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

  void  draw_world ();
  float get_z_pos () { return pos.z; }
};

class Mogli : public AdventObj
{
private:
  CL_Surface sur_left;
  CL_Surface sur_right;
  CL_Surface sur_front;
  CL_Surface sur_back;

  int counter;
  thSlot on_button_press_slot;

  CL_Vector direction;
  CL_Vector pos;
  CL_Vector target;
  float delta;

public: 
  Mogli (Scenario* s);
  ~Mogli ();
  
  bool on_target ();
  void update ();
  void draw_world ();
  void on_button_press(CL_InputDevice *device, const CL_Key &key);
  float  get_z_pos () { return pos.z; }
  bool is_at (int x, int y);
  std::string get_name () { return "Mogli"; }
};

#endif

/* EOF */
