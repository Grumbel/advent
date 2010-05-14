(println "Loading objects.scm...")


(define-class <takeme>   (<advent:object>))
(define-method name ((obj <takeme>)) "takeme")

(define-method use ((obj <takeme>))
  (println "Got takeme"))

;; Defining objects
(define-class <tree>   (<advent:object>))
(define-class <indy>   (<advent:object>))
(define-class <whip>   (<advent:object>))
(define-class <forest>   (<advent:object>))
(define-class <house>  (<advent:object>))
(define-class <inhouse-around>  (<advent:object>))
(define-class <window>  (<advent:object>)
  (broken #:init-value #f #:accessor broken))
(define-class <door>  (<advent:object>)
  (closed #:init-value #t #:accessor closed))

(define-class <switch> (<advent:object>)
  (state #:init-value 'off #:accessor state)
  (broken #:init-value #f #:accessor broken))

(define-class <box>   (<advent:object>)
  (state #:init-value 'closed #:accessor state))

(define-class <book>  (<advent:object>))

(define-class <chest>   (<advent:object>)
  (closed #:init-value #t #:accessor closed))


(define-method name ((obj <tree>)) "tree") 
(define-method name ((obj <forest>)) "forest") 
(define-method name ((obj <house>)) "house")
(define-method name ((obj <indy>)) "Indy")
(define-method name ((obj <whip>)) "whip")
(define-method name ((obj <box>)) "box")
(define-method name ((obj <switch>)) "switch")
(define-method name ((obj <book>)) "book")
(define-method name ((obj <window>)) "window")
(define-method name ((obj <door>)) "door")

;; Around
(define-class <around>  (<advent:object>)
  (light #:init-value #f #:accessor light))
(define-method name ((obj <around>)) "around")
(define-method name ((obj <inhouse-around>)) "around")

(define-method look ((obj <tree>))
  (dialog:add "A large mamut tree, wow!"))
  
(define-method look ((obj <window>))
  (if (broken obj)
      (dialog:add "You see a broken window, looks like you broke it.")
      (dialog:add "A beatifull large window")))

(define-method look ((obj <inhouse-around>))
  (println "You see: ")
  (for-each (lambda (x) (println (name x))) *current-scenario*))

(define-method look ((obj <around>))
  (cond ((light obj)
	 (println "You see: ")
	   (for-each (lambda (x) (println (name x))) *current-scenario*))
	(else
	 (println "You can't see anything, its dark."))))
  
(define-method use ((obj <boolean>))
  (println "Unknown object"))

(define-method look ((obj <book>))
  (println "You read a book full of wisdom."))

(define-method gclose ((obj <book>))
  (println "You close the book."))

(define-method use ((obj1 <boolean>) (obj2 <boolean>))
  (println "You don't have the thing you want to use."))

(define-method use ((obj1 <boolean>) (obj2 <advent:object>))
  (println "You don't have the thing you want to use."))

(define-method use ((obj1 <whip>) (obj2 <boolean>))
  (println "Don't now how to use this unknown thing with a whip"))

(define-method use ((obj1 <whip>) (obj2 <box>))
  (cond ((equal? (state obj2) 'closed)
	 (set! (state obj2) 'opened)
	 (println "You slap the box and it openes."))
	(else
	 (println "You don't need to slap the box, its already opened."))))

(define-method use ((obj1 <whip>) (obj2 <switch>))
  (println "You slap your whip onto the switch... and it breaks...")
  (set! (broken obj2) #t))

(define-method use ((obj1 <whip>) (obj2 <window>))
  (println "You slap your whip onto the window and it cracks! Woops...")
  (set! (broken obj2) #t))

(define-method use ((obj <switch>))
  (if (broken obj)
      (println "The switch is broken, you can not use it.")
      (cond ((equal? (state obj) 'off)
	     (println "You press the switch and the light goes on.")
	     (set! (state obj) 'on)
	     (set! (light (get-obj "around")) #t))
	    (else
	     (println "You press the switch again and the light goes off.")
	     (set! (state obj) 'off)	     
	     (set! (light (get-obj "around")) #f)
	     ))))

(define-method look ((obj <switch>))
  (if (broken obj)
      (println "Looks like the switch is broken and unusable")
      (cond ((equal? (state obj) 'off)
	     (println "The switch is on state `off'"))
	    (else 
	     (println "The switch is on state `on'")))))

(define-method use ((obj <advent:object>))
  (println "Don't know what I should do with " (name obj)))

(define-method use ((obj1 <advent:object>) (obj2 <advent:object>))
  (println "Don't know how to combine " (name obj1) " and " (name obj2) "."))

(define-method look ((obj <boolean>))
  (println "Don't know what you mean"))

(define-method look ((obj <advent:object>))
  (println "You see a " (name obj) ", nothing special."))

(define-method look ((house <house>))
  (println "You see a cool house."))

(define-method look ((whip <whip>))
  (println "This is indys cool whip"))

(define-method look ((box <box>))
  (cond ((equal? 'closed (state box))
	 (println "The box is closed."))
	(else
	 (println "The box is open."))
	 ))

(define-method gopen ((box <box>))
  (if ((equal? (state box) 'closed))
      (println "You can't openen the box, its looked.")
      (println "Its already opened.")))

(define-method pickup ((obj <boolean>))
  (println "Don't know what you mean"))

(define-method pickup ((obj <advent:object>))
  (println "Don't know how to pickup this " (name obj)))

(define-method pickup ((box <box>))
  (println "This box is to heavy to carry it around."))

(define-method pickup ((book <book>))
  (scenario:remove-obj book)
  (add-inventory book))

(define-method pickup ((whip <whip>))
  (scenario:remove-obj whip)
  (add-inventory whip))

(define-method walk ((forest <forest>))
  (println "You walk int the forest.")
  (scenario:set *forest*)
  )

(define-method walk ((house <house>))
  (println "You walk into the house.")
  (scenario:set *in-house*))

(define-method use ((obj <door>))
  (cond ((not (closed obj))
	 (scenario:set-current game-scenario:outdoor-bind)
	 (set! *current-scenario* game-scenario:outdoor-objects))
	(else
	 (println "Door is closed."))))

(define-method gopen ((obj <door>))
  (cond ((closed obj)
	 (advent:set-surface (adv:bind obj) "door_opened")
	 (set! (closed obj) #f))
	(else
	 (advent:set-surface (adv:bind obj) "door_closed")
	 (set! (closed obj) #t))))

;;(define-method walk ((obj <door>))
;;  (println "You walk out of the door, you are outsite again.")
;;  (scenario:set *before-house*))
    
(define-class <gateway:gateway> (<advent:object>))
(define-method name ((obj <gateway:gateway>)) "Gateway")
(define-method use ((obj <gateway:gateway>))
  (scenario:set-current game-scenario:outdoor3-bind)
  (set! *current-scenario* game-scenario:outdoor3-objects))

(define-method use ((obj <whip>))
  (println "You use your whip and slap yourself, stupid!"))

(define (adv:load file)
  (println "Loading file: " file)
  (load file))

(adv:load "scenario1.scm")
(adv:load "scenario2.scm")
(adv:load "scenario3.scm")
(adv:load "scenario4.scm")
(adv:load "scenario5.scm")

;;;;;;;;;
;; END ;;
;;;;;;;;;


(define game-scenario:gateway
  (make <scenario> 
    #:adv:bind game-scenario:gateway-bind
    #:adv:objs game-scenario:gateway-objects
    ))

(println "Scenario: " game-scenario:gateway)
(scenario:set-current game-scenario:gateway-bind)
(set! *current-scenario* game-scenario:gateway-objects)

;; EOF ;;
