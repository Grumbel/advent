#!/usr/bin/guile \
--debug -s
!#

(use-modules (ice-9 getopt-long)
	     (ice-9 string-fun)
	     (oop goops))



(define *current-scenario* '())
(define (scenario:set scenario)
  (set! *current-scenario* scenario))

(define (scenario:remove-obj obj)
  (set! *current-scenario* (filter (lambda (x)
				     (not (equal? obj x)))
				   *current-scenario*)))

(define (scenario:add-obj obj)
  (set! *current-scenario* (cons obj *current-scenario*)))

(define-class <advent:object> ()
  (adv:bind #:accessor adv:bind #:init-value #t #:init-keyword #:adv:bind))

(define-method name ((obj <advent:object>)) "<unset>")

(define-class <scenario> ()
  ;; The bind object contains a pointer back to the C++ Scenario class
  (adv:bind #:init-value #f 
	#:init-keyword #:adv:bind
	#:accessor adv:bind)

  ;; The list of objects in this scenario
  (adv:objs #:init-value '()
	#:init-keyword #:adv:objs
	#:accessor adv:objs))

;;(define (printf fmt . lst)
;;  (display (format #f fmt lst)))

(define (get-obj nme)
  (or (get-obj-helper nme *current-scenario*)
      (get-obj-helper nme *inventory*)))

(define (get-obj-helper nme objs)
  (cond ((null? objs)
	 #f)
	(else
	 (let ((obj-name (name (car objs))))
	   (cond ((string=? nme obj-name)
		  (car objs))
	       (else
		(get-obj-helper nme (cdr objs))))))))


(define (read-command)
  (print "Advent> ")
  (read-line))

(define (advent:help-command args)
  (cond ((equal? (length args) 1)
	 (cond ((string=? (car args) "look")
		(dialog:add "look object - and here what you see."))
	       (else
		(dialog:add (string-append
			     "Can't help you with " (car args))))))
	(else
	 (dialog:add "Commands: help, look, walk, pickup, open, close"))
	))

(define (advent:tokenize command-line)
  (cond ((eof-object? command-line)
	 command-line)
	(else
	 (filter (lambda (x) (not (or (string=? x "")
				      (string=? x "at")
				      (string=? x "to")
				      (string=? x "with")
				      (string=? x "a")
				      (string=? x "the"))))
		 (separate-fields-discarding-char #\space command-line 
						  list)))))

;; Verbs
(define (advent:look args)
  (cond ((equal? (length args) 1)
	 (look (get-obj (car args))))
	(else
	 (dialog:add "Where should I look at?"))))

(define (advent:pickup args)
  (for-each (lambda (x) (pickup (get-obj x)))
	    args))

(define (advent:walk args)
  (cond ((equal? (length args) 1)
	 (walk (get-obj (car args))))
	(else
	 (dialog:add "Don't know where to walk."))))
  
(define (advent:use args)
  (cond ((equal? (length args) 1)
	 (use (get-obj (car args))))
	((equal? (length args) 2)
	 (use (get-obj (car args))
	      (get-obj (cadr args))))
	(else
	 (dialog:add "Don't know what you mean"))))

(define (advent:open args)
  (cond ((equal? (length args) 1)
	 (gopen (get-obj (car args))))
	(else
	 (dialog:add "Don't know what you mean."))
	))

(define-method walk ((obj <boolean>))
  (dialog:add "Don't know what you mean. So I am still here."))

(define-method walk ((obj <advent:object>))
  (dialog:add "I am already there."))

(define-method gopen ((obj <boolean>))
  (dialog:add "Don't know what you mean."))

(define-method gopen ((obj <advent:object>))
  (dialog:add "I can't open this ")); (name obj)))

(define-method gclose ((obj <boolean>))
  (dialog:add "Don't know what you mean."))

(define-method gclose ((obj <advent:object>))
  (dialog:add (string-append "I can't close this " (name obj))))

(define *inventory* '())

(define-method add-inventory ((obj <advent:object>))
  (cond ((not (inventory-has obj))
	 (set! *inventory* (cons obj *inventory*))
	 (dialog:add (string-append "You picked up a " (name obj))))
	(else
	 (dialog:add (string-append "You already have this " (name obj))))))

(define-method inventory-has ((obj <advent:object>))
  (member obj *inventory*))

(define (advent:close args)
  (cond ((equal? (length args) 1)
	 (gclose (get-obj (car args))))
	(else
	 (dialog:add "Don't know what you mean." args))
	))

(define (advent:eval command-line)
  (let ((token (advent:tokenize command-line)))
    (cond ((eof-object? command-line)
	   (exit 0))
	  ((null? token)
	   '())
	  (else
	   (let ((command (car token))
		 (args    (cdr token)))
	     (cond ((string=? command "quit")
		    (dialog:add "Bye, bye")
		    (exit 0))
		   ((string=? command "help")
		    (advent:help-command args))
		   ((string=? command "look")
		    (advent:look args))
		   ((string=? command "walk")
		    (advent:walk args))
		   ((string=? command "pickup")
		    (advent:pickup args))
		   ((string=? command "use")
		    (advent:use args))
		   ((string=? command "open")
		    (advent:open args))
		   ((string=? command "inventory")
		    (dialog:add "Invectory: ")
		    (println *inventory*))
		   (else
		    (println "- unknown command: " command))))))))

(load "helper.scm")

(define (dialog:add str)
  (dialog:add2 str)
  (println str))

(load "syntax-ext.scm")
(load "objects.scm")
(println "Adventure V0.0")


;; EOF ;;