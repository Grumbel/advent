(adv:using workplace:table 
	   (adv:define-object "Table")
	   (adv:bind-surface "cosmos/table" 256 207 236)
	   (adv:set-hotspot! 365 340 'north))

(c:adv:mark-empty (adv:bind workplace:table))

(adv:using workplace:bottle
	   (adv:define-object "Bottle")
	   (adv:bind-empty 310 230 16 34)
	   (adv:set-hotspot! 320 343 'north))

(adv:defmets <workplace:bottle>
	     (look (dialog:add "A bottle full of wine..."
			       "I guess I had to much of that yesterday..."))
	     (speak (dialog:add "No... I had enough of that..."))
	     (use   (dialog:add "No... I had enough of that...")))


(adv:using workplace:papers
	   (adv:define-object "Papers")
	   (adv:bind-empty 421 250 45 18)
	   (adv:set-hotspot! 449 344 'north))

(adv:defmets <workplace:papers>
	     (look (dialog:add "I have to rewrite some of them..."
			       "...quite a lot of work to do.")))

(adv:using workplace:phone
	   (adv:define-object "Phone")
	   (adv:bind-empty 266 255 35 15)
	   (adv:set-hotspot! 249 316 'east))

(adv:defmets <workplace:phone>
	     (look  (dialog:add "My phone... I hate it."))
	     (use   (speak obj))
	     (speak (adv:seq (adv:say "Phone:" "*ring*, *ring*,...")
			     (adv:say "Robi:"  "Hello..?")
			     (adv:say "Phone:" "Hello, is there the CompuLab?")
			     (adv:say "Robi:"  "Yes, here is the CompuLab.")
			     (adv:say "Phone:" "Have you heard of the BioSect?")
			     (adv:say "Robi:"  "Yes.")
			     (adv:say "Phone:" "Do you want to know what they are doing?")
			     (adv:say "Robi:"  "Yes!")
			     (adv:say "Phone:" "I can say you more,..."
				      "...but first you have to do me a favour.")
			     (adv:say  "Robi:" "What should I do?")
			     (adv:say  "Phone:" "Something... *to be continued*")
					 
			     (begin (adv:guy:set-direction 'south)
				    (dialog:add "Wow, weird phone call...")))))


(adv:using workplace:chefs-room
	   (adv:define-object "Chefs room")
	   (adv:set-hotspot! 210 285 'north)
	   (adv:bind-empty 178 168 60 110))
(adv:defmets <workplace:chefs-room>
	     (walk ;;(c:input:disable)
		   (c:guy:set-emotion 1)
		   (adv:seq (adv:sleep 1000)
			    (begin (c:guy:set-emotion 0)
				   (adv:sleep 500))
			    (dialog:add "This is chefs room")
			    (adv:sleep 1000)
			    (adv:guy:walk-to-target 210 320)
			    (adv:sleep 1000)
			    (dialog:add "I shouldn't walk in there, "
					"'cause chef could be getting angry"
					"Its still full of garbage.")
			    ;;(c:input:enable)
			    )))


(adv:using workplace:id-card
	   (adv:define-object  "ID-Card")
	   (adv:bind-surface   "cosmos/id_card" 416 366 242)
	   (adv:set-inv-sur    "cosmos/inv_id_card")
	   (adv:set-hotspot!   403 377 'east))
(adv:defmets <workplace:id-card>
	     (look   (dialog:add "My id card, I finally found it!"))
	     (pickup (dialog:add "Ah, cool my id-card, I thought I lost it.")
		     (scenario:remove workplace:id-card)
		     (inventory:add   workplace:id-card)))

(adv:define-object workplace:computer "Computer")
(adv:bind-empty    workplace:computer 339 215 50 55)
(adv:set-hotspot!  workplace:computer 366 299 'south)
(adv:defmets <workplace:computer>
	     (look  (dialog:add "My computer, I should probally check may mailbox."))
	     (speak (dialog:add "Computer show me my mail..."
				"*sig*"
				"This computer doesn't have voice recognition installed."))
	     (use   (dialog:add "Computer: Please insert your ID-Card!"
			       (if (inventory:has workplace:id-card)
				   "How good that I found my id card :-)"
				   "Damn! I lost my ID-card somewhere...")
			       )))

(adv:def-combine (id <workplace:id-card>) (computer <workplace:computer>)
		 (dialog:add "Computer: ...*ping*... ID-Card accepted..."
			     "Computer: You have mail."
			     "....reading..."
			     "Oh, I should better bring the garbage in the"
			     "cellar before my chef gets angry...")
		 (adv:knowledge:add 'garbage))

(adv:define-object workplace:window "Window")
(adv:bind-empty    workplace:window 517 160 70 100)
(adv:defmets <workplace:window>
	     (look (dialog:add "Its really quiet out there..."
			       "...as always after a party...")))

(adv:define-object workplace:clock "Clock")
(adv:bind-empty    workplace:clock 98 119 30 30)
(adv:defmets <workplace:clock>
	     (look (dialog:add (string-append
				"It shows '"
				(strftime "%H:%M:%S" (localtime (current-time)))
				"'")))
	     (pickup (person:set-current chef))
	     (use    (person:set-current other-chef)))

(adv:define-object workplace:door "Floor Door")
(adv:set-hotspot! workplace:door 148 310 'west)
(adv:bind-empty    workplace:door 82 172 60 120)
(adv:defmets <workplace:door>
	     (walk (cond ((and (adv:knowledge:has 'garbage)
			       (not (inventory:has workplace:garbage)))
			  (dialog:add "I should take the garbage with me."))
			 ((and (adv:knowledge:has 'garbage)
			       (inventory:has workplace:garbage))
			  (adv:set-scenario scenario:floor)
			  (c:guy:set-position 648 284)
			  (c:guy:set-direction 2))
			 (else
			  (dialog:add "I should check my mail first.")))))

(adv:using workplace:garbage
	   (adv:define-object  "Garbage")
	   (adv:bind-empty     62 289 75 65)
	   (adv:set-inv-sur    "cosmos/inv_garbage")
	   (adv:set-hotspot!   154 361 'west))

(adv:defmets <workplace:garbage>
	     (look (dialog:add "The garbage from the party yesterday..."
			       "I should bring it in the cellar sooner or later."))
	     (pickup (cond ((adv:knowledge:has 'garbage)
			    (dialog:add "Ok, lets bring the garbage away."
					"How good that my trousers have so large pockets ;-)"
					"Oh, something has fallen out of the garbage.")
			    (adv:low-pickup obj))
			   (else 
			    (dialog:add "No, I don't want to bring the garbage away now."
					"I feel to sleepy for that.")))))


(adv:define-scenario-new  scenario:workplace
			  #:surface "cosmos/workplace"
			  #:colmap  "cosmos/workplace_cmap"
			  #:objects (list 
					  workplace:table
					  workplace:window
					  workplace:clock
					  workplace:door
					  workplace:chefs-room
					  workplace:garbage
					  workplace:computer
					  workplace:id-card
					  workplace:phone
					  workplace:bottle
					  ))


;; EOF ;;