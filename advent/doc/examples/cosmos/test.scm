;; $Id: test.scm,v 1.1 2003/02/25 23:09:26 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; A simple test adventure game
;;

(load "adventtest.scm")
#!
(debug:set-free #f)

(c:display:setup 800 600 'fullscreen)

(define start-screen (c:layerscreen:create))
(c:screenmanager:set-screen start-screen)
(c:surface-sprite:create "images/trashcan.png")
(gc)
(gc)
(c:surface-sprite:create "images/trashcan.png") 
(c:surface-sprite:create "images/trashcan.png") 
(c:surface-sprite:create "images/trashcan.png") 
(c:surface-sprite:create "images/trashcan.png") 
(c:surface-sprite:create "images/trashcan.png") 
(c:surface-sprite:create "images/trashcan.png") 
(c:surface-sprite:create "images/trashcan.png") 
(c:surface-sprite:create "images/trashcan.png") 
(c:surface-sprite:create "images/trashcan.png") 
(c:surface-sprite:create "images/trashcan.png") 
(c:surface-sprite:create "images/trashcan.png") 
(c:surface-sprite:create "images/trashcan.png") 
(c:surface-sprite:create "images/trashcan.png")
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)
(c:sprite-drawable:create (c:surface-sprite:create "images/trashcan.png") 540 320 4.5)


(gc)
(gc)

(println "***** loading realy done ******")
(println "*******************************")
!#
;; EOF ;;