;; Special class for mantaining doors or doorlike objects which
;; connect two scenarios
(define-class <adv:door> ()
  (adv:bind
   #:init-value #f
   #:init-keyword #:bind
   #:accessor adv:bind)

  (adv:name
   #:init-value "<name-not-set>"
   #:init-keyword #:name
   #:accessor adv:name)

  ;; The scenario to which the guy is transported after walking
  ;; through the door
  (adv:scenario #:accessor adv:door:scenario
		#:init-keyword #:scenario
		#:init-value #f)

  (adv:hotspot #:accessor adv:door:hotspot
	       #:init-value (cons 320 200)
	       #:init-keyword #:hotspot)

  ;; The position to which the guy is transpored once he has walked
  ;; through the door (tuple of x and y position)
  (adv:position #:accessor adv:door:position
		#:init-value (cons 320 200)
		#:init-keyword #:position)

  ;; The before and after hooks are for person independet animations,
  ;; such as opening the door and closing it, say could also be used
  ;; for beam animations or such things.

  ;; This is called once the person reached the doors hotspot
  (adv:before-hook #:accessor adv:door:before-hook
		   #:init-value #f)

  ;; This is called once the person is set into the new scenario
  (adv:after-hook #:accessor adv:door:after-hook
		  #:init-value #f))

;; To something on click
(define-method (adv:on-click (door <adv:door>))
  (println "Click on door: " door)
  (adv:walk-to-door (person:current) door))

;; Order a person to walk to a door
(define-method (adv:walk-to-door (person <adv:person>) (obj <adv:door>))
  (println "Door: " obj)
  (let ((hook (person:walk-to person
			      (car (adv:door:hotspot obj))
			      (cdr (adv:door:hotspot obj))
			      ))
	(delayed-hook (c:delayed-advhook:create)))
    (c:advhook:add hook
		   (lambda ()
		     (println "adv:on-click: Doing on-click action with " obj)
		     ;;(c:scenariolayer:set-scenario scenario-layer (adv:door:scenario obj))

		     ;; FIXME: Engine integration should be handled otherwise
		     (let ((func (lambda ()
				   (println "Switching to: " (adv:door:scenario obj))
				   (person:set-scenario person (adv:door:scenario obj))

				   (person:set-position person
							(car (adv:door:position obj))
							(cdr (adv:door:position obj)))
				   (if (adv:door:after-hook obj)
						 ((adv:door:after-hook obj))
						 ;;(println "adv:door: No adv:after-hook set")
						 )
				   (c:advhook:call delayed-hook))))
		       (if (equal? person (person:current))
			   (c:fadeout-layer:fade fadeout-layer func)
			   (func)))))
    delayed-hook))

  (define-method (adv:walk-to-door (obj <adv:door>))
    (adv:walk-to-door (person:current) obj))

  ;; Error handling when the wrong argument is passed
  (define-method (adv:walk-to-door person obj)
    (println "Error: Wrong argument: adv:walk-to-door: " person " '" obj "'"))

  (define (_adv:defdoor door lst)
    (for-each (lambda (x)
		(case (car x)
		  ((name)
		   (set! (adv:name door) (cadr x)))
		  ((hotspot)
		   (set! (adv:door:hotspot door) (cons (cadr x) (caddr x))))
		  ((target-position)
		   (set! (adv:door:position door) (cons (cadr x) (caddr x))))
		  ((target-scenario)
		   (set! (adv:door:scenario door) (primitive-eval (cadr x))))
		  ((bind)
		   (set! (adv:bind door) (c:empty-advobj:create door (primitive-eval (cadr x)))))
		  (else
		   (println "_adv:defdoor: unknown symbol: " (car x)))))
	      lst))

  (define-syntax adv:defdoor
    (syntax-rules ()
      ((_ name pair ...)
       (begin (define name (make <adv:door>))
	      (_adv:defdoor name '(pair ...))))))

  ;; EOF ;;