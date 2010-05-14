(define-method (adv:walkto-pos (obj <advent:object>))
  #f)

(define-method (adv:walkto-func (obj <advent:object>))
  (walk obj))

(define-method (adv:walkto-func (obj <advent:walk-point>))
  (println "walk-point: Not implemented"))

(define-method (adv:walkto-func (obj <advent:walk-point>))
  (println "walk-point: Not implemented"))

(define-method (adv:combine (obj1 <advent:object>) (obj2 <advent:object>))
  (adv:walkto obj2 (lambda () (combine obj1 obj2))))
      
(define-method (adv:use (obj <advent:object>))
  (adv:walkto obj (lambda () (use obj))))

(define-method (adv:speak (obj <advent:object>))
  (adv:walkto obj (lambda () (speak obj))))
  
(define-method (adv:pickup (obj <advent:object>))
  (adv:walkto obj (lambda () (pickup obj))))
  
(define-method (adv:look (obj <advent:object>))
  (adv:walkto obj (lambda () (look obj))))

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
(define-method (adv:walk (obj <advent:object>))
  (let ((func (lambda () (adv:walkto-func obj))))
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
				 (lambda () (adv:walkto-func obj))))
	      (else
	       (walk obj))))))

;; EOF ;;