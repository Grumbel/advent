;; $Id: person.scm,v 1.21 2003/02/23 17:07:48 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Person manipulation functions.
;;

(export <adv:person> adv:get-hotspots *person:current*
	person:current person:set-current person:set-scenario
	person:get-scenario person:set-position person:get-position
	person:walk-to person:set-direction <adv:talking-point> adv:talk
	person:talk person:remove-from-inventory person:add-to-inventory
	person:create
	adv:inventory adv:inventory-update-hook adv:speech adv:speech-font)

(export-syntax adv:defperson)

(define-class <adv:person> (<adv:object>)
  (adv:inventory #:init-value '()
		 #:init-keyword #:inventory
		 #:accessor adv:inventory)
  (adv:inventory-update-hook #:init-value #f
			     #:accessor adv:inventory-update-hook)
  (adv:speech #:init-value #f
	      #:init-keyword #:speech
	      #:accessor adv:speech)
  (adv:speech-font #:init-value "arialfont14_blue"
		   #:init-keyword #:font
		   #:accessor adv:speech-font))

(define (person:create)
  (let* ((person (make <adv:person>))
	 (bind   (c:person:create person)))
    (set! (adv:bind person) bind)
    person))

(define-method (adv:get-hotspots (person <adv:person>))
  (let ((pos (person:get-position person)))
    (list (list (car pos) (cdr pos) 'north))))

(define-public *person:current* (make-fluid))
(define-public (person:current) (fluid-ref *person:current*))

(define-public (person:set-current person)
  (fluid-set! *person:current* person))

(define-method (person:set-scenario (person <adv:person>) (scenario <adv:scenario>))
  (c:person:set-scenario (adv:bind person) (adv:bind scenario)))

(define-method (person:get-scenario (person <adv:person>))
  (c:person:get-scenario (adv:bind person)))

(define-method (person:set-position (person <adv:person>) x y)
  (c:person:set-position (adv:bind person) x y))

(define-method (person:get-position (person <adv:person>))
  (c:person:get-position (adv:bind person)))

(define-method (person:walk-to (person <adv:person>) x y)
  (c:person:set-target (adv:bind person) x y))

(define-method (person:walk-to (person <adv:person>) (obj <adv:object>))
  (println "Person:walk-to: " (adv:get-hotspots obj))
  (person:walk-to person
		  (car  (car (adv:get-hotspots obj)))
		  (cadr (car (adv:get-hotspots obj)))))

(define-method (person:set-direction (person <adv:person>) sym)
  (cond ((number? sym)
	 (c:person:set-direction (adv:bind person) sym))
	((symbol? sym)
	 (c:person:set-direction (adv:bind person) (adv:symbol->direction sym)))
	(else (println "person:set-direction: Error unknown: " sym))))

;; Class for managing an position from which 'talk' is emitted
(define-class <adv:talking-point> ()
  (adv:scenario #:init-value   #f
		#:accessor     adv:scenario
		#:init-keyword #:scenario)
  (adv:position #:init-value   #f
		#:accessor     adv:position
		#:init-keyword #:position)
  (adv:speech #:init-value   #f
	      #:init-keyword #:speech
	      #:accessor     adv:speech))

(define-public *adv:talk-drawable* #f)

;; Describtion:
;;
;; Present a 'talk' text on the screen
;;
;; FIXME:
;;
;; How do I remove a 'printed talk', the return value is already used
;; for the hook.
;;
(define-method (adv:talk (scenario <adv:scenario>) (pos <pair>) (text <string>))
  (if *use-festival*
      (festival:talk text))

  (let* ((hook (c:delayed-advhook:create))
	 (drawable (c:sprite-drawable:create
		    (c:font-sprite:set-remove-hook
		     (c:font-sprite:create (adv:speech-font person) text)
		     (lambda ()
		       (c:advhook:call hook)))
		    (car pos) (cdr pos) 1000)))
    ;; FIXME: Uncrop not implemented
    ;;(c:sprite-drawable:set-uncrop drawable #t)
    (scenario:add-drawable (person:get-scenario person) drawable)
    (set! *adv:talk-drawable* drawable)
    hook))

;; FIXME: should take multiple strings as arguments
(define-method (person:talk (person <adv:person>) (text <string>))
  ;; Clear a visible sentance of this person if available
  (cond ((adv:speech person)
	 (c:drawable:remove (adv:speech person))))

  (let ((hook (adv:talk (person:get-scenario person)
			  (person:get-position person)
			  text)))
      (set! (adv:speech person) *adv:talk-drawable*)
      hook))

(define-method (person:remove-from-inventory (person <adv:person>) object)
  (set! (adv:inventory person) (filter (lambda (obj)
					 (println "Equal: " obj " " object " => "
						  (not (equal? obj object)))
					 (not (equal? obj object)))
				       (adv:inventory person)))
  (if (adv:inventory-update-hook person)
      ((adv:inventory-update-hook person) person)))

(define-method (person:add-to-inventory (person <adv:person>) object)
  (set! (adv:inventory person) (append (adv:inventory person) (list object)))
  (if (adv:inventory-update-hook person)
      ((adv:inventory-update-hook person) person)))

(define-public (adv:symbol->direction sym)
  (case sym
    ((north) 0)
    ((west)  -1.6)
    ((east)  1.6)
    ((south) 3.14)
    (else
     (println "adv:symbol->direction: unknown sym: " sym)
     0)))

;; Default arguments
(define-method (person:set-scenario scenario)
  (person:set-scenario (person:current) scenario))

(define-method (person:talk (str <string>))
  (person:talk (person:current) str))

(define-method (person:set-position x y)
  (person:set-position (person:current) x y))

(define-method (person:walk-to x y)
  (person:walk-to (person:current) x y))

(define-method (person:set-direction sym)
  (person:set-direction (person:current) sym))

(define-method (person:remove-from-inventory sym)
  (person:remove-from-inventory (person:current) sym))

(define-method (person:add-to-inventory sym)
  (person:add-to-inventory (person:current) sym))

(define-method (person:walk-to (obj <adv:object>))
  (person:walk-to (person:current) obj))

(define-syntax adv:defperson
  (syntax-rules ()
    ((_ sym)
     (define sym (person:create)))))


;; EOF ;;