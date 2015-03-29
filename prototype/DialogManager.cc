//  $Id: DialogManager.cc,v 1.4 2001/07/15 18:54:58 grumbel Exp $
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

#include "Advent.hh"
#include "Dialog.hh"
#include "DialogManager.hh"

DialogManager* DialogManager::instance;

DialogManager::DialogManager ()
{
  font = CL_Font::load ("font", app.get_resource ());
  lambda = SCM_UNSPECIFIED;
  instance = this;
}

DialogManager::~DialogManager ()
{
}

void
DialogManager::init ()
{
  instance = NULL;
  gh_new_procedure2_0 ("c:dialog:show", DialogManager::dialog_show);
}

void
DialogManager::draw ()
{
  if (!sentences.empty ())
    {
      int y_pos = 0;
      CL_Display::fill_rect (0, 390, 640, 480,
			     0.0, 0.0, 0.0, 0.5);

      //font->print_center (320, 100, "Dialog TEST");
      // REPLACE ME WITH A GUI LIKE OF THINKS
      for (std::vector<std::string>::iterator i = sentences.begin ();
	   i != sentences.end (); ++i)
	{
	  if (CL_Mouse::get_y () > 400 + y_pos &&
	      CL_Mouse::get_y () < 400 + y_pos + 20)
	    {
	      CL_Display::fill_rect (0, 400 + y_pos,
				     640, 400 + y_pos + 20,
				     1.0, 1.0, 1.0, 0.5);
	    }

	  font->print_left (10, 400 +  y_pos,
			    i->c_str ());
	  y_pos += 20;
	}
    }
}

void
DialogManager::update (float delta)
{
}

SCM
DialogManager::dialog_show (SCM arg_sentences, SCM arg_lambda)
{
  instance->lambda = arg_lambda;

  instance->sentences.clear ();

  while (arg_sentences != SCM_EOL)
    {
      if (SCM_STRINGP (SCM_CAR (arg_sentences)))
	{
	  instance->sentences.push_back (SCM_CHARS(SCM_CAR (arg_sentences)));
	}
      arg_sentences = SCM_CDR (arg_sentences);
    }

  for (std::vector<std::string>::iterator i = instance->sentences.begin ();
       i != instance->sentences.end (); ++i)
    {
      std::cout << "Sentence: " <<  *i << std::endl;
    }

  input_mode = MODE_DIALOG;

  return SCM_UNSPECIFIED;
}

/// @return true if the click got catched, false if the click was not used
bool
DialogManager::on_mouse_release (const CL_Key&)
{
  if (!sentences.empty ())
    return true;
  else
    return false;
}

bool
DialogManager::on_mouse_press (const CL_Key&)
{
  if (!sentences.empty ())
    return true;
  else
    return false;
}

/// @return true if the click got catched, false if the click was not used
bool
DialogManager::on_mouse_click (const CL_Key& key)
{
  if (!sentences.empty ())
    {
      std::cout << "GOT CLICK" << std::endl;

      int y_pos = 0;
      for (std::vector<std::string>::iterator i = sentences.begin ();
	   i != sentences.end (); ++i)
	{
	  if (key.y > 400 + y_pos &&
	      key.y < 400 + y_pos + 20)
	    {
	      std::cout << "GOT: " << i - sentences.begin () << std::endl;;
	      dialog.add (DialogMessage (*i, 2000));
	      eval (i - sentences.begin ());
	      return true;
	    }
	  y_pos += 20;
	}
      std::cout << "CLick ignored: " << priority () << std::endl;
      return true;
    }
  else
    {
      return false;
    }
}

void
DialogManager::eval (int selection)
{
  if (lambda != SCM_UNSPECIFIED && lambda != SCM_BOOL_F)
    {
      sentences.clear ();
      gh_call1 (lambda, SCM_MAKINUM (selection));
    }
  else
    {
      sentences.clear ();
      //assert(!"DialogManager: NO lambda given");
    }
  std::cout << "Leaving dialog" << std::endl;
  input_mode = MODE_NORMAL;
}

float
DialogManager::priority ()
{
  if (!sentences.empty ())
    {
      return 1000;
    }
  else
    {
      return 0.0;
    }
}

/* EOF */
