//  $Id: Advent.cc,v 1.36 2001/08/21 20:38:43 grumbel Exp $
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

#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <ClanLib/png.h>
#include <ClanLib/jpeg.h>

// Static
extern "C" {
void scm_init_oop_goops_goopscore_module (void);
}
#include <guile/gh.h>

#include <sys/stat.h>
#include <sys/types.h>

#include "Interpreter.hh"
#include "Scenario.hh"
#include "Coin.hh"
#include "System.hh"
#include "Advent.hh"
#include "Font.hh"
#include "AdventObjSmob.hh"
#include "ScenarioSmob.hh"
#include "Dialog.hh"
#include "DialogManager.hh"
#include "Inventory.hh"
#include "Guy.hh"
#include "AdvHook.hh"
#include "TimeManager.hh"
#include "Animation.hh"
#include "ClickManager.hh"
#include "DeltaManager.hh"
#include "View.hh"
#include "FadeOut.hh"
#include "KeyboardManager.hh"

Advent app;

InputMode input_mode;

 ClickManager click_manager;
// Wrapper to call the member func
void inner_main (void* closure, int argc, char* argv[])
{
  app.inner_main (closure, argc, argv);
}

Advent::Advent ()
{
  input_mode = MODE_NORMAL;
}

char* 
Advent::get_title ()
{
  return "Advent - Prototype";
}

int
Advent::main (int argc, char* argv[])
{
  scm_boot_guile (argc, argv,::inner_main, 0);
  return 0;
}

void   
Advent::inner_main (void* closure, int argc, char* argv[])
{
  std::string game_init_file = "games/retriever/objects.scm";
  bool fullscreen = false;
  
  if (argc == 2)
    {
      game_init_file = argv[1];
    }

  // Debuging on
  SCM_DEVAL_P = 1;
  SCM_BACKTRACE_P = 1;
  SCM_RECORD_POSITIONS_P = 1;
  SCM_RESET_DEBUG_MODE;

  // This is used for the static binary
#ifdef ADVENT_STATIC
  std::cout << "..:: Static binary ::.." << std::endl;
  scm_init_oop_goops_goopscore_module ();
#endif

  // Ugly... as the rest of the code..
  the_view = new View ();

  

  //std::cout << "Loading guile code..." << std::endl;
  AdvHook::init ();
  FadeOut::init ();
  ClickManager::init ();
  AdventObjSmob::init ();
  ScenarioSmob::init ();
  Dialog::init ();
  DialogManager::init ();
  Inventory::init ();
  Guy::init_guile ();
  TimeManager::init ();
  DrawableSmob::init ();
  Animation::init ();
  System::init ();
  KeyboardManager::init ();
      
  //std::cout << "Loading guile code...done" << std::endl;



  if (argc == 2)
    {
      if (strcmp (argv[1], "--fullscreen") == 0)
	{
	  fullscreen = true;
	}
    }
  
  try 
    {
      //std::cout << "Advent: Init ClanLib..." << std::endl;
      CL_SetupCore::init ();
      CL_SetupDisplay::init ();
      CL_SetupPNG::init ();
      CL_SetupJPEG::init ();
  
      CL_Display::set_videomode (640, 480, 16, fullscreen, false);

      CL_Display::clear_display ();
      CL_Display::flip_display ();

      resource = new CL_ResourceManager("data/resources.scr", false);

      DialogManager dialog_manager;

      {
	std::string advent_save_path;
	
	char* home = getenv ("HOME");
	if (home) 
	  {
	    advent_save_path = home;
	    advent_save_path += "/.advent/";
	  }
	else
	  {
	    std::cout << "Error: Couldn't get $HOME" << std::endl;
	    exit (EXIT_FAILURE);
	  }

	if (mkdir (advent_save_path.c_str (),
		   S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP) != 0)
	  {
	    std::cout << "Failed to make: " << advent_save_path << std::endl;
	  }
      }
      
      //Scenario scenario;
      coin = new Coin ();

      // FIXME: wrong place to create this...
      //the_guy = new Guy (SCM_BOOL_F);

      gh_load ("engine/adventure.scm");
      gh_load (game_init_file.c_str ());

      int time = CL_System::get_time ();
      int count = 0;
      char str[256] = {"Calculation"};

      //ClickManager click_manager;
      
      inventory = new Inventory ();

      click_manager.add (inventory);
      click_manager.add (coin);
      click_manager.add (&dialog_manager);

      
      assert (Scenario::get_current ());

      the_view->follow(Guy::get_current ());

      /** Main Loop */
      DeltaManager delta_manager;
      while (CL_Keyboard::get_keycode (CL_KEY_ESCAPE) == 0)
	{	  
	  /* FIXME: inputhandling should be somewhere else... */
	  if (CL_Keyboard::get_keycode (CL_KEY_G)) 
	    {
	      while (CL_Keyboard::get_keycode (CL_KEY_G))
		CL_System::keep_alive ();
	      std::cout << "Garbage Collecting..." << std::endl;
	      scm_gc ();
	    }

	  if (CL_Keyboard::get_keycode (CL_KEY_SPACE)) 
	    {
	      while (CL_Keyboard::get_keycode (CL_KEY_SPACE))
		CL_System::keep_alive ();
	      interpreter.launch ();
	    }

	  if (CL_Keyboard::get_keycode (CL_KEY_F6)) 
	    {
	      while (CL_Keyboard::get_keycode (CL_KEY_F6))
		CL_System::keep_alive ();
	      gh_eval_str ("(adv:quick-save)");
	    }

	  if (CL_Keyboard::get_keycode (CL_KEY_F5)) 
	    {
	      while (CL_Keyboard::get_keycode (CL_KEY_F5))
		CL_System::keep_alive ();
	      gh_eval_str ("(adv:quick-load)");
	    }

	  float delta = delta_manager.getset ();

	  the_view->update (delta);
	  Scenario::get_current ()->update (delta);
	  dialog_manager.update (delta);
	  coin->update (delta);
	  dialog.update (delta);
	  inventory->update (delta);
	  TimeManager::update (delta);

	  the_view->draw ();
	  //Scenario::current->draw (the_view);
	  
	  coin->draw ();
	  inventory->draw ();
	  font ("font")->print_left (0, 0, str);
	  dialog.draw ();


	  if (count > 9)
	    {
	      int time_diff = CL_System::get_time () - time;
	      //std::cout << "fps: " << 10000.0 / time_diff << std::endl;
	      sprintf (str, "fps: %f", 10000.0 / time_diff);
	      //std::cout << "Str: " << str << std::endl;
	      count = 0;
	      time = CL_System::get_time ();
	    }
	  dialog_manager.draw ();	  
	  FadeOut::update (delta);
	  FadeOut::draw ();
	  CL_Display::flip_display ();
	  count++;
	  CL_System::keep_alive ();
	  CL_System::sleep (20);
	}

      CL_SetupJPEG::deinit ();
      CL_SetupPNG::deinit ();
      //CL_SetupDisplay::deinit ();
      CL_SetupCore::deinit ();
    }
  
  catch (CL_Error err)
    {
      std::cout << "CL_Error: " << err.message << std::endl;
    }
}

/* EOF */
