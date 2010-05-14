//  $Id: Inventory.cc,v 1.11 2001/06/28 08:32:23 grumbel Exp $
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

#include "Advent.hh"
#include "Coin.hh"
#include "AdventObjSmob.hh"
#include "Inventory.hh"

Inventory* inventory;

Inventory::Inventory ()
  : icon ("inventory", app.get_resource ()),
    icon_h ("inventory_h", app.get_resource ())
{
  visible = false;
  objects.resize (6 * 4);
  for (std::vector<AdventObj*>::iterator i = objects.begin ();
       i != objects.end (); ++i)
    {
      (*i) = NULL;
    }
}

void 
Inventory::add (AdventObj* obj)
{
  for (std::vector<AdventObj*>::iterator i = objects.begin ();
       i != objects.end (); ++i)
    {
      if (*i == NULL)
	{
	  *i = obj;
	  break;
	}
    }
}

bool 
Inventory::has (AdventObj* obj)
{
  for (std::vector<AdventObj*>::iterator i = objects.begin ();
       i != objects.end (); ++i)
    {
      if ((*i) == obj)
	return true;
    }  
  return false;
}

void 
Inventory::remove (AdventObj* obj)
{
  for (std::vector<AdventObj*>::iterator i = objects.begin ();
       i != objects.end (); ++i)
    {
      if ((*i) == obj)
	*i = NULL;
    }
}

void 
Inventory::draw ()
{
  if (!visible)
    {
      icon.put_screen (10, 400);
      
      if (mouse_over (CL_Mouse::get_x (), CL_Mouse::get_y ()))
	icon_h.put_screen (10, 400);
      
      return;
    }

  int size = 80;
  CL_Display::fill_rect (size-10, size-10,
			 640-size+10, 480-size+10,
			 0.0, 0.0, 0.0, 0.5);

  int width = 6;
  int height = 4;

  for (int y = 0; y < height; ++y)
    for (int x = 0; x < width; ++x)
      {
	if (CL_Mouse::get_x () > x*size + size
	    && CL_Mouse::get_x () < x*size + size + size
	    && CL_Mouse::get_y () > y*size + size 
	    && CL_Mouse::get_y () < y*size + size + size)
	  {
	    CL_Display::fill_rect (x*size + 80, y*size + 80, 
				   x*size + size-1 + 80, y*size + size-1 + 80,
				   1.0, 1.0, 1.0, 0.8);	  
	  }
	else
	  {
	    CL_Display::fill_rect (x*size + 80, y*size + 80, 
				   x*size + size-1 + 80, y*size + size-1 + 80,
				   1.0, 1.0, 1.0, 0.5);	  
	  }
	
	int index = width * y + x;
	if (objects[index] != NULL)
	  objects[index]->draw_inventory (x * size + size + size/2, 
					  y * size + size + size/2);
      }
}

void 
Inventory::update (float delta)
{
  if (visible)
    {
      if (CL_Mouse::get_x () < 10 || CL_Mouse::get_x () > 630
	  || CL_Mouse::get_y () < 10 || CL_Mouse::get_y () > 470)
	visible = false;

      if (CL_Mouse::left_pressed ())
	{
	  int size = 80;
	  int width = 6;
	  int height = 4;

	  for (int y = 0; y < height; ++y)
	    for (int x = 0; x < width; ++x)
	      {
		if (CL_Mouse::get_x () > x*size + size
		    && CL_Mouse::get_x () < x*size + size + size
		    && CL_Mouse::get_y () > y*size + size 
		    && CL_Mouse::get_y () < y*size + size + size)
		  {
		    int index = width * y + x;
		    coin->set_current_obj(objects[index]);
		  }
	      }
	  visible = false;
	}
    }
}

void 
Inventory::init ()
{
  puts ("Registering Inventory functions...");
  gh_new_procedure1_0 ("c:inventory:add", &Inventory::add);
  gh_new_procedure1_0 ("c:inventory:remove", &Inventory::remove);
  gh_new_procedure1_0 ("c:inventory:has", &Inventory::has);
  gh_new_procedure0_0 ("c:inventory:show", &Inventory::static_show);
  //gh_new_procedure0_0 ("inventory:hide", &Inventory::static_show);
}

void
Inventory::show ()
{
  puts ("Inventory showing show...");
  inventory->visible = true;
}

SCM 
Inventory::static_show ()
{
  inventory->show ();
  return SCM_UNSPECIFIED;
}

SCM 
Inventory::add (SCM obj)
{
  SCM smob = gh_call1 (gh_lookup ("adv:bind"), obj);
  AdventObjP* advobj = reinterpret_cast<AdventObjP*>(SCM_CDR (smob));
  GuileAdventObj* guile_obj = dynamic_cast<GuileAdventObj*>(advobj->obj);

  inventory->add (guile_obj);

  return SCM_UNSPECIFIED;
}

SCM 
Inventory::has (SCM obj)
{
  SCM smob = gh_call1 (gh_lookup ("adv:bind"), obj);
  AdventObjP* advobj = reinterpret_cast<AdventObjP*>(SCM_CDR (smob));
  GuileAdventObj* guile_obj = dynamic_cast<GuileAdventObj*>(advobj->obj);

  bool ret = inventory->has (guile_obj);

  if (ret)
    return SCM_BOOL_T;
  else
    return SCM_BOOL_F;
}

SCM 
Inventory::remove (SCM obj)
{
  SCM smob = gh_call1 (gh_lookup ("adv:bind"), obj);
  AdventObjP* advobj = reinterpret_cast<AdventObjP*>(SCM_CDR (smob));
  GuileAdventObj* guile_obj = dynamic_cast<GuileAdventObj*>(advobj->obj);

  inventory->remove (guile_obj);

  return SCM_UNSPECIFIED;
}

bool  
Inventory::mouse_over (int x_pos, int y_pos)
{
  if (visible)
    return true;
  else
    return
      x_pos > 10  && x_pos < 10 + int(icon.get_width ())
      && y_pos > 400 && y_pos < 400 + (int) icon.get_height ();
}

bool 
Inventory::on_mouse_click (const CL_Key& key)
{
  std::cout << "INVENTORY: GOT CLICK" << key.id << std::endl;
  if (key.id == CL_MOUSE_LEFTBUTTON || key.id == 0)
    {
      std::cout << "Got click event..." << std::endl;
      show ();
      return true;
    }
  
  // We eat all clicks so we avoid confusion
  return true;
}

float 
Inventory::priority ()
{
  if (!visible)
    return 1.0f;
  else
    return 100.0f;
}

/* EOF */
