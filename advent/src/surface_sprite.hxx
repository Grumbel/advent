//  $Id: surface_sprite,v 1.15 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef SURFACESPRITE_HXX
#define SURFACESPRITE_HXX

#include <guile/gh.h>
#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "sprite.hxx"

namespace Advent {

class SurfaceSprite : public Sprite
{
private:
  CL_Sprite sprite;
  std::string filename;
  float frame;
  float fps;
  bool animated;

public:
  SurfaceSprite (std::string filename);
  SurfaceSprite (std::string filename, int frames);
  virtual ~SurfaceSprite ();

  void update (float delta);
  void draw (boost::dummy_ptr<View> view, const CL_Vector& pos);
  void draw (boost::dummy_ptr<View> view, const CL_Vector& pos, float zoom);

  // Set the frames per seconds of the animation
  void set_fps (float arg_fps);

  int get_width () const  { return sprite.get_frame_size(sprite.get_current_frame()).width; }
  int get_height () const { return sprite.get_frame_size(sprite.get_current_frame()).height; }

  void set_align (int, int);
  void set_align_center_bottom ();
  void set_align_center ();

  // static guile bindings
public:
  static void register_guile_bindings ();

  static SCM scm_surface_sprite_create (SCM name);
  static SCM scm_surface_sprite_create_anim (SCM name, SCM frames);
  static SCM scm_surface_sprite_set_fps (SCM scm_sprite, SCM scm_fps);
  static SCM scm_surface_sprite_set_align_center (SCM scm_sprite);
  static SCM scm_surface_sprite_set_align (SCM scm_sprite, SCM scm_x, SCM scm_y);
};

} // namespace Advent

#endif

/* EOF */
