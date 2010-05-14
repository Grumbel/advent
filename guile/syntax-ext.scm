(use-modules (ice-9 syncase))

(define-syntax adv:define-object
  (syntax-rules ()
    ((_ type)
     (let ((classname (string->symbol (string-append "<" (symbol->string 'type) ">"))))
       (eval `(define-class ,classname (<advent:object>)))
       (eval `(define type (make ,classname)))
       ))
    ((_ type str-name (mem-name value) ...)
     (let ((classname (string->symbol (string-append "<" (symbol->string 'type) ">"))))
       (eval `(define-class ,classname (<advent:object>)
		(name #:accessor name #:init-value str-name)
		(mem-name #:accessor mem-name
			  #:init-value value
;;		      #:init-keyword #:,(string->symbol "#:name")
		      )
		...))
       (eval `(define type (make ,classname)))
       ))
    ))

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

;; EOF ;;