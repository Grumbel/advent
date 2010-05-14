#!/usr/local/bin/guile \
--debug -e main -s
!#

(use-modules (advent core))

(define (main args)
  (load "guile/engine.scm")
  (chdir "../doc/examples/cosmos/")
  (load "cosmos.scm")
  (advent:main-loop))

;; EOF ;;
