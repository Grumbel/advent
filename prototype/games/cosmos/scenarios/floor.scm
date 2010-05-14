(adv:define-object fire-ex1 "fire extinguisher")
(adv:set-hotspot! fire-ex1 1027 285 'north)
(adv:bind-surface  fire-ex1 "cosmos/fire-ex" 1020 200 0)
(adv:define-messages fire-ex-pickup
		     "I don't see a reason to take this with me."
		     "Its to heavy to carry it around without a reason."
		     "A fire-ex, why should I take this withme?")

(adv:defmets <fire-ex1>
	     (pickup ;;(dialog:add (adv:get-message fire-ex-pickup)))
	      (adv:seq (adv:guy:set-target 930 297)
		       (adv:walk fire-ex1)
		       (adv:guy:set-target 1002 302)))
	     ;; A simple cutscene
	     (look   ;;(c:input:disable)
		     (adv:seq
		      (dialog:add "FIIIRRRREEE....?!"
				  "I better go into the cellar and ceck the cell.")
		      (adv:walk cellar-door)

		      (adv:guy:walk-to-target 395 251)
		      (adv:guy:walk-to-target 317 255)

		      (adv:walk cell-door)
		      (adv:guy:set-target 327 336)
		      (adv:sleep 250)
		      (begin
			(adv:guy:set-direction 'north)
			(adv:sleep 250))
		      (begin
			(adv:guy:set-direction 'east)
			(adv:sleep 250))
		      (begin
			(adv:guy:set-direction 'south)
			(adv:sleep 250))
		      (dialog:add "Everything looks ok, good"
				  "Than I can go back to work")
		      (adv:sleep 1000)
		      (adv:walk cell-door-out)

		      (adv:guy:walk-to-target 317 255)
		      (adv:guy:walk-to-target 395 251)

		      (adv:walk cellar:floor-door)
		      (adv:sleep 1000)
		      (dialog:add "Fires are dangerous,"
				  "checking for them is important.")
		      (adv:walk workplace-door)
		      ;;(c:input:enable)
		      )))

;;(adv:sequential (adv:walk cellar-door)
;;                (adv:walk cell-door)
;;                (dialog:add "Everything looks ok, good"))


(adv:using fire-ex
	   (adv:define-object "fire extinguisher")
	   (adv:set-hotspot!  257 285 'north)
	   (adv:bind-surface  "cosmos/fire-ex" 245 200 0)
	   (adv:set-inv-sur   "cosmos/fire-ex"))

(adv:defmets <fire-ex>
	     (pickup (adv:low-pickup fire-ex)))

(adv:def-combine (fire-ex <fire-ex>) (garbage <workplace:garbage>)
		 (dialog:add "The garbage isn't buring so there is no reason"
			     "to use the fire-ex, but its always good"
			     "to have an fire-ex at hand when you need it."))

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
	     (walk ;;(dialog:add "Its closed and I lost the keys, not good.")
		(adv:set-scenario scenario:server-room)
		(adv:guy:set-pos 508 319 'west)
		))

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
(adv:set-hotspot!  workplace-door  646 277 'north)
(adv:bind-empty    workplace-door 608 141 72 110)

(define (rotate-the-guy count speed finalize)
  (if (> count 0)
      (adv:sequential (0     (adv:guy:set-direction 'east))
		      (speed (adv:guy:set-direction 'south))
		      (speed (adv:guy:set-direction 'west))
		      (speed (adv:guy:set-direction 'north))
		      (speed (rotate-the-guy (1- count) speed finalize)))
      (finalize)))

(adv:defmets <workplace-door>
	     (walk (adv:set-scenario scenario:workplace)
		   (c:guy:set-position  162 310))
	     (look (println "Starting sequenze")
		   (rotate-the-guy 10 100
				   (lambda () (dialog:add "Oh, I feel dizzy...")))))

;;(define-method (adv:walkto-pos (obj <workplace-door>))
;;  (cons 648 284))


(adv:define-object cellar-door "Cellar")
(adv:set-hotspot! cellar-door 902 272 'north)
(adv:bind-empty cellar-door 849 151 100 100)
(adv:defmets <cellar-door>
	     (walk (println "Walk...")
		   (adv:fade-in/out
		    (adv:set-scenario scenario:cellar)
		    (c:guy:set-position 434 213)
		    (c:guy:set-direction 3))))

(adv:define-scenario-new  scenario:floor
			  #:surface "cosmos/floor"
			  #:colmap  "cosmos/floor_cmap"
			  #:objects (list fire-ex1 
					  fire-ex
					  chef-sign
					  server-sign
					  workplace-sign
					  server-door chef-door workplace-door
					  cellar-door
					  uni-rest
					  ))

;; EOF ;;