//  $Id: Dialog.cc,v 1.12 2001/08/21 20:38:43 grumbel Exp $
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

      if (!speaker.empty ())
	{
	  font ("font")->print_left (320-200, 110, speaker.c_str ());
	}
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
	  if (texts.empty()) call_hooks ();
	}
    }
}

void
Dialog::call_hooks ()
{
  // Create a temporary object to avoid that the iterators get
  // invalideded on a pushback event inside the gh_call0()
  std::vector<SCM> tmp_hooks (hooks);
  hooks.clear ();
  for (std::vector<SCM>::iterator i = tmp_hooks.begin (); i != tmp_hooks.end (); ++i)
    {
      gh_call0 (*i);
      //scm_unprotect_object (*i);
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
  if (SCM_STRINGP (text))
    {
      char * char_str = SCM_CHARS (text);
      std::string str (char_str);
      dialog.texts.push_back (DialogMessage (str, str.length () * 50 + 1000));
    }
  else if (SCM_SYMBOLP (text))
    {
      std::cout << "feeling expressions are not supported" << std::endl;
    }

  return SCM_UNSPECIFIED;
}

SCM
Dialog::dialog_clear ()
{
  dialog.texts.clear ();

  return SCM_UNSPECIFIED;
}

SCM
Dialog::dialog_add_hook (SCM lambda)
{
  scm_protect_object (lambda);
  dialog.hooks.push_back (lambda);
  return SCM_UNSPECIFIED;
}

void
Dialog::set_speaker (std::string arg_speaker)
{
  speaker = arg_speaker;
}

SCM
Dialog::dialog_set_speaker (SCM arg_speaker)
{
  if (SCM_STRINGP(arg_speaker))
    {
      dialog.set_speaker(SCM_CHARS (arg_speaker));
    }
  else
    {
      assert (!"Dialog: Invalide argument type to dialog_set_speaker");
    }
  return SCM_UNSPECIFIED;
}

void
Dialog::init ()
{
  std::cout << "Dialog: Registering guile stuff..." << std::endl;
  gh_new_procedure1_0 ("c:dialog:set-speaker", &Dialog::dialog_set_speaker);
  gh_new_procedure1_0 ("c:dialog:push", &Dialog::dialog_push);
  gh_new_procedure0_0 ("c:dialog:clear", &Dialog::dialog_clear);

  gh_new_procedure1_0 ("c:dialog:add-hook", &Dialog::dialog_add_hook);
  std::cout << "Registering guile stuff...done" << std::endl;
}

/* EOF */
