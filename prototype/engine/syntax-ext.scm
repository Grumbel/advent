;; $Id: syntax-ext.scm,v 1.7 2001/07/02 10:27:13 grumbel Exp $                                                             
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Macros of various stuff, all this should be sorted.
;;

(define (get-keyword-value args keyword default)
  (let ((kv (memq keyword args)))
    (if (and kv (>= (length kv) 2))
	(cadr kv)
	default)))

;; Register a scenario and load it on demand
(define-syntax adv:register-scenario
  (syntax-rules ()
    ((_ name filename)
     (define name (cons 'name filename)))))

(define-syntax adv:register-scenarios
  (syntax-rules ()
    ((_ (name filename) ...)
     (begin 
       (define name (cons 'name filename))
       ...))))

;; Define a class and the corresponding object
;;(define-syntax adv:bind-hotspot
;;  (syntax-rules ()
;;    ((_ type)

;; TimeManager, timed
(define-syntax adv:timed
  (syntax-rules ()
    ((_ macro:time macro:func ...)
     (c:add-timed macro:time
		  (lambda () macro:func ...)))))

;; Define a class and the corresponding object
(define-syntax adv:define-object
  (syntax-rules ()
    ((_ type)
     (let ((classname (string->symbol (string-append "<" (symbol->string 'type) ">"))))
       (eval `(define-class ,classname (<advent:object>)))
       (eval `(define type (make ,classname)))
       ))
    ((_ type str-name (mem-name value) ...)
     (let ((classname  (string->symbol (string-append "<" (symbol->string 'type) ">")))
	   )
       (eval `(define-class ,classname (<advent:object>)
		(name #:accessor name #:init-value str-name) 
		(mem-name #:accessor mem-name
			  #:init-value value
			  #:setter  ,(string->symbol
				      (string-append "set-" (symbol->string 'mem-name))))
		...))
		;;		      #:init-keyword #:,(string->symbol "#:name")
       (eval `(define type (make ,classname)))
       ))
    ))

;; Define only a class (rarly used)
(define-syntax adv:define-class
  (syntax-rules ()
    ((_ type)
     (let ((classname (string->symbol (string-append "<" (symbol->string 'type) ">"))))
       (eval `(define-class ,classname (<advent:object>)))
		    ))
    ((_ type (name value) ...)
     (let ((classname (string->symbol (string-append "<" (symbol->string 'type) ">"))))
       (eval `(define-class ,classname (<advent:object>) 
		(name #:accessor name
		      #:init-value value)
		...))
       ))
    ))

;; Define an scenario
(define-syntax adv:define-scenario-new
  (syntax-rules ()
    ((_ name var ...)
     (eval `(define name 
	      ((lambda (. args)
		   (let ((surface  (get-keyword-value args #:surface #f))
			 (colmap   (get-keyword-value args #:colmap  #f))
			 (objects  (get-keyword-value args #:objects '()))
			 (with-guy (get-keyword-value args #:with-guy #t)))

		     ;;(println "Args: " args)
		     (adv:assert surface)
		     ;;(println "Objects: " objects)

		     (make <scenario> 
		       #:adv:symbol name
		       #:adv:bind 
		       (c:scenario:make-bind "name-blub" surface colmap
					     (map (lambda (x) (adv:bind x))
						  objects) with-guy)
		       #:adv:objs objects))) var ...))))))


(define-syntax adv:define-scenario
  (syntax-rules ()
    ((_ name surface colmap objects)
     (let ((classname (string->symbol 
		       (string-append "<" (symbol->string 'type) ">"))))
       (eval `(define name (make <scenario> 
			     #:adv:bind 
			     (c:scenario:make-bind "name-blub" surface colmap
						   (map (lambda (x) (adv:bind x))
							objects) #t)
			     #:adv:objs objects)))))
    ))

;(define-syntax adv:define-walkpoint 
;  (syntax-rules ()
;    ((_ name x1 y1 width height); new-scenario)
;     (adv:define-object name "WalkPoint")
;     (adv:bind-empty name x1 y1 width height)
;;     (define-method (adv:walkto-func (obj <name>) (adv:set-scenario game-scenario:scenario11))
;     )))

(define-syntax adv:set-scenario
  (syntax-rules ()
    ((_ scenario)
     (_adv:set-scenario 'scenario scenario))))
  

;; Define an scenario
(define-syntax adv:defmet
  (syntax-rules ()
    ((_ var ...)
     (define-method var ...))))


(define-syntax adv:defmets
  (syntax-rules ()
    ((_ type 
	(method body ...) 
	...)
     (begin 
       (adv:defmet (method (obj type))
		   body ...)
       ...)
     )))

(define-syntax adv:using
  (syntax-rules ()
    ((_ type
	(method body ...)
	...)
     (begin
       (method type body ...)
       ...))))

;; throws adv:assert if var is #f
(define-syntax adv:assert
  (syntax-rules ()
    ((_ var)
     (cond ((not var)
	    (display "Advent: Error: '")
	    (display 'var)
	    (display "' not defined")
	    (newline)
	    (throw 'adv:assert))))))

(define-syntax adv:get-message
  (syntax-rules ()
    ((_ queue)
     (begin 
       (cond ((null? (car queue))
	      (set-car! queue (reverse (cdr queue)))
	      (set-cdr! queue '())))

       (let* ((todo (car queue))
	      (done (cdr queue))
	      (current (car todo)))
	 (set-car! queue (cdr todo))
	 (set-cdr! queue (cons current done))
	 current)))))

(define-syntax adv:define-messages
  (syntax-rules ()
    ((_ name str ...)
     (define name 
       (cons
	(list str ...)
	'()))
       )))

;; EOF ;;