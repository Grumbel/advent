
(adv:defdoor farm:door
	     (name "Door")
	     (hotspot 332 293 'north)
	     (target-position 320 346)
	     (target-scenario scenario:cage)
	     (bind (c:rect-collideable:create 287 140 363 282)))


(adv:defobj farm:fork
	    (name "Fork")
	    (hotspot 570 300 'north)
	    (bind 545 173 582 285)
	    (methods (game:look (person:talk "A nice old-style fork."))
		     (game:use  (person:talk "I have currently no use for this."))
		     ))

(adv:defobj farm:window
	    (name "Window")
	    (hotspot 490 296 'north)
	    (bind 442 137 524 205)
	    (methods (game:speak (dialog-test))))

(define (dialog-test)
  (dialog:show game-screen window-dialog))

;; FIXME: Namespace polution... time for a module system
(define-method (farm-window-talk (text <string>))
  (adv:talk scenario:farm (cons 485 71) text))

(adv:defdialog  window-dialog
		("Hello, is anybody there?"           
		 (adv:seq (farm-window-talk "No.") 
			  (dialog:show game-screen anybody-there?-dialog)))
		
		("Open the door! Here is the police."
		 (adv:seq (farm-window-talk "NOOOOOO, the POLICE!")
			  (dialog:show game-screen police-dialog)))
		
		("Sorry, for bothering you."
		 #f #f))

(adv:defdialog anybody-there?-dialog
	       ("blablub" #f #f))

(adv:defdialog police-dialog
	       ("Hello? bla/blub" #f #f)
	       ("Hello how are you" #f #f))

(adv:defscenario scenario:farm
		 (dimension 640 480)

		 (drawables (adv:drawable:create "images/farm.jpg" 0 0 0)
			    (adv:drawable:create "images/farm_barrel.png" 0 (- 480 149) 1)
			    (adv:drawable:create "images/farm_hay.png" (- 640 171) (- 480 109) 2))

		 (advobjs farm:fork
			  farm:door
			  farm:window)

		 (colmap "images/farm_cmap.png"))

;; EOF ;;