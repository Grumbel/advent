; Biosec door
(adv:using biodoor:biosecdoor
	   (adv:define-object "Door"
			      (locked #t))
	   (adv:set-hotspot! 236 320 'north)
	   (adv:bind-empty 192 209 75 100))

(adv:defmets <biodoor:biosecdoor>
	     (look (dialog:add "I need a level five card to unlock the door."))
	     (walk (cond ((locked biodoor:biosecdoor)
			  (dialog:add "The door is locked."
				      "I need a level five card to unlock it."))
			 (else
			  (adv:guy:set-scenario scenario:biosec)
			  (adv:guy:set-pos 145 299 'east)))))
(define (biodoor:unlock)
  (set! (locked biodoor:biosecdoor) #f))

; Keycard panel
(adv:using biodoor:panel
	   (adv:define-object "Keycard Panel")
	   (adv:set-hotspot! 289 317 'north)
	   (adv:bind-empty 278 248 15 25))

(adv:defmets <biodoor:panel>
	     (look (dialog:add "This is a keycard reader, all doors are locked this way."
			       "I need a level five card to unlock it.")))

; Bio Hazard sign
(adv:using biodoor:sign
	   (adv:define-object "Biohazard Sign")
	   (adv:set-hotspot! 435 345 'north)
	   (adv:bind-empty 382 112 100 95))

(adv:using biodoor:cellar
	   (adv:define-object "Cellar")
	   (adv:bind-empty 0 0 100 400)
	   (adv:set-hotspot! 40 345 'west))

(adv:defmets <biodoor:cellar>
	     (walk (adv:guy:set-pos 442 244 'west)
		   (adv:guy:set-scenario scenario:cellar)))

(adv:def-combine (card <workplace:chef-id-card>) (panel <biodoor:panel>)
		 (dialog:add "*ping*"
			     "The door is unlocked now, cool :-)")
		 (biodoor:unlock))

(adv:def-combine (card <workplace:id-card>) (panel <biodoor:panel>)
		 (dialog:add "*brrr...*"
			     "Damn, I only have a level two card, this won't work."))

(adv:define-scenario-new  scenario:biodoor
			  #:surface "cosmos/biodoor"
			  #:colmap  "cosmos/biodoor_cmap"
			  #:objects (list biodoor:cellar
					  biodoor:biosecdoor
					  biodoor:sign
					  biodoor:panel))

;; EOF ;;