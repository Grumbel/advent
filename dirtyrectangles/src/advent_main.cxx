//  $Id$
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#include <guile/gh.h>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/sdl.h>

//#include "scripting/display.hxx"
//#include "scripting/graphics.hxx"
//#include "scripting/input.hxx"

#include "view.hxx"
#include "timeable_manager.hxx"
#include "drawable_manager.hxx"
#include "clickable_manager.hxx"
#include "resource_manager.hxx"
#include "advent_main.hxx"

extern "C" void SWIG_init(void);

namespace Advent {

AdventMain::AdventMain()
{
  
}

AdventMain::~AdventMain()
{
  
}

int
AdventMain::main(int argc, char** argv)
{
  bool launch_shell = false;
  bool use_opengl = false;

  CL_CommandLine argp;
  argp.add_usage("[SCRIPT]");
  argp.add_doc("Advent - Graphic Adventure Game Engine");

  argp.add_option('o', "opengl", "", "Use OpenGL");
  argp.add_option('s', "shell", "", "Launch Shell");
  argp.parse_args(argc, argv);

  while (argp.next())
    {
      switch(argp.get_key())
        {
        case CL_CommandLine::REST_ARG:
          break;
        case 's':
          launch_shell = true;
          break;
        case 'o':
          use_opengl = true;
          break;
        default:
          break;
        }
    }

  scm_init_guile();
  SWIG_init();
  
  try {
    CL_SetupCore::init();
    CL_SetupDisplay::init();

    if (use_opengl)
      CL_SetupGL::init();
    else
      CL_SetupSDL::init();

    resources = new CL_ResourceManager("../data/advent.xml");
    timeable_manager  = new TimeableManager();
    drawable_manager  = new DrawableManager();
    clickable_manager = new ClickableManager();

    gh_eval_str("(debug-enable 'debug)"
                "(debug-enable 'backtrace)"
                "(read-enable  'positions)");
    
    std::cout << "Loading script..." << std::endl;
    if (launch_shell)
      scm_shell(0, NULL);
    else
      scm_c_primitive_load("advent.scm");
    std::cout << "Loading script...done" << std::endl;    

    if (!View::current())
      {
        std::cout << "No view given" << std::endl;
      }
    else
      {
        unsigned int last_time = CL_System::get_time();
        while(!CL_Keyboard::get_keycode(CL_KEY_ESCAPE))
          {
            float delta = (CL_System::get_time() - last_time)/1000.0f;

            //CL_Display::clear();
            View::current()->draw();
            View::current()->update(50);

            {
              TimeableManager::Objects tmp = timeable_manager->objects;
              for (TimeableManager::Objects::iterator i = tmp.begin(); 
                   i != tmp.end(); ++i)
                {
                  (*i)->update(delta);
                }
            }

            if (CL_Keyboard::get_keycode(CL_KEY_D))
              {
                SCM func = gh_lookup("advent:repl");
                scm_call_0(func);
                
                while (CL_Keyboard::get_keycode(CL_KEY_D))
                  CL_System::keep_alive();
              }

            CL_System::sleep(10);
            CL_System::keep_alive();
          }
      }

    delete clickable_manager;
    delete drawable_manager;
    delete timeable_manager;
    delete resources;

    if (use_opengl)
      CL_SetupGL::deinit();
    else
      CL_SetupSDL::deinit();

    CL_SetupDisplay::deinit();
    CL_SetupCore::deinit();
  } catch (CL_Error& error) {
    std::cout << "Error: " << error.message << std::endl;
  }
  return 0;
}

} // namespace Advent

/* EOF */
