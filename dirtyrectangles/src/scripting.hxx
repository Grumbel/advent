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

#ifndef HEADER_SCRIPTING_DISPLAY_HXX
#define HEADER_SCRIPTING_DISPLAY_HXX

#include <string>
#include "depth_map.hxx"
#include "view.hxx"

//tolua_begin

/** Creates a CL_DisplayWindow with the given width and height */
void display_init(const char* title, int width, int height, bool fullscreen);

/** Destroys the current CL_DisplayWindow */
void display_deinit();

/** Enter the main loop and give controll to the C++ code */
void display_main_loop();

void display_hide_system_cursor();
void display_show_system_cursor();

/** Create a new scene */
int  scene_create();

/** Add a sprite drawable to the scene */
int sprite_drawable_create(int x, int y, const char* name);

int  font_drawable_create(int x, int y, const char* font, const char* text);
int  rect_drawable_create(int x1, int y1, int x2, int y2, int r, int g, int b, int a);
int  detachable_drawable_create();
void detachable_drawable_set(int detachable, int drawable);
int  detachable_drawable_get(int detachable);
void detachable_drawable_set_offset(int detachable, int x, int y);

int scene_add_drawable(int scene, int drawable);

/** Remove a drawable by its id */
void scene_remove_drawable(int scene, int drawable);

/** Remove all drawables from a scene */
void scene_clear();

/** Make the scene given by scene_id the current one */
void scene_set_active(int scene_id);

void drawable_set_pos(int drawable_id, int x, int y);

Advent::DepthMap* depth_map_create(const char* name, float scale);

int depth_drawable_create(int drawable_id, Advent::DepthMap* depth);

int  clickable_scene_create();

int  rect_clickable_create(int x1, int y1, int x2, int y2);
int  input_add_drawable_clickable(int scene_id, int drawable_id);
int  detachable_clickable_create();
void detachable_clickable_set(int clickable_id, int target_id);
void detachable_clickable_set_offset(int clickable_id, int x, int y);

void input_add_clickable(int scene_id, int clickable_id);
int  drawable_clickable_create(int drawable_id);

void clickable_grab_input(int clickable_id);
void clickable_release_input();

void timeable_add(int timeable);

int  person_timeable_create(int drawable_id, int x, int y);
void person_timeable_walk_to(int person_id, int x, int y);
void person_timeable_set_pos(int person_id, int x, int y);
void person_timeable_set_depthmap(int person_id, Advent::DepthMap* d);

int scroll_timeable_create(int drawable_id, int clickable_id, int person_id);

int  mouse_timeable_create(int drawable_id);

Advent::View* view_create(int scene_id, int clickable_id);
void  view_set_pos(Advent::View* view, int x, int y);
void  view_set_drawables(Advent::View* view,  int id);
void  view_set_clickables(Advent::View* view, int id);
//tolua_end

#ifdef SWIGGUILE
int  callback_timeable_create(float timeout, SCM func);
void person_timeable_set_target_callback(int person_id, SCM func);

void clickable_register_on_click(int drawable_id, SCM func);
void clickable_register_on_press(int drawable_id, SCM func);
void clickable_register_on_release(int drawable_id, SCM func);

void clickable_register_mouse_enter(int drawable_id, SCM func);
void clickable_register_mouse_leave(int drawable_id, SCM func);
#endif

#endif

/* EOF */
