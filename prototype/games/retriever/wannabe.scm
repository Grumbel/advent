(define *adv:current_character* #f)

(define-class <inventory> ()
  (smob #:accessor smob
	#:init-value #f)
  (objects #:accessor objects
	   #:init-value '()))

(define-class <character> ()
  (smob #:accessor smob
	#:init-value #f)
  (inventory #:accessor inventory 
	     #:init-value #f))

(define-class <some-character> (<character>)
  (inventory #:init-value (make <inventory>)))

(define-method adv:set-current-character! (character <character>)
  (set! *adv:current_character* character))

(define-method (adv:add-to-inventory (object <adv:object>))
  (adv:assert *adv:current_character*)
  (adv:add-to-inventory *adv:current_character* object))

(define-method (adv:add-to-inventory (character <character>)
				     (object    <adv:object>))
  (set! (adv:inventory character) (cons object (adv:inventory character))))

;; Refcounted
(define *adv:disable-interactions* 0)

(define (adv:disable-interactions)
  (if (equal? *adv:disable-interactions* 0)
      (c:disable-mouse))
  (set! *adv:disable-interactions* (1+ *adv:disable-interactions*)))

define-obj:
  look:
     if () {
     }


(define (adv:enable-interactions)
  (cond ((= *adv:disable-interactions* 0)
	 (c:enable-mouse)

;; Non-Refcounted
(c:disable-mouse)
(c:enable-mouse)

;; EOF ;;
