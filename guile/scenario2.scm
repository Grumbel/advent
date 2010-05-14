;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; First outdoor scene, in front of the house ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Objects
(define-class <plant>   (<advent:object>))
(define-method name ((obj <plant>)) "plant")

(define-class <outdoor:way> (<advent:object>))
(define-method name ((obj <outdoor:way>)) "NextWay")

(define-method use ((obj <outdoor:way>))
  (scenario:set-current game-scenario:outdoor2-bind)
  (set! *current-scenario* game-scenario:outdoor2-objects))

(define game-scenario:outdoor-objects
  (list (make <plant> #:adv:bind (advent:makeobj-surface "plant" "plant2"
						  208  350 194))
	(make <outdoor:way> #:adv:bind (advent:makeobj-empty "NextWay" 
							     0  260
							     70 220))
	))

(define game-scenario:outdoor-bind
  (scenario:make-bind "game-scenario:outdoor"
		      "background2" "background2_cmap"
		      (map (lambda (x) (adv:bind x))
			   game-scenario:outdoor-objects)))

(define game-scenario:outdoor
  (make <scenario> 
    #:adv:bind game-scenario:outdoor-bind
    #:adv:objs game-scenario:outdoor-objects))

;; EOF ;;