//  $Id: Dialog.hh,v 1.6 2001/08/21 20:38:43 grumbel Exp $
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

#ifndef DIALOG_HH
#define DIALOG_HH

#include <deque>
#include <guile/gh.h>

class DialogMessage
{
public:
  std::string text;
  int display_time;
  int start_time;

  DialogMessage (const std::string text, const int d_time)
  {
    this->text = text;
    display_time = d_time;
    start_time = -1;
  }
};

class Dialog
{
private:
  std::deque<DialogMessage> texts;
  std::vector<SCM> hooks;
  std::string speaker;

public:
  Dialog () {}
  virtual ~Dialog () {}

  void add (const DialogMessage& message);
  void draw ();
  void update (float delta);
  void call_hooks ();
  void set_speaker (std::string arg_speaker);

  // Guile bindings
  static SCM dialog_set_speaker (SCM arg_speaker);
  static SCM dialog_push (SCM text);
  static SCM dialog_clear ();
  static SCM dialog_add_hook (SCM);
  static void init ();
};

extern Dialog dialog;

#endif

/* EOF */
