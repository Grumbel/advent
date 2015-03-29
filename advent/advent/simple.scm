;; $Id: simple.scm,v 1.1 2001/08/31 16:00:31 grumbel Exp $

;; Description:
;; ~~~~~~~~~~~~
;; A set of default animations and person definition to quickly setup
;; a basic adventure game

(use-modules (oop goops))

(define simple:person (make <adv:person>))

(person:set-current simple:person)

;; EOF ;;