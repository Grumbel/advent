(adv:define-object cell-door-out "Door")
(adv:set-hotspot! cell-door-out 472 336 'east)
(adv:bind-empty cell-door-out 464 197 70 130)
(adv:defmets <cell-door-out>
	     (walk (adv:set-scenario scenario:cellar)
		   (adv:guy:set-pos 257 230 'south)
		    ))

(adv:define-scenario-new  scenario:cell
			  #:surface "cosmos/cell"
			  #:colmap  "cosmos/cell_cmap"
			  #:objects (list cell-door-out))

;; EOF ;;