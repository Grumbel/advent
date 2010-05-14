(println "Loading objects.scm...")

;; Currently not implemented
(define-method (use (obj1 <advent:object>) (obj2 <advent:object>))
  (println "Don't know how to combine " (name obj1) " and " (name obj2) "."))

(define-method (use (obj <advent:object>))
  (println "Don't know what I should do with " (name obj)))

(define-method (look (obj <advent:object>))
  (dialog:add (string-append "You see a " (name obj) ", nothing special.")))

(define-method (speak (obj <advent:object>))
  (dialog:add "Nobody to speak to."))

(define-method (pickup (obj <advent:object>))
  (dialog:add "Don't know how to pick that up."))

(define-method (walk (obj <advent:object>))
  (println "WALK NOT IMPLEMENTED")
  #f)

;;(gc-set-debug-check-freelist! #t)


(adv:register-scenarios (game-scenario:gateway "scenario1.scm")
			(game-scenario:outdoor "scenario2.scm")
			(game-scenario:outdoor2 "scenario3.scm")
			(game-scenario:outdoor3 "scenario4.scm")
			(game-scenario:outdoor4 "scenario5.scm")
			(game-scenario:outdoor6 "scenario6.scm")
			(game-scenario:outdoor7 "scenario7.scm")
			(game-scenario:outdoor8 "scenario8.scm")
			(game:scenario9          "scenario9.scm")
			(game-scenario:scenario10 "scenario10.scm")
			(game-scenario:scenario11 "scenario11.scm")
			(game-scenario:scenario12 "scenario12.scm")
			(scenario:console "console.scm"))


;;(println "Scenario: " game-scenario:gateway)

;; Ship - on the mountain
;;(adv:set-scenario game-scenario:scenario10)
;;(c:guy:set-position 595 465)
;;(c:guy:set-position 50 470)

;; Ship - down
;;(adv:set-scenario game-scenario:scenario11)
;;(c:guy:set-position 150 550)

;; Elevator
;;(adv:set-scenario game-scenario:scenario12)
;;(c:guy:set-position 310 330)

;; Create the person to control
(define my-person (person:make mogli-gfx))

;; Gateway
(adv:set-scenario game-scenario:gateway)
(c:guy:set-position 310 330)

;;(adv:set-scenario game-scenario:outdoor8)
;;(adv:set-scenario game-scenario:outdoor7)

;; EOF ;;
