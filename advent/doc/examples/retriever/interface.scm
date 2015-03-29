;; If true let the game run in editor mode, else in game mode
(define *editor-mode* #f)

;; The Object that is currently in use (once it is put out of the inventory
(define *current-object* #f)

(define (editor-mode?) *editor-mode*)
(define (game-mode?) (not *editor-mode*))

(define *coin-visible #f)
(define game-screen  (c:layerscreen:create))

(define object-name (c:font-sprite:create "arialfont20" "none"))
(define object-name-layer (c:drawable-layer:create
			   (c:sprite-drawable:create
			    object-name
			    320 20 1000)))

(define editor-mode-logo (c:drawable-layer:create
			  (c:sprite-drawable:create
			   (c:font-sprite:create "arialfont20" "Editor Mode")
			   20 20 1000)))

(define scenario-layer (c:scenariolayer:create))

;; FIXME: Wannabe
;; (some-function (cons 'mouse-press '(45 102)))

;;(c:scenariolayer:set-callback
;; scenario-layer
;; (lambda (event-type data)
;; (case event-type
;;  ((mouse-button-press)
;;   (car data))
;;   ((mouse-button-release)
;;     )
;;     (else

(c:scenariolayer:set-callback
 scenario-layer
 (lambda (x y))
 (println "Event not handled: " event-type " " data)))))

(cond ((game-mode?)
       (let ((hook (person:walk-to person x y)))
	 (c:advhook:add hook (lambda ()
			       #f;;(println "On Target...")
			       ))))
      ((editor-mode?)
       (println "Press at: " (round x) " " (round y))))))

;; Mouse Cursor Setup
(define mouse-cursor (c:mousecursor:create))
(define mouse-sprite (c:surface-sprite:set-align-center
		      (c:surface-sprite:create-anim "images/cursor.png" 8)))
(define door-mouse-sprite (c:surface-sprite:set-align-center
			   (c:surface-sprite:create "images/door_cursor.png")))
(c:surface-sprite:set-fps mouse-sprite 15)
(c:mousecursor:set-sprite mouse-cursor mouse-sprite)

(c:scenariolayer:set-mouse-over-callback
 scenario-layer
 (lambda (obj)
   (cond ((not *coin-visible)
	  (if (is-a? obj <adv:door>)
	      (c:mousecursor:set-sprite mouse-cursor door-mouse-sprite)
	      (c:mousecursor:set-sprite mouse-cursor mouse-sprite))
	  ;;(println "Mouse over object: " obj)
	  (c:font-sprite:set-text object-name
				  (if obj
				      (adv:name obj)
				      "none"))))))

(define inventory-layer (c:inventory:create))

(println "Creating time manager")
(define timemanager (c:timemanager:create))
(c:layerscreen:push game-screen timemanager)


(define coin-layer (c:coinlayer:create))

(println "Creating game-scree")
(c:layerscreen:push game-screen scenario-layer)
(c:layerscreen:push game-screen object-name-layer)
(c:layerscreen:push game-screen coin-layer)
(c:layerscreen:push game-screen mouse-cursor)
(c:screenmanager:set-screen game-screen)

(define game-keymap (c:keymap:create))
(define editor-keymap (c:keymap:create))
(define keymaphandler (c:keymaphandler:create))
(c:keymaphandler:set-keymap keymaphandler game-keymap)

(define (switch-to-editor-mode)
  (println "Switching to editor mode")
  (set! *editor-mode* #t)
  (c:keymaphandler:set-keymap keymaphandler editor-keymap)
  (c:layerscreen:push game-screen editor-mode-logo))

(define (switch-to-game-mode)
  (println "Switching to game mode")
  (set! *editor-mode* #f)
  (c:keymaphandler:set-keymap keymaphandler game-keymap)
  (c:layerscreen:remove game-screen editor-mode-logo))

(c:keymap:bind-key game-keymap   KEY:F1 switch-to-editor-mode)
(c:keymap:bind-key editor-keymap KEY:F1 switch-to-game-mode)

;; Define on object click events
(define (my-on-click-handler obj)
  (person:walk-to obj))

;;  ;;(println "Doing on-click action with " obj)
;; (cond ((not *current-object*)
;;	 (set! *coin-visible #t)
;;	 (c:coinlayer:enable coin-layer obj))
;;	(else
;;	 ;; FIXME: walk-to doesn't work
;;	 (let ((obj2 *current-object*))
;;	   (adv:seq (person:walk-to obj)
;;		    (adv:combine obj obj2)))
;;	 (set! *current-object* #f)
;;	 (c:scenariolayer:mouse-update scenario-layer)
;;	 )))

(define-method (my:on-click (obj <adv:object>))
  (println "No my:on-click action set for: " obj))

(define-method (my:on-click (obj <adv:door>))
  (println "CLICK ON DOOR"))

;; This one is called once
(adv:set-on-click-handler my-on-click-handler)


;; EOF ;;