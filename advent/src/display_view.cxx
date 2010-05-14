//  $Id: display_view.cxx,v 1.7 2004/01/14 02:28:24 grumbel Exp $
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

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "display_view.hxx"

namespace Advent {

DisplayView::DisplayView (int arg_x1, int arg_y1, 
			  int arg_x2, int arg_y2,
			  int arg_x_offset, int arg_y_offset) :
  x1 (arg_x1), y1 (arg_y1), x2 (arg_x2), y2 (arg_y2),
  x_offset (-arg_x_offset), y_offset (-arg_y_offset),
  zoom (1.0f)
{
  x_offset -= x1;
  y_offset -= y1;
}

DisplayView::~DisplayView ()
{
}

/*
void 
DisplayView::draw ()
{
  //std::cout << "Drawing: " << x_offset << " " << y_offset << std::endl;
  CL_Display::push_clip_rect (CL_ClipRect (x1, y1, x2, y2));
  // Draw-command here
  //world->draw (this);
  CL_Display::pop_clip_rect ();
}*/

int DisplayView::get_x_offset () { return x1 - x_offset + (x2 - x1)/2; }
int DisplayView::get_y_offset () { return y1 - y_offset + (y2 - y1)/2; }
int DisplayView::get_x1 () { return x1; }
int DisplayView::get_x2 () { return x2; }
int DisplayView::get_y1 () { return y1; }
int DisplayView::get_y2 () { return y2; }

CL_Vector 
DisplayView::display_to_view (const CL_Vector& pos)
{
  return CL_Vector(pos) - CL_Vector (get_x_offset (), get_y_offset ());
}

void 
DisplayView::set_view (const CL_Vector& pos)
{
  x_offset = int(pos.x);
  y_offset = int(pos.y);
}

void 
DisplayView::set_zoom (float z)
{
  zoom = z;
}

void
DisplayView::draw (CL_Sprite& sprite, int x, int y)
{
  sprite.draw (x, y);
}

void 
DisplayView::draw (CL_Surface& sur, const CL_Vector& pos)
{
  if (zoom == 1.0)
    {   
      sur.draw (int(pos.x + get_x_offset ()),
		      int(pos.y + get_y_offset ()));
    }
  else
    {
      sur.draw (int(int(pos.x + get_x_offset ()) * zoom),
                int(int(pos.y + get_y_offset ()) * zoom));
      //zoom, zoom); FIXME: Sun Feb 23 17:59:33 2003 zooming not supported
    }
}

void 
DisplayView::draw (CL_Surface& sur, int x_pos, int y_pos)
{
  if (zoom == 1.0)
    {
      sur.draw (x_pos + get_x_offset (),
		      y_pos + get_y_offset ());
    }
  else
    {
      sur.draw (int((x_pos + get_x_offset ()) * zoom),
                int((y_pos + get_y_offset ()) * zoom));
      // FIXME: zoom, zoom); Sun Feb 23 18:00:00 2003 zooming broken
    }
}

void 
DisplayView::draw (CL_Surface& sur, int x_pos, int y_pos, int frame)
{
  if (zoom == 1.0)
    {
      sur.draw (x_pos + get_x_offset (),
                y_pos + get_y_offset ());
      //FIXME: Sun Feb 23 18:00:24 2003  frame);
    }
  else
    {
      sur.draw (int((x_pos + get_x_offset ()) * zoom),
                int((y_pos + get_y_offset ()) * zoom));
      //FIXME: Sun Feb 23 18:00:40 2003
      //zoom, zoom,
      //frame);  
    }
}

void 
DisplayView::draw (CL_Surface& sur, int x_pos, int y_pos, 
	    float size_x, float size_y, int frame)
{
  sur.draw (x_pos + get_x_offset (),
            y_pos + get_y_offset ());
            //FIXME: Sun Feb 23 18:00:50 2003 size_x * zoom, size_y * zoom, frame);  
}

void 
DisplayView::draw_line (int x1, int y1, int x2, int y2, 
		float r, float g, float b, float a)
{
  if (zoom == 1.0)
    {
      CL_Display::draw_line (x1 + get_x_offset (), y1 + get_y_offset (),
			     x2 + get_x_offset (), y2 + get_y_offset (),
                             CL_Color(int(255*r), int(255*g), int(255*b), int(255*a)));
    }
  else
    {
      CL_Display::draw_line (int((x1 + get_x_offset ()) * zoom),
			     int((y1 + get_y_offset ()) * zoom),
			     int((x2 + get_x_offset ()) * zoom),
			     int((y2 + get_y_offset ()) * zoom),
                             CL_Color(int(255*r), int(255*g), int(255*b), int(255*a)));
    }
}

void 
DisplayView::draw_fillrect (int x1, int y1, int x2, int y2, 
		    float r, float g, float b, float a)
{
  CL_Display::fill_rect (CL_Rect(int((x1 + get_x_offset ()) * zoom),
                                 int((y1 + get_y_offset ()) * zoom), 
                                 int((x2 + get_x_offset ()) * zoom),
                                 int((y2 + get_y_offset ()) * zoom)),
                         CL_Color(int(255*r), int(255*g), int(255*b), int(255*a)));
}

void 
DisplayView::draw_rect (int x1, int y1, int x2, int y2, 
		 float r, float g, float b, float a)
{
  CL_Display::draw_line (x1 + get_x_offset (), y1 + get_y_offset (), 
			 x1 + get_x_offset (), y2 + get_y_offset (),
                         CL_Color(int(255*r), int(255*g), int(255*b), int(255*a)));
  CL_Display::draw_line (x2 + get_x_offset (), y1 + get_y_offset (), 
			 x2 + get_x_offset (), y2 + get_y_offset (),
			 CL_Color(int(255*r), int(255*g), int(255*b), int(255*a)));
  CL_Display::draw_line (x1 + get_x_offset (), y1 + get_y_offset (), 
			 x2 + get_x_offset (), y1 + get_y_offset (),
			 CL_Color(int(255*r), int(255*g), int(255*b), int(255*a)));
  CL_Display::draw_line (x1 + get_x_offset (), y2 + get_y_offset (), 
			 x2 + get_x_offset (), y2 + get_y_offset (),
                         CL_Color(int(255*r), int(255*g), int(255*b), int(255*a)));
}

void 
DisplayView::draw_pixel (int x_pos, int y_pos, 
		   float r, float g, float b, float a)
{
  //CL_Display::put_pixel (x1 + get_x_offset (),
  //			 y1 + get_y_offset (), r, g, b, a);
  std::cout << "DisplayView::draw_pixel () not implemented" << std::endl;
}

void 
DisplayView::draw_circle (int x_pos, int y_pos, int radius,
		   float r, float g, float b, float a)
{
  // FIXME: Probally not the fast circle draw algo on this world...
  const float pi = 3.1415927f * 2.0f;
  const float steps = 8;
  CL_Vector current (radius, 0);
  CL_Vector next = current.rotate (pi/steps, CL_Vector (0, 0, 1.0f));

  for (int i = 0; i < steps; ++i)
    {
      draw_line (int(x_pos + current.x), int(y_pos + current.y),
		 int(x_pos + next.x), int(y_pos + next.y),
		 r, g, b, a);
      current = next;
      next = next.rotate (pi/8, CL_Vector (0, 0, 1.0f));
    }
}

void 
DisplayView::print (CL_Font* font, int x_pos, int y_pos, const std::string& str)
{
  CL_Vector tmp_pos (x_pos + get_x_offset (), y_pos + get_y_offset ());

  if (true)// || always_visible)
    {
      int width = 100; //FIXME: Sun Feb 23 18:02:41 2003font->get_text_width (str.c_str ())/2 + 30;
      int height = font->get_height ()/2 + 30;

      if (tmp_pos.x - width < 0)
	tmp_pos.x = width;
      else if (tmp_pos.x + width > CL_Display::get_width ())
	tmp_pos.x = CL_Display::get_width () - width;

      if (tmp_pos.y - height < 0)
	tmp_pos.y = height;
      else if (tmp_pos.y + height > CL_Display::get_height ())
	tmp_pos.y = CL_Display::get_height () - height;
    }

  font->draw (int(tmp_pos.x), 
              int(tmp_pos.y), str);
}

} // namespace Advent

/* EOF */
