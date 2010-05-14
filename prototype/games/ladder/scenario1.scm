(adv:using window1
	   (adv:define-object "Window")
	   (adv:set-hotspot! 266 350 'north)
	   (adv:bind-empty 227 209 80 70))

#! Wannabe code:
(adv:define-object window
		   (name "Window")
		   (members (open #f))
		   (hotspot (366 250 'north))
		   (bind (region 227 209 80 70)))
!#

(adv:using window2
	   (adv:define-object "Window")
	   (adv:set-hotspot! 266 350 'north)
	   (adv:bind-empty 229 46 80 70))

(adv:defmets <window1>
	     (use (adv:say "Mogli:"
			   "Can't enter the window\nnextline")))

(define ladder #f)

(println "Current Module: ")
(display-module (current-module))

(adv:define-scenario-new  ladder
			  #:surface "ladder/ladder"
			  #:colmap  "ladder/ladder_cmap"
			  #:objects (adv:extract-objects (current-module)))

;; EOF ;;