;; Cave

(adv:define-object scenario9:stone "Stone")
(adv:bind-surface scenario9:stone "stone" 442 336 255)

(adv:define-object scenario9:exit "Exit")
(adv:bind-empty scenario9:exit 145 212 90 120)

(define-method (walk (ojb <scenario9:exit>))
  (c:guy:set-target 202 326
		    (lambda ()
		      (adv:set-scenario game-scenario:outdoor8)
		      (c:guy:set-position 342 292)
		      (c:guy:set-direction 2))))
  
(adv:define-scenario-new game:scenario9
			 #:surface "background9"
			 #:colmap  "background9_cmap"
			 #:objects (list 
				    scenario9:stone
				    scenario9:exit))
;; EOF ;;