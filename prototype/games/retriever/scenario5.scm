;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Fourth outdoor scene, the door ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;
(adv:define-object scenario5:smoke "Smoke")
(adv:bind-surface scenario5:smoke "smoke_anim" 491 -56 0)
;;;;;;;;;


(adv:define-object outdoor4:console "Console")
(adv:bind-surface outdoor4:console "console" 250 398 228)

(define-method (adv:walkto-pos (obj <outdoor4:console>))
  (cons 245 462))

(define-method (look (console <outdoor4:console>))
  ;;  (dialog:add "The console has a large keyhole like hole, maybe you can find a key for it?")
  (adv:set-scenario scenario:console))

(define-method (use (console <outdoor4:console>))
  (dialog:add "You press a button but nothing happens")
  (dialog:add "Maybe you should place a key in the keyhole?")
  )
;;  (let ((obj (get-obj "door"))) ;; no need for get-obj here
;;    (cond ((closed obj)
;;	   (set! (closed obj) #f)
;;	   (advent:set-surface (adv:bind obj) "door_obj"))
;;	  (else
;;	   (set! (closed obj) #t)
;;	   (advent:set-surface (adv:bind obj) "")))))

(define-method (combine (obj1 <outdoor2:key>) (obj2 <outdoor4:console>))
  (cond ((not (broken scenario5:door-control))
	 (cond ((closed outdoor4:door)
		(cond ((firsttime outdoor4:door)
		       (dialog:add "Krgggrrr..."
				   "Something is happening...")
		       (c:add-timed 5000
				    (lambda ()
				      (set! (firsttime outdoor4:door) #f)
				      (set! (closed outdoor4:door) #f)
				      (advent:set-surface (adv:bind outdoor4:door) "door_obj")
				      (c:advent:set-surface-pos (adv:bind outdoor4:door) 294 108 0)
				      (dialog:add "Wow, its finally open"))))
		      (else
		       (set! (closed outdoor4:door) #f)
		       (advent:set-surface (adv:bind outdoor4:door) "door_obj")
		       (c:advent:set-surface-pos (adv:bind outdoor4:door) 294 108 0))))
	       (else
		(set! (closed outdoor4:door) #t)
		(advent:set-surface (adv:bind outdoor4:door) "bdoor_c")
		(c:advent:set-surface-pos (adv:bind outdoor4:door) 362 12 0))))
	 (else
	  (dialog:add "You put the key in the keyhole and turn it around, but nothing happens."))))

;;;;;;;;;;;;;;;;;;
;; Door Control ;;
;;;;;;;;;;;;;;;;;;

(adv:define-object scenario5:door-control "Hole"
		   (broken #t))
(adv:bind-surface scenario5:door-control "rod_not_in_door" 581 419 0)
;;(advent:set-surface (adv:bind scenario5:door-control) "")

(define-method (adv:walkto-pos (obj <scenario5:door-control>))
  (cons 552 467))

(define-method (combine (obj1 <scenario2:rod>) (obj2 <scenario5:door-control>))
  (advent:set-surface (adv:bind obj2) "rod_in_door")
  (set! (broken obj2) #f)
  (inventory:remove obj1)
  (dialog:add "You place the rod in the hole..."))

(define-method (look (obj <scenario5:door-control>))
  (if (broken obj)
      (dialog:add "Looks like connection rod is missing.")
      (dialog:add "Looks like this fix could work.")))

(define-method (pickup (obj <scenario5:door-control>))
  (if (broken obj)
      (dialog:add "There is nothing that I could take with me.")
      (dialog:add "I better leave the rod there.")))

;;;;;;;;;;;;;;;;;;;;;;;;;

(adv:define-object outdoor4:back "back")
(adv:bind-empty outdoor4:back 0 300 70 340)
(define-method (adv:walkto-pos (obj <outdoor4:back>))
  (cons 0 426))
(define-method (adv:walkto-func (obj <outdoor4:back>))
  (adv:set-scenario game-scenario:outdoor2)
  (c:guy:set-position 599 326)
  (c:guy:set-direction 2))

(adv:define-object outdoor4:door "Door"
		   (closed #t)
		   (firsttime #t))
(adv:bind-surface outdoor4:door "bdoor_c" 362 12 0)

(define-method (walk (obj <outdoor4:door>))
  (c:guy:set-target 487 422 (lambda ()
			      (cond ((not (closed outdoor4:door))
				     (adv:set-scenario game-scenario:outdoor6)
				     (c:guy:set-position 122 409)
				     (c:guy:set-direction 1))))))

(define game-scenario:outdoor4-objects 
  (list outdoor4:door
	outdoor4:console
	outdoor4:back
	scenario5:door-control
	scenario5:smoke))

(define game-scenario:outdoor4-bind
  (c:scenario:make-bind "game-scenario:outdoor4"
			"door" "door_cmap"
			(map (lambda (x) (adv:bind x))
			     game-scenario:outdoor4-objects) #t))

(define game-scenario:outdoor4
  (make <scenario> 
    #:adv:symbol 'game-scenario:outdoor4
    #:adv:bind game-scenario:outdoor4-bind
    #:adv:objs game-scenario:outdoor4-objects))

;; EOF ;;