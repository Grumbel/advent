;;;;;;;;;;;;;;;;;;;;;
;;
;;;;;;;;;;;;;;;;;;;;;;

(adv:define-object scenario11:back)
(adv:bind-empty scenario11:back 0 0 100 800)

(define-method (adv:walkto-pos (obj <scenario11:back>))
  (cons 50 550))

(define-method (adv:walkto-func (obj <scenario11:back>))
  (adv:set-scenario game-scenario:scenario10)
  (c:guy:set-position  510 285)
  (c:guy:set-direction 2))

;;;;;;;;; Scenario ;;;;;;;;;
(adv:define-scenario-new game-scenario:scenario11
			 #:surface "background11"
			 #:colmap  "background11_cmap"
			 #:objects (list scenario11:back))

;; EOF ;;