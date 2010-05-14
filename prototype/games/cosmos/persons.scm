(define person-gfx (make <person:gfx>
		     #:north "mogli_back"
		     #:south "mogli_front"
		     #:west  "person_west"
		     #:east  "person_east"))

(define roboter-gfx (make <person:gfx>
		     #:north "cosmos/roboter_north"
		     #:south "cosmos/roboter_south"
		     #:west  "cosmos/roboter_east"
		     #:east  "cosmos/roboter_west"))

;; Create two persons
(define other-chef (person:make mogli-gfx))
(set! (name other-chef) "Mogli Nr. 1")

(define chef (person:make roboter-gfx))
(set! (name chef) "Mogli Nr. 2")

;; FIXME: Subtyping would be cool
(adv:defmets <person>
	     (look (adv:seq 
		    (dialog:add (string-append "This is my twin, his name is "(name obj))
				"We look to equal, time to get some new clodes")
		    (if (eq? obj chef)
			(person:set-gfx other-chef person-gfx)
			(person:set-gfx chef       person-gfx)
		   ))))

(adv:bind-key KEY:F1 (lambda () (person:set-current chef)))
(adv:bind-key KEY:F2 (lambda () (person:set-current other-chef)))

;;(adv:set-scenario scenario:floor)
;;(c:guy:set-position 950 297)

;; EOF ;;