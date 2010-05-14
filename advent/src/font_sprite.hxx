//  $Id: font_sprite.hxx,v 1.8 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef FONTDRAWABLE_HXX
#define FONTDRAWABLE_HXX

#include <string>
#include <ClanLib/display.h>
#include <ClanLib/core.h>
#include <guile/gh.h>
#include "boost/dummy_ptr.hpp"
#include "view.hxx"
#include "sprite.hxx"
#include "scm_obj.hxx"

namespace Advent {

/** A Drawable that holds a string
    FIXME: Could probally become a sprite
 */
class FontSprite : public Sprite
{
private:
  CL_Font* font;
  std::string message;
  unsigned int start_time;
  unsigned int display_time;
  SCMObj remove_hook;

  typedef enum { FS_CENTER, FS_LEFT, FS_RIGHT } EAlign;
  EAlign align;
  
  /** Clips the text position so that the text is complete visible on
      the screen and not crop at the screen boarder. Many used to let
      person talk. */
  bool always_visible;
public:
  FontSprite (const std::string&, const std::string&);
  virtual ~FontSprite ();

  void  update (float delta);
  void  draw (boost::dummy_ptr<View> view, const CL_Vector&);
  void  draw (boost::dummy_ptr<View> view, const CL_Vector&, float);

  int get_width() const;
  int get_height() const;

  /** Return the z_pos of the drawable, it is used to sort a list of
      drawables */
  float get_z_pos ();
  bool  removable ();
  
  // static guile bindings
public:
  static void register_guile_bindings ();

  static SCM scm_font_sprite_create (SCM scm_font, SCM message);
  static SCM scm_font_sprite_set_text (SCM sprite, SCM message);
  static SCM scm_font_sprite_set_remove_hook (SCM sprite, SCM hook);
};

} // namespace Advent

#endif

/* EOF */
