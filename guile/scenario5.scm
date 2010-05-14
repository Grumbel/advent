;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Fourth outdoor scene, the door ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-class <outdoor4:console> (<advent:object>))
(define-method name ((obj <advent:object>)) "console") 
(define-method use ((console <outdoor4:console>))
  (let ((obj (get-obj "door")))
    (cond ((closed obj)
	   (set! (closed obj) #f)
	   (advent:set-surface (adv:bind obj) "door_obj"))
	  (else
	   (set! (closed obj) #t)
	   (advent:set-surface (adv:bind obj) "")))))
  
(define-class <outdoor4:back> (<advent:object>))
(define-method name ((obj <outdoor4:back>)) "back")
(define-method use ((obj <outdoor4:back>))
  (scenario:set-current game-scenario:outdoor2-bind)
  (set! *current-scenario* game-scenario:outdoor2-objects))

(define-class <outdoor4:door> (<advent:object>)
  (closed #:accessor closed
	  #:init-value #f))
(define-method name ((obj <outdoor4:door>)) "door")

(define game-scenario:outdoor4-objects 
  (list (make <outdoor4:door> #:adv:bind (advent:makeobj-surface "door" "door_obj"
								 310 31 0))
	(make <outdoor4:console> #:adv:bind (advent:makeobj-surface "console" "console"
								    250 398 228))
	(make <outdoor4:back> #:adv:bind (advent:makeobj-empty "back" 0 300
							       70 340))
	))

(define game-scenario:outdoor4-bind
  (scenario:make-bind "game-scenario:outdoor4"
		      "door" "door_cmap"
		      (map (lambda (x) (adv:bind x))
			   game-scenario:outdoor4-objects)))

(define game-scenario:outdoor4
  (make <scenario> 
    #:adv:bind game-scenario:outdoor4-bind
    #:adv:objs game-scenario:outdoor4-objects))

;; EOF ;;