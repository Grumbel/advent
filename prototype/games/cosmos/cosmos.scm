(load "action-defaults.scm")

(adv:register-scenarios (scenario:floor       "scenarios/floor.scm")
			(scenario:workplace   "scenarios/workplace.scm")
			(scenario:cellar      "scenarios/cellar.scm")
			(scenario:cell        "scenarios/cell.scm")
			(scenario:server-room "scenarios/server-room.scm")
			(scenario:biodoor     "scenarios/biodoor.scm")
			(scenario:biosec      "scenarios/biosec.scm")
			)

;; FIXME: Workaround for broken on demand loading (on demand loading
;; does not work with adv:seq since scenario objects are not handled
;; seperatly)
(load "persons.scm")
(load "scenarios/workplace.scm")
(load "scenarios/floor.scm")
(load "scenarios/cell.scm")
(load "scenarios/cellar.scm")
(load "scenarios/server-room.scm")
(load "scenarios/biosec.scm")
(load "scenarios/biodoor.scm")

(person:set-current other-chef)
(adv:guy:set-scenario other-chef scenario:floor)
(c:guy:set-position 473 291)

(person:set-current chef)
(adv:guy:set-scenario chef scenario:workplace)
(c:guy:set-position 219 358)

#!
(c:input:disable)
(adv:guy:set-pos 316 356 'west)
(adv:seq 
 (adv:guy:walk-to-target 231 359)
 (adv:guy:walk-to-target 443 360)
 (adv:guy:walk-to-target 231 359)
 (adv:guy:walk-to-target 443 360)
 (adv:guy:walk-to-target 331 359)
 (adv:sleep 300)
 (begin (adv:guy:set-direction 'south)
	(adv:seq  (adv:sleep 300) 
		  (dialog:add "What a party last night..."
			      "...lets get back to work..."
			      "*sig*"
			      "I should probally check my email.")
		  (c:input:enable))))
(adv:blackout)
(adv:seq
 (adv:sleep 1000)
 (adv:fade-in))
!#

;; EOF ;;