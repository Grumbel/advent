(adv:def-dialog 
 scenario1:schoener-tag

 ("Hallo, wie gehts?" 
  (dialog:add "Soweit ganz gut und dir?")
  (adv:dialog 
   ("Sehr gut."
    (adv:dialog-backto scenario1:schoener-tag))
   ("Nicht so besonders :-("
    (dialog:add "Wo jucks denn?")
    (adv:dialog
     ("Da red ich nicht drueber"
      (dialog:add "Ok, Themen wechsel.")
      (adv:dialog-backto scenario1:schoener-tag))
     ))))
 
 ("Schoener Tag heute!"
  (dialog:add "Jo, sieht heute wirklich gut aus")
  (adv:dialog-backto scenario1:schoener-tag))

 ("Komm hau mich..."
  (dialog:add "*zuschlag*")
  (adv:dialog
   ("Aua, was sollte das?"
    (dialog:add "War nur Spass"))
   ("*zuerueckschlag*"
    (dialog:add "*zu-boden-geh*"
		"Ok, du hast gewonnen"
		"Hier nimm das Gold.")
    )))
 )

(c:dialog:show (list "Hallo, wie gehts?"
		     "Schoener Tag heute!"
		     "Kommt hau mich")
	       (lambda (selection)
		 (cond ((= selection 0)
			)
		       ((= selection 1)
			)
		       )))

(adv:dialog:show scenario1:schoener-tag)


(define (adv:dialog:show dialog)
  (c:dialog:set-current dialog)
  (c:dialog:show dialog))