;; Ship ;;

;;;;;;;; Tree ;;;;;;;;
(adv:define-object scenario10:tree "Tree")
(adv:bind-empty scenario10:tree 630 290 70 170)

;;;;;;;; Stone ;;;;;;;;
(adv:define-object scenario10:stone "Stone")
(adv:bind-surface scenario10:stone "s10-stone" 446 531 185)

;;;;;;;; Bough ;;;;;;;;
(adv:define-object scenario10:bough "Bough")
(adv:bind-empty scenario10:bough 725 450 25 25)

;;;;;;;;; Way back to something ;;;;;;;;;
;(adv:define-walkpoint 686 500 100 100 scenario10:wayback)

;;;;;;;; Engine ;;;;;;;
(adv:define-object scenario10:engine "Engine")
(adv:bind-empty scenario10:engine 470 243 80 60)

(define-method (adv:walkto-pos (obj <scenario10:engine>))
  (cons 510 285))

(define-method (adv:walkto-func (obj <scenario10:engine>))
  (adv:set-scenario game-scenario:scenario11)
  (c:guy:set-position  100 550)
  (c:guy:set-direction 1))

;;;;;;;;; Scenario ;;;;;;;;;
(adv:define-scenario-new game-scenario:scenario10
			 #:surface "background10"
			 #:colmap  "background10_cmap"
			 #:objects (list scenario10:tree
					 scenario10:stone
					 scenario10:bough
					 ;;scenario10:wayback
					 scenario10:engine))

;; EOF ;;