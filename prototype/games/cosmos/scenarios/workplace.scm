(adv:define-object workplace:window "Window")
(adv:bind-empty    workplace:window 517 160 70 100)
(adv:defmets <workplace:window>
	     (look (dialog:add "A window")))

(adv:define-object workplace:clock "Clock")
(adv:bind-empty    workplace:clock 98 119 30 30)
(adv:defmets <workplace:clock>
	     (look (dialog:add (string-append
				"It shows '"
				(strftime "%H:%M:%S" (localtime (current-time)))
				"'"))))

(adv:define-object workplace:door "Floor Door")
(adv:set-hotspot! workplace:door 148 310 'west)
(adv:bind-empty    workplace:door 82 172 60 120)
(adv:defmets <workplace:door>
	     (walk (adv:set-scenario scenario:floor)
		   (c:guy:set-position 648 284)
		   (c:guy:set-direction 2)))

(adv:define-object workplace:garbage "Garbage")
(adv:bind-empty    workplace:garbage 62 289 75 65)

(adv:define-scenario-new  scenario:workplace
			  #:surface "cosmos/workplace"
			  #:colmap  "cosmos/workplace_cmap"
			  #:objects (list workplace:window
					  workplace:clock
					  workplace:door
					  workplace:garbage))

;; EOF ;;