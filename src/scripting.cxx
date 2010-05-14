//  $Id$
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include <iostream>
#include <assert.h>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/sdl.h>

#include "view.hxx"
#include "timeable_manager.hxx"
#include "sprite_drawable.hxx"
#include "scroll_timeable.hxx"
#include "scm_functor.hxx"
#include "resource_manager.hxx"
#include "rect_drawable.hxx"
#include "rect_clickable.hxx"
#include "person_timeable.hxx"
#include "mouse_timeable.hxx"
#include "font_drawable.hxx"
#include "drawable_manager.hxx"
#include "drawable_group.hxx"
#include "drawable_clickable.hxx"
#include "detachable_drawable.hxx"
#include "detachable_clickable.hxx"
#include "depth_map.hxx"
#include "depth_drawable.hxx"
#include "clickable_manager.hxx"
#include "clickable_group.hxx"
#include "clickable.hxx"
#include "callback_timeable.hxx"

using namespace Advent;

/** Creates a CL_DisplayWindow with the given width and height */
void
display_init(const char* title, int width, int height, bool fullscreen)
{
  CL_SetupCore::init();
  CL_SetupDisplay::init();
  
  if (false) //use_opengl
    CL_SetupGL::init();
  else
    CL_SetupSDL::init();
  
  resources = new CL_ResourceManager("../data/advent.xml");
  timeable_manager  = new TimeableManager();
  drawable_manager  = new DrawableManager();
  clickable_manager = new ClickableManager();
  
  new CL_DisplayWindow(title, width, height, fullscreen);
}

/** Destroys the current CL_DisplayWindow */
void
display_deinit()
{
  delete clickable_manager;
  delete drawable_manager;
  delete timeable_manager;
  delete resources;
  
  if (false) // use_opengl)
    CL_SetupGL::deinit();
  else
    CL_SetupSDL::deinit();
  
  CL_SetupDisplay::deinit();
  CL_SetupCore::deinit();
}

void
display_main_loop()
{
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

          CL_System::sleep(10);
          CL_System::keep_alive();
        }
    }
}

void display_hide_system_cursor()
{
  CL_Mouse::hide();
}

void display_show_system_cursor()
{
  CL_Mouse::show();
}

ClickableGroup*
clickable_scene_by_id(int id)
{
  ClickableGroup* scene = dynamic_cast<ClickableGroup*>(clickable_manager->get_by_id(id));
  if (!scene)
    {
      std::cout << "Not a ClickableGroup: " << id << std::endl;
      // FIXME: scm_backtrace();
    }
  return scene;
}

int clickable_scene_create()
{
  ClickableGroup* scene = new ClickableGroup();
  return clickable_manager->add(scene);
}

int drawable_clickable_create(int drawable_id)
{
  Clickable* obj = new DrawableClickable(drawable_manager->get_by_id(drawable_id));
  return clickable_manager->add(obj);
}

int rect_clickable_create(int x1, int y1, int x2, int y2)
{
  Clickable* obj        = new RectClickable(CL_Rect(x1, y1, x2, y2));
  return clickable_manager->add(obj);
}

int input_add_drawable_clickable(int scene_id, int drawable_id)
{
  //return clickable_manager->add(obj);
  return 0;
}

void input_add_clickable(int scene_id, int clickable_id)
{
  ClickableGroup* group = clickable_scene_by_id(scene_id);
  group->add_clickable(clickable_manager->get_by_id(clickable_id));
}

void clickable_grab_input(int clickable_id)
{
  Clickable* clickable = clickable_manager->get_by_id(clickable_id);
  View::current()->grab_input(clickable);
}

void clickable_release_input()
{
  View::current()->release_input();
}

int detachable_clickable_create()
{
  return clickable_manager->add(new DetachableClickable());
}

void detachable_clickable_set(int clickable_id, int target_id)
{
  DetachableClickable* clickable 
    = dynamic_cast<DetachableClickable*>(clickable_manager->get_by_id(clickable_id));

  if (clickable)
    clickable->set_clickable(clickable_manager->get_by_id(target_id));
  else
    {
      std::cout << "Error: not a DetachableClickable: " << clickable_id << std::endl;
    }
}

void detachable_clickable_set_offset(int clickable_id, int x, int y)
{
  DetachableClickable* clickable 
    = dynamic_cast<DetachableClickable*>(clickable_manager->get_by_id(clickable_id));

  if (clickable)
    clickable->set_offset(CL_Point(x, y));
  else
    {
      std::cout << "Error: not a DetachableClickable: " << clickable_id << std::endl;
    }
}

using namespace Advent;

View* view_create(int scene_id, int clickable_id)
{
  View* view = new View(drawable_manager->get_by_id(scene_id),
                        dynamic_cast<ClickableGroup*>(clickable_manager->get_by_id(clickable_id)));
  return view;
}

void view_set_pos(View* view, int x, int y)
{
  view->set_pos(CL_Point(x, y));
}

void  view_set_drawables(View* view,  int id)
{
  view->set_drawable(drawable_manager->get_by_id(id));
}

void  view_set_clickables(View* view, int id)
{
  view->set_clickable_group(dynamic_cast<ClickableGroup*>(clickable_manager->get_by_id(id)));
}

DrawableGroup* scene_by_id(int id)
{
  DrawableGroup* scene = dynamic_cast<DrawableGroup*>(drawable_manager->get_by_id(id));
  return scene;
}

Advent::Drawable*
drawable_by_id(int id)
{
  return (drawable_manager->get_by_id(id));
}

int scene_create()
{
  DrawableGroup* scene = new DrawableGroup();
  return drawable_manager->add(scene);
}

int font_drawable_create(int x, int y, const char* font, const char* text)
{
  return drawable_manager->add(new FontDrawable(CL_Point(x, y), font, text));
}

int sprite_drawable_create(int x, int y, const char* name)
{
  try {
    Advent::Drawable* drawable = new SpriteDrawable(CL_Sprite(name, resources), CL_Point(x, y));
    return drawable_manager->add(drawable);
  } catch(CL_Error& err) {
    std::cout << "Error: " << err.message << std::endl;
    return -1;
  }
}

int rect_drawable_create(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
{
  return drawable_manager->add(new RectDrawable(CL_Rect(x1, y1, x2, y2),
                                                CL_Color(r, g, b, a)));
}

int detachable_drawable_create()
{
  return drawable_manager->add(new DetachableDrawable());
}

void detachable_drawable_set(int detachable_id, int drawable_id)
{
  DetachableDrawable* detachable = dynamic_cast<DetachableDrawable*>(drawable_by_id(detachable_id));
  if (detachable)
    detachable->set_drawable(drawable_by_id(drawable_id));
  else
    {
      std::cout << "Error: Drawable " << detachable_id << " isn't a DetachableDrawable" << std::endl;
      //FIXME:scm_backtrace();
    }
}

int  detachable_drawable_get(int detachable_id)
{
  DetachableDrawable* detachable = dynamic_cast<DetachableDrawable*>(drawable_by_id(detachable_id));
  return drawable_manager->get_id(detachable->get_drawable());
}

int scene_add_drawable(int scene_id, int drawable_id)
{
  DrawableGroup* scene = scene_by_id(scene_id);
  if (scene)
    scene->add_drawable(drawable_by_id(drawable_id));
  return drawable_id;
}

/** Remove a drawable by its id */
void scene_remove_drawable(int scene_id, int drawable_id)
{
  DrawableGroup* scene = scene_by_id(scene_id);
  if (scene)
    scene->remove_drawable(drawable_by_id(drawable_id));
}

/** Remove all drawables from a scene */
void scene_clear()
{
  
}

/** Make the scene given by scene_id the current one */
void scene_set_active(int scene_id)
{
}

void drawable_set_pos(int drawable_id, int x, int y)
{
  Advent::Drawable* drawable = drawable_by_id(drawable_id);
  drawable->set_pos(CL_Point(x, y));
}

void detachable_drawable_set_offset(int drawable_id, int x, int y)
{
  DetachableDrawable* drawable = dynamic_cast<DetachableDrawable*>(drawable_by_id(drawable_id));
  if (drawable)
    drawable->set_offset(CL_Point(x, y));
}

DepthMap* depth_map_create(const char* name, float scale)
{
  try { 
    return new DepthMap(name, scale);
  } catch(CL_Error& err) {
    std::cout << "CL_Error: " << err.message << std::endl;
    return 0;
  }
}

int depth_drawable_create(int drawable_id, DepthMap* depth)
{
  DepthDrawable* depth_drawable = new DepthDrawable(drawable_by_id(drawable_id), depth);
  return (drawable_manager->add(depth_drawable));
}

void timeable_add(int timeable)
{
}

int  person_timeable_create(int drawable_id, int x, int y)
{
  return timeable_manager->add(new PersonTimeable(drawable_manager->get_by_id(drawable_id), CL_Point(x, y)));
}

void person_timeable_set_pos(int person_id, int x, int y)
{
  PersonTimeable* timeable = dynamic_cast<PersonTimeable*>(timeable_manager->get_by_id(person_id));
  if (timeable)
    timeable->set_pos(CL_Point(x, y));
  else
    std::cout << "Error: not a PersonTimeable: " << person_id << std::endl;
}

void person_timeable_walk_to(int person_id, int x, int y)
{
  PersonTimeable* timeable = dynamic_cast<PersonTimeable*>(timeable_manager->get_by_id(person_id));
  if (timeable)
    timeable->walk_to(CL_Point(x, y));
  else
    std::cout << "Error: not a PersonTimeable: " << person_id << std::endl;
}

#if SWIGGUILE
void person_timeable_set_target_callback(int person_id, SCM func)
{
  PersonTimeable* timeable = dynamic_cast<PersonTimeable*>(timeable_manager->get_by_id(person_id));
  // FIXME: Memleak
  new CL_Slot(timeable->sig_target_callback().connect_functor(SCMFunctor(func)));
}
#endif

void person_timeable_set_depthmap(int person_id, DepthMap* d)
{
  PersonTimeable* timeable = dynamic_cast<PersonTimeable*>(timeable_manager->get_by_id(person_id));
  if (timeable)
    timeable->set_depthmap(d);
}

int  mouse_timeable_create(int drawable_id)
{
  return timeable_manager->add(new MouseTimeable(drawable_manager->get_by_id(drawable_id)));
}

int scroll_timeable_create(int drawable_id, int clickable_id, int person_id)
{
  DetachableDrawable* drawable 
    = dynamic_cast<DetachableDrawable*>(drawable_manager->get_by_id(drawable_id));
  DetachableClickable* clickable 
    = dynamic_cast<DetachableClickable*>(clickable_manager->get_by_id(clickable_id));
  PersonTimeable* timeable
    = dynamic_cast<PersonTimeable*>(timeable_manager->get_by_id(person_id));

  if (!drawable || !clickable || !timeable)
    {
      std::cout << "Error creating ScrollTimeable" << std::endl;
      return -1;
    }
  else
    {
      return timeable_manager->add(new ScrollTimeable(drawable, clickable, timeable));
    }
}

#ifdef SWIGGUILE
int callback_timeable_create(float timeout, SCM func)
{
  assert(SCM_BOOL_T == scm_procedure_p(func));

  CallbackTimeable* timeable = new CallbackTimeable(timeout);
  // FIXME: Memleak
  new CL_Slot(timeable->sig_callback().connect_functor(SCMFunctor(func)));
  return timeable_manager->add(timeable);
}
#endif


#if SWIGGUILE
void clickable_register_on_click(int id, SCM func)
{
  Clickable* clickable = clickable_manager->get_by_id(id);  
  clickable->set_callback(new GenericClickableCallback<SCMFunctor>(func));
}

void clickable_register_on_press(int drawable_id, SCM func)
{
  Clickable* clickable = clickable_manager->get_by_id(drawable_id);
  new CL_Slot(clickable->sig_mouse_down().connect_functor(SCMFunctor(func)));
}

void clickable_register_on_release(int drawable_id, SCM func)
{
  Clickable* clickable = clickable_manager->get_by_id(drawable_id);
  new CL_Slot(clickable->sig_mouse_up().connect_functor(SCMFunctor(func)));
}
#endif

#if SWIGGUILE
void clickable_register_mouse_enter(int drawable_id, SCM func)
{
  Clickable* clickable = clickable_manager->get_by_id(drawable_id);  
  new CL_Slot(clickable->sig_mouse_enter().connect_functor(SCMFunctor(func)));  
}

void clickable_register_mouse_leave(int drawable_id, SCM func)
{
  Clickable* clickable = clickable_manager->get_by_id(drawable_id);  
  new CL_Slot(clickable->sig_mouse_leave().connect_functor(SCMFunctor(func)));  
}

#endif

/* EOF */
