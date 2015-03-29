//  $Id: GuileAdventObj.hh,v 1.13 2001/07/16 17:44:10 grumbel Exp $
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

#include <guile/gh.h>
#include <ClanLib/core.h>
#include "AdventObj.hh"

class GuileAdventObj : public AdventObj
{
private:
  std::string name;
  SCM scm_object;

  /// The uniq id of this object instance
  int id;

  bool surface_visible;

  CL_Surface sur;
  CL_Surface inventory_sur;
  CL_Vector pos;

  int width;
  int height;
  int counter;

  std::string surname;
  bool is_init;


  void init ();
public:
  // true if object is 'empty', that means doesn't has a name and
  // isn't captureable
  bool empty_object;

  /// Empty default constructor
  GuileAdventObj (SCM arg_name,
		  std::string arg_surname, CL_Vector pos);

  GuileAdventObj (SCM arg_name,
		  CL_Vector pos, int arg_width, int arg_height);

  /// Empty default destructor
  virtual ~GuileAdventObj () {}

  /// Update the status of the object, this function is called once an
  /// event loop
  virtual void update (float delta);

  /// Draw the object to the world
  virtual void draw_world (int x_offset = 0, int y_offset = 0);

  /// Draw the object into the inventory
  virtual void draw_inventory (int x, int y);

  virtual void call (std::string func, std::string id);
  SCM call (std::string func);
  SCM get_scm () { return scm_object; }

  virtual bool is_at (int x, int y);

  virtual std::string get_name () { return name; }

  virtual float get_z_pos () { return pos.z; }

  virtual void set_surface (std::string str);
  virtual void set_surface_pos (int x_pos, int y_pos, int z_pos);
  virtual void set_inventory_surface (std::string str);
};

#endif

/* EOF */
