//  $Id: view.hxx,v 1.5 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef VIEW_HXX
#define VIEW_HXX

#include <string>

class CL_Sprite;
class CL_Vector;
class CL_Surface;
class CL_Font;

namespace Advent {

class Sprite;

/* Class for drawing objects
 */
class View
{
private:

public:
  virtual void set_view (const CL_Vector& pos) =0;

  virtual int get_x_offset () =0;
  virtual int get_y_offset () =0;
  virtual int get_x1 () =0;
  virtual int get_x2 () =0;
  virtual int get_y1 () =0;
  virtual int get_y2 () =0;

  virtual void draw (CL_Sprite&  sprite, int x_pos, int y_pos) =0;
  virtual void draw (CL_Surface& sur, const CL_Vector& pos) =0;
  virtual void draw (CL_Surface& sur, int x_pos, int y_pos) =0;
  virtual void draw (CL_Surface& sur, int x_pos, int y_pos, int frame) =0;
  virtual void draw (CL_Surface& sur, int x_pos, int y_pos,
		     float size_x, float size_y, int frame) =0;


  virtual void draw_line (int x1, int y1, int x2, int y2,
			  float r, float g, float b, float a = 1.0f) =0;
  virtual void draw_fillrect (int x1, int y1, int x2, int y2,
			      float r, float g, float b, float a = 1.0f) =0;
  virtual void draw_rect (int x1, int y1, int x2, int y2,
			  float r, float g, float b, float a = 1.0f) =0;
  virtual void draw_pixel (int x_pos, int y_pos,
			   float r, float g, float b, float a = 1.0f) =0;
  virtual void draw_circle (int x_pos, int y_pos, int radius,
		    float r, float g, float b, float a = 1.0f) =0;

  virtual void print (CL_Font* font, int x_pos, int y_pos, const std::string& str) =0;
};

} // namespace Advent

#endif

/* EOF */
