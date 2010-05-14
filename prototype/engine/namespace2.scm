(use-modules (ice-9 syncase))

(define (low:import-module module symb)
     ;;     (module-add! (current-module) 'my-module:a 
     ;;		  (module-local-variable module 'a))
     (begin 
       (display "Module1: " ) (display symb) (newline)
       (display "Module2: " ) (display module) (newline)
     (module-for-each 
      (lambda (sym var)
	(module-add! (current-module) 
		     (string->symbol
		      (string-append (symbol->string symb)
				     ":"
				     (symbol->string sym)))
		     (module-local-variable module sym)
		     ))
      module)))

(define-syntax import-module
  (syntax-rules ()
    ((_ module)
     (low:import-module module 'module)
     )))

(define-syntax adv:load-module
  (syntax-rules ()
    ((_ module)
     (define module (load-scenario (string-append (symbol->string 'module) ".scm")
		    'module))
     )))

(define (display-module module)
  (newline)
  (display "[Module: ") (display module) (display "]") (newline)
  (module-for-each
   (lambda (sym var) 
     (display "  ")
     (display sym)
     (display " => ")
     (display (variable-ref var))(newline))
   module)
  (newline))

(define (load-scenario file sym)
  (let ((module        (make-module))
	(tmp-module (current-module)))
    (module-use! module (current-module))
    (set-current-module module)
    (load file)
    (set-current-module tmp-module)
    (low:import-module module sym)
    module
    ))
#!
(define sub-module (make-module))
(define global-module (current-module))
(module-use! sub-module global-module)

(set-current-module sub-module)
(define a 5)
(display a) (newline)
(set-current-module global-module)

(import-module sub-module)

(display sub-module:a) (newline)
(display-module sub-module)

;;(load-scenario "test.scm" 'test)

(adv:load-module 'test)

;;(display-module (current-module))
(display test:bcar) (newline)
(display test:bike) (newline)
(display (test:speed test:bike)) (newline)
!#


;; Extract all advent:object from the current file
(define (adv:extract-objects module)
  (let ((lst '()))
    (module-for-each
     (lambda (sym var) 
       ;;(println "Lst: " lst)
       (if (is-a? (variable-ref var) <advent:object>)
	   (set! lst (cons (variable-ref var) lst))))
     module)
    lst))

;; EOF ;;