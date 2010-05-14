;;;;;;;;;; Panel ;;;;;;;;;
(adv:define-object scenario12:panel "Panel")
(adv:bind-empty scenario12:panel 360 218 390 256)
(define-method (adv:walkto-pos (obj <scenario12:panel>))
  (cons 364 323))
(define-method (look (obj <scenario12:panel>))
  (dialog:add "Hm, maybe this thing can be used to controll the elevator."))
(define-method (use (obj <scenario12:panel>))
  (dialog:add "Lets press this button...")
  (adv:timed 2000
	     (dialog:add "Grrrr.... Zrrrr...  Kronk..."
			 "Its moving...")))

;;;;;;;;; Scenario ;;;;;;;;;
(adv:define-scenario-new game-scenario:scenario12
			 #:surface "background12"
			 #:colmap  "background12_cmap"
			 #:objects (list scenario12:panel))

;; EOF ;;