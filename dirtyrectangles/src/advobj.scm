;;  Advent
;;  Copyright (C) 2004 Ingo Ruhnke <grumbel@gmx.de>
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

(define (get-keyword-value args keyword default)
  (let ((kv (memq keyword args)))
    (if (and kv (>= (length kv) 2))
        (cadr kv)
        default)))

(define-class <advobj> ()
  ;; Clickables bound to this object
  (clickables #:init-value '()
              #:accessor get-clickables
              #:init-keyword #:clickables)
  ;; Drawables bound to this object
  (drawables  #:init-value '()
              #:accessor get-drawables
              #:init-keyword #:drawables)
  ;; Methods bound to this object
  (methods    #:init-value '()
              #:accessor get-methods
              #:init-keyword #:methods)
  ;; Hotspots bound to this object
  (hotspots   #:init-value '()
              #:accessor get-hotspots
              #:init-keyword #:hotspots))

(define-method (create-advobj (scenario <scenario>) . args)
  (let* ((drawable-names  (get-keyword-value args #:drawables '()))
         (clickable-names (get-keyword-value args #:clickables '()))
         (methods    (get-keyword-value args #:methods '()))
         (hotspots   (get-keyword-value args #:hotspots '()))
         (drawables  (map (lambda (name) (get-drawable-by-name scenario name))
                          drawable-names))
         (clickables (map (lambda (name) (get-clickable-by-name scenario name))
                          clickable-names))
         
         (advobj (make <advobj> 
                   #:drawables  drawables
                   #:clickables clickables
                   #:methods  methods
                   #:hotspots hotspots)))

    (for-each (lambda (clickable)
                (clickable-register-mouse-enter clickable
                                                (lambda () (mouse-set-glow)))
                (clickable-register-on-press    clickable  
                                                (lambda (x y)
                                                  (advobj-click-handler advobj clickable x y)))
                ;;                (clickable-register-on-release  clickable  
                ;;                                               (lambda (x y)
                ;;                                                  (advobj-click-handler advobj clickable x y)))
                )
              clickables)
    advobj))

(define (advobj-click-handler advobj clickable x y)
  ;;(format #t "AdvObj: ~a [~a, ~a]~%" clickable x y)
  (let ((hotspots (get-hotspots advobj)))
    (cond ((pair? hotspots)
           (person-timeable-walk-to person-ai
                                    (caar hotspots) (cadar hotspots)))
          (else
           (person-timeable-walk-to person-ai x y))))
  
   (let ((func (assoc-ref (get-methods advobj) current-method)))
     (cond (func
            (person-timeable-set-target-callback person-ai
                                                 (lambda ()
                                                   (format #t "Reached: ~a~%" advobj)
                                                   (func)
                                                   )))))
  )

;; EOF ;;
