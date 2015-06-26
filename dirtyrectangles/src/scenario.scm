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

(define-class <scenario> ()
  (clickable #:init-thunk clickable-scene-create
             #:accessor get-clickable
             #:init-keyword #:clickable)

  (clickable-lookup #:init-form '()
                    #:accessor get-clickable-lookup)

  (drawable  #:init-thunk scene-create
             #:accessor get-drawable
             #:init-keyword #:drawable)

  (drawable-lookup #:init-form '()
                   #:accessor get-drawable-lookup))

(define (create-detachable-scenario)
  (make <scenario>
    #:drawable  (detachable-drawable-create)
    #:clickable (detachable-clickable-create)))

(define-method (create-scenario lst)
  (let* ((scenario (make <scenario>
                     #:drawable  (scene-create)
                     #:clickable (clickable-scene-create))))
    (let loop ((lst lst))
      (cond ((pair? lst)
             (case (caar lst)
               ((drawables)  (create-drawables  scenario (cdar lst)))
               ((clickables) (create-clickables scenario (cdar lst)))
               (else (error "Unknown keyword")))
             (loop (cdr lst)))))
    scenario))

(define-method (get-clickable-by-name (scenario <scenario>) name)
  (assoc-ref (get-clickable-lookup scenario) name))

(define-method (get-drawable-by-name (scenario <scenario>) name)
  (assoc-ref (get-drawable-lookup scenario) name))

(define-method (add-scenario (box <scenario>) (scenario <scenario>))
  (scene-add-drawable  (get-drawable  box) (get-drawable  scenario))
  (input-add-clickable (get-clickable box) (get-clickable scenario)))

(define-method (set-scenario (box <scenario>) (scenario <scenario>))
  (detachable-drawable-set  (get-drawable  box) (get-drawable scenario))
  (detachable-clickable-set (get-clickable box) (get-clickable scenario)))

(define-method (create-clickables (group <scenario>) clickables)
  (cond ((pair? clickables)
         (let* ((data (car clickables))
                (type (car data))
                (name (cadr data))
                (rest (cddr data))
                (clickable  (case type
                              ((rect) 
                               (display "rect: ")(display data)(newline)
                               (rect-clickable-create (car   rest)
                                                      (cadr  rest)
                                                      (caddr rest)
                                                      (cadddr rest))))))
           (set! (get-clickable-lookup group)
                 (cons (cons name
                             clickable)
                       (get-clickable-lookup group)))
           (input-add-clickable (get-clickable group) clickable)
           (create-clickables group (cdr clickables))))))

(define-method (create-drawables (group <scenario>) drawables)
  (cond ((pair? drawables)
         (let* ((data (car drawables))
                (type (car data))
                (name (cadr data))
                (rest (cddr data))
                (drawable (case type
                            ((sprite)                             
                             (sprite-drawable-create (car   rest)
                                                     (cadr  rest)
                                                     (caddr rest)))
                            ((rect)
                             (rect-drawable-create (list-ref rest 0)
                                                   (list-ref rest 1)
                                                   (list-ref rest 2)
                                                   (list-ref rest 3)

                                                   (list-ref rest 4)
                                                   (list-ref rest 5)
                                                   (list-ref rest 6)
                                                   (list-ref rest 7)))
                            )))
           (set! (get-drawable-lookup group)
                 (cons (cons name
                             drawable)
                       (get-drawable-lookup group)))

           (scene-add-drawable (get-drawable group) drawable)
           (create-drawables group (cdr drawables))))))

;; EOF ;;
