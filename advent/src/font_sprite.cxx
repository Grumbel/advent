//  $Id: font_sprite.cxx,v 1.22 2004/01/14 02:28:24 grumbel Exp $
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

#include "scm_converter.hxx"
#include "font_sprite.hxx"

namespace Advent {

FontSprite::FontSprite (const std::string& font_str, const std::string& m)
  : message (m), align (FS_CENTER), always_visible (true)
{
  //std::cout << "FontSprite::FontSprite" << std::endl;
  // FIXME: Hack, replace with something real
  try {
    font = new CL_Font (font_str.c_str (),
                        new CL_ResourceManager("images/resources.scr", false));
  } catch (CL_Error& err) {
    std::cout << "CL_Error: " << err.message << std::endl;
  }
  start_time = CL_System::get_time ();

  // Calculate of long this text should be displayed
  // FIXME: should be changeable from guile
  display_time = message.length () * 50 + 1000;
}

FontSprite::~FontSprite ()
{
  std::cout << "FontSprite::~FontSprite" << std::endl;
}

int
FontSprite::get_width() const
{
  return font->get_width(message);
}

int
FontSprite::get_height() const
{
  // FIXME: This might not work with multiline fonts
  return font->get_height ();
}

void
FontSprite::update (float delta)
{
  if ((CL_System::get_time () > start_time + display_time)
      && remove_hook.get_scm () != SCM_BOOL_F)
    {
      //std::cout << "FontSprite::update (float delta): Calling remove hook (unimp)" << std::endl;
      gh_call0 (remove_hook.get_scm ());
      remove_hook.set_scm (SCM_BOOL_F);
    }
}

void
FontSprite::draw (boost::dummy_ptr<View> view, const CL_Vector& pos)
{
#if 0 // Mon Feb 24 20:30:25 2003
  //std::cout << "FontSprite::draw" << std::endl;
  //std::cout << "Message: " << message << std::endl;
  /*CL_Display::fill_rect (pos.x, pos.y,
    pos.x + get_width (), pos.y + get_width (),
    1.0, 1.0, 1.0);*/

  // FIXME: get_width/height are expensive, could need caching
  CL_Vector tmp_pos (pos);

  switch (align)
    {
    case FS_CENTER:
      view->print (font, int(tmp_pos.x), int(tmp_pos.y), message.c_str());
      break;
    case FS_LEFT:
      view->print (font, int(tmp_pos.x), int(tmp_pos.y), message.c_str());
      break;
    case FS_RIGHT:
      view->print (font, int(tmp_pos.x), int(tmp_pos.y), message.c_str());
      break;
    }
#endif
}

void
FontSprite::draw (boost::dummy_ptr<View> view, const CL_Vector& pos, float)
{
  switch (align)
    {
    case FS_CENTER:
      font->draw ((int) pos.x, (int)pos.y, message.c_str());
      break;
    case FS_LEFT:
      font->draw ((int) pos.x, (int)pos.y, message.c_str());
      break;
    case FS_RIGHT:
      font->draw ((int)pos.x, (int)pos.y, message.c_str());
      break;
    }
}

float
FontSprite::get_z_pos ()
{
  return 1000.0f;
}

bool
FontSprite::removable ()
{
  /*std::cout << "removable: " << CL_System::get_time () << " "
	    << (CL_System::get_time () > start_time + 3000) << std::endl;*/
  return (CL_System::get_time () > start_time + display_time);
}

void
FontSprite::register_guile_bindings ()
{
  puts ("FontSprite::register_guile_bindings ()");

  gh_new_procedure2_0("c:font-sprite:create", &FontSprite::scm_font_sprite_create);
  gh_new_procedure2_0("c:font-sprite:set-text", &FontSprite::scm_font_sprite_set_text);
  gh_new_procedure2_0("c:font-sprite:set-remove-hook", &FontSprite::scm_font_sprite_set_remove_hook);
}
/*
SCM
FontSprite::mark (SCM smob)
{
  return SCM_BOOL_F;
}

scm_sizet
FontSprite::free (SCM smob)
{
  delete smob_cast<FontSprite>(smob);
  return 0; //sizeof (FontSprite);
}

int
FontSprite::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:FontSprite>", port);
  return 1;
}
*/
SCM
FontSprite::scm_font_sprite_create (SCM scm_font, SCM message)
{
  assert(gh_string_p (message));
  return SpriteSmob::create (new FontSprite (SCM_CHARS (scm_font), SCM_CHARS (message)));
}

SCM
FontSprite::scm_font_sprite_set_text (SCM sprite, SCM scm_message)
{
  smobbox_cast<FontSprite>(sprite)->message = SCM_CHARS (scm_message);
  return sprite;
}

SCM
FontSprite::scm_font_sprite_set_remove_hook (SCM sprite, SCM scm_hook)
{
  smobbox_cast<FontSprite>(sprite)->remove_hook.set_scm (scm_hook);
  return sprite;
}

} // namespace Advent

/* EOF */
