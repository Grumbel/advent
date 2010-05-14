//  $Id: Scenario.cc,v 1.18 2001/07/02 10:27:13 grumbel Exp $
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

///
std::list<Scenario*> Scenario::scenario_list;
///
Scenario* Scenario::current;

void
Scenario::set_current_scenario (std::string name)
{
  for (std::list<Scenario*>::iterator i = scenario_list.begin ();
       i != scenario_list.end ();
       i++)
    {
      if ((*i)->get_name () == name)
	{
	  set_current_scenario (*i);
	  return;
	}
    }
  assert (false);
}

void
Scenario::set_current_scenario (Scenario* scenario)
{
  assert (scenario);
  current = scenario;
}

Scenario::Scenario (SCM arg_name,
		    std::string arg_background, std::string arg_colmap,
		    std::list<AdventObj*> arg_objects,
		    bool arg_with_guy) 
  : is_init (false)
{
  if (SCM_STRINGP (arg_name))
    name = SCM_CHARS (arg_name);
  else
    scm_object = arg_name;

  colmap_name = arg_colmap;
  background_name = arg_background;

  objects = arg_objects;

  if (arg_with_guy)
    this->objects.push_back (the_guy);
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
Scenario::draw ()
{
  if (!is_init) init ();
  
  int x_offset = -int(the_guy->get_x_pos ()) + CL_Display::get_width ()/2;
  int y_offset = -int(the_guy->get_y_pos ()) + CL_Display::get_height ()/2;
  
  if (background->get_width () + x_offset < CL_Display::get_width ())
    x_offset = CL_Display::get_width () - background->get_width ();

  if (background->get_height () + y_offset < CL_Display::get_height ())
    y_offset = CL_Display::get_height () - background->get_height ();

  if (x_offset > 0)
    x_offset = 0;

  if (y_offset > 0)
    y_offset = 0;

  background->draw (x_offset, y_offset);

  view.x_offset = x_offset;
  view.y_offset = y_offset;
  
  if (CL_Mouse::middle_pressed ())
    {
      std::cout << ";" 
		<< CL_Mouse::get_x() - x_offset << " " << CL_Mouse::get_y() - y_offset << " " 
		<< Scenario::current->get_colmap ()->get_pixel (CL_Mouse::get_x (),
								CL_Mouse::get_y ())
		<< std::endl;
      while (CL_Mouse::middle_pressed ())
	CL_System::keep_alive ();
    }

  // z-Sort all objects
  objects.sort (AdventObj_less ());

  std::list<Drawable*> draw_lst;

  for (std::list<AdventObj*>::iterator i = objects.begin ();
       i != objects.end (); ++i)
    {
      draw_lst.push_back (*i);
    }

  for (std::list<Drawable*>::iterator i = drawables.begin (); 
       i != drawables.end (); ++i)
    {
      draw_lst.push_back (*i);
    }

  draw_lst.sort (AdventObj_less ());

  for (std::list<Drawable*>::iterator i = draw_lst.begin (); 
       i != draw_lst.end (); ++i)
    {
      (*i)->draw_world (x_offset, y_offset);
    }
}

void
Scenario::update (float delta)
{
  if (!is_init) init ();

  for (std::list<AdventObj*>::iterator i = objects.begin (); 
       i != objects.end (); i++)
    {
      (*i)->update (delta);
    }

  for (std::list<Drawable*>::iterator i = drawables.begin (); 
       i != drawables.end (); ++i)
    {
      (*i)->update (delta);
    }

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

AdventObj* 
Scenario::get_object (int x, int y)
{
  //std::cout << "Objects: " << objects.size() << std::endl;
  AdventObj* obj = 0;
  for (std::list<AdventObj*>::iterator i = objects.begin (); 
       i != objects.end (); i++)
    {
      if ((*i)->is_at (x, y))
	obj = (*i);
    }
  return obj;
}

void 
Scenario::add (AdventObj* obj)
{
  objects.push_back (obj);
}

void 
Scenario::add (Drawable* obj)
{
  std::cout << "Adding drawable" << std::endl;
  drawables.push_back (obj);
}

void
Scenario::remove (AdventObj* obj)
{
  std::list<AdventObj*>::iterator obj_iter;
  obj_iter = std::find (objects.begin (), objects.end (), obj);
  if (obj_iter != objects.end ())
    objects.erase (obj_iter);
}

/* EOF */
