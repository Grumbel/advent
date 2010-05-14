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
	     (walk (adv:fade-in/out
		    (adv:set-scenario scenario:floor)
		    (adv:guy:set-pos 899 276 'south)
		   )))

(adv:using cellar:bio-section
	   (adv:define-object "..:: Biologie Section ::..")
	   (adv:set-hotspot! 444 240  'east)
	   (adv:bind-empty 511 76 130 220))

(adv:defmets <cellar:bio-section>
	     (look (dialog:add "This is the famous section of the biologist."
			       "Nobody really knows what is happening in there,"
			       "but there is lots of rumor that it is not really"
			       "legal what they are doing."))
	     (use (dialog:add "Would really like to know whats going on in there."
			      "But I need a \"Security Level 5\" card to get in there."
			      "I only have a \"Level 2\" card :-("))
	     (speak (dialog:add "I should better not fool around with the comunication stuff."
				"The guards are getting angry very quick."))
	     (walk (adv:guy:set-scenario scenario:biodoor)
		   (adv:guy:set-pos 58 365 'east)))

(adv:define-scenario-new  scenario:cellar
			  #:surface "cosmos/cellar"
			  #:colmap  "cosmos/cellar_cmap"
			  #:objects (list cell-door
					  cellar:floor-door
					  cellar:bio-section))

;; EOF ;;