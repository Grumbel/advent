(define (bind-obj obj surface x y z)
  (set! (adv:bind obj) (advent:makeobj-surface (name obj) surface x y z))
  obj)

(adv:define-object scenario1:chest "Chest"
		   (closed #t))

(define-method gopen ((obj <scenario1:chest>))
  (cond ((closed obj)
	 (advent:set-surface (adv:bind obj) "chest_opened")
	 (set! (closed obj) #f)
	 (dialog:add "Opened chest"))
	(else
	 (advent:set-surface (adv:bind obj) "chest_closed")
	 (dialog:add "Closed chest")
	 (set! (closed obj) #t))
	 ))

(define game-scenario:gateway-objects
  (list (bind-obj scenario1:chest "chest_closed" 214 331 230)
	(make <door> #:adv:bind (advent:makeobj-surface "door" "door_closed" 
						198 211 0))
	(make <gateway:gateway> #:adv:bind (advent:makeobj-empty "Gateway" 
								 405 105
								 130 225))
	))

(define game-scenario:gateway-bind
  (scenario:make-bind "game-scenario:gateway"
		      "background" "background_cmap"
		      (map (lambda (x) (adv:bind x))
			   game-scenario:gateway-objects)))

;; EOF ;;
