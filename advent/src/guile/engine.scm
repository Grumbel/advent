;; $Id: engine.scm,v 1.11 2002/04/16 11:01:00 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Main file of the guile part of Advent, all sub-modules are loaded
;; from here
;;

;;(define-module (advent engine))

(use-modules (oop goops)
	     (ice-9 format)
	     (ice-9 syncase)
	     (ice-9 optargs)
	     (advent core))

;;(use-modules (advent helper)
;;	     (advent for))

;;(module-for-each
;; (lambda (name binding)
;;    (display "re-exporting ") (display name) (newline)
;;    (module-re-export! (current-module) (list name)))
;; (module-public-interface (resolve-module '(oop goops))))

;; Stuff that is completly independent of advent
(load "for.scm")
(load "helper.scm")

(define (adv:load filename)
  (println "Advent:Engine: loading " filename)
  (load filename))

(define-public *use-festival* #f)

(adv:load "object.scm")
(adv:load "keymap.scm")
(adv:load "defobj.scm")
(adv:load "inventory.scm")
(adv:load "scenario.scm")
(adv:load "person.scm")
(adv:load "door.scm")
(adv:load "sequence.scm")
(adv:load "dialog.scm")

(cond (*use-festival*
       (adv:load "festival.scm")))

;; EOF ;;