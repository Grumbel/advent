;; $Id: sequence.scm,v 1.9 2002/04/16 11:01:00 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Helper functions for cutscenes and sequencial animations
;;

(export adv:timed adv:seq)

;; TimeManager, timed
(define-syntax adv:timed
  (syntax-rules ()
    ((_ macro:time macro:func ...)
     (c:add-timed macro:time
		  (lambda () macro:func ...)))))

;; Evaluate a list of expressions in sequential order, instead of
;; instantan evaluation.
;; FIXME: Works *only* with '(order)=>hook' able functions
#!
(define-syntax adv:seq
  (syntax-rules ()
    ((_ first)
     first)
    ((_ first rest ...)
     (let ((hook first))
       (if (c:delayed-advhook? hook)
	   (c:advhook:add hook (lambda () (adv:seq rest ...)))
	   (adv:seq rest ...))))))
!#

(define-syntax adv:seq
  (syntax-rules ()
    ((_ lst ...)
     (_adv:seq (list (delay lst) ...)))))

(define-public (_adv:seq lst)
  ;;(println "Sequenze: " lst)
  (cond ((null? lst)
	 #f)
	((null? (cdr lst)) ;; last element in list
	 (force (car lst))) ;; FIXME: Is this usefull... I guess not.
	(else
	 (let ((hook (force (car lst))))
	   (cond ((c:delayed-advhook? hook)
		  (c:advhook:add hook (lambda () (_adv:seq (cdr lst)))))
		 (else
		  (_adv:seq (cdr lst))))))))

;; Returns a hook that will be involked in 'time' number of seconds
(define-public (adv:sleep time)
  (let ((hook (c:delayed-advhook:create)))
    (c:timemanager:add
     timemanager ;; FIXME: TimeManager needs to be a global thing
     time (lambda () (c:advhook:call hook)))
    hook))

;; EOF ;;