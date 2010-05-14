
(adv:defobj park:lake
	    (name "See")
	    (bind 973 407 1142 599)
	    (hotspot 899 468 'east)
	    (methods (game:use (person:talk "What a nice lake!"))
		      ))

(adv:defobj park:tree
	    (name "Tree") 
	    (bind 48 127 232 450)
	    (hotspot 318 441 'west))


(adv:defdoor park:brunnen
	     (name "Brunnen")
	     (hotspot 920 225)
	     (target-position 460 346)
	     (target-scenario scenario:cage)
	     (bind (c:rect-collideable:create 944 64 1141 235)))

(adv:defdoor park:city
	     (name "City")
	     (hotspot 302 349)
	     (target-position 320 346)
	     (target-scenario scenario:cage)
	     (bind (c:rect-collideable:create 250 173 327 338)))	     

(let ((scale 1.7))
  (adv:defscenario scenario:park
		   (dimension 1142 600)

		   (drawables (adv:drawable:create "images/park.jpg" 0 0 0)
			      (adv:drawable:create "images/park_house.png" 415 137 (/ 0.70 scale)))
		   (advobjs park:lake
			    park:tree
			    park:brunnen
			    park:city)

		   (colmap "images/park_cmap.png" scale)))


;; EOF ;;