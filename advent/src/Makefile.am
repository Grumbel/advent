bindir=$(prefix)/games

lib_LTLIBRARIES = libadvent.la

SUBDIRS = guile boost

EXTRA_DIST = cosmos.scm

libadvent_la_SOURCES = \
adv_hook.cxx  \
adv_hook.hxx  \
adv_hook_smob.cxx  \
adv_hook_smob.hxx  \
adv_obj.cxx  \
adv_obj.hxx  \
advent_main.cxx  \
advent_main.hxx  \
button_layer.cxx  \
button_layer.hxx  \
coin_layer.cxx  \
coin_layer.hxx  \
collideable.cxx  \
collideable.hxx  \
collideable_smob.cxx  \
collideable_smob.hxx  \
colmap.cxx  \
colmap.hxx  \
colmap_smob.cxx  \
colmap_smob.hxx  \
color.hxx  \
debug.cxx  \
debug.hxx  \
delayed_adv_hook.cxx  \
delayed_adv_hook.hxx  \
delta_manager.hxx  \
display.cxx  \
display.hxx  \
display_view.cxx  \
display_view.hxx  \
drawable.cxx  \
drawable.hxx  \
drawable_adv_obj.cxx  \
drawable_adv_obj.hxx  \
drawable_display.cxx  \
drawable_display.hxx  \
drawable_layer.cxx  \
drawable_layer.hxx  \
drawable_smob.cxx  \
drawable_smob.hxx  \
empty_adv_obj.cxx  \
empty_adv_obj.hxx  \
empty_region_adv_obj.hxx  \
fade_out_layer.cxx  \
fade_out_layer.hxx  \
font_sprite.cxx  \
font_sprite.hxx  \
game_screen.hxx  \
guile.cxx  \
guile.hxx  \
inactive_layer.cxx  \
inactive_layer.hxx  \
instant_adv_hook.cxx  \
instant_adv_hook.hxx  \
inventory.cxx  \
inventory.hxx  \
key_map.cxx  \
key_map.hxx  \
key_map_handler.cxx  \
key_map_handler.hxx  \
layer.cxx  \
layer.hxx  \
layer_group.cxx  \
layer_group.hxx  \
layer_manager.hxx  \
layer_screen.cxx  \
layer_screen.hxx  \
layer_smob.cxx  \
layer_smob.hxx  \
mouse_cursor.cxx  \
mouse_cursor.hxx  \
person.cxx  \
person.hxx  \
person_gfx.cxx  \
person_gfx.hxx  \
polygon_collideable.cxx  \
polygon_collideable.hxx  \
rect_collideable.cxx  \
rect_collideable.hxx  \
rect_sprite.cxx  \
rect_sprite.hxx  \
resource_manager.cxx  \
resource_manager.hxx  \
scenario.cxx  \
scenario.hxx  \
scenario_layer.cxx  \
scenario_layer.hxx  \
scm_converter.hxx  \
scm_obj.hxx  \
screen.hxx  \
screen_manager.cxx  \
screen_manager.hxx  \
smob.hxx  \
smob_helper.hxx  \
smob_tuple.hxx  \
smob_tuple_base.hxx  \
sprite.cxx  \
sprite.hxx  \
sprite_collideable.cxx  \
sprite_collideable.hxx  \
sprite_drawable.cxx  \
sprite_drawable.hxx  \
sprite_group.cxx  \
sprite_group.hxx  \
sprite_smob.cxx  \
sprite_smob.hxx  \
static_smob_tuple.hxx  \
surface_colmap.cxx  \
surface_colmap.hxx  \
surface_sprite.cxx  \
surface_sprite.hxx  \
time_manager.cxx  \
time_manager.hxx  \
valid.hxx  \
view.cxx  \
view.hxx

advent:
	ln -s guile advent
	ln -s ../.libs/libadvent.so guile/libcore.so

libadvent_la_LIBADD = -lclanDisplay -lclanCore

# EOF #
