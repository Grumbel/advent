;; $Id: inventory.scm,v 1.6 2001/08/21 20:38:43 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Inventory manipulation methods

(define-class <inventory> ()
  (adv:bind #:accessor adv:bind))

;; Inventory handling is all done in C++, so we just change the names
;; here. FIXME: What else do we need?
(define inventory:remove c:inventory:remove)
(define inventory:show   c:inventory:show)
(define inventory:has    c:inventory:has)


(define-method (inventory:add (inventory <inventory>) (obj <advent:object>))
  (inventory:add obj))

(define-method (inventory:add (obj <advent:object>))
  ;;(inventory:add *current-person* inventory)
  (c:inventory:add obj))

(define-method (adv:set-inv-sur (obj <advent:object>) (str <string>))
  (advent:set-inventory-surface (adv:bind obj) str))

;; Low level pickup... FIXME: stupid name
(define (adv:low-pickup obj)
  (scenario:remove obj)
  (inventory:add   obj))

(define-method (inventory:add (person <person>) (obj <advent:object>))
  (inventory:add (adv:inventory person) obj))

(define-method (inventory:save-stat)
  (println ";; Trying to save inventory")
  (for-each (lambda (obj)
	      (println "(if (not (inventory:has " (adv:uid obj) ")) (inventory:add " (adv:uid obj) "))")
	      (adv:save-obj-stat obj))
 	    (c:inventory:get-objects))
  (println ";; inventory saving done"))

(define (inventory:make)
  (make <inventory>))

;; EOF ;;