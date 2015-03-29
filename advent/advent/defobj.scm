(use-modules (oop goops))

(export adv:compact-args adv:defobj-name adv:defobj-hotspot adv:defobj-bind
	adv:defobj-setter adv:evaluate-setter adv:create-class adv:status-to-slots
	adv:defobj_ adv:create-methods)

(export-syntax adv:defobj)

(define (adv:compact-args lst)
  (for-each (lambda (x)
	      (let ((sym  (car x))
		    (rest (cdr x)))
		(case sym
		  ((members)
		   (println "OK"))
		  (else
		   (println "Unknown symbol: " sym)))))
	    lst))

(define (adv:defobj-name obj class lst)
  ;;(println "Name: " lst " " obj " "class)
  (set! (adv:name obj) (car lst)))

(define (adv:defobj-hotspot obj class lst)
  (cond ((and (= (length lst) 3)
	      (integer? (car lst))
	      (integer? (cadr lst)))
	      ;; FIXME: Doesn't work: (symbol?  (caddr lst)))
	 ;; Only a single hotspot is given
	 (set! (adv:hotspots obj) (list lst)))
	(else
	 ;; Multiple hotspots are given
	 (set! (adv:hotspots obj) lst))))

(define (adv:defobj-bind obj class lst)
;;  (println "XXXXXXXXXXXX: " lst)
  (cond ((= (length lst) 4)
	 (cond ((string? (primitive-eval (car lst)))
			 (let* ((sprite (sprite-drawable:create (primitive-eval (car lst))
								(primitive-eval (cadr lst))
								(primitive-eval (caddr lst))
								(primitive-eval (cadddr lst))))
				(collideable (c:sprite-collideable:create sprite))
				(advobj (c:drawable-advobj:create obj sprite collideable)))
			   (set! (adv:bind obj) advobj)))
	       (else
		(let ((advobj (c:empty-advobj:create
			       obj (c:rect-collideable:create (primitive-eval (car lst))
							      (primitive-eval (cadr lst))
							      (primitive-eval (caddr lst))
							      (primitive-eval (cadddr lst))))))
		  (set! (adv:bind obj) advobj)
		))))
	((= (length lst) 5)
	 (let* ((sprite (sprite-drawable:create-anim (primitive-eval (car lst))
						     (primitive-eval (cadr lst))
						     (primitive-eval (caddr lst))
						     (primitive-eval (cadddr lst))
						     (primitive-eval (car (cddddr lst)))))
		(collideable (c:sprite-collideable:create sprite))
		(advobj (c:drawable-advobj:create obj sprite collideable)))
	   (set! (adv:bind obj) advobj)))

	(else
	 (set! (adv:bind obj) (primitive-eval (car lst))))))

(define (adv:defobj-setter obj class lst)
  ;; Replace this with a for-each loop
  (cond ((not (null? lst))
	 (case (caar lst)
	   ((name)    (adv:defobj-name    obj class (cdar lst)))
	   ((hotspot) (adv:defobj-hotspot obj class (cdar lst)))
	   ((bind)    (adv:defobj-bind    obj class (cdar lst)))
	   ((status)  #t) ;; This are handled elsewhere
	   ((methods) #t) ;; This are handled elsewhere
	   (else      (println "Error: Unknown symbol: " (caar lst))
		      (exit)))
	 (adv:defobj-setter obj class (cdr lst)))))

(define-syntax adv:defobj
  (syntax-rules ()
    ((_ objname pair ...)
     (let ((classname (adv:symbol->classname 'objname)))
       ;; Create the object
       (adv:defobj_ 'objname classname (assoc-ref '(pair ...) 'status))

       ;; Create the methods
       (adv:create-methods classname (assoc-ref '(pair ...) 'methods))

       ;; Set everything
       (adv:defobj-setter objname (primitive-eval classname) '(pair ...))))))

(define (adv:evaluate-setter setter)
  #f)

(define (adv:create-class classname status)
  (if status
      (append (list 'define-class  classname '(<adv:object>))
	      (adv:status-to-slots status))
      (list 'define-class  classname '(<adv:object>))))

;; Converts a list of form ((bla #f)(blub #t)) to a slot list
(define (adv:status-to-slots status)
  (println "adv:status-to-slots: " status)
  (if status
      (map (lambda (x)
	     (list (car x)
		   #:accessor (car x)
		   #:init-value (cadr x)
		   ))
	   status)))

(define (adv:defobj_ obj-name classname
		     status)
  (println "Defobj: " obj-name " " classname " " status)
  (println "ToEval: " (adv:create-class classname status))
  (primitive-eval (adv:create-class classname status))
  (primitive-eval `(define ,obj-name (make ,classname)))
  (adv:evaluate-setter setter))

(define (adv:create-methods classname methods)
  (println "adv:create-methods: " classname " Methots: " methods)
  (if methods
      (for-each (lambda (x)
		  (let ((methodname (car x))
			(method     (cdr x)))
		    (primitive-eval (append `(define-method (,methodname (obj ,classname)))
				  method))))
		methods)))

#!
(adv:defclass <workplace:phone>
	      (name    "Phone")
	      (bind    (adv:empty-region 266 255 35 15))
	      (hotspot 249 316 'east)
	      (active #f)

	      (status (broken #t))

	      (methods <person:roboter>
		       (look  (dialog:add "pip pip... bib..."))
		       (use   (dialog:add "no...pip pip...")))

	      (methods
	       (look  (dialog:add "My phone... I hate it."))
	       (use   (speak obj))
	       (fix   (set! (broken this) #f))
	       (pickup (adv:pickup this)
		       (adv:say "A nice telephon, could be usefull later on..."))
	       (speak (adv:seq (adv:say "Phone:" "*ring*, *ring*,...")
			       (adv:say "Robi:"  "Hello..?")))))

(adv:defobj workplace:phone
	    (name    "Phone")
	    (bind    (adv:empty-region 266 255 35 15))
	    (hotspot 249 316 'east)
	    (active #f)
	    [...])

(adv:defobj workplace:phone
	    (class <workplace:phone>) ;; default: <adv:object>
	    (bind (adv:empty-region 344 399 299 199 15))
	    (hotspot 256 234 'east))


adv:defobj:
~~~~~~~~~~~
- define an object of a certain class
-

!#

;; EOF ;;