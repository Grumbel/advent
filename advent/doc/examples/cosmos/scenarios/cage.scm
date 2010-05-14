(adv:defobj
 cage:switch
 (name "Switch")
 (hotspot  417 323 'east)
 (bind 444 226 458 252)
 (methods (game:look (person:talk "Its a light switch."))
	  (game:use  (person:talk "No, that would be a bad idea."))))

(adv:defobj
 cage:garbage
 (name "Garbage")
 (hotspot 352 320 'north)
 (bind 289 193 408 301)
 (methods (game:look   (person:talk "Lots of garbage here..."))
	  (game:pickup (person:talk "No, that is useless."))
	  (game:talk   (person:talk "I can't talk to garbage."))
	  ))

(adv:defdoor cage:door
	     (name "Door")
	     (hotspot 469 346 'east)
	     (target-position   1716 402 'south)
	     (target-scenario scenario:floor)
	     (bind (c:rect-collideable:create 460 175 540 340)))

(adv:defscenario scenario:cage
		 (dimension 640 480)
		 (drawables (adv:drawable:create "images/scenario_cage.jpg" 0 0 0))
		 (advobjs cage:door
			  cage:switch
			  cage:garbage)
		 (colmap "images/scenario_cage_cmap.png" 1.25))

;; EOF ;;