;; $Id: inventory.scm,v 1.5 2003/02/24 22:41:55 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Inventory handling functions
;;

;;(use-modules (advent object))

(export <adv:inventory> adv:write inventory:remove)

(define-class <adv:inventory> ()
  (objects #:init-value '() #:accessor adv:objects))

(define-method (adv:write (inventory <adv:inventory>) port)
  (for-each (lambda (obj)
	      (format port "<~S> " obj))
	    (adv:objects inventory)))

;(define-method (inventory:add (inventory <adv:inventory>) (obj <adv:object>))
;  (set! (adv:objects inventory) (cons obj (adv:objects inventory))))
  
(define-method (inventory:remove (inventory <adv:inventory>) (obj <adv:object>))
  #f)

;; EOF ;;