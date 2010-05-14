(define-method (adv:walkto-pos (obj <advent:object>))
  #f)

(define-method (adv:walkto-func (obj <advent:object>))
  (walk obj))

(define-method (adv:walkto-func (obj <advent:walk-point>))
  (println "walk-point: Not implemented"))

(define-method (adv:walkto-func (obj <advent:walk-point>))
  (println "walk-point: Not implemented"))


;;;;;;;;;;;;;
;; Actions ;;
;;;;;;;;;;;;;
(define-method (adv:combine (obj1 <advent:object>) (obj2 <advent:object>))
  (adv:walkto obj2 (lambda () (combine obj1 obj2))))

(define-method (adv:use (obj <advent:object>))
  (adv:walkto obj (lambda () (use obj))))

(define-method (adv:speak (obj <advent:object>))
  (adv:walkto obj (lambda () (speak obj))))

(define-method (adv:speak (person <person>) (obj <advent:object>))
  (adv:walkto obj (lambda () (speak obj))))

(define-method (adv:pickup (obj <advent:object>))
  (adv:walkto obj (lambda () (pickup obj))))


(define-method (adv:look (obj <advent:object>))
  (adv:walkto obj (lambda () (look obj))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; The same as above but with a new argument 'person' ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-method (adv:pickup (person <person>) (obj <advent:object>))
  (adv:walkto obj (lambda () (pickup obj))))

(define-method (adv:speak (person <person>) (obj <advent:object>))
  (adv:walkto obj (lambda () (speak obj))))

(define-method (adv:look (person <person>) (obj <advent:object>))
  (adv:walkto obj (lambda () (look obj))))

(define-method (adv:pickup (person <person>) (obj <advent:object>))
  (adv:walkto obj (lambda () (pickup obj))))

(define-method (adv:use (person <person>) (obj <advent:object>))
  (adv:walkto obj (lambda () (use obj))))

(define-method (adv:combine (person <person>) 
			    (obj1 <advent:object>) (obj2 <advent:object>))
  (adv:walkto obj2 (lambda () (combine obj1 obj2))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; This one is issued when anoter action requires it that the
;; character is near the object
(define-method (adv:walkto (obj <advent:object>) func)
  (if (adv:hotspot obj)
      (c:guy:set-target (car (adv:hotspot obj))
			(cdr (adv:hotspot obj))
			(if (adv:hotspot-direction obj)
			    (lambda () 
			      (c:guy:set-direction 
			       (adv:hotspot-direction obj))
			      (func))
			    func))
      (cond ((adv:walkto-pos obj)
	     (c:guy:set-target (car (adv:walkto-pos obj))
			       (cdr (adv:walkto-pos obj))
			       (lambda () ;;(adv:walkto-func obj)
				 (func))))
	    (else
	     (func)))))

;; This is called when an explicit walk to action is issued
;; FIXME: This must not be overwritten!
(define-method (adv:walk (obj <advent:object>) . hooks)
  (let ((func (lambda () 
		(let ((ret (adv:walkto-func obj))) ;; Calls (walk obj)
		  (for-each (lambda (x) (x)) hooks)
		  ret))))
    (if (adv:hotspot obj)
	(let ((hook (adv:guy:walk-to-target (car (adv:hotspot obj))
					    (cdr (adv:hotspot obj))))
	      (newhook (c:adv:hook:make)))
	  ;; Call function and correct the direction
	  (c:adv:hook:add-finish hook (lambda ()
					(if (adv:hotspot-direction obj)
					    (c:guy:set-direction 
					     (adv:hotspot-direction obj)))
					(let ((walk-hook (func)))
					  (if (adv:hook? walk-hook)
					      (c:adv:hook:add-finish 
					       walk-hook
					       (lambda () 
						 (c:adv:hook:call-finish newhook)))
					      (c:adv:hook:call-finish newhook))
					  )))
	  newhook)
	;; FIXME: no hotspot given... do something else, but what?!
	(cond ((adv:walkto-pos obj)
	       (c:guy:set-target (car (adv:walkto-pos obj))
				 (cdr (adv:walkto-pos obj))
				 (lambda () (adv:walkto-func obj))))
	      (else
	       (walk obj))))))

;; EOF ;;