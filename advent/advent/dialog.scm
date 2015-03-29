(use-modules (oop goops)
	     (advent core))

(export <dialog:choice> <dialog> *current-dialog* dialog:clear dialog:add-button dialog:show)
(export-syntax adv:defdialog)

(define-class <dialog:choice> ()
  ;; The sentance which is shown in the select menu, when multiple
  ;; lines are given, only the first is shown. FIMXE: Not sure if we
  ;; need this multiline support
  (sentence #:init-value   "<dialog:choice: not set>"
	    #:init-keyword #:sentence
	    #:accessor get-sentence)

  ;; Function or a <dialog> object
  (next #:init-value #f
	#:init-keyword #:next
	#:accessor get-next)
  
  ;; Type: symbol or list of symbols
  ;; Some mark, like read or something
  (mark #:init-value #f
	#:init-keyword #:mark
	#:accessor get-mark))

;; A set of choices
(define-class <dialog> ()
  (choices #:init-value '()
	   #:accessor get-choices
	   #:init-keyword #:choices))

(define *current-dialog* #f)

(define (dialog:clear)
  (cond (*current-dialog*
	 (for-each (lambda (button)
		     (c:layerscreen:remove game-screen button))
		   *current-dialog*))))

(define (dialog:add-button button)
  (cond ((not *current-dialog*)
	 (set! *current-dialog* (list button)))
	(else
	 (append! *current-dialog* (list button)))))

(define-method (dialog:show screen (dialog <dialog>))
  (dialog:clear)
  (let ((y-pos 70))
    (for-each (lambda (choice)
		(let ((button (c:buttonlayer:create 
			       (c:font-sprite:create "arialfont14_magenta" 
						     (get-sentence choice))
			       #f
			       (c:font-sprite:create "arialfont14_orange" 
						     (get-sentence choice))
			       10 y-pos)))
		  (c:layerscreen:push screen button)
		  (dialog:add-button button)
		  (c:buttonlayer:set-press-callback 
		   button
		   (lambda ()
		     (adv:seq (dialog:clear)
			      (person:talk (get-sentence choice))
			      (let ((ret ((get-next choice))))
				(cond ((is-a? ret <dialog>)
				       ;; FIXME: Clear dialog here
				       (dialog:show screen ret))
				      )))))
		  (set! y-pos (+ y-pos 20))))
	      (get-choices dialog))))

;; Syntax:
;;
;; (adv:defdialog DIALOGNAME 
;;                (SENTANCE EXPRESSION ...)
;;                ...)
;;
;; Describtion:
;;
;;  Define a new dialog object, where SENTANCE is the sentance to
;;  speak, EXPRESSION is an scheme expresion which will be evaluated
;;  or another dialog object and MARK-LIST is a list of marks.
;;
;; FIXME:
;;  
;;  - How to do different colors for sentances (some kind of mark-up?!)
;;  - How can one use marks, examples of marks
;; 
;; (get-mark 'counter test-dialog 5) => 3
;; (get-mark 'read    test-dialog 5) => #t

;; "Auto-marks", Readmarks, Countmarks, etc.
(define-syntax adv:defdialog
  (syntax-rules ()
    ((_ dialogname (sentance next ...) ...)
     (define dialogname 
       (make <dialog> #:choices
	     (list
	      (make <dialog:choice>
		#:sentence sentance 
		#:next (lambda () next ...)
		)
	      ...))))))


#!
Wannabe:

(adv:defdialog 
 ("Hello? bla/blub" action)
 ("Hello how are you" "bla/blub"))

(define-dialog mydialog
  [choices
   (add-choice 1 "dies und das...")
   (add-choice 2 "blublub")
   (if foobar (add-choice 3 "Having a bad day?"))]

  [switch
    (1 (say bob "blablub"))
    (2 (say bob "boaeuaou"))
    ((3 4 5)
     (show myotherdialog))])
    

click -> click-events -> get-action -> callback -> script


!#

;; EOF ;;