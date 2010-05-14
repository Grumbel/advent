;; All classes need to be singletone

(scene 'house
       (background "test.png")
       (colmap     "test_col.png")
       (has 
	(item 'indy 'controlable
	      (image "indy.png")
	      (item 'whip 
		   "whip.png"))
	(item 'chair
	      (image "chair.png")))
       (event ((collision 'indy 'chair)
	       (locate 'indy 'outsite))
	      ((use 'indy 'chair)
	       (locate 'indy (pos 'chair)))))

(scene 'outsite
       (background "outsite.png")
       (colmap     "outsite_col.png")
       (item 'indy)
       (event ((collision 'indy 'hole)
	       (locate 'indy 'house))
	      ))

(object <chest> (container)
	(contains 'treasure)
	(name ("Open chest"))