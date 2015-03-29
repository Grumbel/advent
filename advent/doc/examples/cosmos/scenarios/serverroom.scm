;; $Id: serverroom.scm,v 1.8 2001/11/02 08:43:00 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;

(person:set-scenario person2 scenario:serverroom)
(person:set-position person2 400 320)
(scenario:add-drawable scenario:serverroom (adv:bind person))

(adv:defobj serverroom:terminal
	    (name "Terminal")
	    (bind 303 187  353 236)
	    (hotspot 323 295 'north)
	    (methods (game:look (adv:seq (person:talk "Our good old terminal...")
					 (person:talk "Lets see whats going on.")
					 (person:talk "Terminal: C:\\ _")
					 (person:talk "Nothing special ;-)")
					 ))
		     (game:use (serverroom:terminal-use))
		     ))

(define (serverroom:terminal-use)
  (adv:seq (c:layerscreen:disable-input game-screen)
	   (person:talk "Lets try to use this thing...")
	   (person:talk "Could be fun ;-)")
	   (person:talk "...click...click...")
	   (person:talk "NSA Login: ")
	   (person:talk "Got it... lets better run away.")
	   (adv:walk-to-door scenario2-door)
	   (person:walk-to (person:current) 516 349)
	   (adv:sleep 2000)
	   (person:talk "Lets hope they wont find me here...")
	   (person:talk "Oh no... I guess they fount me...")
	   (c:layerscreen:enable-input game-screen)
	   ))

#!
(repeat 20
	(lambda ()
	  (scenario:add-drawable scenario:serverroom
				 (c:sprite-drawable:create
				  (c:font-sprite:create "font" "Bla...")
				  (random 640) (random 480) 1000))))
!#


(adv:defdoor serverroom:workplace-door
	     (name     "Tuer zum Arbeitsplatz")
	     (hotspot   437 288 'north)
	     (target-position  208 286 'south)
	     (target-scenario scenario:workplace)
	     (bind (c:rect-collideable:create 403 161 467 279)))

(adv:defdoor serverroom:floor-door
	     (name     "Tuer zum Flur")
	     (hotspot    514 315 'north)
	     (target-position  1225 398 'south)
	     (target-scenario scenario:floor)
	     (bind (c:rect-collideable:create 501 168  565 320)))


(adv:defscenario scenario:serverroom
		 (dimension 640 480)
		 (advobjs serverroom:terminal
			  serverroom:floor-door
			  serverroom:workplace-door)
		 (colmap "images/server-room_cmap.png" 1.7))

#!
 Wannabe syntax: keyword's
(colmap #:surface-file "images/server-room_cmap.png"
	#:scale 1.7)
!#

;; EOF ;;