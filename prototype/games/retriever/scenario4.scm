;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Third outdoor scene, the othe gateway ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(adv:define-object outdoor3:gateway "Gateway")
(adv:bind-empty outdoor3:gateway 440 200 130 140)

;;(define-method (use (obj <outdoor3:gateway>))
;;  (adv:set-scenario game-scenario:gateway)
;;  (c:guy:set-position  423 327)
;;  (c:guy:set-direction 3))

(define-method (walk (obj <outdoor3:gateway>))
  (c:guy:set-target 455 338
		    (lambda ()
		      (adv:set-scenario game-scenario:gateway)
		      (c:guy:set-position  423 327)
		      (c:guy:set-direction 3))))

(define game-scenario:outdoor3-objects
  (list outdoor3:gateway))

(define game-scenario:outdoor3-bind
  (c:scenario:make-bind "game-scenario:outdoor3"
		      "background4" "background4_cmap"
		      (map (lambda (x) (adv:bind x))
			   game-scenario:outdoor3-objects) #t))

(define game-scenario:outdoor3
  (make <scenario> 
    #:adv:symbol 'game-scenario:outdoor3
    #:adv:bind game-scenario:outdoor3-bind
    #:adv:objs game-scenario:outdoor3-objects))

;; EOF ;;