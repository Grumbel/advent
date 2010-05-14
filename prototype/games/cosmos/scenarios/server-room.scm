;; Chef room
;409 165 0
;461 276 0
(adv:using server:chefs-room
	   (adv:define-object "Chefs room")
	   (adv:bind-empty    409 165 50 111)
	   (adv:set-hotspot!  434 282 'north))

; floor door
;501 172 0
;561 311 0
(adv:using server:floor-door
	   (adv:define-object "Floor door")
	   (adv:bind-empty    501 172 60 140)
	   (adv:set-hotspot!  517 318 'east))

(adv:defmets <server:floor-door>
	     (walk (adv:set-scenario scenario:floor)
		   (adv:guy:set-pos 132 277 'south)))

; Terminal
;303 188 0
;349 230 0
(adv:using server:terminal
	   (adv:define-object "Terminal")
	   (adv:bind-empty    300 188 50 40)
	   (adv:set-hotspot!  326 291 'north))

(adv:defmets <server:terminal>
	     (look (dialog:add "Here you can the the server stats..."
			       "Everything looks ok.")))

; Steckerleiste
;20 213 0
;39 323 0
(adv:using server:steckerleiste
	   (adv:define-object "Steckerleiste")
	   (adv:bind-empty    20 213 20 90)
	   (adv:set-hotspot!  56 374 'west))

(adv:defmets <server:steckerleiste>
	     (look (dialog:add "...")))

; Serverschrank
;46 147 0
;249 305 0
(adv:using server:serverschrank
	   (adv:define-object "Serverschrank")
	   (adv:bind-empty 46 147 200 155)
	   (adv:set-hotspot!  193 332 'west))
(adv:defmets <server:serverschrank>
	     (look (dialog:add "This are our large servers.")))

; Leitungen
;220 339 0
;254 366 0
(adv:using server:cabels
	   (adv:define-object "Cabels")
	   (adv:bind-empty 220 340 35 25)
	   (adv:set-hotspot! 196 355 'east))

(adv:defmets <server:cabels>
	     (look (dialog:add "This cables could need some...")))

; Klimaanlage1
;114 109 0
;198 141 0
;;(adv:define-object server:  "Cabels")

; Klimaanlage2
;523 108 0
;437 137 0

(adv:define-scenario-new  scenario:server-room
			  #:surface "cosmos/server-room"
			  #:colmap  "cosmos/server-room_cmap"
			  #:objects (list server:terminal
					  server:floor-door
					  server:chefs-room
					  server:cabels
					  server:serverschrank
					  server:steckerleiste
					  ))

;; EOF ;;