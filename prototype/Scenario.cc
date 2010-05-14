//  $Id: Scenario.cc,v 1.25 2001/07/15 21:00:31 grumbel Exp $
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

#include <algorithm>
#include "View.hh"
#include "Advent.hh"
#include "GuileAdventObj.hh"
#include "Guy.hh"
#include "Position.hh"
#include "Scenario.hh"
#include "Drawable.hh"

struct adv_is_removeable
{
  bool operator ()  (AdventObj* obj)
  {
    if (obj == 0)
      return true;
    else
      return false;
  }
};


///
std::list<Scenario*> Scenario::scenario_list;
///

Scenario::Scenario (SCM arg_name,
		    std::string arg_background, std::string arg_colmap,
		    std::list<AdventObj*> arg_objects,
		    bool arg_with_guy) 
  : is_init (false)
{
  std::cout << "Creating scenario: " << this << std::endl;

  adv_list_lock = 0;
  drawable_list_lock = 0;
  
  if (SCM_STRINGP (arg_name))
    name = SCM_CHARS (arg_name);
  else
    {
      scm_protect_object (scm_object);
      scm_object = arg_name;
    }
  
  colmap_name = arg_colmap;
  background_name = arg_background;

  objects = arg_objects;

  // FIXME: Ugggllyyyy...
  /*if (arg_with_guy)
    this->objects.push_back (Guy::get_current ());
  */
}

void
Scenario::init ()
{
  if (is_init)
    {
      std::cout << "Warrning: Scenario:" << name << ":already init!" << std::endl;
    }
  else
    {
      background = new Background (background_name);
      
      if (!colmap_name.empty ())
	colmap = new CollisionMap (colmap_name);
      else
	colmap = NULL;

      is_init = true;
    }
}

Scenario::~Scenario ()
{
}
  
void
Scenario::draw (View* view)
{
  if (!is_init) init ();
  
  int x_offset = -int(Guy::get_current ()->get_x_pos ()) + CL_Display::get_width ()/2;
  int y_offset = -int(Guy::get_current ()->get_y_pos ()) + CL_Display::get_height ()/2;
  
  if (background->get_width () + x_offset < CL_Display::get_width ())
    x_offset = CL_Display::get_width () - background->get_width ();

  if (background->get_height () + y_offset < CL_Display::get_height ())
    y_offset = CL_Display::get_height () - background->get_height ();

  if (x_offset > 0)
    x_offset = 0;

  if (y_offset > 0)
    y_offset = 0;

  background->draw (x_offset, y_offset);

  view->x_offset = x_offset;
  view->y_offset = y_offset;
  
  if (CL_Mouse::middle_pressed ())
    {
      std::cout << ";" 
		<< CL_Mouse::get_x() - x_offset << " " << CL_Mouse::get_y() - y_offset << " " 
		<< Scenario::get_current ()->get_colmap ()->get_pixel (CL_Mouse::get_x (),
								CL_Mouse::get_y ())
		<< std::endl;
      while (CL_Mouse::middle_pressed ())
	CL_System::keep_alive ();
    }

  // z-Sort all objects
  objects.sort (AdventObj_less ());

  std::list<Drawable*> draw_lst;

  //draw_lst.push_back(Guy::get_current ());

  // Add all advent objects to the drawable list
  ++adv_list_lock;
  for (std::list<AdventObj*>::iterator i = objects.begin ();
       i != objects.end (); ++i)
    {
      if (*i) draw_lst.push_back (*i);
    }
  --adv_list_lock;

  // Draw all drawables to the draw list
  ++drawable_list_lock;
  for (std::list<Drawable*>::iterator i = drawables.begin (); 
       i != drawables.end (); ++i)
    {
      if (*i) draw_lst.push_back (*i);
    }
  --drawable_list_lock;

  // Sort the Scene
  draw_lst.sort (AdventObj_less ());

  // Draw thhe scene
  ++drawable_list_lock;
  for (std::list<Drawable*>::iterator i = draw_lst.begin (); 
       i != draw_lst.end (); ++i)
    {
      if (*i) (*i)->draw_world (x_offset, y_offset);
    }
  --drawable_list_lock;
}

void
Scenario::update (float delta)
{
  //std::cout << "Update: " << delta << std::endl;
  //Guy::get_current ()->update (delta);
  //std::cout << "Updating scenario: " << this << std::endl;
  if (!is_init) init ();

  ++adv_list_lock;
  for (std::list<AdventObj*>::iterator i = objects.begin (); 
       i != objects.end (); i++)
    {
      if (*i) (*i)->update (delta);
    }
  --adv_list_lock;

  //std::cout << "AdvLockCount: " << adv_list_lock << std::endl;
  if (need_list_update) update_list ();

  ++drawable_list_lock;
  for (std::list<Drawable*>::iterator i = drawables.begin (); 
       i != drawables.end (); ++i)
    {
      if (*i) (*i)->update (delta);
    }
  --drawable_list_lock;

  drawables.remove_if (is_removeable ());

  background->update (delta);
  if (colmap)
    colmap->update (delta);
}

CollisionMap* 
Scenario::get_colmap ()
{
  if (!is_init) init ();

  return colmap;
}

/** FIXME: Do we use world or mouse CO's here? */
AdventObj* 
Scenario::get_object (int x, int y)
{
  //std::cout << "Objects: " << objects.size() << std::endl;
  AdventObj* obj = 0;
  for (std::list<AdventObj*>::iterator i = objects.begin (); 
       i != objects.end (); i++)
    {
      if (*i && (*i)->is_at (x, y))
	obj = (*i);
    }
  return obj;
}

void 
Scenario::add (Drawable* obj)
{
  //std::cout << "uhAOEUAOEUAOETUTsnotehu Adding drawable" << std::endl;
  if (drawable_list_lock == 0)
    drawables.push_back (obj);
  else
    std::cout << "DrawableList is currently locked: " << adv_list_lock << std::endl;
}

void 
Scenario::add (AdventObj* obj)
{
  need_list_update = true;
  adv_add_list.push_back (obj);
}

void
Scenario::remove (AdventObj* obj)
{
  need_list_update = true;
  std::list<AdventObj*>::iterator obj_iter;
  obj_iter = std::find (objects.begin (), objects.end (), obj);
  
  if (obj_iter != objects.end ()) 
    *obj_iter = 0;
  else
    {
      std::cout << "Scenario:remove: Couldn't find object: " << obj << std::endl;
      for (std::list<AdventObj*>::iterator i = objects.begin ();
	   i != objects.end (); ++i)
	{
	  std:: cout << "  Obj: " << **i << std::endl;
	}
    }
}

void 
Scenario::update_list ()
{
  std::cout << "Updating the list " << std::endl;
  objects.remove_if (adv_is_removeable ());

  for (std::list<AdventObj*>::iterator i = adv_add_list.begin ();
       i != adv_add_list.end (); ++i)
    {
      objects.push_back (*i);
    }
  adv_add_list.clear ();

  need_list_update = false;
}

Scenario*
Scenario::get_current ()
{
  return Guy::get_current ()->get_scenario ();
}

/* EOF */
