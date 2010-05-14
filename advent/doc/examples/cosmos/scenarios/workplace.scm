;; $Id: workplace.scm,v 1.21 2003/02/26 23:11:44 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 
;;

(define bottle-of-wine-sprite  (c:surface-sprite:set-align-center
				(c:surface-sprite:create "images/bottle_inv.png")))

(define sprite-drawable1   (sprite-drawable:create "images/bottle.png" 220 300 0.760784))
(define calendar-drawable  (sprite-drawable:create "images/calendar.png" 220 300 0.760784))
(define sprite-collideable (c:sprite-collideable:create sprite-drawable1))

(println "Test1: " sprite-drawable1)
(println "Test2: " calendar-drawable)
(println "Test3: " sprite-collideable)

(adv:defobj
 workplace:calendar
 (name "Calendar")
 (hotspot 85 351 'north)
 (bind "images/calendar.png" 10 180 0.01)
 (status (game:burned #f))
 (methods (game:look   (person:talk "Hm, nothing special todo this week"))
	  (game:use    (person:talk "Currently no entries to make"))
	  (game:pickup (person:talk "Don't know if I need it.")
		       (person:add-to-inventory obj)
		       (scenario:remove-advobj scenario:workplace obj))))

(set! (adv:inventory-sprite workplace:calendar) 
      (c:surface-sprite:set-align-center
       (c:surface-sprite:create "images/calendar.png")))

(adv:defobj 
 bottle-of-wine
 (name "Bottle of Wine")
 (hotspot 245 338 'south)
 (bind   (c:drawable-advobj:create bottle-of-wine sprite-drawable1 sprite-collideable))
 (status (game:broken  #f)
	 (game:toggle #t)
	 (game:counter 0))
 (methods (game:look   (adv:seq (c:layerscreen:disable-input game-screen)
				(person:talk "A bottle full of wine.")
				(person:talk "I love wine ;-)")
				(c:layerscreen:enable-input game-screen)))
	  (game:pickup (person:talk "Might be usefull at a later point.")
		       (person:add-to-inventory obj)
		       (scenario:remove-advobj scenario:workplace obj)
		       (println "Removing..."))
	  (game:use    (println "--==:: Method on " obj " ::==--")
		       (cond ((game:toggle obj)
			      (c:drawable-advobj:set-drawable (adv:bind obj) calendar-drawable)
			      (set! (game:toggle obj) #f))
			     (else
			      (c:drawable-advobj:set-drawable (adv:bind obj) sprite-drawable1)
			      (set! (game:toggle obj) #t))))))

(adv:defobj
 workplace:burning-trash
 (name "burning trash")
 (hotspot 425 315 'south)
 (bind "images/burningtrashcan.png" 390 230 0.70 4)
 (status (game:burning #t)
	 (game:has-calendar #f))
 (methods
  (game:look 
   (println "Calendar Debug: " obj)
   (cond ((game:burning obj)
	  (cond ((game:has-calendar obj)
		 (person:talk "I see the calendar burning..."))
		(else
		 (person:talk "Its burning..."))))
	 (else
	  (cond ((game:has-calendar obj)
		 (adv:seq (person:talk "I see the burning calendar, I better take it")
			  (person:add-to-inventory workplace:calendar)))
		(else
		 (person:talk "The fire is out.")))
	  )))

  (game:pickup (cond ((game:burning obj)
		      (person:talk "I can't take it while it is burning."))
		     (else
		      (person:add-to-inventory obj)
		      (scenario:remove-advobj scenario:workplace obj))))))

(set! (adv:inventory-sprite workplace:burning-trash) 
      (c:surface-sprite:set-align-center
       (c:surface-sprite:create "images/burningtrashcanout_inv.png")))

(set! (adv:inventory-sprite bottle-of-wine) bottle-of-wine-sprite)

(define-method (adv:combine (obj2 <workplace:calendar>) (obj1 <bottle-of-wine>))
  (person:talk "Doing something else..."))

(define-method (adv:combine (obj1 <workplace:burning-trash>) (obj2 <bottle-of-wine>))
  (cond ((game:burning obj1)
	 (set! (game:burning obj1) #f)
	 (person:talk "The fire is out now")
	 (c:drawable-advobj:set-drawable 
	  (adv:bind obj1) 
	  (sprite-drawable:create "images/burningtrashcanout.png" 390 230 0.70)))
	(else
	 (person:talk "Its already out."))))

(define-method (adv:combine (obj1 <workplace:burning-trash>) (obj2 <workplace:calendar>))
  (cond ((game:burning obj1)
	 (adv:seq (person:talk "Lets try this and see what happens...")
		  (primitive-eval `(begin
                                    (person:remove-from-inventory ,obj2)
                                    (inventory-update (person:current))
                                    (person:talk "The calendar is now burned and destroyed.")
                                    (set! (game:burned ,obj2) #t)
                                    (set! (game:has-calendar ,obj1) #t)
                                    (set! (adv:inventory-sprite workplace:calendar) 
                                          (c:surface-sprite:set-align-center
                                           (c:surface-sprite:create "images/calendar_burned_inv.png")))))))
	(else
	 (person:talk "The trashcan isn't buring, so I can't destroy the calendar here."))))


(define-method (adv:combine (obj1 <bottle-of-wine>) (obj2 <workplace:calendar>))
  (person:talk "Doing something..."))

;; Window
(adv:defobj workspace-window
	    (name "Window")
	    (hotspot 511 330 'east)
	    (bind (c:empty-advobj:create workspace-window 
					 (c:rect-collideable:create 518 152 587 259)))
	    (methods (game:speak
		      (person:talk "I see the street..."))

		     (game:use 
		      (person:talk "I don't want to open the window.\nI would be getting cold."))

		     (game:pickup 
		      (person:set-position 326 365)
		      (person:set-scenario scenario:park)
		      )
		     ))


(define dark-layer (c:sprite-drawable:create (c:rect-sprite:create 640 480 '(0 0 0 0.7)) 0 0 500))

(adv:defobj
 light-switch
 (name    "Light switch")
 (hotspot 167 293 'west)
 (bind    (c:empty-advobj:create light-switch
				 (c:rect-collideable:create 147 217 155 232)))
 (status (game:on #f))
 (methods (game:use (println "Switch status: " (game:on obj))
		    (cond ((game:on obj)
			   (scenario:remove-drawable scenario:workplace dark-layer)
			   (fixme:say-pos "*click*" 150 200)
			   (set! (game:on obj) #f))
			  (else
			   (scenario:add-drawable scenario:workplace dark-layer)
			   (fixme:say-pos "*click*" 150 200)
			   (set! (game:on obj) #t))))))

(adv:defdoor workplace-chef-door
	     (name "Tuer zum Chef")
	     (hotspot 216 290)
	     (target-position  435 285)
	     (target-scenario scenario:serverroom)
	     (bind (c:rect-collideable:create 181 169 242 281)))


(adv:defdoor serverroom-door
	     (name "Tuer zum Floor")
	     (hotspot 132 320)
	     (target-position 1225 398 'east)
	     (target-scenario scenario:floor)
	     (bind (c:rect-collideable:create 81 169  141 311)))

(define-method (adv:combine (obj1 <light-switch>) (obj2 <bottle-of-wine>))
  (person:talk "Thats not a good idea...\nElectricity and liquids don't mix well."))

(println "<<<<<<<<<<<<<<<<<<<<<<<<")
(adv:defscenario scenario:workplace ;; Scenarioname
		 (dimension 640 480)
		 (drawables (adv:drawable:create "images/trashcan.png" 255 280 0.713726)
			    (adv:drawable:create "images/trashcan.png" 325 285 0.901961)
			    (adv:drawable:create "images/trashcan.png" 330 320 0.94002)
			    (adv:drawable:create "images/trashcan.png" 300 330 0.94902)
			    (adv:drawable:create "images/bottle.png"   400 330 30)
			    (adv:drawable:create "images/bottle.png"   450 300 30)
			    (adv:drawable:create "images/workplace-room.jpg" 0 0 0))
		 (advobjs light-switch 
			  bottle-of-wine
			  workspace-window
			  workplace:calendar
			  workplace:burning-trash
			  ;; Doors
			  workplace-chef-door
			  serverroom-door)
		 (colmap "images/colmap.png" 1.25))
(println ">>>>>>>>>>>>>>>>>>>>>>>>")

;; EOF ;;
