;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Third outdoor scene, the othe gateway ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-class <outdoor3:gateway> (<advent:object>))
(define-method name ((obj <outdoor3:gateway>)) "NextWay")
(define-method use ((obj <outdoor3:gateway>))
  (scenario:set-current game-scenario:gateway-bind)
  (set! *current-scenario* game-scenario:gateway-objects))

(define game-scenario:outdoor3-objects
  (list (make <outdoor3:gateway> #:adv:bind (advent:makeobj-empty "NextWay"
						       440 200
						       130 140))))

(define game-scenario:outdoor3-bind
  (scenario:make-bind "game-scenario:outdoor3"
		      "background4" "background4_cmap"
		      (map (lambda (x) (adv:bind x))
			   game-scenario:outdoor3-objects)))

(define game-scenario:outdoor3
  (make <scenario> 
    #:adv:bind game-scenario:outdoor3-bind
    #:adv:objs game-scenario:outdoor3-objects))

;; EOF ;;