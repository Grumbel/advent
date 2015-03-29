//  $Id: time_manager.hxx,v 1.8 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef TIMEMANAGER_HH
#define TIMEMANAGER_HH

#include <list>
#include <guile/gh.h>
#include "boost/smart_ptr.hpp"
#include "layer.hxx"

namespace Advent {

class TimedLambda;

class TimeManager : public Layer
{
private:
  typedef std::list<boost::shared_ptr<TimedLambda> > TimedList;
  TimedList lambdas;

public:
  TimeManager ();
  virtual ~TimeManager ();

  void add (int activation_time, SCM lambda);
  void update (float delta);

  // FIXME: All this is useless, probally update() and draw() should
  // FIXME: be seperated
  void draw(boost::dummy_ptr<View>) {}
  bool is_over(int, int) { return false; }
  void on_button_press(const CL_InputEvent&) {}
  void on_button_release(const CL_InputEvent&) {}

  // static guile stuff
public:
  static void register_guile_bindings ();

  static SCM scm_timemanager_create ();
  static SCM scm_timemanager_add (SCM scm_manager, SCM scm_time, SCM scm_func);
};

} // namespace Advent

#endif

/* EOF */
