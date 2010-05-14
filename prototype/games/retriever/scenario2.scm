;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; First outdoor scene, in front of the house ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;; Crack ;;;;;;;;;;;;
(adv:define-object scenario2:crack "Crack")
(adv:bind-empty scenario2:crack 475 266 80 80)
(adv:set-hotspot! scenario2:crack  488 363 0)

(define (adv:dance args end-func)
  (cond ((not (null? args))
	 (c:guy:set-target (car args) (cadr args)
			   (lambda ()
			     (adv:dance (cddr args) end-func))))
	(else
	 (if end-func
	     (end-func)))))

(define-method (adv:look (obj <scenario2:crack>))
  (dialog:add "I am gonna feel like I need to dance...")
  (adv:dance (list 354 431
		   444 420
		   295 428
		   349 385
		   295 428
		   354 431
		   444 420
		   295 428
		   443 428
		   413 424
		   322 424
		   443 428
		   413 424
		   322 424
		   277 371
		   349 385
		   295 428
		   354 431
		   444 420
		   295 428
		   443 428
		   413 424
		   322 424
		   277 371
		   349 385
		   295 428)
	     (lambda ()
	         (dialog:add "...wow, enough dancing for now."))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(adv:define-object scenario2:path "Path")

(define-method (adv:walkto-pos (obj <scenario2:path>))
  (cons 22 424))

(define-method (adv:walkto-func (obj <scenario2:path>))
  (adv:set-scenario game-scenario:outdoor2)
  (c:guy:set-position  614 439)
  (c:guy:set-direction 3))

(adv:bind-empty scenario2:path  0 260 70 220)

;; Objects

;; Plant

(adv:define-object scenario2:plant "Plant")
(adv:bind-surface scenario2:plant "plant2" 208  350 194)

(define-method (adv:walkto-pos (obj <scenario2:plant>))
  (cons 180 420))

(define-method (adv:walkto-func (obj <scenario2:plant>))
  (c:guy:set-direction 1))

;; Door
(adv:define-object scenario2:door "Door" (foobar #f))
(adv:bind-surface scenario2:door "s2_door_opened" 236 247 0)

(define-method (adv:walkto-pos (obj <scenario2:door>))
  (cons 302 336))

(define-method (adv:walkto-func (obj <scenario2:door>))
  (cond ((not (closed scenario1:door))
	 (adv:set-scenario game-scenario:gateway)
	 (c:guy:set-position  241 278)
	 (c:guy:set-direction 2)) 
	(else
	 (dialog:add "Door is closed."))))

(define-method (look (obj <scenario2:door>))
  (cond ((closed scenario1:door)
	 (dialog:add "The door is close."))
	(else
	 (dialog:add "The door is open."))))

(define-method (use (obj <scenario2:door>))
  (cond ((closed scenario1:door)
	 (advent:set-surface (adv:bind obj) "s2_door_opened")
	 (set! (closed scenario1:door) #f))
	(else
	 (advent:set-surface (adv:bind obj) "s2_door_closed")
	 (set! (closed scenario1:door) #t))
	 ))

;;;;;;;;;
;; Rod ;;
;;;;;;;;;

(adv:define-object scenario2:rod "Rod")
(adv:bind-surface scenario2:rod  "rod" 511 392 0)
(advent:set-inventory-surface (adv:bind scenario2:rod) "rod_inventory")

(define-method (adv:walkto-pos (obj <scenario2:rod>))
  (cons 530 390))

(define-method (pickup (obj <scenario2:rod>))
  (dialog:add "This rod is really solid, looks usefull.")
  (inventory:add obj)
  (scenario:remove obj))

(define-method (look (obj <scenario2:rod>))
  (dialog:add "A solid rod, maybe it is usefull for something..."))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define game-scenario:outdoor-objects
  (list scenario2:door
	scenario2:plant
	scenario2:path
	scenario2:crack
	scenario2:rod))

(define game-scenario:outdoor-bind
  (c:scenario:make-bind "game-scenario:outdoor"
		      "background2" "background2_cmap"
		      (map (lambda (x) (adv:bind x))
			   game-scenario:outdoor-objects)
		      #t))

(define game-scenario:outdoor
  (make <scenario> 
    #:adv:symbol 'game-scenario:outdoor
    #:adv:bind game-scenario:outdoor-bind
    #:adv:objs game-scenario:outdoor-objects))

;; EOF ;;