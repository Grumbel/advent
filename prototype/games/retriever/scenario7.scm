;;Button pressed: 0 94 0
;;Button pressed: 23 271 0

(adv:define-object scenario7:way "way")
(adv:bind-empty scenario7:way 0 94 24 121)

(define-method (walk (obj <scenario7:way>))
  (c:guy:set-target 5 234 (lambda ()
			    (adv:set-scenario game-scenario:scenario10)
			    (c:guy:set-position 595 465)
			    (c:guy:set-direction 3))))

;;;;;;;;;;;;;;
(adv:define-object scenario7:tunnel "Tunnel")
(adv:bind-empty scenario7:tunnel 26 97 100 121)

(define-method (walk (obj <scenario7:tunnel>))
  (c:guy:set-target 78 224 (lambda ()
			     (adv:set-scenario game-scenario:outdoor6) 
			     (c:guy:set-position   492 335)
			     (c:guy:set-direction 3))))

(adv:define-object scenario7:path "Path")
(adv:bind-empty scenario7:path 336 61 130 160)
(define-method (walk (obj <scenario7:path>))
  (c:guy:set-target   403 195 (lambda ()
				(adv:set-scenario game-scenario:outdoor8)
				(c:guy:set-position   25 306)
				(c:guy:set-direction 1))))

(define game-scenario:outdoor7-objects 
  (list scenario7:tunnel
	scenario7:path))

(define game-scenario:outdoor7-bind
  (c:scenario:make-bind "game-scenario:outdoor7"
		      "background7" "background7_cmap"
		      (map (lambda (x) (adv:bind x))
			   game-scenario:outdoor7-objects) #t))

(define game-scenario:outdoor7
  (make <scenario> 
    #:adv:bind game-scenario:outdoor7-bind
    #:adv:objs game-scenario:outdoor7-objects))

;; EOF ;;