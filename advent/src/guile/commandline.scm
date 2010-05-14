;; Code for emulation a readline like thing
(use-modules (oop goops)
	     (ice-9 format)
	     (ice-9 syncase)
	     (ice-9 optargs))

(define (command-line:get-completions str lst)
  (cond ((not (null? lst))
	 (cond ((string=? str (substring (car lst) 0 (string-length str)))
		(cons (car lst)
		      (get-completions str (cdr lst))))
	       (else
		(get-completions str (cdr lst)))))
	(else
	 '())))

(define *command-line:history '())

(define *command-line:buffer* "-----")
(define *command-line:cursor-pos* 0)

(define (command-line:insert-char char)
  (case char
    ((backspace)       (command-line:insert-backspace))
    ((enter)           (command-line:eval))
    ((a b c d e f g h) (command-line:insert-alphanum))
    ((up)              (command-line:history-up))
    ((down)            (command-line:history-down))
    ))

(define (command-line:insert-alphanum char)
  #f)

(define (command-line:insert-backspace)
  (cond ((not (= *command-line:cursor-pos* 0))
	 (set! *command-line:cursor-pos* (1- *command-line:cursor-pos*))
	 (set! *command-line:buffer*
	       (string-append (substring *command-line:buffer* 0 *command-line:cursor-pos*)
			      (substring *command-line:buffer* (+ 1 *command-line:cursor-pos*)))))))

(define (string-insert-char pos char)
  #f)

(define (string-remove-char pos)
  #f)

;; EOF ;;