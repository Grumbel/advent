#!/usr/bin/guile \
--debug -e main -s
!#

(use-modules (ice-9 getopt-long)
	     (ice-9 string-fun)
	     (ice-9 syncase)
	     (oop goops))

(define-class <topic> ()
  (sentences #:accessor sentences 
	     #:init-keyword #:sentences 
	     #:init-value '()))

(define-class <sentence> ()
  (text  #:accessor text 
	 #:init-keyword #:text 
	 #:init-value "[unset]")
  (answer-func #:accessor answer
	       #:init-keyword #:answer
	       #:init-value "[unset]")
  (follow-func  #:accessor follow-func
		#:init-keyword #:follow-func 
		#:init-value #f)
  (follow-topic #:accessor follow-topic
		#:init-keyword #:follow-topic
		#:init-value #f))

(define gesundheit-dialog 
  (make <topic> #:sentences (list (make <sentence> 
				    #:text "Habe gehoert du hast dir das bein gebrochen." 
				    #:answer-func (lambda () (println "Yepp, ist aber wieder verheilt."))
				    #:follow-topic 'dialog)
				  (make <sentence> 
				    #:text "Habe gehoert du hast einen unfall mit dem Schlitten gehabt." 
				    #:answer "Hab mir dabei das Bein gebrochen."
				    #:follow-topic 'dialog))))

(define wetter-dialog 
  (make <topic> #:sentences (list (make <sentence> 
				    #:text "Gestern hasts geregnet." 
				    #:answer "Jo, da waren ziemlich grosse Pfuetzen."
				    #:follow-topic 'dialog)
				  (make <sentence> 
				    #:text "Wird wohl morgen wieder die Sonne scheinen?"
				    #:answer "Ich glaub kaum, solch ein Glueck hat man nicht jeden Tag."
				    #:follow-topic 'dialog))))

(define dialog 
  (make <topic> #:sentences (list (make <sentence> 
				    #:text "Hi, wie gehts?" 
				    #:answer "So weit ganz gut."
				    #:follow-topic 'gesundheit-dialog)
				  (make <sentence> 
				    #:text "Wie ist das Wetter." 
				    #:answer "Die Sonne scheint."
				    #:follow-topic 'wetter-dialog)
				  (make <sentence> 
				    #:text "Gibt nichts mehr zu sagen, tschuess." 
				    #:answer "Ok, bye."
				    #:follow-func (lambda () (exit 0)))
				  )))

(define-method (show-sentence (obj <sentence>))
  (println (text obj))
  )

(define-method (show-topic (topic <topic>))
  (nfor-each (lambda (num el)
	      (print num ": ")
	      (show-sentence el)) (sentences topic)))

(define-method (eval-topic (topic <topic>) (selection <integer>))
  (let ((sent (list-ref (sentences topic) selection)))
    (println "< " (text sent))
    (println "> " (answer sent))
    (if (follow-func sent)
	((follow-func sent)))
    ;;    (println "Next Topic: " (eval (follow-topic sent)))
    (if (follow-topic sent)
	(show-dialog (eval (follow-topic sent)))
	(exit 0))
))

(define-method (show-dialog (topic <topic>))
  (show-topic topic)
  (print "Question: ")
  (let ((selection (1- (read))))
    (eval-topic topic selection)
    ))

(define (main args)
  (load "helper.scm")
  (println "Dialog V0.0")
  (show-dialog dialog))

;; EOF ;;