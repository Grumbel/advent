(load "action-defaults.scm")
(load "../../engine/namespace2.scm")

(define person (person:make mogli-gfx))
(define scenario:ladder #f) ;; <- seems ugly

(adv:load-module scenario1)

(display-module scenario1)

(display-module (current-module))

(person:set-current person)

(adv:guy:set-scenario person scenario1:ladder)
(adv:guy:set-pos 100 400 'east)

;; EOF ;;