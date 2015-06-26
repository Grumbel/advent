//  $Id: Inventory.hh,v 1.9 2001/08/21 20:38:43 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef INVENTORY_HH
#define INVENTORY_HH

#include <guile/gh.h>
#include "AdventObj.hh"
#include "Clickable.hh"

class Inventory : public Clickable
{
private:
  std::vector<AdventObj*> objects;
  typedef std::vector<AdventObj*>::iterator ObjIter;
  bool visible;
  CL_Surface icon;
  CL_Surface icon_h;
  bool ignore_release;
public:
  Inventory ();
  virtual ~Inventory () {}

  void draw ();
  void update (float delta);

  /// Show the inventory and allow the user to select or manipulate it
  void show ();

  bool is_visible () { return visible; }

  /// Add
  void add (AdventObj*);

  /// Remove
  void remove (AdventObj*);

  bool has (AdventObj*);

  // ..:: Guile Specific Stuff ::..
  static void init ();
  static SCM add (SCM obj);
  static SCM remove (SCM obj);
  static SCM has (SCM obj);
  static SCM static_show ();
  static SCM get_objects ();

  // Clickable
  // Ignore presses when the inventory is visible
  bool  on_mouse_press (const CL_Key&);
  bool  on_mouse_release (const CL_Key&);
  float priority ();
  bool  mouse_over (int, int);
};

extern Inventory* inventory;

#endif

/* EOF */
