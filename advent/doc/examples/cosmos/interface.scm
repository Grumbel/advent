;; $Id: interface.scm,v 1.7 2003/02/24 23:35:55 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; The interface of the adventure game
;;

(println "XXXXXX############## c:delayed-advhook:create: " c:delayed-advhook:create)

;; Create the screens
(define start-screen (c:layerscreen:create))
(define game-screen  (c:layerscreen:create))

(define *coin-visible #f)

(define object-name (c:font-sprite:create "arialfont14" ""))
(define object-name-layer (c:drawable-layer:create
			   (c:sprite-drawable:create
			    object-name
			    320 20 1000)))

(define scenario-layer (c:scenariolayer:create))
(c:scenariolayer:set-callback scenario-layer
			      (lambda (x y)
				(println "Got click at: " x " " y)
				(let ((hook (person:walk-to person x y)))
				  (c:advhook:add hook (lambda ()
							#f;;(println "On Target...")
							)))))
(define mouse-cursor (c:mousecursor:create))
(define mouse-sprite (c:surface-sprite:set-align-center 
		      (c:surface-sprite:create-anim "images/cursor.png" 8)))
(define glow-mouse-sprite (c:surface-sprite:set-align-center 
			   (c:surface-sprite:create-anim "images/cursor_glow.png" 8)))
(define door-mouse-sprite (c:surface-sprite:set-align-center 
			   (c:surface-sprite:create "images/door_cursor.png")))
(define inactive-mouse-sprite (c:surface-sprite:set-align-center 
			       (c:surface-sprite:create "images/cursor_inactive.png")))
(c:surface-sprite:set-fps mouse-sprite 10)
(c:surface-sprite:set-fps glow-mouse-sprite 15)
(c:mousecursor:set-sprite mouse-cursor mouse-sprite)
(c:layerscreen:push start-screen mouse-cursor)

(define *input-enabled* #t) 

(c:layerscreen:set-input-enabled-hook  
 game-screen
 (lambda ()
   (c:mousecursor:set-sprite mouse-cursor mouse-sprite)
   (set! *input-enabled* #t)
   (println "Input enabled")))

(c:layerscreen:set-input-disabled-hook 
 game-screen
 (lambda ()
   (c:mousecursor:set-sprite mouse-cursor inactive-mouse-sprite)
   (set! *input-enabled* #f)
   (println "Input enabled")))

(c:scenariolayer:set-mouse-over-callback
 scenario-layer
 (lambda (obj)
   (if *input-enabled*
       (cond ((and (not *coin-visible)
		   (not *current-object*))
	      (cond ((is-a? obj <adv:door>)
		     (c:mousecursor:set-sprite mouse-cursor door-mouse-sprite))
		    ((is-a? obj <adv:object>)
		     (c:mousecursor:set-sprite mouse-cursor glow-mouse-sprite))
		    (else
		     (c:mousecursor:set-sprite mouse-cursor mouse-sprite)))
	      ;;(println "Mouse over object: " obj)
	      (c:font-sprite:set-text object-name 
				      (if obj
					  (adv:name obj)
					  "")))))))

(define inventory-layer (c:inventory:create))

;; Create start screen interface
(define start-button
  (c:buttonlayer:create (c:surface-sprite:create "images/start.png") #f #f 150 400))
(define exit-button  
  (c:buttonlayer:create (c:surface-sprite:create "images/exit.png") #f #f 390 400))
(c:buttonlayer:set-press-callback start-button (lambda () 
						 (println "Start pressed")
						 (c:screenmanager:set-screen game-screen)))
(c:buttonlayer:set-press-callback exit-button (lambda () 
						(println "Exit pressed")
						(exit)))

(define button2
  (c:buttonlayer:create (c:surface-sprite:create "images/button.png") #f #f 10 400))
(c:buttonlayer:set-press-callback button2 (lambda () 
					    (c:screenmanager:set-screen start-screen)))


(define gc-button  (c:buttonlayer:create 
		    (c:surface-sprite:create "images/gc.png") #f 
		    (adv:surface-sprite:create "images/gc_over.png")
		    608 0))
(c:buttonlayer:set-press-callback
 gc-button 
 (lambda () 
   (println "  ********* Garbage Collecting...")
   (gc)
   (println "  ********* Garbage Collecting...done")))


(c:layerscreen:push start-screen
		    (c:drawable-layer:create (sprite-drawable:create "images/logo.jpg" 0 0 0)))
(c:layerscreen:push start-screen start-button)
(c:layerscreen:push start-screen exit-button)

(println "Creating time manager")
(define timemanager (c:timemanager:create))
(c:layerscreen:push game-screen timemanager)


(define coin-layer (c:coinlayer:create))

(println "Creating game-scree")
(c:layerscreen:push game-screen scenario-layer)
(c:layerscreen:push game-screen button2)
(c:layerscreen:push game-screen gc-button)
(c:layerscreen:push game-screen object-name-layer)
(c:layerscreen:push game-screen coin-layer)
(c:layerscreen:push game-screen mouse-cursor)

(define fadeout-layer (c:fadeout-layer:create))
(c:layerscreen:push game-screen fadeout-layer)
(c:fadeout-layer:blackout fadeout-layer)
(adv:seq (adv:sleep 2000)
	 (c:fadeout-layer:fade-in fadeout-layer))

(c:screenmanager:set-screen game-screen)



;; EOF ;;