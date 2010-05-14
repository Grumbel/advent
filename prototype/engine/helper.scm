;; $Id: helper.scm,v 1.2 2001/07/02 10:27:13 grumbel Exp $                                                             
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; A bunch of helper functions to make scheme usable (println,
;; filter, grep, ...)
;;

;; Return a list containing all the objects which match 'pred?'
(define (filter pred? objects)
  (let loop ((objs objects)
	     (result '()))
    (cond ((null? objs) (reverse! result))
	  ((pred? (car objs)) (loop (cdr objs) (cons (car objs) result)))
	  (else (loop (cdr objs) result)))))

;; Return a list of the strings which match the regex 'rx'
(define (grep rx strings)
  (let ((r (make-regexp rx)))
    (filter (lambda (x) (regexp-exec r x)) strings)))

(define (print . str)
  (for-each (lambda (x) (display x)) str)
  (force-output))

(define (println-sep . str)
  (for-each (lambda (x) 
	      (display "\"")
	      (display x)
	      (display "\"")) str)
  (newline))

;; Print the given strings and a newline
(define (println . str)
  (apply print str) (newline))

;; Returns a list with numbers from 'start' to 'end'
;; Example: (seq 1 5) => (1 2 3 4 5)
(define (seq start end)
  (if (<= start end)
      (cons start (seq (1+ start) end))
      '()))

;; Don't know: FIXME, DOCUMENT ME
(define (nfor-each func lst)
  (define (nfor-each-helper num func lst)
    (cond ((not (null? lst))
	   (func num (car lst))
	   (nfor-each-helper (1+ num) func (cdr lst)))))
  (nfor-each-helper 1 func lst))

;; EOF ;;