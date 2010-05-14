;;;;;;;;;;;
;;  Odd  ;;
;;;;;;;;;;;

(adv:define-object scenario1:odd "Odds Device"
		   (seen 0)
		   (touched #f))
(adv:bind-surface scenario1:odd "odd" 339 223 239)
(adv:set-hotspot! scenario1:odd  378 345 2)

;;(define-method (adv:walkto-func (obj <scenario1:odd>))
;;(c:guy:set-direction 2))

#!(define-method (update (obj <scenario1:odd>))
    (println "Updating..")
    (c:advent:set-surface-pos obj 339 223 239))
!#
(define (repeat func times)
  (cond ((> times 0)
	 (func)
	 (repeat func (1- times)))))

(define (scenario1:odd-explosion)
  (println "TIME: " (sys:get-time))
  (c:fill-display 255 255 255 200)
  (adv:timed 100
	     (c:fill-display 255 255 255 220)
	     (adv:timed 100
			(c:fill-display 255 255 255 255)
			(adv:play (adv:frame "explo" '(282 146 255) 150 0)
				  (adv:frame "explo" '(282 126 255) 150 1)
				  (adv:frame "explo" '(282  96 255) 150 2)
				  (adv:frame "explo" '(282  56 255) 150 3)))))

;   (c:animation-play (make <animation> 
; 		      #:frames (list (make <frame> 
; 				       #:display-time 150
; 				       #:sub-frame 0
; 				       #:position  (list 282 146 255)
; 				       #:surface-name "explo")
; 				     (make <frame> 
; 				       #:display-time 150
; 				       #:sub-frame 1
; 				       #:position  (list 282 126 255)
; 				       #:surface-name "explo")
; 				     (make <frame> 
; 				       #:display-time 150
; 				       #:sub-frame 2
; 				       #:position  (list 282 96 255)
; 				       #:surface-name "explo")
; 				     (make <frame> 
; 				       #:display-time 150
; 				       #:sub-frame 3
; 				       #:position  (list 282 56 255)
; 				       #:surface-name "explo")
; 				     )))


(define-method (use (obj <scenario1:odd>))
  (cond ((not (touched obj))
	 (scenario1:odd-explosion)
	 (adv:timed 1000
		    (dialog:add "WOOOOW... what was that?!")
		    (set-touched obj #t)))
	(else
	 (dialog:add (random-ref '("Lets see if we can reproduce this effect."
				   "Let us touch it again..."
				   "It might be dangerous, but it looks cool")))
	 (adv:timed 2000
		    (scenario1:odd-explosion)
		    (adv:timed 1000
			       (dialog:add "So cool as if it where the first time..."))))))

(define-method (look (obj <scenario1:odd>))
  (repeat (lambda ()
	    (c:draw "odd" (list (random 640) (random 480)
				(random 255))))
	  250)
  (dialog:add "The crystal is flowting in the air..."
	      "...weird device")
  (adv:timed 2000
	     (set-seen obj (1+ (seen obj)))
	     (println "Timing... 2000")
	     (println "and again Timing... 2000")
	     (println "SEEN: " (seen obj)))
  (adv:timed 1000
	     (println "Timing... 1000")
	     )
  (println obj))

;;;;;;;;;;;
;; Chest ;;
;;;;;;;;;;;

;; We define an object, which can be referenced as "scenario1:chest"
(adv:define-object scenario1:chest "Chest"
		   (closed #t)) ;; The object has a state variable
;; closed, which will be #t by default

;; Connect the scm object to the c++ world...
(adv:bind-surface scenario1:chest "chest_closed" 214 331 230)

(println "scenario1:chest: " (adv:bind  scenario1:chest))
(advent:set-inventory-surface (adv:bind scenario1:chest) "chest_closed")

;;;;;;;;;;
;; Tree ;;
;;;;;;;;;;
(adv:define-object scenario1:tree "Tree")
(adv:bind-surface scenario1:tree "tree" 0 211 255)

;;;;;;;;;;;;;
;; Gateway ;;
;;;;;;;;;;;;;
(adv:define-object scenario1:gateway "Gateway")
(adv:bind-empty scenario1:gateway 405 105 130 225)

(define-method (use (obj <scenario1:gateway>))
  (adv:set-scenario game-scenario:outdoor3)
  (c:guy:set-position 450 340)
  (c:guy:set-direction 3))

(define-method (adv:walkto-pos (obj <scenario1:gateway>))
  (cons 424 324))

(define-method (adv:walkto-func (obj <scenario1:gateway>))
  (c:fill-display 255 255 255 200)
  (adv:timed 100
	     (c:fill-display 255 255 255 220)
	     (adv:timed 100
			(c:fill-display 255 255 255 255)
			(adv:set-scenario game-scenario:outdoor3)
			(c:guy:set-position 450 340)
			(c:guy:set-direction 3))))


;;;;;;;;;;
;; Door ;;
;;;;;;;;;;
(adv:define-object scenario1:door "Door"
		   (closed #t))
(adv:bind-surface scenario1:door  "door_closed" 198 211 0)

(define-method (adv:walkto-pos (obj <scenario1:door>))
  (cons 244 278))

(define-method (adv:walkto-func (obj <scenario1:door>))
  (cond ((not (closed obj))
	 (adv:set-scenario game-scenario:outdoor)
	 (c:guy:set-position   300 340)
	 (c:guy:set-direction 2))
	(else
	 (println "Door is closed."))))

(define-method (use (obj <scenario1:door>))
  (cond ((closed obj)
	 (advent:set-surface (adv:bind obj) "door_opened")
	 (set! (closed obj) #f))
	(else
	 (advent:set-surface (adv:bind obj) "door_closed")
	 (set! (closed obj) #t))))

(define (random-ref lst)
  (list-ref lst (random (length lst))))

(define scenario1:chest-counter 0)

(define-method (adv:walkto-pos (obj <scenario1:chest>))
  (cons 308 391))

(define-method (adv:walkto-func (obj <scenario1:chest>))
  (c:guy:set-direction 3))

#! This update stuff is silly and stupid, should be replaced with
something usefull (timed callbacks?)
;; The update methode is called once a game loop (15 times per second)
(define-method (update (obj <scenario1:chest>))
  (set! scenario1:chest-counter (1+ scenario1:chest-counter))
  (cond ((> scenario1:chest-counter 400)
	 (set! scenario1:chest-counter 0)
	 (dialog:add (random-ref '("...something is waiting for you..."
				   "...your dreams might come true..."
				   "...is this really happening..."
				   "...is their a life before death..."
				   "...will this ever have an end..."
				   )))
	 ))
  ;;(println "Updating chest")
  )
!#

;; This methode is involved when an open action (a click on the coin)
;; is performed
(define-method (use (obj <scenario1:chest>))
  (cond ((closed obj)
	 (advent:set-surface (adv:bind obj) "chest_opened")
	 (set! (closed obj) #f)
	 (dialog:add "Opened chest"))
	(else
	 (advent:set-surface (adv:bind obj) "chest_closed")
	 (dialog:add "Closed chest")
	 (set! (closed obj) #t))
	))

(define-method (pickup (obj <scenario1:chest>))
  (println "Trying to pick up the chest...")
  (inventory:add obj)
  (scenario:remove obj)
  (println "Picked up chest"))

(adv:define-scenario-new game-scenario:gateway 
			 #:surface  "background"
			 #:colmap   "background_cmap"
			 #:objects  (list scenario1:chest
					  scenario1:gateway
					  scenario1:door
					  scenario1:tree
					  scenario1:odd
					  ))

(set! (adv:enter-func game-scenario:gateway) 
      (lambda ()
	(println "enter game-scenario")))

(set! (adv:leave-func game-scenario:gateway) 
      (lambda ()
	(println "leave game-scenario")))

;; EOF ;;
