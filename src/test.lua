-- print "LUA Advent"

display_init("LUA Advent", 640, 480, false)

myclickable = clickable_scene_create()
myscene     = scene_create()

view_create(myscene, myclickable)

sprite = sprite_drawable_create(320, 320, "person")

scene_add_drawable(myscene, sprite)
scene_add_drawable(myscene, sprite)

display_main_loop();

display_deinit();

-- EOF --
