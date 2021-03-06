(define-method (adv:drawable:create (filename <string>)
				    (x-pos <integer>) (y-pos <integer>) (z-pos <number>))
  (sprite-drawable:create filename x-pos y-pos z-pos))

(define (sprite-drawable:create filename x y z)
  (c:sprite-drawable:create
   (c:surface-sprite:create filename)
   x y z))

(define (adv:surface-sprite:create filename . args)
  (define (align2pair sprite alignsym)
    (cond ((pair? alignsym)
	   alignsym)
	  ((symbol? alignsym)
	   (case (alignsym)
	     ((center)
	      (cons (quotient (c:sprite:get-width sprite) 2)
		    (quotient (c:sprite:get-height sprite) 2)))
	     ((center-bottom)
	      (cons (quotient (c:sprite:get-width sprite) 2)
		    (- (c:sprite:get-height sprite))))
	     ))))

  (let* ((frames (get-keyword-value args #:frames #f))
	 (fps    (get-keyword-value args #:fps 2.7))
	 (sprite (cond (frames
			(c:surface-sprite:create-anim  filename frames))
		       (else
			(c:surface-sprite:create filename)))))
    (let* ((align     (get-keyword-value args  #:align   (cons 0 0)))
	   (x-align   (get-keyword-value args  #:x-align (car align)))
	   (y-align    (get-keyword-value args #:y-align (cdr align))))

      (println "Frames per second: " fps)
      (c:surface-sprite:set-fps sprite fps)
      (c:surface-sprite:set-align sprite x-align y-align))))


;; EOF ;;