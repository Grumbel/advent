(adv:defdoor gateway:door
	     (name "Door")
	     (hotspot 629 279 'north)
	     (target-position 320 376)
	     (target-scenario scenario:gateway)
	     (bind (c:rect-collideable:create 579 207 682 272)))


(adv:defobj gateway:gateway
	    (name "Gateway")
	    (hotspot  777 316 'west)
	    ;;	    (bind 402 128 562 324)

	    (methods (game:look (person:talk "A nice old-style fork."))
		     (game:use  (person:talk "I have currently no use for this."))
		     )

	    (bind ;; FIXME: The empty-advobj:create thing doesn't feel good, should be changed
	     (c:empty-advobj:create
	      gateway:gateway
	      (c:polygon-collideable:create (list 781 134
						  887 66
						  944 67
						  949 326
						  899 335
						  783 298
						  783 132)))))

(adv:defobj gateway:tree
	    (name "Tree")
	    (hotspot (298 398 east)
		     (580 382 west))
	    (methods (game:look (person:talk "An old tree")))
	    (bind
	     (c:empty-advobj:create
	      gateway:tree
	      (c:polygon-collideable:create (list 384 0
						  471 0
						  457 38
						  485 105
						  535 73
						  566 32
						  557 0
						  650 0
						  608 82
						  529 145
						  513 194
						  521 351
						  533 389
						  474 438
						  420 422
						  440 362
						  453 230
						  448 171
						  421 68)))))

(adv:defscenario scenario:gateway
		 (dimension 1024 480)

		 (drawables (adv:drawable:create "gateway/data/background.jpg" 0 0 0)
			    (adv:drawable:create "gateway/data/tree.png" 359 0 255))

		 (advobjs gateway:door
			  gateway:gateway
			  gateway:tree)

		 (colmap "gateway/data/colmap.png"))

;; EOF ;;