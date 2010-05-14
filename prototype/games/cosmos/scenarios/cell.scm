;; Fire
;; 315 140
;;

(adv:using cell:fire
	   (adv:define-object "Fire")
	   (adv:bind-surface "cosmos/fire" 315 140 0)
	   (adv:set-hotspot! 377 306 'north))

(adv:using workplace:chef-id-card
	   (adv:define-object "Chef's ID-Card")
	   (adv:bind-surface  "cosmos/chef_id_card" 330 299  0)
	   (adv:set-inv-sur   "cosmos/inv_chef_id_card")
	   (adv:set-hotspot!  330 299 'south))

(adv:defmets <workplace:chef-id-card>
	     (pickup (dialog:add "Chefs level five id card... :-)")
		     (adv:low-pickup obj)))

(adv:using cell:garbage
	   (adv:define-object "Garbage Place")
	   (adv:bind-empty 335 180 95 100)
	   (adv:set-hotspot! 377 306 'north))

#!
(adv:def-obj cell:garbage
	     (name "Garbage Place")
	     (bind-empty 3 3 2 3 2)
	     (hotspot 12313  23 'north))
!#

(adv:defmets <cell:garbage> 
	     (look (dialog:add "Here we collect all garbage."
			       "It is carried away once a week.")))

(adv:def-combine (garbage <workplace:garbage>) (place <cell:garbage>)
		 (inventory:remove garbage)
		 (adv:seq
		  (dialog:add "Ok, garbage is dumped."
			      "Now back to the fun...."
			      "Woops, something has fallen out of the garbage"
			      "...wow...something is happening...")
		  (scenario:add cell:fire)))

(adv:def-combine (fire-ex <fire-ex>) (fire <cell:fire>)
		 (scenario:remove cell:fire)
		 (dialog:add "The fire is extinguishes."
			     "Wow, that could have have gotten dangerous.")
		 (scenario:add workplace:chef-id-card))

(adv:def-combine (fire-ex <fire-ex>) (garbage <cell:garbage>)
		 (dialog:add "The garbage isn't buring so there is no reason"
			     "to use the fire-ex, but its always good"
			     "to have an fire-ex at hand when you need it."))

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
			  #:objects (list cell-door-out
					  cell:garbage))

;; EOF ;;