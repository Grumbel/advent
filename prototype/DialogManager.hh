//  $Id: DialogManager.hh,v 1.2 2001/04/27 20:42:57 grumbel Exp $
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

#ifndef DIALOGMANAGER_HH
#define DIALOGMANAGER_HH

#include <ClanLib/core.h>
#include <guile/gh.h>
#include "Clickable.hh"

class DialogManager : public Clickable
{
private:
  CL_Font* font;
  SCM lambda;
  std::vector<std::string> sentences;
  static DialogManager* instance;

public:
  static void init ();

  DialogManager ();
  virtual ~DialogManager ();

  void draw ();
  void update (float delta);

  /// @return true if the click got catched, false if the click was not used
  bool  on_mouse_release (const CL_Key&);

  bool  on_mouse_press (const CL_Key&);

  /// @return true if the click got catched, false if the click was not used
  bool  on_mouse_click (const CL_Key&);

  void eval (int selection);

  float priority ();
  bool  mouse_over (int, int) { return true;}

  static SCM dialog_show (SCM sentences, SCM arg_lambda);
};

#endif

/* EOF */
