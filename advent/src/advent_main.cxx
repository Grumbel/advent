//  $Id: advent_main.cxx,v 1.37 2004/01/14 02:28:24 grumbel Exp $
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

//#include <config.h>
#include <iostream>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/sdl.h>

#include "screen_manager.hxx"
#include "delta_manager.hxx"
#include "advent_main.hxx"

#include "sprite_drawable.hxx"
#include "scenario.hxx"
#include "display.hxx"
#include "scenario_layer.hxx"
#include "person.hxx"
#include "surface_colmap.hxx"
#include "layer_screen.hxx"
#include "screen_manager.hxx"
#include "button_layer.hxx"
#include "coin_layer.hxx"
#include "drawable_adv_obj.hxx"
#include "sprite_collideable.hxx"
#include "drawable_layer.hxx"
#include "rect_collideable.hxx"
#include "polygon_collideable.hxx"
#include "empty_adv_obj.hxx"
#include "mouse_cursor.hxx"
#include "surface_sprite.hxx"
#include "instant_adv_hook.hxx"
#include "delayed_adv_hook.hxx"
#include "key_map_handler.hxx"
#include "key_map.hxx"
#include "time_manager.hxx"
#include "inventory.hxx"
#include "adv_obj.hxx"
#include "resource_manager.hxx"
#include "font_sprite.hxx"
#include "rect_sprite.hxx"
#include "debug.hxx"
#include "person_gfx.hxx"
#include "fade_out_layer.hxx"

#include "adv_hook_smob.hxx"
#include "sprite_group.hxx"
#include "colmap_smob.hxx"
#include "layer_smob.hxx"
#include "sprite_smob.hxx"
#include "sprite.hxx"
#include "collideable_smob.hxx"
#include "drawable_smob.hxx"
#include "drawable.hxx"

// Static
extern "C" {
void scm_init_oop_goops_goopscore_module (void);
}

void init_app_advent_core ()
{
  std::cout << "------ scm_init_app_advent_core ----------" << std::endl;
  Advent::app.init_advent ();
}

// Use C namemangaling so that guile can find this function
extern "C" {
  void scm_init_advent_core_module ()
  {
    std::cout << "scm_init_app_advent_core" << std::endl;
    scm_register_module_xxx ("advent core", (void*)&init_app_advent_core);
  }
}

SCM advent_main_loop ()
{
  Advent::app.main_loop ();
  return SCM_UNSPECIFIED;
}

namespace Advent {

char*
AdventMain::get_title ()
{
  return "Advent V0.1.0";
}

void
AdventMain::parse_args (int argc, char* argv[])
{
  std::cout << "Parsing Arguments..." << std::endl;
}

void
AdventMain::register_guile_bindings ()
{
  std::cout << " *** Registering: start **************" << std::endl;

  gh_new_procedure0_0 ("advent:main-loop", &advent_main_loop);

  SpriteDrawable::register_guile_bindings ();
  Scenario::register_guile_bindings ();
  Display::register_guile_bindings ();
  ScenarioLayer::register_guile_bindings ();
  Person::register_guile_bindings ();
  SurfaceColMap::register_guile_bindings ();
  ScreenManager::register_guile_bindings ();
  LayerScreen::register_guile_bindings ();
  ButtonLayer::register_guile_bindings ();
  CoinLayer::register_guile_bindings ();
  DrawableAdvObj::register_guile_bindings ();
  SpriteCollideable::register_guile_bindings ();
  DrawableLayer::register_guile_bindings ();
  EmptyAdvObj::register_guile_bindings ();
  RectCollideable::register_guile_bindings ();
  PolygonCollideable::register_guile_bindings ();
  MouseCursor::register_guile_bindings ();
  SurfaceSprite::register_guile_bindings ();
  AdvHook::register_guile_bindings ();
  InstantAdvHook::register_guile_bindings ();
  DelayedAdvHook::register_guile_bindings ();
  AdvObj::register_guile_bindings ();

  KeyMapHandler::register_guile_bindings ();
  KeyMap::register_guile_bindings ();
  TimeManager::register_guile_bindings ();
  Inventory::register_guile_bindings ();
  ResourceManager::register_guile_bindings ();
  FontSprite::register_guile_bindings ();
  RectSprite::register_guile_bindings ();
  Debug::register_guile_bindings ();

  AdvHookSmob::register_guile_bindings ();
  ColMapSmob::register_guile_bindings ();
  LayerSmob::register_guile_bindings ();
  SpriteSmob::register_guile_bindings ();
  SpriteGroup::register_guile_bindings ();
  Sprite::register_guile_bindings ();
  CollideableSmob::register_guile_bindings ();
  DrawableSmob::register_guile_bindings ();
  Drawable::register_guile_bindings ();
  PersonGfx::register_guile_bindings ();
  FadeOutLayer::register_guile_bindings ();
  std::cout << " *** Registering: stop ***************" << std::endl;
}

int
AdventMain::main (int argc, char* argv[])
{
  if (argc != 2)
    {
      std::cout << "Usage: ./advent FILENAME" << std::endl;
      exit (EXIT_FAILURE);
    }

  scm_boot_guile (argc, argv,Advent::inner_main, 0);
  return 0;
}

void
AdventMain::init_advent ()
{
  std::cout << "Advent Final 0.1.0" << std::endl;

  // Debuging on
  SCM_DEVAL_P = 1;
  SCM_BACKTRACE_P = 1;
  SCM_RECORD_POSITIONS_P = 1;
  SCM_RESET_DEBUG_MODE;

#ifdef ADVENT_STATIC
  std::cout << "..:: Static binary ::.." << std::endl;
  scm_init_oop_goops_goopscore_module ();
#endif

  std::cout << "Registring Guile Bildings" << std::endl;
  register_guile_bindings ();

  try {
    std::cout << "CL_SetupCore::init" << std::endl;
    CL_SetupCore::init ();
    std::cout << "CL_SetupDisplay::init" << std::endl;
    CL_SetupDisplay::init ();
    CL_SetupSDL::init ();

  } catch (CL_Error& err) {
    std::cout << "CL_Error: " << err.message << std::endl;
  } catch (...) {
    std::cout << "Catched some exception" << std::endl;
  }
}

void
AdventMain::deinit_advent ()
{
  try {
    std::cout << "Shutting down Advent..." << std::endl;
    CL_SetupSDL::init ();
    CL_SetupDisplay::deinit ();
    CL_SetupCore::deinit ();
  } catch (CL_Error& err) {
    std::cout << "CL_Error: " << err.message << std::endl;
  } catch (...) {
    std::cout << "Catched some exception" << std::endl;
  }
}

void
AdventMain::main_loop()
{
  // FIXME: Directory handling is stupid and broken
  std::cout << "Loading Engine" << std::endl;
  //gh_load ("../../../src/guile/engine.scm");
  //gh_load (argv[1]);

  puts ("Entering Main loop");

  DeltaManager delta;

  // Main Loop
  while (!CL_Keyboard::get_keycode(CL_KEY_ESCAPE))
    {
      ScreenManager::instance()->update(delta.getset ());
      ScreenManager::instance()->draw();
      CL_System::keep_alive ();
    }
}

int
AdventMain::inner_main (void* closure, int argc, char* argv[])
{
  try {
    //parse_args (argc, argv);
    init_advent ();
    main_loop ();
    deinit_advent ();
  } catch (CL_Error& err) {
    std::cout << "CL_Error: " << err.message << std::endl;
  } catch (...) {
    std::cout << "Catched some exception" << std::endl;
  }

  return 0;
}

} // namespace Advent

/* EOF */
