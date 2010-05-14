;; $Id: person.scm,v 1.5 2001/07/15 15:29:49 grumbel Exp $                                                             
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Guy manipulation functions.
;;

;; Sprite description ;;

;; Surface -> A set of frames
;; Sprite -> Surface with times for frames or a set of frames

(define mogli-gfx (make <person:gfx>
		    #:north "mogli_back"
		    #:south "mogli_front"
		    #:west  "mogli_left"
		    #:east  "mogli_right"))

;;;;;;;;;;;;;;;;;;;;;;;;


;; Manipulate the guy's position
;; FIXME: there should be a way to handle multiple guy's
(define (adv:guy:set-pos x-pos y-pos direction)
  (c:guy:set-position x-pos y-pos)
  (case direction
    ((north) (c:guy:set-direction 0))
    ((east)  (c:guy:set-direction 1))
    ((south) (c:guy:set-direction 2))
    ((west)  (c:guy:set-direction 3))
    (else (println "Error; Unknown direction: " direction))))

(define-syntax adv:guy:set-target
  (syntax-rules ()
    ((_ x y)
     (let ((hook (c:adv:hook:make)))
       (c:guy:set-target x y (lambda () (c:adv:hook:call-finish hook)))
       hook))))

(define-syntax adv:guy:walk-to-target
  (syntax-rules ()
    ((_ x y)
     (let ((hook (c:adv:hook:make)))
       (c:guy:set-target x y (lambda () (c:adv:hook:call-finish hook)))
       hook))))

(define (adv:guy:set-direction direction)
  (c:guy:set-direction (adv:direction->number direction)))

;; The person thats currently controlled by the player
(define *current-person* #f)

(define (person:current) *current-person*)

(define-method (adv:guy:set-scenario (scenario <scenario>))
  (adv:guy:set-scenario (person:current) scenario))

(define-method (adv:guy:set-scenario (person <person>) (scenario <scenario>))
  (c:guy:set-scenario (adv:bind person) (adv:bind scenario)))

                
(define *current-person* #f)

(define (person:make gfx)
  (let ((person (make <person> #:gfx gfx)))
    (set! (adv:bind person) (c:person:make person))
;;    (set! (adv:inventory person) (inventory:make))
    (set! *current-person* person)
    person
    ))

(define-method (person:set-current (person <person>))
  ;;(println "person:set-current: Not implemented")
  (set! *current-person* person)
  (c:person:set-current (adv:bind person))
  )

(define-method (person:set-gfx (person <person>) (gfx <person:gfx>))
  (c:guy:set-gfx (adv:bind person) gfx))

;; EOF ;;