bindir=$(prefix)/games

bin_PROGRAMS = advent

advent_SOURCES = Advent.cc         Background.cc    Font.cc            Position.hh \
Advent.hh         Background.hh    Font.hh            Scenario.cc \
AdventObj.cc      Coin.cc          GuileAdventObj.cc  Scenario.hh \
AdventObj.hh      Coin.hh          GuileAdventObj.hh \
AdventObjSmob.cc  CollisionMap.cc  Inventory.cc \
AdventObjSmob.hh  CollisionMap.hh  Inventory.hh

# SUBDIRS = guile data

EXTRA_DIST = guile/*.scm data/resources.scr \
             data/images/*.png data/images/*.jpg

# EOF #
