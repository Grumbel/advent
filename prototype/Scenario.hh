//  $Id: Scenario.hh,v 1.12 2001/07/12 09:23:16 grumbel Exp $
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

#ifndef SCENARIO_HH
#define SCENARIO_HH

#include <list>
#include <libguile.h>

#include "View.hh"
#include "AdventObj.hh"
#include "Background.hh"
#include "CollisionMap.hh"

class AdventObj;
class View;
class Scenario
{
protected:
  std::list<AdventObj*> objects;
  Background* background;
  CollisionMap* colmap;
  std::string name;
  SCM scm_object;

  // Stuff for on-demand loading
  bool is_init;
  std::string background_name;
  std::string colmap_name;

  std::list<Drawable*> drawables;

  void init ();

  int adv_list_lock;
  int drawable_list_lock;

  bool need_list_update;
  std::list<AdventObj*> adv_add_list;
public:
  ///
  static std::list<Scenario*> scenario_list;

  Scenario (SCM name,
	    std::string background, std::string colmap,
	    std::list<AdventObj*> objects, bool with_guy = true);
  virtual ~Scenario ();

  virtual std::string get_name () { return name; }

  static Scenario* get_current ();
  virtual void draw (View* view);
  virtual void update (float delta);
  virtual CollisionMap* get_colmap ();
  virtual AdventObj* get_object (int x, int y);
  virtual void add (AdventObj* obj);
  virtual void remove (AdventObj* obj);
  virtual void add (Drawable* obj);

  /** Since add and remove are proxied, we need an extra call to
      update the lists */
  virtual void update_list ();
};

#endif

/* EOF */
