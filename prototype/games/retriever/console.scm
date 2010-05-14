;;;;;;;;;;;;;;;;;;;;;;;;
;; Console Fullscreen ;;
;;;;;;;;;;;;;;;;;;;;;;;;

(adv:define-object console:top    "Back")
(adv:define-object console:left   "Back")
(adv:define-object console:right  "Back")
(adv:define-object console:bottom "Back")
(adv:define-object console:console "Console")

(adv:bind-empty console:top 0 0 640 50)
(adv:bind-empty console:left   0 50 50 480)
(adv:bind-empty console:right  590 50 640 480)
(adv:bind-empty console:bottom  50 0 590 50)
(adv:bind-empty console:console  50 50 590 480)


(define-method (look (obj <console:console>))
  (dialog:add "This thing look rodden."))

(define-method (combine (obj1 <outdoor2:key>) (obj2 <console:console>))
  (combine obj1 outdoor4:console)
  (dialog:add "You unlock the door and it opens."))

(define-method (walk (obj <console:top>))
  (console:leave-console))
(define-method (walk (obj <console:bottom>))
  (console:leave-console))
(define-method (walk (obj <console:left>))
  (console:leave-console))
(define-method (walk (obj <console:right>))
  (console:leave-console))

(define (console:leave-console)
  (adv:set-scenario game-scenario:outdoor4)
  (c:guy:set-position  245 462)
  (c:guy:set-direction 1))

(adv:define-scenario-new scenario:console
			 #:surface  "console_large"
			 #:objects (list console:top
					 console:left
					 console:right
					 console:bottom
					 console:console)
			 #:with-guy #f)

;; EOF ;;
			 
