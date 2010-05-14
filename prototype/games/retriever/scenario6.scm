;;;;;
(adv:define-object scenario6:smoke "Smoke")
(adv:bind-surface scenario6:smoke "smoke_anim" 491 -56 0)
;;;;;;;;;;

(adv:define-object scenario6:tunnel "Tunnel")
(define-method (walk (obj <scenario6:tunnel>))
  (c:guy:set-target 502 334 (lambda ()
			      (adv:set-scenario game-scenario:outdoor7)
			      (c:guy:set-position 80 220)
			      (c:guy:set-direction 2))))
(adv:bind-empty scenario6:tunnel 425 240 125 120)

(adv:define-object scenario6:village "Village")
(adv:bind-empty scenario6:village 0 80 170 320)
(define-method (walk (obj <scenario6:village>))
  (c:guy:set-target 103 411 (lambda ()
			      (adv:set-scenario game-scenario:outdoor4)
			      (c:guy:set-position 460 420)
			      (c:guy:set-direction 3))))

(define game-scenario:outdoor6-objects
  (list scenario6:tunnel
	scenario6:village
	scenario6:smoke))

(define game-scenario:outdoor6-bind
  (c:scenario:make-bind "game-scenario:outdoor6"
		      "background6" "background6_cmap"
		      (map (lambda (x) (adv:bind x))
			   game-scenario:outdoor6-objects) #t))

(define game-scenario:outdoor6
  (make <scenario> 
    #:adv:bind game-scenario:outdoor6-bind
    #:adv:objs game-scenario:outdoor6-objects))

;; EOF ;;