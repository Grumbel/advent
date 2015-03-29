;; $Id: helper.scm,v 1.8 2002/04/16 11:01:00 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; A bunch of helper functions to make scheme more usable (println,
;; filter, grep, ...)
;;

;;(define-public-module (advent helper))
;;(use-modules (oop goops))

(define-public (get-keyword-value args keyword default)
  (let ((kv (memq keyword args)))
    (if (and kv (>= (length kv) 2))
	(cadr kv)
	default)))

;; Return a list containing all the objects which match 'pred?'
(define-public (filter pred? objects)
  (let loop ((objs objects)
	     (result '()))
    (cond ((null? objs) (reverse! result))
	  ((pred? (car objs)) (loop (cdr objs) (cons (car objs) result)))
	  (else (loop (cdr objs) result)))))

;; Return a list of the strings which match the regex 'rx'
(define-public (grep rx strings)
  (let ((r (make-regexp rx)))
    (filter (lambda (x) (regexp-exec r x)) strings)))

(define (myprint . str)
  (for-each (lambda (x) (display x)) str)
  (force-output))
(export myprint)

(define (println-sep . str)
  (for-each (lambda (x)
	      (display "\"")
	      (display x)
	      (display "\"")) str)
  (newline))
(export println-sep)

;; Print the given strings and a newline
(define (println . str)
  (apply myprint str) (newline))
(export println)

(define-public (repeat n func)
  (cond ((> n 0)
	 (func)
	 (repeat (1- n) func))))

;; Returns a list with numbers from 'start' to 'end'
;; Example: (seq 1 5) => (1 2 3 4 5)
(define-public (seq start end)
  (if (<= start end)
      (cons start (seq (1+ start) end))
      '()))

(define-public (nfor-each-helper num func lst)
  (cond ((not (null? lst))
	 (func num (car lst))
	 (nfor-each-helper (1+ num) func (cdr lst)))))

;; Don't know: FIXME, DOCUMENT ME
(define-public (nfor-each func lst)
  (nfor-each-helper 1 func lst))

(define-public (adv:symbol->classname sym)
  (string->symbol (string-append "<" (symbol->string sym) ">")))

(define-public (random-ref lst)
  (list-ref lst (random (length lst))))

;;
(define-public first car)
(define-public rest  cdr)

;; EOF ;;