;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Second outdoor since, the vilage ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;
;; Smoke ;;
;;;;;;;;;;;
(adv:define-object scenario3:smoke "Smoke")
(adv:bind-surface scenario3:smoke "smoke_anim" 350 0 150)

(define-method (walk (obj <scenario3:smoke>))
  (c:guy:set-target  474 444 (lambda ()
			       (c:guy:set-direction 0))))
(define-method (look (obj <scenario3:smoke>))
  (dialog:add "You see some smoke, maybe something is burning there..."))


(adv:define-object outdoor2:key "Key")
(adv:bind-surface outdoor2:key "key" 286 416 220)
(advent:set-inventory-surface (adv:bind outdoor2:key) "key")

(define-method (adv:walkto-pos (obj <outdoor2:key>))
  (cons 316 416))

(define-method (speak (obj <outdoor2:key>))
  (c:dialog:show (list "Hello key!"
		       "Stupid key!"
		       "Naaa... it's only a key, I don't talk to them.")
		 (lambda (selection)
		   (cond ((equal? selection 0)
			  (dialog:add "Hello Mogli...")
			  (c:dialog:show (list "bye"
					       "tschuess")
					 #f))

			 ((equal? selection 1)
			  (dialog:add "NOOO! I'am inteligent")
			  (c:dialog:show (list "your not!")
					 (lambda (x)
					   (dialog:add "I'am!")
					   (dialog:add "Ok, I'll belive you!"))))

			 ((equal? selection 2)
			  (dialog:add "Please... talk to me..."))
			 )
		   (println "DIALOG:LAMBDA:" selection))))

(define-method (pickup (obj <outdoor2:key>))
  (inventory:add obj)
  (scenario:remove obj))

(adv:define-object outdoor2:way "back to gateway station")
(adv:bind-empty outdoor2:way 560 400 80 80)
(define-method (walk (obj <outdoor2:way>))
  (c:guy:set-target 614 439
		    (lambda ()
		      (adv:set-scenario game-scenario:outdoor)
		      (c:guy:set-position 25 433)
		      (c:guy:set-direction 1))))

(adv:define-object outdoor2:way2 "WayToDoor")
(adv:bind-empty outdoor2:way2 585 260 55 40)

(define-method (adv:walkto-pos (obj <outdoor2:way2>))
  (cons 618 326))

(define-method (adv:walkto-func (obj <outdoor2:way2>))
  (adv:set-scenario game-scenario:outdoor4)
  (c:guy:set-position 35 430)
  (c:guy:set-direction 1))

(adv:define-object outdoor2:plate "plate"
		   (activated #f)
		   (known #f))
(adv:bind-empty outdoor2:plate 210 300 40 40)

(define-method (look (obj <outdoor2:plate>))
  (dialog:add "This plate looks like an communication panel or something like that."
	      "Can I speak to it?")
  (set! (known obj) #t))

(define-method (use (obj <outdoor2:plate>))
  (dialog:add "You press a button on the panel and it seems like the panel is now activated.")
  (set! (activated obj) #t))

(define-method (adv:walkto-pos (obj <outdoor2:plate>))
  (cons 232 397))

(define-method (adv:walkto-func (obj <outdoor2:plate>))
  (c:guy:set-direction 0))

(define-method (speak (obj <outdoor2:plate>))
  (if (known obj)
      (cond ((activated obj)
	     (dialog:add "Helloooo..."
			 "HELLLLOOOOO"
			 "Wow! What was that?"))
	    (else
	     (dialog:add "Helloooo..."
			 "sigh... nothing happens")))
      (dialog:add "Don't know what I should do with this thing.")))

(define game-scenario:outdoor2-objects 
  (list outdoor2:way
	outdoor2:way2
	outdoor2:key
	scenario3:smoke
	outdoor2:plate))
(define game-scenario:outdoor2-bind
  (c:scenario:make-bind "game-scenario:outdoor2"
		      "background3" "background3_cmap"
		      (map (lambda (x) (adv:bind x))
			   game-scenario:outdoor2-objects) #t))
(define game-scenario:outdoor2
  (make <scenario> 
    #:adv:symbol 'game-scenario:outdoor2
    #:adv:bind game-scenario:outdoor2-bind
    #:adv:objs game-scenario:outdoor2-objects))

;; EOF ;;