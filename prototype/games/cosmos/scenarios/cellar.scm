(adv:define-object cell-door "Door")
(adv:set-hotspot! cell-door 253 229 'north)
(adv:bind-empty cell-door 222 149 50 60)
(adv:defmets <cell-door> 
	     (walk (adv:set-scenario scenario:cell)
		   (c:guy:set-position 473 337)
		   (c:guy:set-direction 3)
		   ))

(adv:define-object cellar:floor-door "Door")
(adv:set-hotspot! cellar:floor-door 437 211 'east)
(adv:bind-empty cellar:floor-door 422 145 40 50)
(adv:defmets <cellar:floor-door>
	     (walk (adv:set-scenario scenario:floor)
		   (adv:guy:set-pos 899 276 'south)
		   ))

(adv:define-scenario-new  scenario:cellar
			  #:surface "cosmos/cellar"
			  #:colmap  "cosmos/cellar_cmap"
			  #:objects (list cell-door
					  cellar:floor-door))

;; EOF ;;