;; Animation interface

(define-class <animation> ()
  (loop   #:init-value #f
	  #:init-keyword #:loop
	  #:accessor loop)
  (frames #:accessor frames
	  #:init-value '()
	  #:init-keyword #:frames))

;;(define-method (adv:play (obj <animation>))
;;  (for-each (lambda (x)
;;	      (println "Surface: "  x))
;;	    (frames obj)))

(define-class <frame> ()
  (display-time #:accessor display-time
		#:init-value #f
		#:init-keyword #:display-time)

  (surface-name #:accessor surface-name
		#:init-value #f
		#:init-keyword #:surface-name)
  (sub-frame    #:accessor sub-frame
		#:init-value 0
		#:init-keyword #:sub-frame)

  (position     #:accessor position
		#:init-value (list 320 200 150)
		#:init-keyword #:position))

(define-method (adv:frame surface-name position display-time sub-frame)
  (make <frame>
    #:surface-name surface-name
    #:position     position
    #:display-time display-time
    #:sub-frame    sub-frame))

(define-method (adv:frame surface-name position display-time)
  (make <frame>
    #:surface-name surface-name
    #:position     position
    #:display-time display-time))

(define (adv:play . args)
 (c:animation-play (make <animation> 
		     #:frames args)))

(define-method (write (obj <frame>) port)
  (display (format #f "<sur: ~A ~A ~A>" 
		   (surface-name obj)
		   (sub-frame obj)
		   (display-time obj))
	   port))


;(adv:define-animation (frame #:time 10 
;			     #:surface "sur"
;			     #:subframe 3
;			     #:position '(45 24 34))
;		      (frame #:time 10 
;			     #:surface "sur"
;			     #:subframe 3))

;; EOF ;;