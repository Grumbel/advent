(load "action-defaults.scm")

(adv:register-scenarios (scenario:floor     "scenarios/floor.scm")
			(scenario:workplace "scenarios/workplace.scm")
			(scenario:cellar    "scenarios/cellar.scm")
			(scenario:cell      "scenarios/cell.scm"))

(adv:set-scenario scenario:floor)
(c:guy:set-position 651 295)

;; EOF ;;