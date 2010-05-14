#!/usr/bin/guile \
--debug -e main -s
!#

(use-modules (ice-9 getopt-long)
	     (ice-9 string-fun)
	     (ice-9 syncase)
	     (oop goops))

(define-class <topic> ()
  (dialog   #:init-value '() #:accessor dialog   #:init-keyword #:dialog)
  (register #:init-value '() #:accessor register #:init-keyword #:register)
  (func     #:init-value (lambda () (println "Func unset"))
	    #:accessor func
	    #:init-keyword #:func))

(define-method (select-dialog (obj <topic>))
  ((func obj)))

(define-method (show-dialog (obj <topic>))
  (for-each println (dialog obj)))
;;  (println "show-dialog--"))

(define *general-topic* 
  (make <topic> 
    #:dialog (list "Hallo, wie gehts?"
		   "Wie ist das Wetter heute?"
		   "Einen schoenen Tag noch, ich habe wichtigeres zu tun.")
    #:func (lambda () (println "Bla selected"))))

(define-class <sentence> ()
  (text #:init-value "[unset]" #:accessor text #:init-keyword #:text)
  (func #:init-value (lambda () (println "[unset]"))
	#:accessor func 
	#:init-keyword #:func))

(define *current-topic* *general-topic*)

(define (main args)
  (load "helper.scm")
  (println "Dialog V0.0")
  (let loop ((a 5))
    (show-dialog *current-topic*)
    (select-dialog *current-topic*)
    ))

;;;;;;;;;;;;;;;;;;;;;;;
;; Topic
;; |
;; +-Sentence
;; | +-Topic
;; +-Sentence
;; | +-Topic
;; |   +-Sentence
;; |   +-Sentence
;; +-Sentence
;;;;;;;;;;;;;;;;;;;;;; 

;; EOF ;;
