;;(define-method (speak (obj <outdoor2:key>))
;;  (c:dialog:show (list "Hello key!"
;;		       "Stupid key!"
;;		       "Naaa... it's only a key, I don't talk to them.")
;;		 (lambda (selection)
;;		   [...])))

(define-class <dialog:choice> ()
  (sentence #:init-value   "<dialog:choice: not set>"
	    #:init-keyword #:sentence
	    #:accessor get-sentence)
  ;; Function or a <dialog> object
  (func #:init-value #f
	#:init-keyword #:func
	#:accessor get-func)

  (mark #:init-value #f
	#:init-keyword #:mark
	#:accessor get-mark))

(define-class <dialog> ()
  (choices #:init-value '()
	   #:accessor get-choices
	   #:init-keyword #:choices))
  
(define (dialog:enable)
  (println "dialog:enable: not implemented"))

(define (dialog:disable)
  (println "dialog:enable: not implemented"))

(define-method (dialog:show (dialog <dialog>))
  (c:dialog:show (map (lambda (x) (get-sentence x))
		      (get-choices dialog))
		 (lambda (selection)
		   (let ((func (list-ref (map (lambda (x) (get-func x)) (get-choices dialog))
					 selection)))
		     (cond ((procedure? func)
			    (func))
			   ((is-a? func <dialog>)
			    (dialog:show func))
			   ((is-a? (eval func) <dialog>)
			    (dialog:show (eval func)))
			   (else
			    (println "Error:dialog:show: Unknown type: " func)))))))

(define (dialog:make . lst)
  (make <dialog> #:choices (map (lambda (x)
				  (if (equal? (length x) 3)
				      (make <dialog:choice>
					#:sentence (car x) 
					#:func (cadr x) 
					#:mark (caddr x))
				      (make <dialog:choice>
					#:sentence (car x) 
					#:func (cadr x))))
				lst)))

(define-syntax adv:define-dialog
  (syntax-rules ()
    ((_ name lst ...)
     (define name (dialog:make lst ...)))))

;; Add a string or a list of strings to the dialog
;; FIXME: Dialogs should be connected to a person.
(define (dialog:add . lst)
  (c:dialog:clear)
  (for-each (lambda (x) 
	      (c:dialog:push x))
	    lst)
  ;; FIXME: This is probally incompatible with older code
  (let ((hook (c:adv:hook:make)))
    (c:dialog:add-hook (lambda () (c:adv:hook:call-finish hook)))
    hook))

(define (adv:say person . lst)
  (println "person: " person "lst: " lst)
  (c:dialog:set-speaker person)
  (apply dialog:add lst))

(define-syntax dialog:add-hook 
  (syntax-rules ()
    ((_ body ...)
     (c:dialog:add-hook (lambda () body ...)))))

#!
(adv:say *current-person* 'normal "This is" 'angry "fucking stupid!")
!#

;; EOF ;;
