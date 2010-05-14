(adv:using biosec:boxes
	   (adv:define-object "Boxes")
	   (adv:bind-empty 405 176 140 90)
	   (adv:set-hotspot! 452 286 'north))

(adv:using biosec:door
	   (adv:define-object "Door")
	   (adv:bind-empty 106 232 25 65)
	   (adv:set-hotspot! 138 301 'west))

(adv:defmets <biosec:door>
	     (walk (adv:guy:set-scenario scenario:biodoor)
		   (adv:guy:set-pos 230 322 'south)
		   ))

(adv:using biosec:transporter
	   (adv:define-object "Transporter")
	   (adv:bind-surface "cosmos/transporter" 153 240 194))

(adv:define-scenario-new  scenario:biosec
			  #:surface "cosmos/biosec"
			  #:colmap  "cosmos/biosec_cmap"
			  #:objects (list biosec:transporter
					  biosec:door
					  biosec:boxes))

;; EOF ;;