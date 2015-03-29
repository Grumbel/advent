#!/usr/bin/guile \
--debug -e main -s
!#

;; $Id: cosmos.scm,v 1.25 2003/02/26 23:11:44 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; A simple test adventure game
;;

(use-modules (advent core)
;;	     (advent engine)
	     (oop goops))

(load-from-path "advent/engine.scm")

(println "############## c:delayed-advhook:create: " c:delayed-advhook:create)

(c:display:setup 640 480 'fullscreen)

(load "helper.scm")
(load "interface.scm")
(load "inventory.scm")
(println "cosmos:step1")


(adv:defperson person2)
(set! (adv:speech-font person2) "arialfont14_orange")

(adv:defperson person)
(set! (adv:inventory-update-hook person) inventory-update)

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

(define (center-bottom-sprite:create sprite)
  (let ((sprite-group (c:sprite-group:create)))
    (c:sprite-group:add sprite-group sprite
			(- (quotient (c:sprite:get-width sprite) 2))
			(- (c:sprite:get-height sprite)))
    sprite-group))

(define person2-gfx
  (c:persongfx:create (list
		       (list
			(center-bottom-sprite:create
			 (c:surface-sprite:create "images/roboter_north.png"))
			(center-bottom-sprite:create
			 (c:surface-sprite:create "images/roboter_east.png"))
			(center-bottom-sprite:create
			 (c:surface-sprite:create "images/roboter_south.png"))
			(center-bottom-sprite:create
			 (c:surface-sprite:create "images/roboter_west.png")))
		       (list
			(center-bottom-sprite:create
			 (c:surface-sprite:create "images/roboter_north.png"))
			(center-bottom-sprite:create
			 (c:surface-sprite:create "images/roboter_east.png"))
			(center-bottom-sprite:create
			 (c:surface-sprite:create "images/roboter_south.png"))
			(center-bottom-sprite:create
			 (c:surface-sprite:create "images/roboter_west.png"))))))

(c:person:set-gfx (adv:bind person) person-gfx)
(c:person:set-gfx (adv:bind person2) person2-gfx)

(define (sprite-group:create . sprites)
  (let ((sprite (c:sprite-group:create)))
    (for-each (lambda (obj)
		(println "SpriteGroup: " obj)
		(c:sprite-group:add sprite obj 0 0))
	      sprites)
    sprite))

(define (center-sprite:create sprite)
  (let ((sprite-group (c:sprite-group:create)))
    (c:sprite-group:add sprite-group sprite
			(- (/ (c:sprite:get-width sprite) 2))
			(- (/ (c:sprite:get-height sprite) 2)))
    sprite-group))


(define keymap (c:keymap:create))
(define keymaphandler (c:keymaphandler:create))
(c:keymaphandler:set-keymap keymaphandler keymap)
(c:keymap:bind-key keymap KEY:F9 (lambda () (println "Got press")))


(adv:defdialog test-dialog
	       ("Hello 1" #f test1-dialog)
	       ("Hello 2" #f test1-dialog)
	       ("Hello 3" #f test1-dialog)
	       ("Hello 4" #f test1-dialog)
	       ("Hello 5" #f test1-dialog))

(adv:defdialog test1-dialog
	       ("Hello? bla/blub" #f (dialog:clear))
	       ("Hello how are you" #f (dialog:clear)))

(c:keymap:bind-key keymap KEY:F8 (lambda () (dialog:show game-screen test-dialog)))

;; Establish symbol->file mappings
(adv:load-scenarios (scenario:workplace  "scenarios/workplace.scm")
		    (scenario:serverroom "scenarios/serverroom.scm")
		    (scenario:cage       "scenarios/cage.scm")
		    (scenario:park       "scenarios/park.scm")
		    (scenario:floor      "scenarios/floor.scm")
		    (scenario:farm       "scenarios/farm.scm"))

(person:set-current person)
(c:scenariolayer:set-person scenario-layer (adv:bind person))

(c:person:set-catchable (adv:bind person2) #t)

;; Start Position
(person:set-scenario person scenario:floor)
(person:set-position person 300 430)

;;(person:set-scenario person scenario:farm)
;;(person:set-position person 300 350)

;; The object which the person is holding currently in its hand
(define *current-object* #f)

(define (person2-repeating)
  (person:talk person2 (random-ref '("no time... no time..."
				     "I need to hurry..."
				     "what should I do..."
				     "need to run away...")))
  (c:timemanager:add timemanager 2000 person2-repeating))

;;(c:timemanager:add timemanager 2000 person2-repeating)


(set! (adv:inventory-update-hook person) inventory-update)

(define (fixme:say text)
  (let ((drawable (c:sprite-drawable:create
		   (c:font-sprite:create "arialfont14_blue" text)
		   320 64 1000))
	(scenario (person:get-scenario person)))

    (scenario:add-drawable scenario drawable)
    (c:timemanager:add timemanager 1000 (lambda ()
					  (scenario:remove-drawable scenario drawable)))
    ))

(define (fixme:say-pos text pos-x pos-y)
  (let ((drawable (c:sprite-drawable:create
		   (c:font-sprite:create "font" text)
		   pos-x pos-y 1000))
	(scenario (person:get-scenario person)))

    (scenario:add-drawable scenario drawable)
    (c:timemanager:add timemanager 400 (lambda ()
					 (scenario:remove-drawable scenario drawable)))
    ))




(println "Trying that")
(define-class <calendar> (<adv:object>))

;(scenario:add-advobj scenario (c:sprite-advobj:create (make <calendar>)
;							"images/calendar.png" 10 180 50))
;;(define-method (my:on-click (obj <calendar>))
;;  (c:scenariolayer:set-scenario scenario-layer scenario:serverroom))

;; Scenario2

(scenario:add-drawable scenario:serverroom
		       (sprite-drawable:create "images/trashcan.png" 540 320 4.5))
(scenario:add-drawable scenario:serverroom
		       (sprite-drawable:create "images/server-room.jpg" 0 0 0))

(c:coinlayer:set-click-func coin-layer
			    (lambda (obj x y)
			      (println "Offset: " x " " y)
			      (let ((func (case (cond ((< x 0)
						       (cond ((< y 0) 'use)
							     ((> y 0) 'pickup)))
						      ((> x 0)
						       (cond ((< y 0) 'look)
							     ((> y 0) 'speak)))
						      (else #f))
					    ((use)    game:wrapper-use)
					    ((look)   game:wrapper-look)
					    ((pickup) game:wrapper-pickup)
					    ((speak)  game:wrapper-speak)
					    (else #f))))
				(cond (func
				       (func obj))
				      (else
				       (println "Cursor left Coin")))
				(set! *coin-visible #f)
				)))

(define-method (adv:combine (obj1 <adv:object>) (obj2 <adv:object>))
  (person:talk "Don't know how to combine these objects.")
  (println "Obj: " obj1 " " obj2))

(define (my-on-click-handler obj)
  (println "Doing on-click action with " obj)
  (cond ((not *current-object*)
	 (set! *coin-visible #t)
	 (c:coinlayer:enable coin-layer obj))
	(else
	 ;; FIXME: walk-to doesn't work
	 (let ((obj2 *current-object*))
	   (adv:seq (person:walk-to obj)
		    (adv:combine obj obj2)))
	 (set! *current-object* #f)
	 (c:scenariolayer:mouse-update scenario-layer)
	 )))

(define-method (my:on-click (obj <adv:object>))
  (println "No my:on-click action set for: " obj))

(define-method (my:on-click (obj <adv:door>))
  (println "CLICK ON DOOR"))

(adv:set-on-click-handler my-on-click-handler)
(println "Loading done...")
(println "Smob: " game-screen)

(define-method (game:wrapper-use (obj <adv:object>))
  ;; FIXME: Hotspot handling not good...
  (adv:seq (person:walk-to obj)
	   (game:use obj)))

;; Wrapper functions which cause the guy to walk to the object instead
;; of acting immediatly
(define-method (game:wrapper-look (obj <adv:object>))
  (adv:seq (person:walk-to obj)
	   (begin (person:set-direction (caddr (adv:get-hotspots obj)))
		  (println "Direction setter"))
	   (game:look obj)))

(define-method (game:wrapper-pickup (obj <adv:object>))
  (adv:seq (person:walk-to obj)
	   (game:pickup obj)))

(define-method (game:wrapper-speak (obj <adv:object>))
  (adv:seq (person:walk-to obj)
	   (game:speak obj)))

(define-method (game:use (obj <adv:object>))
  (println "--==:: use not implemnted"))
(define-method (game:look (obj <adv:object>))
  (println "look not implemnted"))
(define-method (game:pickup (obj <adv:object>))
  (person:talk "I cannot pickup this")
  (println "pickup not implemnted")
   )
(define-method (game:speak (obj <adv:object>))
  (println "speak not implemnted"))

(define-method (game:use (obj <calendar>))
  (println "This is a callendar"))


(println "Creating keymap")


;;(c:keymap:bind-key keymap KEY:F4 person2-walkaround)
(println "Inventory preparing")
(define (show-inventory)
  (c:layerscreen:push game-screen inventory-layer)
  (c:inventory:set-visible inventory-layer #t)
  (c:keymap:bind-key keymap KEY:F4 hide-inventory))

(define (hide-inventory)
  (c:layerscreen:pop game-screen)
  (c:inventory:set-visible inventory-layer #f)
  (c:keymap:bind-key keymap KEY:F4 show-inventory))

(c:keymap:bind-key keymap KEY:F4 show-inventory)

;; This is extremly slow... don't know why. Probally some bug in the mark function
(define (person2-walkaround)
  ;;  (with-fluids ((*person:current* person2))
  (adv:seq (adv:walk-to-door person2 scenario2-door)
	   (person:walk-to   person2 320 380)
	   (println "Dies ist ein Test")
	   (println "Dies ist ein Test")
	   (adv:sleep 1000)
	   (println "Dies ist ein Test")
	   (adv:walk-to-door person2 serverroom-door)
	   (person:walk-to person2 320 380)
	   (person2-walkaround)
	   ))

(c:keymap:bind-key keymap KEY:F1 person2-walkaround)

(c:sprite-drawable:create (c:surface-sprite:create "images/404.png") 540 320 4.5)

(println "Step 11")

;; LOAD SCREEN

(define load-screen (c:layerscreen:create))

(define load-screen:load-button
  (c:buttonlayer:create (c:font-sprite:create "font" "Load") #f #f 50 50))
(define load-screen:play-button
  (c:buttonlayer:create (c:font-sprite:create "font" "Play") #f #f 50 100))
(println "Step 12")
(c:buttonlayer:set-press-callback load-screen:play-button
				  (lambda ()
				    ;;(c:screenmanager:set-screen game-screen)
				    (c:layerscreen:pop game-screen)
				    ))

(c:buttonlayer:set-press-callback load-screen:load-button
				  (lambda ()
				    (println "Not implemented")))


(c:layerscreen:push load-screen (c:drawable-layer:create
				 (c:sprite-drawable:create
				  (c:rect-sprite:create 640 480 '(0.4 0.4 0.4 0.5))
				  0 0 0)))

(c:layerscreen:push load-screen (c:drawable-layer:create
				 (c:sprite-drawable:create
				  (c:rect-sprite:create 540 420 '(0 0 0 1))
				  50 30 0)))

(for (y 50 380 100)
     (for (x 100 540 175)
	  (let* ((button (c:buttonlayer:create
			  (c:surface-sprite:create "images/scenario1.png") #f #f x y))
		 (rect-sprite (c:rect-sprite:create 130 95 '(1 1 1 0.5)))
		 (status #f)
		 (rect 	(c:drawable-layer:create
			 (c:sprite-drawable:create rect-sprite
						   (- x 10) (- y 10) 10))))
	    (c:layerscreen:push load-screen rect)
	    (c:layerscreen:push load-screen button)

	    (c:buttonlayer:set-press-callback button
					      (lambda ()
						(println "Pressed button: " x " " y)
						(cond ((not status)
						       (c:rect-sprite:set-color rect-sprite '(1 1 1 1))
						       (set! status #t))
						      (else
						       (c:rect-sprite:set-color rect-sprite '(.5 .5 .5 1))
						       (set! status #f))
						      ))
					      ))))

(println "Step 15.0")
(c:layerscreen:push load-screen load-screen:load-button)
(c:layerscreen:push load-screen load-screen:play-button)
(println "Step 16")
(c:layerscreen:push load-screen mouse-cursor)
;; END LOAD SCREEN



(define (display-save-screen)
  (println "Displaying load screen...")
  #f)

(define (display-load-screen)
  (println "Displaying load screen...")
  (c:layerscreen:push game-screen load-screen)
  ;;  (c:screenmanager:set-screen load-screen)
  #f)

(c:keymap:bind-key keymap KEY:F5 (lambda () (display-load-screen)))
(c:keymap:bind-key keymap KEY:F6 (lambda () (display-save-screen)))


;; Help Window
(define help-screen #f)

;; Load a file into a vector
(define (file->vector filename)
  (let ((port (open-file filename "r"))
	(content '()))
    (let loop ((line (read-line port)))
      (cond ((eof-object? line)
	     '())
	    (else
	     (set! content (cons line content))
	     (loop (read-line port)))))
    (close-port port)
    (list->vector (reverse content))
    ))

(define start-line 0)
(define content #f)
(define (display-text-file filename)
  (set! help-screen (c:layerscreen:create))
  (if (not content)
      (set! content (file->vector filename)))
  ;;(println content)
  (c:layerscreen:push help-screen (c:drawable-layer:create
				   (c:sprite-drawable:create
				    (c:rect-sprite:create 640 480 '(0.4 0.4 0.4 0.5))
				    0 0 0)))

  (if (< start-line 0)
      (set! start-line 0))
  (if (>= (+ start-line 20) (vector-length content))
      (set! start-line (- (vector-length content) 21)))

  (for (i 0 20)
       (c:layerscreen:push help-screen
			   (c:drawable-layer:create
			    (c:sprite-drawable:create
			     (c:font-sprite:create "font"
						   (vector-ref content (+ start-line i)))
			     10 (+ 10 (* i 20)) 10))))
  (c:screenmanager:set-screen help-screen))


(c:keymap:bind-key keymap KEY:F9  (lambda () (set! start-line (1- start-line))
					  (display-text-file "cosmos.scm")))
(c:keymap:bind-key keymap KEY:F10 (lambda () (set! start-line (1+ start-line))
					  (display-text-file "cosmos.scm")))

(c:keymap:bind-key keymap KEY:F7 (lambda ()
				   (person:talk "Test text...aeuoeu")))

(c:keymap:bind-key keymap KEY:F11 (lambda ()
				    (println "Remove: " (adv:inventory person))
				    (person:remove-from-inventory bottle-of-wine)
				    (inventory-update (person:current))))

(c:keymap:bind-key keymap KEY:F12 (lambda ()
				    (println "Add:" (adv:inventory person))
				    (person:add-to-inventory bottle-of-wine)
				    (inventory-update (person:current))))

(c:keymap:bind-key keymap KEY:F2 (lambda ()
				   (c:layerscreen:enable-input game-screen)))
(c:keymap:bind-key keymap KEY:F3 (lambda ()
				   (c:layerscreen:disable-input game-screen)))

;; Start the engine
(advent:main-loop)

;; EOF ;;