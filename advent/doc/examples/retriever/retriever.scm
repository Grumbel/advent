#!/usr/bin/guile \
--debug -e main -s
!#

(use-modules (advent core)
	     (oop goops))

(load "../../../advent/engine.scm") ;; Should be a module

;; --- Helper Stuff ;;

;; --- Helper Stuff ;;
(load "helper.scm")

;; The 'GUI' of the game
(load "interface.scm")

(adv:defperson person)

#! Wannabe:
(adv:defperson person
  (speed 5.0)      ;; speed in pixel per second
  (frame-step #f)) ;; let the person work only on frame changes
!#

(define (persongfx:create . args)
  (let* ((standing (get-keyword-value args #:standing #f))
	 (walking  (get-keyword-value args #:walking standing)))

    (if (not standing)
	(println "persongfx:create: standing gfx not set"))

    (c:persongfx:create (list walking standing))
    ))

(define person-gfx
  (persongfx:create
   #:standing (list (adv:surface-sprite:create "images/prof_north.png" #:align '(-62 . -265))
		    (adv:surface-sprite:create "images/prof_east.png"  #:align '(-45 . -265))
		    (adv:surface-sprite:create "images/prof_south.png" #:align '(-62 . -265))
		    (adv:surface-sprite:create "images/prof_west.png"  #:align '(-45 . -265)))
   #:walking (list (adv:surface-sprite:create "images/prof_north.png" #:align '(-62 . -265))
		   (adv:surface-sprite:create "images/prof_east_anim.png" #:align '(-45 . -265)
					      #:frames 8)
		   (adv:surface-sprite:create "images/prof_south.png" #:align '(-62 . -265))
		   (adv:surface-sprite:create "images/prof_west_anim.png" #:align '(-45 . -265)
					      #:frames 8))))

(c:scenariolayer:set-person scenario-layer (adv:bind person))
(c:person:set-gfx (adv:bind person) person-gfx)
(c:person:set-catchable (adv:bind person) #f)

(person:set-current person)

(adv:load-scenarios (scenario:gateway  "gateway/gateway.scm")) ;; ok

(person:set-scenario person scenario:gateway)

(define fadeout-layer (c:fadeout-layer:create))
(c:layerscreen:push game-screen fadeout-layer)
(c:fadeout-layer:blackout fadeout-layer)
(adv:seq (adv:sleep 2000)
	 (c:fadeout-layer:fade-in fadeout-layer))


(define (main args)
  (c:display:setup 640 480 'fullscreen) ;; should be nicer integrated
  (display "---------------------------------")  (newline)
  (advent:main-loop) ;; ok
  )

;; EOF ;;
