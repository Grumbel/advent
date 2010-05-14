;; $Id: lkw.scm,v 1.4 2001/07/15 18:54:59 grumbel Exp $ 

(adv:load "action-defaults.scm")
(adv:register-scenario scenario:lkw "scenario-lkw.scm")

(define my-person (person:make mogli-gfx))

(adv:set-scenario scenario:lkw)
(c:guy:set-position 516 417)

;; EOF ;;