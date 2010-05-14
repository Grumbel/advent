;; $Id: scenario.scm,v 1.1 2001/07/02 10:27:13 grumbel Exp $                                                             
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Scenario bindings and handling stuff.
;;

;; The object list of the current scenario 
;; FIXME: should be renamed/removed
(define *current-scenario* #f)

;; The current scenario object
(define *current-real-scenario* #f)

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


;; Remove the given object from the scenarios object list
(define (scenario:remove obj)
  (_scenario:remove-obj obj)
  (c:scenario:remove (adv:bind obj)))


;; FIXME: only here for bw-comp
(define (_scenario:remove-obj obj)
  (set! *current-scenario* (filter (lambda (x)
				     (not (equal? obj x)))
				   *current-scenario*)))


;; Low-level adv:set-scenario which does load on demand
;; see-also: adv:set-scenario
(define (_adv:set-scenario symbol scen)
  ;;(println "Scenario is: " scen)
  ;; In case the scenario isn't loaded, we load it.
  (cond ((pair? scen)
	 (adv:load (cdr scen))
	 (set! scen (eval symbol))))
  
  ;;(println "Scenario is: " scen)

  ;; Call the leave function
  (if (and *current-real-scenario*
	   (adv:leave-func *current-real-scenario*))
      ((adv:leave-func *current-real-scenario*)))
  
  (c:scenario:set-current (adv:bind scen))
  (set! *current-scenario* (adv:objs scen))
  (set! *current-real-scenario* scen)

  ;; Call the enter function
  (if (adv:enter-func *current-real-scenario*)
      ((adv:enter-func *current-real-scenario*))))



;; EOF ;;