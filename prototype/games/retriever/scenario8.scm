(adv:define-object scenario8:cave "Cave")
(adv:bind-empty scenario8:cave 300 170 390 120)
(define-method (walk (obj <scenario8:cave>))
  (c:guy:set-target 341 288 
		    (lambda ()
		      (adv:set-scenario game:scenario9)
		      (c:guy:set-position  204 332)
		      (c:guy:set-direction 2))))

(adv:define-object scenario8:exit "Exit")
(adv:bind-empty scenario8:exit 0 160 70 200)
(define-method (walk (obj <scenario8:exit>))
  (c:guy:set-target 14 305
		    (lambda ()
		      (adv:set-scenario game-scenario:outdoor7)
		      (c:guy:set-position  420 200)
		      (c:guy:set-direction 2))))

(define game-scenario:outdoor8-objects 
  (list scenario8:cave
	scenario8:exit))
(define game-scenario:outdoor8-bind
  (c:scenario:make-bind "game-scenario:outdoor8"
		      "background8" "background8_cmap"
		      (map (lambda (x) (adv:bind x))
			   game-scenario:outdoor8-objects) #t))
(define game-scenario:outdoor8
  (make <scenario> 
    #:adv:bind game-scenario:outdoor8-bind
    #:adv:objs game-scenario:outdoor8-objects))

;; EOF ;;