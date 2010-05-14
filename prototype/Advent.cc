//  $Id: Advent.cc,v 1.1 2000/12/28 20:00:48 grumbel Exp $
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

#include <ClanLib/png.h>
#include <ClanLib/jpeg.h>
#include <guile/gh.h>

#include "Scenario.hh"
#include "Coin.hh"
#include "Advent.hh"
#include "Font.hh"
#include "AdventObjSmob.hh"

Advent app;
Inventory inventory;

Scenario* current_scenario;

// Wrapper to call the member func
void inner_main (void* closure, int argc, char* argv[])
{
  app.inner_main (closure, argc, argv);
}

Advent::Advent ()
{
}

char* 
Advent::get_title ()
{
  return "Advent - Prototype";
}

int
Advent::main (int argc, char* argv[])
{
  std::cout << "Starting guile..." << std::endl;
  scm_boot_guile (argc, argv,::inner_main, 0);
  std::cout << "this should never be reached..." << std::endl;
  return 0;
}

void   
Advent::inner_main (void* closure, int argc, char* argv[])
{
  bool fullscreen = false;
  std::cout << "Loading guile code..." << std::endl;
  AdventObjSmob::init ();

  std::cout << "Loading guile code...done" << std::endl;

  if (argc == 2)
    {
      if (strcmp (argv[1], "--fullscreen") == 0)
	{
	  fullscreen = true;
	}
    }
  
  try 
    {
      CL_SetupCore::init ();
      CL_SetupCore::init_display ();
      CL_SetupPNG::init ();
      CL_SetupJPEG::init ();
  
      CL_Display::set_videomode (640, 480, 16, fullscreen, false);

      resource = CL_ResourceManager::create("data/resources.scr", false);

      Scenario scenario;
      Coin coin (&scenario);

      current_scenario = &scenario;

      gh_load ("guile/adventure.scm");

      int time = CL_System::get_time ();
      int count = 0;
      char str[256] = {"Calculation"};

      gh_eval_str("(let ((obj (advent:makeobj \"testobj\" \"takeme\" 400 100 100))) (println obj))");

      while (CL_Keyboard::get_keycode (CL_KEY_ESCAPE) == 0)
	{
	  //std::cout << "Looping..." << std::endl;
	  //CL_Display::fill_rect (CL_Mouse::get_x (), CL_Mouse::get_y (),
	  //CL_Mouse::get_x () + 16, CL_Mouse::get_y () + 16,
	  //1.0, 1.0, 1.0, 1.0);
	  //CL_Display::clear_display (1.0, 1.0, 0.0, 0.01);
	  scenario.update ();
	  coin.update ();
	  scenario.draw ();
	  coin.draw ();
	  font ("font")->print_left (0, 0, str);

	  if (count > 9)
	    {
	      int time_diff = CL_System::get_time () - time;
	      //std::cout << "fps: " << 10000.0 / time_diff << std::endl;
	      sprintf (str, "fps: %f", 10000.0 / time_diff);
	      //std::cout << "Str: " << str << std::endl;
	      count = 0;
	      time = CL_System::get_time ();
	    }
	  CL_Display::flip_display ();
	  count++;
	  CL_System::keep_alive ();
	}

      CL_SetupJPEG::deinit ();
      CL_SetupPNG::deinit ();
      CL_SetupCore::deinit_display ();
      CL_SetupCore::deinit ();
    }
  
  catch (CL_Error err)
    {
      std::cout << "CL_Error: " << err.message << std::endl;
    }
}

/* EOF */
