;; $Id: scenario.scm,v 1.15 2003/02/24 22:41:55 grumbel Exp $

(export <adv:scenario> adv:write scenario:create scenario:add-drawable scenario:remove-drawable
	scenario:add-advobj scenario:remove-advobj scenario:set-colmap _adv:defscenario:add-advobjs
	_adv:defscenario:set-dimension _adv:defscenario:add-drawables _adv:defscenario:set-colmap
	_adv:defscenario _adv:load-scenarios adv:bind)

(export-syntax adv:defscenario adv:load-scenarios)

(define-class <adv:scenario> ()
  ;; FIXME: Is this of some kind usefull?!
  (name     #:init-value "<name-not-set>" #:accessor adv:name)
  (adv:bind #:init-value   #f
	    #:init-keyword #:bind
	    #:accessor adv:bind))

(define-method (adv:write (scenario <adv:scenario>) port)
  (format port "[Scenario: ~S]: " (adv:name scenario)))
					;  (for-each (lambda (obj)
			     ;	      (format port "  <~S>" obj))
				  ;	    (adv:objects scenario)))

(define (scenario:create)
  (let ((scenario (make <adv:scenario>)))
    (set! (adv:bind scenario) (c:scenario:create scenario))
    scenario))

(define (scenario:add-drawable scenario drawable)
  (c:scenario:add-drawable (adv:bind scenario)
			   drawable))

(define (scenario:remove-drawable scenario drawable)
  (c:scenario:remove-drawable (adv:bind scenario)
			      drawable))

(define (scenario:add-advobj scenario advobj)
  (c:scenario:add-advobj (adv:bind scenario)
			 (adv:bind advobj)))

(define (scenario:remove-advobj scenario advobj)
  (println "scenario:remove-advobj")
  (c:scenario:remove-advobj (adv:bind scenario) (adv:bind advobj)))

(define-method (scenario:set-colmap (scenario <adv:scenario>) colmap)
  (println "Scenario: " scenario " " colmap)
  (c:scenario:set-colmap (adv:bind scenario) colmap))

;; Syntax stuff for adv:defscenario
(define-syntax adv:defscenario
  (syntax-rules ()
    ((_ name
	(section-name values ...)
	...)
     (_adv:defscenario name (list (list 'section-name  values ...)
				  ...)))))

(define (_adv:defscenario:add-advobjs name lst)
  (for-each (lambda (advobj)
	      (scenario:add-advobj name advobj))
	    lst))

(define (_adv:defscenario:set-dimension scenario lst)
  (println  "Dimension: " lst)
  (c:scenario:set-dimension (adv:bind scenario) (car lst) (cadr lst)))

(define (_adv:defscenario:add-drawables scenario lst)
  (println "Adding drawables: " lst)
  (for-each (lambda (drawable)
	      (scenario:add-drawable scenario drawable))
	    lst))

(define (_adv:defscenario:set-colmap scenario lst)
  (cond ((string? (car lst))
	 (let ((colmap (c:surfacecolmap:create (car lst))))
	   (scenario:set-colmap scenario colmap)
	   (cond ((= (length lst) 2)
		  (c:surfacecolmap:set-scale colmap (cadr lst))))))
	(else ;; is a surface colmap
	 (scenario:set-colmap scenario (car obj)))))

(define (_adv:defscenario scenario lst)
  ;; FIXME: Removed cause it should be handled inside the scenario
  ;; loading
  ;;(primitive-eval `(define ,name (scenario:create)))
  (println "DefScenario: " lst)
  (for-each (lambda (pair)
	      (case (car pair)
		((drawables)
		 (_adv:defscenario:add-drawables scenario (cdr pair)))
		((advobjs)
		 (_adv:defscenario:add-advobjs scenario (cdr pair)))
		((colmap)
		 (_adv:defscenario:set-colmap scenario (cdr pair)))
		((dimension)
		 (_adv:defscenario:set-dimension scenario (cdr pair)))
		(else
		 (println "Scenario: Unknown symbol " (car pair)))))
	    lst))

(define (_adv:load-scenarios lst)
  (for-each (lambda (x)
	      (primitive-eval `(define ,(car x) (scenario:create))))
	    lst)
  (for-each (lambda (x)
	      (primitive-load (cadr x)))
	    lst))

(define-syntax adv:load-scenarios
  (syntax-rules ()
    ((_ lst ...)
     (_adv:load-scenarios (list (quote lst) ...)))))


;; EOF ;;
