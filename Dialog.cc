//  $Id$
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

#include "Font.hh"
#include "Dialog.hh"

Dialog dialog;

void 
Dialog::draw ()
{
  if (!texts.empty ())
    {
      DialogMessage& message = texts.front ();
      
      CL_Display::fill_rect (320 - 200, 150 - 40, 320 + 200, 150 + 50,
			     0.0, 0.0, 0.0, 0.5);
      font ("font")->print_center (320, 150, message.text.c_str ());
    }
}

void 
Dialog::update ()
{
  if (!texts.empty ())
    {
      DialogMessage& message = texts.front ();
      
      if (message.display_time < 0)
	texts.pop ();
      else
	message.display_time -= 1;
    }
}

void 
Dialog::add (const DialogMessage& message)
{
  texts.push (message);
}

SCM 
Dialog::dialog_1 (SCM text)
{
  puts ("Dialog1");
  char * char_str = SCM_CHARS (text);
  printf ("CharStr: %s\n", char_str);
  std::string str (char_str);
  dialog.texts.push (DialogMessage (str, str.length () * 2));
  return SCM_UNSPECIFIED;
}

SCM dialog_add (SCM text)
{
  puts (SCM_CHARS (text));
  return SCM_UNSPECIFIED;
}

void 
Dialog::init ()
{
  std::cout << "Registering guile stuff..." << std::endl;
  gh_new_procedure1_0 ("dialog:add2", &Dialog::dialog_1);
  std::cout << "Registering guile stuff...done" << std::endl;
}

/* EOF */
