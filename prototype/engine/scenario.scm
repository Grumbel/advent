;; $Id: scenario.scm,v 1.8 2001/07/16 19:31:05 grumbel Exp $                                                             
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Scenario bindings and handling stuff.
;;

;; The object list of the current scenario 
;; FIXME: should be renamed/removed
;;(define *current-scenario* #f)

;; The current scenario object
(define *current-real-scenario* #f)

;; Remove the given object from the scenarios object list
(define (scenario:remove obj)
  ;;(_scenario:remove-obj obj)
  (c:scenario:remove (adv:bind obj)))

(define (scenario:add obj)
  ;;(_scenario:remove-obj obj)
  (c:scenario:add (adv:bind obj)))

;; FIXME: only here for bw-comp
;;(define (_scenario:remove-obj obj)
;;  (set! *current-scenario* (filter (lambda (x)
;;				     (not (equal? obj x)))
;;				   *current-scenario*)))


;; Low-level adv:set-scenario which does load on demand
;; see-also: adv:set-scenario
(define (_adv:set-scenario symbol scen)
  ;;(println "Scenario is: " scen)
  ;; In case the scenario isn't loaded, we load it.
  (cond ((pair? scen)
	 (adv:load (cdr scen))
	 (set! scen (eval symbol))))
  
  ;;(println "Scenario is: " scen)

  (adv:guy:set-scenario (person:current) scen)

  ;; Call the leave function
  (if (and *current-real-scenario*
	   (adv:leave-func *current-real-scenario*))
      ((adv:leave-func *current-real-scenario*)))
  
  ;;(set! *current-scenario* (adv:objs scen))
  (set! *current-real-scenario* scen)
 

  ;;(scenario:add *current-person*)


  ;; Call the enter function
  (if (adv:enter-func *current-real-scenario*)
      ((adv:enter-func *current-real-scenario*))))


(define adv:blackout c:adv:blackout)
(define adv:fade-in c:adv:fade-in)

(define-syntax adv:fade-in/out
  (syntax-rules ()
    ((_ body ...)
     (c:adv:fade-in/out (lambda () body ...)))))

#!
(define-syntax adv:seq-wrapper
  (syntax-rules ()
    ((_ body ...)
     )))
!#

;; EOF ;;