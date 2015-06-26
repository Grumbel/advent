//  $Id: Drawable.hh,v 1.5 2001/04/27 20:42:57 grumbel Exp $
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

#ifndef DRAWABLE_HH
#define DRAWABLE_HH

#include <ClanLib/display.h>

class Drawable
{
private:

public:
  virtual void draw_world (int x_offset = 0, int y_offset = 0) =0;
  virtual void update (float delta) {}
  virtual float get_z_pos () { return 0.0; }
  virtual bool removeable () { return false; }
};

struct is_removeable
{
  bool operator ()  (Drawable* obj)
  {
    return obj->removeable ();
  }
};

class DrawableFill : public Drawable
{
public:
  int drawn;
  float red, green, blue, alpha;
public:
  DrawableFill (float red, float green, float blue, float alpha);
  virtual ~DrawableFill () {}
  virtual void draw_world (int x_offset = 0, int y_offset = 0);
  virtual float get_z_pos ();
  virtual bool removeable ();
};

class DrawableObj : public Drawable
{
private:
  CL_Surface sur;
  CL_Vector pos;
public:
  DrawableObj (std::string sur_name, const CL_Vector arg_pos);
  virtual ~DrawableObj ();

  virtual void draw_world (int x_offset = 0, int y_offset = 0);
  virtual float get_z_pos () { return pos.z; }
};

class DrawableSmob {
private:
  static void add (std::string sur_name, const CL_Vector& vec);

public:
  static void init ();
  static SCM draw (SCM sur_name, SCM pos);
  static SCM fill_display (SCM red, SCM green, SCM blue, SCM alpha);
};

#endif

/* EOF */
