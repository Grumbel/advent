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
#include <ClanLib/Core/core_iostream.h>
#include <ClanLib/Core/Math/rect.h>
#include <ClanLib/Core/Math/size.h>
#include <ClanLib/Core/Math/point.h>
#include <ClanLib/Core/core_iostream.h>
#include <ClanLib/Display/input_event.h>
#include <ClanLib/Display/mouse.h>
#include <ClanLib/Display/display.h>
#include "drawable.hxx"
#include "clickable_group.hxx"
#include "graphic_context.hxx"
#include "rect_optimizier.hxx"
#include "view.hxx"

namespace Advent {

View*  View::current_ = 0;

View::View(Drawable* arg_drawable, Clickable* arg_clickable_group)
{
  std::cout << "View: " << arg_drawable << " " << arg_clickable_group << std::endl;
  drawable = arg_drawable;
  clickable_group = arg_clickable_group;
  current_ = this;
  current_clickable = 0;
  mouse_down_clickable = 0;
  grab = 0;

  //std::cout << "View: " <<  drawable << " " << clickable_group << std::endl;

  down_slot  = CL_Mouse::sig_key_down().connect(this, &View::on_mouse_down);
  up_slot    = CL_Mouse::sig_key_up().connect(this, &View::on_mouse_up);
  move_slot  = CL_Mouse::sig_move().connect(this, &View::on_mouse_move);
}

View::~View()
{
}

void
View::draw()
{
  if (drawable)
    {
      if (0) // busy drawing
        {
          GraphicContext bla;
          drawable->draw(bla);
          CL_Display::flip();
        }
      else
        {
          MarkContext gc;      
          drawable->draw_marks(gc);
      
          std::vector<CL_Rect> dirty = gc.calc_diff(last_gc);

          last_gc = gc;

          RectOptimizier optimizier(CL_Rect(0, 0, 639, 479));
          
          for(std::vector<CL_Rect>::iterator i = dirty.begin(); i != dirty.end(); ++i)
            {
              optimizier.add(*i);
            }

          std::vector<CL_Rect> rects = optimizier.get_rects();
          
          for(std::vector<CL_Rect>::iterator i = rects.begin(); i != rects.end(); ++i)
            {
              if (*i == CL_Rect(0, 0, 639, 479))
                {
                  GraphicContext bla;
                  drawable->draw(bla);
                  CL_Display::flip();
                  return;
                }
            }

          for(std::vector<CL_Rect>::iterator i = rects.begin(); i != rects.end(); ++i)
            {
              GraphicContext bla;
              
              CL_Display::push_cliprect(*i);
              drawable->draw(bla);
              CL_Display::pop_cliprect();
            }

          for(std::vector<CL_Rect>::iterator i = rects.begin(); i != rects.end(); ++i)
            CL_Display::update(*i);
        }
    }
  else
    {
      std::cout << "View: update: no drawable set!" << std::endl;
    }
}

void
View::update(float delta)
{
  if (drawable)
    drawable->update(delta);
  else
    std::cout << "View: update: no drawable set!" << std::endl;
}

void
View::set_clickable_group(Clickable* clickable_group_)
{
  clickable_group = clickable_group_;
}

void
View::set_drawable (Drawable*  drawable_)
{
  drawable = drawable_;
}

void
View::on_mouse_down(const CL_InputEvent& ev)
{
  if (!grab)
    {  
      CL_Point pos = ev.mouse_pos;
      Clickable* clickable = clickable_group->find_clickable(pos);
      if (clickable)
        {
          clickable->sig_mouse_down()(pos);
          mouse_down_clickable = clickable;
        }
    }
  //std::cout << "\nView:\n";
  //clickable_group->print("  ");
}

void
View::on_mouse_up(const CL_InputEvent& ev)
{
  if (!grab)
    {  
      CL_Point pos = ev.mouse_pos;
      Clickable* clickable = clickable_group->find_clickable(pos);
      if (clickable)
        {
          clickable->sig_mouse_up()(pos);
          if (mouse_down_clickable == clickable)
            {
              // FIXME:
              clickable->call_callback(pos);
              mouse_down_clickable = 0;
            }
        }
    }
  else
    {
      CL_Point pos = ev.mouse_pos;
      Clickable* clickable = clickable_group->find_clickable(pos);
      if (mouse_down_clickable == clickable)
        {
          // FIXME:
          clickable->call_callback(pos);
          mouse_down_clickable = 0;
        }
      grab->sig_mouse_up()(pos);
    }
}

void
View::set_pos(CL_Point arg_pos)
{
  offset_pos = arg_pos;
}

void
View::on_mouse_move(const CL_InputEvent& ev)
{
  if (!grab)
    {
      CL_Point pos = ev.mouse_pos;
      Clickable* clickable = clickable_group->find_clickable(pos);  
      if (current_clickable != clickable)
        {
          if (current_clickable)
            current_clickable->sig_mouse_leave()();

          current_clickable = clickable;

          if (current_clickable)
            current_clickable->sig_mouse_enter()();
        }
    }
}

void
View::grab_input(Clickable* c)
{
  grab = c;
}

void
View::release_input()
{
  grab = 0;
}

} // namespace Advent

/* EOF */
