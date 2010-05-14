;; $Id: adventure.scm,v 1.8 2001/07/02 10:27:13 grumbel Exp $                                                             
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; The main initialisation file of the scheme advent engine, all stuff
;; that needs to be loaded should be loaded from here, except the game
;; files itself, which are loaded from C++.
;;

(use-modules (ice-9 format)
	     (oop goops)
	     (ice-9 syncase)
	     (ice-9 optargs))

;; Load a 'file' from 'path' or signal an error if the file cannot be
;; found in 'path'
;; FIXME: This should throw an error instead of an error message.
(define (_adv:load-from-path file path)
  (cond ((not (null? path))
	 (let ((filename (string-append (car path) "/" file)))
	   (cond ((access? filename R_OK)
		  ;;(println "Found: " filename)
		  (primitive-load filename))
		 (else
		  (_adv:load-from-path file (cdr path))))))
	(else
	 (println "Error: adv:load: File not found: " file))
	))

;; Load the given file from the game path
(define (adv:load file)
  (println "Loading file: " file)
  ;; FIXME
  (_adv:load-from-path file '("." ;; FIXME: This is stupid and braindead...
			      "games/retriever"
			      "games/lkw"
			      "games/cosmos"
			      "games/cosmos/scenarios/")))



;; The main adventure logic object from which all other are inherit
(define-class <advent:object> ()
  (adv:hotspot  #:accessor adv:hotspot
		#:init-value #f)    
  (adv:hotspot-direction  #:accessor adv:hotspot-direction
			  #:init-value #f)
  (adv:bind #:accessor adv:bind 
	    #:init-value #f
	    #:init-keyword #:adv:bind))

;; FIXME: document me!
(define-class <advent:walk-point> (<advent:object>)
  (adv:scenario #:accessor adv:scenario
		#:init-value #f)
  (adv:change-hook #:accessor adv:change-hook
		   #:init-value #f))

;; FIXME: Should be rewritten
(define-method (name (obj <advent:object>)) "<unset>")

;; FIXME: Should be removed and replaced by timed callback's
(define-method (update (obj <advent:object>))
  #f ;;(println "Nothing to do for " (name obj))
  )

;; FIXME: Should be removed and replaced by timed callback's
(define (adv:update obj)
  (println "Calling update for " (name obj))
  (update obj))

;; Create a binding to a surface in the c++ world
(define (adv:bind-surface obj surface x y z)
  (set! (adv:bind obj) (advent:makeobj-surface obj surface x y z))
  obj)

;; Create a binding to a region in the c++ world
(define (adv:bind-empty obj x-pos y-pos width height)
  (set! (adv:bind obj) (advent:makeobj-empty obj x-pos y-pos
					     width height)))


;; Convert a symbol-direction into the numeric representation in the
;; c++ world
(define (adv:direction->number sym)
  (case sym
    ((north) 0)
    ((east)  1)
    ((south) 2)
    ((west)  3)))

;; Set the hotspot of an object
(define (adv:set-hotspot! obj x-pos y-pos direction)
  (set! (adv:hotspot obj) (cons x-pos y-pos))

  (cond ((number? direction)
	 (set! (adv:hotspot-direction obj) direction))
	((symbol? direction)
	 (set! (adv:hotspot-direction obj) (adv:direction->number direction)))
	(else
	 (println "Error 6894"))))

;; Combine two objects
;; FIXME: This is order-dependent, should be rewritten as a macro
(define-method (combine (obj1 <advent:object>) (obj2 <advent:object>))
  (dialog:add "Don't know of to combine this two objects")
  (println "Obj1: " (name obj1)" Obj2: " (name obj2)))


(load "helper.scm")
(load "inventory.scm")
(load "scenario.scm")
(load "guy.scm")
(load "animation.scm")
(load "actions.scm")
(load "syntax-ext.scm")
(load "dialog.scm")
(load "stat.scm")

;;(load "objects.scm")

;; EOF ;;