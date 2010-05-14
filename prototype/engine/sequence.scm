;; $Id: sequence.scm,v 1.1 2001/07/07 10:58:59 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Helper functions for cutscenes and sequencial animations
;;

;; TimeManager, timed
(define-syntax adv:timed
  (syntax-rules ()
    ((_ macro:time macro:func ...)
     (c:add-timed macro:time
		  (lambda () macro:func ...)))))

(define (_adv:sequential lst)
  (cond ((not (null? lst))
	 ;;(println "Sequanital: " lst)
	 ;;(println ">>>>> " (caar lst) (cdar lst))
	 (c:add-timed (caar lst)
		      (lambda ()
			((cdar lst)) ;; Call
			;;(println "Timed call: " (cdr lst))
			(_adv:sequential (cdr lst))
			)))))

(define-syntax adv:sleep
  (syntax-rules ()
    ((_ time)
     (let ((hook (c:adv:hook:make)))
       (c:add-timed time (lambda () (c:adv:hook:call-finish hook)))
       hook)
     )))

;; Call non-hookivied functions in a hookived environment
#!
(define-syntax adv:par
  (syntax-rules ()
    ((_ body ...)
     (let ((hook (c:adv:hook:make)))
       body ...
       hook))
     ))
!#

(define-syntax adv:sequential
  (syntax-rules ()
    ((_ (time body ...) ...)
     (_adv:sequential (list (cons time (lambda () body ...))
			    ...)))))

;; EOF ;;