;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Second outdoor since, the vilage ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-class <outdoor2:way> (<advent:object>))
(define-method name ((obj <outdoor2:way>)) "NextWay")
(define-method use ((obj <outdoor2:way>))
  (scenario:set-current game-scenario:outdoor-bind)
  (set! *current-scenario* game-scenario:outdoor-objects))

(define-class <outdoor2:way2> (<advent:object>))
(define-method name ((obj <outdoor2:way2>)) "WayToDoor")
(define-method use ((obj <outdoor2:way2>))
  (scenario:set-current game-scenario:outdoor4-bind)
  (set! *current-scenario* game-scenario:outdoor4-objects))

(define-class <outdoor2:plate> (<advent:object>))
(define-method name ((obj <outdoor2:plate>)) "plate")
(define-method use ((obj <outdoor2:plate>))
  (dialog:add "You see a plate"))

(define game-scenario:outdoor2-objects 
  (list (make <outdoor2:way> #:adv:bind (advent:makeobj-empty "NextWay"
						       560  320
						       80 160))
	(make <outdoor2:way2> #:adv:bind (advent:makeobj-empty "WayToDoor"
							       585 260
							       55 40))
	(make <outdoor2:plate> #:adv:bind (advent:makeobj-empty "plate"
								210 300
								40 40))
	))

(define game-scenario:outdoor2-bind
  (scenario:make-bind "game-scenario:outdoor2"
		      "background3" "background3_cmap"
		      (map (lambda (x) (adv:bind x))
			   game-scenario:outdoor2-objects)))

(define game-scenario:outdoor2
  (make <scenario> 
    #:adv:bind game-scenario:outdoor2-bind
    #:adv:objs game-scenario:outdoor2-objects))

;; EOF ;;