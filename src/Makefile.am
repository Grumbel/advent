bindir=$(prefix)/games

SUBDIRS = scripting

EXTRA_DIST = cosmos.scm

bin_PROGRAMS = advent

advent_SOURCES = \
  advent_main.cxx  \
  advent_main.hxx  \
  drawable_group.hxx \
  drawable_group.cxx \
  drawable_clickable.hxx \
  drawable_clickable.cxx \
  font_drawable.hxx \
  font_drawable.cxx \
  drawable.hxx \
  drawable.cxx \
  detachable_drawable.hxx \
  detachable_drawable.cxx \
  detachable_clickable.hxx \
  detachable_clickable.cxx \
  depth_drawable.hxx \
  depth_drawable.cxx \
  drawable_manager.hxx \
  drawable_manager.cxx \
  sprite_drawable.hxx \
  sprite_drawable.cxx \
  resource_manager.hxx \
  resource_manager.cxx \
  graphic_context.hxx \
  graphic_context.cxx \
  callback_timeable.hxx \
  callback_timeable.cxx \
  timeable.hxx \
  timeable_manager.hxx \
  timeable_manager.cxx \
  clickable_group.hxx \
  clickable_group.cxx \
  clickable_manager.hxx \
  clickable_manager.cxx \
  clickable.hxx \
  mouse_timeable.hxx \
  mouse_timeable.cxx \
  person_timeable.hxx \
  person_timeable.cxx \
  rect_drawable.hxx \
  rect_drawable.cxx \
  rect_clickable.hxx \
  rect_clickable.cxx \
  scm_functor.hxx \
  scm_functor.cxx \
  view.hxx \
  view.cxx \
  rect_optimizier.hxx \
  rect_optimizier.cxx \
  depth_map.hxx \
  depth_map.cxx \
  mark_context.hxx \
  mark_context.cxx \
  scroll_timeable.hxx \
  scroll_timeable.cxx

advent_LDADD    = scripting/libadvent_scripting.a @ADVENT_DEPS_LIBS@
advent_CPPFLAGS = @ADVENT_DEPS_CFLAGS@

# EOF #
