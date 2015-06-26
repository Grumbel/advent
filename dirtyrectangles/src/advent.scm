;;  Advent
;;  Copyright (C) 2004 Ingo Ruhnke <grumbel@gmail.com>
;;
;;  This program is free software; you can redistribute it and/or
;;  modify it under the terms of the GNU General Public License
;;  as published by the Free Software Foundation; either version 2
;;  of the License, or (at your option) any later version.
;;
;;  This program is distributed in the hope that it will be useful,
;;  but WITHOUT ANY WARRANTY; without even the implied warranty of
;;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;  GNU General Public License for more details.
;;
;;  You should have received a copy of the GNU General Public License
;;  along with this program; if not, write to the Free Software
;;  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

(use-modules (oop goops))
(load "scenario.scm")
(load "gui.scm")
(load "advobj.scm")
(load "person.scm")

(display "Advent Test Script\n")

(display-init "Advent Test" 640 480 #f)
(display-hide-system-cursor)

(define gui       (make <scenario>
                    #:clickable (clickable-scene-create)
                    #:drawable  (scene-create)))
(define view      (view-create (get-drawable gui) (get-clickable gui)))
(define overlay   (make <scenario>
                    #:clickable (clickable-scene-create)
                    #:drawable  (scene-create)))
(define playfield (create-detachable-scenario))

(add-scenario gui playfield)
(add-scenario gui overlay)

(create-drawables overlay
                  '(
                    (rect "darkness" 0 0 20 20  0 0 0 50)))

;; GUI
(let ((x 0))
  (make-button gui 0 440 "Left" 
               (lambda args
                 (set! x (+ x 50))
                 (detachable-drawable-set-offset  (get-drawable  playfield) x 0)
                 (detachable-clickable-set-offset (get-clickable playfield) x 0)))
  (make-button gui 540 440 "Right" 
               (lambda args
                 (set! x (- x 50))
                 (detachable-drawable-set-offset  (get-drawable  playfield) x 0)
                 (detachable-clickable-set-offset (get-clickable playfield) x 0)))
  ;; Methods
  (make-button gui 220 440 "Goto" 
               (lambda args
                 (set! current-method "goto")))
  (make-button gui 320 440 "Look" 
               (lambda args
                 (set! current-method "look")))
  )

(define scenario-one (create-scenario
                      '((drawables
                         (sprite "background"   0 0 "background")
                         (sprite "tree"       250 0 "tree")
                         )
                        (clickables
                         (rect "background" -4000 -4000 4000 4000)
                         (rect "gateway" 797 112 944 332)
                         (rect "door"    572 209 691 276)
                         (rect "box1"    367 199 454 284)
                         (rect "box2"     37 121 153 335)
                         (rect "lightswitch" 531 224 557 246)
                         ))))

(define scenario-two (create-scenario
                      '((drawables
                         (sprite "background" 0  0 "background2"))
                        (clickables
                         (rect "background" -4000 -4000 4000 4000)
                         (rect "door" 236 257 376 330)
                         ))))

(set-scenario playfield scenario-one)

(display "Test: ")
(display (get-clickable gui))
(display " ")
(display (get-clickable playfield))

(define current-method "goto")

(let ((scenario scenario-one))
  (create-advobj scenario
                 #:drawables  '()
                 #:clickables '("gateway")
                 #:hotspots    '((787 323))
                 #:methods     (list
                                (cons "goto" (lambda ()
                                               (say overlay "I see a gateway")))))
  (create-advobj scenario
                 #:drawables  '()
                 #:clickables '("door")
                 #:hotspots    '((629 285))
                 #:methods     (list
                                (cons "goto" (lambda ()
                                               (display "Changing scenario\n")
                                               (set-scenario playfield scenario-two)
                                               (scene-add-drawable (get-drawable scenario-two) person)
                                               (person-timeable-set-pos person-ai 295 340)
                                               ))
                                (cons "look" (lambda ()
                                               (say scenario "I see a door\n")))
                                ))

  (let ((light #f))
    (create-advobj scenario
                   #:drawables  '()
                   #:clickables '("lightswitch")
                   #:hotspots    '((540 260))
                   #:methods     (list
                                  (cons "goto" (lambda ()
                                                 (cond (light
                                                        (scene-add-drawable (get-drawable overlay)
                                                                            (get-drawable-by-name overlay "darkness"))
                                                        (say overlay "I switched off the light...")
                                                        (set! light #f))
                                                       (else
                                                        (scene-remove-drawable (get-drawable overlay)
                                                                               (get-drawable-by-name overlay "darkness"))
                                                        (say overlay "I switched on the light...")
                                                        (set! light #t))))))))

  (create-advobj scenario
                 #:drawables  '()
                 #:clickables '("box1")
                 #:hotspots    '((405 303))
                 #:methods     (list
                                (cons "goto" (lambda ()
                                               (scene-add-drawable (get-drawable scenario-one)
                                                                   (get-drawable-by-name scenario-one "tree"))
                                               (say overlay "I see a box1")))))
  (create-advobj scenario
                 #:drawables  '()
                 #:clickables '("box2")
                 #:hotspots   '((208 348))
                 #:methods     (list
                                (cons "goto" (lambda ()
                                               (scene-remove-drawable (get-drawable scenario-one)
                                                                      (get-drawable-by-name scenario-one "tree"))
                                               (say overlay "I see a box2"))))))

(create-advobj scenario-two
               #:drawables  '()
               #:clickables '("door")
               #:hotspots   '((295 340))
               #:methods     (list
                              (cons "goto" (lambda ()
                                             (set-scenario playfield scenario-one)
                                             (scene-add-drawable (get-drawable scenario-one) person)
                                             (person-timeable-set-pos person-ai 629 285)
                                             ))))

(for-each (lambda (scenario)
            (let ((rect (get-clickable-by-name scenario "background")))
              (clickable-register-mouse-enter rect (lambda () (mouse-set-normal)))
              (clickable-register-on-click 
               rect
               (lambda (x y)
                 (format #t "Pos: ~a ~a~%" x y)
                 (person-timeable-walk-to person-ai x y)
                 ))))
          (list scenario-one scenario-two))

(define depthmap  (depth-map-create "background_depth" 1.0))

(define person    (depth-drawable-create
                   (sprite-drawable-create 0 0 "person")
                   depthmap))
;;(define person    (sprite-drawable-create 0 0 "person"))

(define person-ai (person-timeable-create person 300 300))
(person-timeable-set-depthmap person-ai depthmap)

(define scroll-manager (scroll-timeable-create (get-drawable playfield) 
                                               (get-clickable playfield)
                                               person-ai))

(scene-add-drawable (get-drawable scenario-one) person)

;; Mouse Cursor
(define mouse-sprite-normal (sprite-drawable-create 0 0 "cursor"))
(define mouse-sprite-glow   (sprite-drawable-create 0 0 "cursor_glow"))
(define mouse-sprite (detachable-drawable-create))
(detachable-drawable-set mouse-sprite mouse-sprite-normal)
(mouse-timeable-create  mouse-sprite)
(scene-add-drawable (get-drawable gui) mouse-sprite)

(define (mouse-set-glow)
  (detachable-drawable-set mouse-sprite mouse-sprite-glow))

(define (mouse-set-normal)
  (detachable-drawable-set mouse-sprite mouse-sprite-normal))

(define (advent:repl)
  (display "### Advent repl, exit with (quit)\n")
  (let ((old-prompt scm-repl-prompt))
    (set-repl-prompt! "advent> ")
    (catch #t
           (lambda ()
             (top-repl)
             (display "Advent Readline exited nicly.\n"))
           (lambda args
             (display "Error: ")
             (display args)(newline)))
    (set-repl-prompt! old-prompt)))

(callback-timeable-create 50.0
                          (lambda ()
                            (display "REMOVE\n")))

;; EOF ;;
