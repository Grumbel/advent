//  $Id: Animation.hh,v 1.4 2001/04/27 20:42:57 grumbel Exp $
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

#ifndef ANIMATION_HH
#define ANIMATION_HH

class Frame : public Drawable
{
public:
  int display_time;
  unsigned int sub_frame;
  CL_Vector pos;
  CL_Surface sur;


  Frame (SCM frame);
  virtual ~Frame ();

  virtual float get_z_pos ();
  virtual void draw_world (int x_offset = 0, int y_offset = 0);
};

class Animation : public Drawable
{
private:
  std::list<Frame*> frames;
  std::list<Frame*>::iterator current_frame;
  bool remove_me;
  unsigned int display_start;

public:
  Animation (SCM animation);
  virtual ~Animation ();

  virtual void draw_world (int x_offset = 0, int y_offset = 0);
  virtual void update (float delta);
  virtual float get_z_pos ();
  virtual bool  removeable () { return remove_me; }

  static void init ();
  static SCM  play (SCM animation);
};

#endif

/* EOF */
