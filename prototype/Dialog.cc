//  $Id: Dialog.cc,v 1.6 2001/04/27 20:42:57 grumbel Exp $
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
      if (message.start_time == -1)
	message.start_time = CL_System::get_time ();

      CL_Display::fill_rect (320 - 200, 150 - 40, 320 + 200, 150 + 50,
			     0.0, 0.0, 0.0, 0.5);
      font ("font")->print_center (320, 150, message.text.c_str ());
    }
}

void 
Dialog::update (float delta)
{
  if (!texts.empty ())
    {
      DialogMessage& message = texts.front ();
      
      if (message.start_time != -1 
	  && message.start_time + message.display_time < (int) CL_System::get_time ())
	{	
	  //std::cout << "Poping: " << message.text << std::endl;
	  texts.pop_front ();
	}
    }
}

void 
Dialog::add (const DialogMessage& message)
{
  texts.push_back (message);
}

SCM 
Dialog::dialog_push (SCM text)
{
  char * char_str = SCM_CHARS (text);
  std::string str (char_str);

  dialog.texts.push_back (DialogMessage (str, 2000));

  return SCM_UNSPECIFIED;
}

SCM
Dialog::dialog_clear ()
{
  dialog.texts.clear ();

  return SCM_UNSPECIFIED;
}

void 
Dialog::init ()
{
  std::cout << "Registering guile stuff..." << std::endl;
  gh_new_procedure1_0 ("c:dialog:push", &Dialog::dialog_push);
  gh_new_procedure0_0 ("c:dialog:clear", &Dialog::dialog_clear);
  std::cout << "Registering guile stuff...done" << std::endl;
}

/* EOF */
