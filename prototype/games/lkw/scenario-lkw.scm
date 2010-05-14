;; Scenario LKW

;; Coins
(define-class <scenario:lkw:coin> (<advent:object>)
  (name #:init-value "Coin" #:accessor name)
  (number-of #:init-value 1
	     #:accessor number-of))

(define scenario:lkw:coin-group (make <scenario:lkw:coin> #:number-of 0))
(define scenario:lkw:coin1 (make <scenario:lkw:coin>))
(define scenario:lkw:coin2 (make <scenario:lkw:coin>))
(define scenario:lkw:coin3 (make <scenario:lkw:coin>))
(define scenario:lkw:coin4 (make <scenario:lkw:coin>))

;(set! (name scenario:lkw:coin-group) "Coins")

(adv:bind-surface scenario:lkw:coin-group "lkwcoin" 385 443 253)
(adv:bind-surface scenario:lkw:coin1 "lkwcoin" 385 443 253)
(adv:bind-surface scenario:lkw:coin2 "lkwcoin" 434 387 237)
(adv:bind-surface scenario:lkw:coin3 "lkwcoin" 492 435 245)
(adv:bind-surface scenario:lkw:coin4 "lkwcoin" 595 373 225)

(adv:set-hotspot! scenario:lkw:coin1  385 443 0)
(adv:set-hotspot! scenario:lkw:coin2  434 387 0)
(adv:set-hotspot! scenario:lkw:coin3  492 435 0)
(adv:set-hotspot! scenario:lkw:coin4  595 373 0)

(define-method (combine (coin <scenario:lkw:coin>) (obj <advent:object>))
  (dialog:add (string-append "Don't know of to use " (name coin) " with " (name obj))))

(define-method (pickup (coin <scenario:lkw:coin>))
  (scenario:remove coin)
  (cond ((inventory:has scenario:lkw:coin-group)
	 (set! (number-of scenario:lkw:coin-group) 
	       (+ (number-of scenario:lkw:coin-group) (number-of coin))))
	(else
	 (inventory:add scenario:lkw:coin-group)
	 (set! (number-of scenario:lkw:coin-group) (number-of coin))))

  (case (number-of scenario:lkw:coin-group)
    ((1)
     (advent:set-inventory-surface (adv:bind scenario:lkw:coin-group) "invcoin1"))
    ((2)  (advent:set-inventory-surface (adv:bind scenario:lkw:coin-group) "invcoin2"))
    (else (advent:set-inventory-surface (adv:bind scenario:lkw:coin-group) "invcoinm")))

  (if (equal? (number-of scenario:lkw:coin-group) 1)
      (set! (name scenario:lkw:coin-group) "a coin")
      (set! (name scenario:lkw:coin-group) 
	    (string-append (number->string (number-of scenario:lkw:coin-group)) " coins")))
      )

;; Cockpit ;;
(adv:define-object scenario:lkw:cockpit "Cockpit")
(adv:bind-empty  scenario:lkw:cockpit 420 164  45 160)
(adv:set-hotspot!  scenario:lkw:cockpit  449 352 0)

(define (lkw:cockpit:smashwindow)
  (dialog:add "SMASSSSSHHHH"
	      "The window is now open..."
	      "Cockpit: Ok, I come out now..."))

(adv:define-dialog 
 lkw:cockpit:dialog:help:window:really
 (list "<smash the window>" lkw:cockpit:smashwindow)
 (list "No way, I go bye." #f))

(adv:define-dialog 
 lkw:cockpit:dialog:help:window
 (list "<smash the window>" lkw:cockpit:smashwindow)
 (list "Sorry, I can't do this." (lambda ()
				   (dialog:add "Cockpit: Hey! Come on I need you help")
				   (dialog:show lkw:cockpit:dialog:help:window:really))))

(define (lkw:cockpit:fluid)
  (dialog:add "Cockpit: The fluid is... *arg*... FIIIRRREEE"))

(adv:define-dialog 
 lkw:cockpit:dialog:help:question:2
 (list "What is that fluid you transported?" lkw:cockpit:fluid)
 (list "Who are you working for?" (lambda ()
				    (dialog:add "Cockpit: General Gene...")
				    (dialog:show lkw:cockpit:dialog:help:question:2)
				    )))

(adv:define-dialog 
 lkw:cockpit:dialog:help:question
 (list "Hey, you are the one that is traped! Answer or die in your truck" lkw:cockpit:dialog:help:question:2)
 (list "Come on, what is that for a green fluid you transported?" lkw:cockpit:fluid)
 (list "Its your life you are wasting, bye!" #f))

(adv:define-dialog 
 lkw:cockpit:dialog:help
 (list "How can I help you?" (lambda ()
			       (dialog:add "Cockpit: Try to smash the window!")
			       (dialog:show lkw:cockpit:dialog:help:window)))
 (list "Before I can help you, you first have to answer me some questions!"
       (lambda ()
	 (dialog:add "Cockpit: No way!")
	 (dialog:show lkw:cockpit:dialog:help:question)))
 (list "Sorry, no time for helping you..." #f))



(adv:define-dialog 
 lkw:cockpit:dialog 
 (list "Hello, anybody there?" (lambda ()
				 (dialog:add "Cockpit: Yes, I am traped under the seat.")
				 (dialog:show lkw:cockpit:dialog:help)))
 (list "Where are you" 'lkw:cockpit:where-are-you)
 (list "<Leave>"   #f))

(adv:define-dialog 
 lkw:cockpit:where-are-you
 (list "back to topic" 'lkw:cockpit:dialog)
 (list "Come on tell me" #f))

(adv:defmets <scenario:lkw:cockpit>
	     (look (dialog:add "There is a radio set inside the cockpit."
			       "Looks like it is switched on."))
	     (speak (dialog:show lkw:cockpit:dialog)))

;; Fluid ;;
(adv:define-object scenario:lkw:fluid "Dangerous Fluid")
(adv:bind-empty    scenario:lkw:fluid 60 323  290 90)
(adv:set-hotspot!  scenario:lkw:fluid 399 387 3)


;; Lamp1
(adv:define-object scenario:lkw:lamp1 "Lamp")
(adv:bind-empty    scenario:lkw:lamp1 480 185 15 15)
(adv:set-hotspot!  scenario:lkw:lamp1 495 357 0)

(adv:defmet (pickup (obj <scenario:lkw:lamp1>))
	    (dialog:add "I can reach the lamp."))

;; Lamp2
;;(adv:define-object scenario:lkw:lamp2 "Lamp")
;;(adv:bind-empty    scenario:lkw:lamp2 480 300 15 15)
;;(adv:set-hotspot!  scenario:lkw:lamp2 495 357 0)

(adv:using scenario:lkw:lamp2
	   (adv:define-object "Lamp")
	   (adv:bind-empty    480 300 15 15)
	   (adv:set-hotspot!  495 357 0))

(adv:defmets <scenario:lkw:lamp2>
	     (look   (dialog:add "The lamp is lose."))
	     (use    (dialog:add "Its lose, probally I should pick it up."))
	     (pickup (dialog:add "I got a lamp.")))

;; Define the scenario
(adv:define-scenario-new  scenario:lkw
			  #:surface "lkw"
			  #:colmap  "lkw_cmap"
			  #:objects (list scenario:lkw:cockpit
					  scenario:lkw:fluid
					  scenario:lkw:lamp1
					  scenario:lkw:lamp2
					  scenario:lkw:coin1
					  scenario:lkw:coin2
					  scenario:lkw:coin3
					  scenario:lkw:coin4
;;					  scenario:lkw:coin-group
					  ))

#! wannabe syntax
(adv:define-object 
 scenario:lkw:cockpit 
		   
 (name         "Cockpit")
 (bind-empty   420 164 45 160)
 (set-hotspot! 449 352 'north)

 (members (bla 0)
	  (blub 56))
 
 (actions (look (dialog:add "bla blub..."))
	  (use  (dialog:add "Not so usefull..."))
  ))
!#


;; EOF ;;