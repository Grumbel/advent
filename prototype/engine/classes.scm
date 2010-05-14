;; $Id: classes.scm,v 1.6 2001/07/16 07:48:36 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Advent classes
;;

;; <person:gfx> encapsulates all information which is needed for the
;; gfx representation of a person
(define-class <person:gfx> ()
  (north #:init-value #f
	 #:accessor north
	 #:init-keyword #:north)
  (east #:init-value #f
	 #:accessor east
	 #:init-keyword #:east)
  (south #:init-value #f
	 #:accessor south
	 #:init-keyword #:south)
  (west #:init-value #f
	 #:accessor west
	 #:init-keyword #:west))

(define-class <person> (<advent:object>)
  (name #:accessor name #:init-value "<unset-person>")
  (gfx  #:accessor gfx #:init-value #f #:init-keyword #:gfx)
  (adv:bind #:accessor adv:bind
	    #:init-value #f)
  (adv:inventory #:accessor adv:inventory
		 #:init-value #f)
  (adv:knowledge #:accessor adv:knowledge
		 #:init-value '()))

;; Scenario handling object
;; FIXME: could need some cleanup
(define-class <scenario> ()
  ;; Probally used for on demand loading
  (adv:file #:init-value #f
	    #:init-keyword #:adv:file
	    #:accessor adv:file)

  ;; The bind object contains a pointer back to the C++ Scenario class
  (adv:bind #:init-value #f 
	    #:init-keyword #:adv:bind
	    #:accessor adv:bind)

  ;; The list of objects in this scenario
  (adv:objs #:init-value '()
	    #:init-keyword #:adv:objs
	    #:accessor adv:objs)

  (adv:symbol #:init-value #f
	      #:init-keyword #:adv:symbol
	      #:accessor adv:symbol)

  (adv:enter-func #:init-value #f 
		  #:accessor adv:enter-func)
  (adv:leave-func #:init-value #f 
		  #:accessor adv:leave-func))

;; EOF ;;