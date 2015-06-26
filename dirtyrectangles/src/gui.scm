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



(define-method (make-button (parent <scenario>) x y str func)
  (let* ((id        (scene-create))
         (sprite    (detachable-drawable-create))
         (text      (font-drawable-create (+ x 20)  (+ y 10) "font" str))
         (up        (sprite-drawable-create x  y "button"))
         (down      (sprite-drawable-create x  y "button_down"))
         (highlight (sprite-drawable-create x  y "button_h"))
         (clickable (drawable-clickable-create up)))

    (scene-add-drawable  (get-drawable parent)  id)
    (input-add-clickable (get-clickable parent) clickable)

    (detachable-drawable-set sprite up)
    (scene-add-drawable  id    sprite)
    (scene-add-drawable  id    text)

    (clickable-register-on-click clickable func)

    (clickable-register-on-press 
     clickable 
     (lambda (x y)
       (detachable-drawable-set sprite down)
       (clickable-grab-input clickable)))

    (clickable-register-on-release 
     clickable 
     (lambda (x y)
       (detachable-drawable-set sprite up)
       (clickable-release-input)))

    (clickable-register-mouse-enter 
     clickable 
     (lambda ()
       (detachable-drawable-set sprite highlight)))

    (clickable-register-mouse-leave 
     clickable 
     (lambda ()
       (detachable-drawable-set sprite up)))))

;; EOF ;;
