cmake_minimum_required(VERSION 3.0)
project(advent VERSION 0.0.0)

set(WARNINGS 0 CACHE BOOL "Switch on extra warnings")

if(WARNINGS)
  set(WARNINGS_CXX_FLAGS
    -pedantic -Wall -Wextra -Wno-c++0x-compat -Wnon-virtual-dtor -Weffc++
    -Wconversion -Werror -Wshadow -Wcast-qual -Winit-self -Wno-unused-parameter)
  # -Winline -Wfloat-equal -Wunreachable-code
endif()

include_directories(src/)

add_definitions(-DSWIGGUILE)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GUILE REQUIRED guile-1.8)
pkg_search_module(CLANCORE REQUIRED clanCore-1.0)
pkg_search_module(CLANAPP REQUIRED clanApp-1.0)
pkg_search_module(CLANDISPLAY REQUIRED clanDisplay-1.0)
pkg_search_module(CLANSDL REQUIRED clanSDL-1.0)
pkg_search_module(CLANGL REQUIRED clanGL-1.0)
pkg_search_module(CLANSOUND REQUIRED clanSound-1.0)
pkg_search_module(CLANMIKMOD REQUIRED clanMikMod-1.0)
pkg_search_module(CLANVORBIS REQUIRED clanVorbis-1.0)

set_source_files_properties(src/swig_scripting.i PROPERTIES CPLUSPLUS ON)
swig_add_module(advent_wrap guile src/swig_scripting.i)
set(ADVENT_WRAP_GENERATED_SOURCES ${swig_generated_file_fullname})

file(GLOB ADVENT_SOURCES
  src/*.cxx)

list(APPEND ADVENT_SOURCES ${ADVENT_WRAP_GENERATED_SOURCES})

add_executable(advent ${ADVENT_SOURCES})
target_link_libraries(advent PRIVATE
  ${GUILE_LIBRARIES}
  ${CLANCORE_LIBRARIES}
  ${CLANAPP_LIBRARIES}
  ${CLANDISPLAY_LIBRARIES}
  ${CLANSDL_LIBRARIES}
  ${CLANGL_LIBRARIES}
  ${CLANSOUND_LIBRARIES}
  ${CLANMIKMOD_LIBRARIES}
  ${CLANVORBIS_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(advent PRIVATE
  ${GUILE_INCLUDE_DIRS}
  ${CLANCORE_INCLUDE_DIRS}
  ${CLANAPP_INCLUDE_DIRS}
  ${CLANDISPLAY_INCLUDE_DIRS}
  ${CLANSDL_INCLUDE_DIRS}
  ${CLANGL_INCLUDE_DIRS}
  ${CLANSOUND_INCLUDE_DIRS}
  ${CLANMIKMOD_INCLUDE_DIRS}
  ${CLANVORBIS_INCLUDE_DIRS})

# EOF #

