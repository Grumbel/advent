;; $Id: inventory.scm,v 1.1 2001/07/02 10:27:13 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Inventory manipulation methods

;; Inventory handling is all done in C++, so we just change the names
;; here. FIXME: What else do we need?
(define inventory:add    c:inventory:add)
(define inventory:remove c:inventory:remove)
(define inventory:show   c:inventory:show)
(define inventory:has    c:inventory:has)


#!
;; FIXME: Document me!
(define (get-obj nme)
  (or (get-obj-helper nme *current-scenario*)
      (get-obj-helper nme *inventory*)))

;; FIXME: Document me!
(define (get-obj-helper nme objs)
  (cond ((null? objs)
	 #f)
	(else
	 (let ((obj-name (name (car objs))))
	   (cond ((string=? nme obj-name)
		  (car objs))
		 (else
		  (get-obj-helper nme (cdr objs))))))))
!#

;; EOF ;;