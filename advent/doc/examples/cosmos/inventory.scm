(define inventory-icons '())

(define-method (inventory-update (person <adv:person>))
  (for-each (lambda (obj)
	      (c:layerscreen:remove game-screen obj))
	    inventory-icons)

  (println "Updating inventory: inventory-update")
  (let ((x 48))
    (for-each (lambda (obj)
		(cond ((not (adv:inventory-sprite obj))
		       (println "No inventory sprite set for " obj)
		       (exit)))
		(let ((button (c:buttonlayer:create
			       (sprite-group:create
				(center-sprite:create
				 (c:rect-sprite:create 52 52 '(0.5 0.5 0.5)))
				(adv:inventory-sprite obj))
			       #f
			       (sprite-group:create
				(center-sprite:create
				 (c:rect-sprite:create 52 52 '(1.0 1.0 1.0)))
				(adv:inventory-sprite obj))
			       x 32)))
		  (c:buttonlayer:set-press-callback
		   button (lambda ()
			    (println "Inventory Button clicked")
			    (set! *current-object* obj)
			    (c:mousecursor:set-sprite mouse-cursor (adv:inventory-sprite obj))
			    ))
		  (c:layerscreen:push game-screen button)
		  (set! inventory-icons (cons button inventory-icons)))
		(set! x (+ x 64)))
	      (adv:inventory person))))

;; EOF ;;