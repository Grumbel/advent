(adv:define-object fire-ex1 "fire extinguisher")
(adv:set-hotspot! fire-ex1 1027 285 'north)
(adv:bind-empty  fire-ex1 1020 200 15 40)
(adv:define-messages fire-ex-pickup
 "I don't see a reason to take this with me."
 "Its to heavy to carry it around without a reason."
 "A fire-ex, why should I take this withme?")

(adv:defmets <fire-ex1>
	     (pickup (dialog:add (adv:get-message fire-ex-pickup)))
	     (look   (dialog:add "FIIIRRRREEE...."
				 "I better go into the cellar and ceck the cell."
				 "FIXME: Replace me with some kind of cutscene")
		     ;;(adv:sequential (adv:walk cellar-door)
		     ;;                (adv:walk cell-door)
		     ;;                (dialog:add "Everything looks ok, good"))
		     ))

(adv:define-object fire-ex2 "fire extinguisher")
(adv:set-hotspot! fire-ex2 257 285 'north)
(adv:bind-empty  fire-ex2 245 200 15 40)

;; SIGNs ;;
(adv:define-object server-sign    "Sign")
(adv:bind-empty  server-sign 65 165 20 20)
(adv:defmets <server-sign>
	     (look (dialog:add "Server Room"
			       "Authorized Personal only!"
			       "How good that I am authorived.")))

(adv:define-object chef-sign      "Sign")
(adv:bind-empty  chef-sign 339 165 20 20)
(adv:defmets <chef-sign>
	     (look (dialog:add "Mr. Fritz Mueller"
			       "Phone: 4523"
			       "Thats my bosses room.")))

(adv:define-object workplace-sign "Sign")
(adv:bind-empty  workplace-sign 590 165 20 20)
(adv:defmets <workplace-sign>
	     (look (dialog:add "Hans Franz"
			       "Phone: 4234"
			       "Thats my room.")))

(adv:define-object server-door    "Server Room")
(adv:set-hotspot!  server-door 132 277 'north)
(adv:bind-empty    server-door 96 157 65 110)
(adv:defmets <server-door>
	     (walk (dialog:add "Its closed and I lost the keys, not good.")))

(adv:define-object chef-door    "Chefs Room")
(adv:set-hotspot! chef-door 391 277 'north)
(adv:bind-empty    chef-door 358 152 65 110)
(adv:defmets <chef-door>
	     (walk (dialog:add "I shouldn't enter this room while chef isn't there.")))

(adv:define-object uni-rest    "University")
(adv:set-hotspot!  uni-rest 1255 293 'south)
(adv:bind-empty    uni-rest 1219 63 60 250)
(adv:defmets <uni-rest>
	     (walk (dialog:add "No time for walking around in the university."
			       "I got to finish my work first.")))
;1068 292 255

(adv:define-object workplace-door    "Workplace")
(adv:set-hotspot! workplace-door  646 277 'north)
(adv:bind-empty    workplace-door 608 141 72 110)
(adv:defmets <workplace-door>
	     (walk (adv:set-scenario scenario:workplace)
		   (c:guy:set-position  162 310)
		   ))
;;(define-method (adv:walkto-pos (obj <workplace-door>))
;;  (cons 648 284))


(adv:define-object cellar-door "Cellar")
(adv:set-hotspot! cellar-door 902 272 'north)
(adv:bind-empty cellar-door 849 151 100 100)
(adv:defmets <cellar-door>
	     (walk (adv:set-scenario scenario:cellar)
		   (c:guy:set-position 434 213)
		   (c:guy:set-direction 3)
		   ))

(adv:define-scenario-new  scenario:floor
			  #:surface "cosmos/floor"
			  #:colmap  "cosmos/floor_cmap"
			  #:objects (list fire-ex1 
					  fire-ex2
					  chef-sign
					  server-sign
					  workplace-sign
					  server-door chef-door workplace-door
					  cellar-door
					  uni-rest
					  ))

;; EOF ;;