# Advent
# Copyright (C) 2015 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.0)
project(feuerkraft VERSION 0.2.0)

set(WARNINGS 0 CACHE BOOL "Switch on extra warnings")

if(WARNINGS)
  set(WARNINGS_CXX_FLAGS
    -pedantic -Wall -Wextra -Wno-c++0x-compat -Wnon-virtual-dtor -Weffc++
    -Wconversion -Werror -Wshadow -Wcast-qual -Winit-self -Wno-unused-parameter)
  # -Winline -Wfloat-equal -Wunreachable-code
endif()

include_directories(src/)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GUILE REQUIRED guile-1.8)
pkg_search_module(CLANCORE REQUIRED clanCore-1.0)
pkg_search_module(CLANAPP REQUIRED clanApp-1.0)
pkg_search_module(CLANSDL REQUIRED clanSDL-1.0)
pkg_search_module(CLANDISPLAY REQUIRED clanDisplay-1.0)
pkg_search_module(CLANSOUND REQUIRED clanSound-1.0)

set(ADVENT_SOURCES
  src/adv_hook.cxx
  src/adv_hook_smob.cxx
  src/adv_obj.cxx
  src/advent_main.cxx
  src/button_layer.cxx
  src/coin_layer.cxx
  src/collideable.cxx
  src/collideable_smob.cxx
  src/colmap.cxx
  src/colmap_smob.cxx
  src/debug.cxx
  src/delayed_adv_hook.cxx
  src/display.cxx
  src/display_view.cxx
  src/drawable.cxx
  src/drawable_adv_obj.cxx
  src/drawable_display.cxx
  src/drawable_layer.cxx
  src/drawable_smob.cxx
  src/empty_adv_obj.cxx
  src/fade_out_layer.cxx
  src/font_sprite.cxx
  src/guile.cxx
  src/inactive_layer.cxx
  src/instant_adv_hook.cxx
  src/inventory.cxx
  src/key_map.cxx
  src/key_map_handler.cxx
  src/layer.cxx
  src/layer_group.cxx
  src/layer_screen.cxx
  src/layer_smob.cxx
  src/mouse_cursor.cxx
  src/person.cxx
  src/person_gfx.cxx
  src/polygon_collideable.cxx
  src/rect_collideable.cxx
  src/rect_sprite.cxx
  src/resource_manager.cxx
  src/scenario.cxx
  src/scenario_layer.cxx
  src/screen_manager.cxx
  src/sprite.cxx
  src/sprite_collideable.cxx
  src/sprite_drawable.cxx
  src/sprite_group.cxx
  src/sprite_smob.cxx
  src/surface_colmap.cxx
  src/surface_sprite.cxx
  src/time_manager.cxx
  src/view.cxx)

add_library(advent SHARED ${ADVENT_SOURCES})
target_link_libraries(advent PUBLIC
  ${GUILE_LIBRARIES}
  ${CLANCORE_LIBRARIES}
  ${CLANAPP_LIBRARIES}
  ${CLANSDL_LIBRARIES}
  ${CLANDISPLAY_LIBRARIES}
  ${CLANGL_LIBRARIES}
  ${CLANSOUND_LIBRARIES}
  ${CLANMIKMOD_LIBRARIES}
  ${CLANVORBIS_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(advent PUBLIC
  ${GUILE_INCLUDE_DIRS}
  ${CLANCORE_INCLUDE_DIRS}
  ${CLANAPP_INCLUDE_DIRS}
  ${CLANSDL_INCLUDE_DIRS}
  ${CLANDISPLAY_INCLUDE_DIRS}
  ${CLANGL_INCLUDE_DIRS}
  ${CLANSOUND_INCLUDE_DIRS}
  ${CLANMIKMOD_INCLUDE_DIRS}
  ${CLANVORBIS_INCLUDE_DIRS})

# EOF #
