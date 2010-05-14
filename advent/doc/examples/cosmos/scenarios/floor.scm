
; 579 184 0
;Press at: 618 214 0
; 649 145 0
;Press at: 781 381 0


;Schild:
;Press at: 1077 184 0
;Press at: 1118 215 0
;Tuer
;;; 

(adv:defdoor floor:cellar-door
	     (name "Cellar")
	     (hotspot 1716 402 'north)
	     (target-position 469 346 'east)
	     (target-scenario scenario:cage)
	     (bind (c:rect-collideable:create 1648 152 1775 369)))

(adv:defdoor floor:workspace-door
	     (name "Workspace door")
	     (hotspot 1225 398 'east)
	     (target-position 141 311)
	     (target-scenario scenario:workplace)
	     (bind (c:rect-collideable:create 1146 142 1285 382)))


(adv:defdoor floor:serverroom-door
	     (name "Tuer zum Serverroom")
	     (hotspot 246 403 'north)
	     (target-position 514 319)
	     (target-scenario scenario:serverroom)
	     (bind (c:rect-collideable:create 174 147 305 381 )))


;1079 184 0
;Press at: 1120 216

(adv:defobj floor:serverroom-sign
	    (name    "Sign")
	    (hotspot 119 402 'north)
	    (bind    (c:empty-advobj:create floor:serverroom-sign
					    (c:rect-collideable:create 102 184 141 214)))
	    (methods (game:look   (person:talk "This is the server room."))
		     (game:pickup (person:talk "I better leave it here."))
		     (game:speak  (person:talk "Nothing to talk to."))
		     (game:use    (person:talk "I can't use this thing."))
		     ))
 
(adv:defscenario scenario:floor
		 (dimension 2079 480)

		 (drawables (adv:drawable:create "images/floor.jpg" 0 0 0))

		 (advobjs floor:serverroom-sign
			  floor:serverroom-door
			  floor:workspace-door
			  floor:cellar-door)

		 (colmap "images/floor_cmap.png"))

;; EOF ;;
