(use-modules (ice-9 syncase))

(display (current-module)) (newline)
(define var-a (make-variable 5 'a) )
(variable-ref var-a)
(define my-module (make-module))
(module-add! my-module 'a var-a)

(define (display-module module)
  (module-for-each
   (lambda (sym var) 
     (display sym)
     (display " => ")
     (display (variable-ref var))(newline))
   module))

(define my-module (make-module))
(define old-module (current-module))
(define global-module (current-module))
(module-use! my-module (current-module))
(set-current-module my-module)
(define (bla) (display "bla") (newline))
(bla)
(set-current-module old-module)
;;(bla)
(define (lookup sym)
  (variable-ref (module-variable my-module sym)))

(module-for-each (lambda (sym var)
  ;;(module-add! global-module sym var)
		   (display sym)
		   (display " => ")
		   (display (variable-ref var))(newline)
		   ;;(display-module (current-module))
		   (module-add! (current-module) 'bla var)
		   )
		   ;;(display-module (current-module)))
		 my-module)

(define-syntax import 
  (syntax-rules ()
    ((_ module oldsym)
     (module-add! (current-module) 
		  (string->symbol
		   (string-append "bla:" (symbol->string oldsym)))
		  (module-local-variable module oldsym))
     )))

(display (current-module)) (newline)

#!
(let ((tmp-module (current-module))
      (new-module (make-module)))
  (define my-module new-module)
  (module-use! new-module (current-module))
  (set-current-module new-module)
  (module-make-local-var! (current-module) 'a)
  (set-current-module tmp-module))

!#

;; EOF ;;