;; $Id: object.scm,v 1.10 2003/02/23 17:07:48 grumbel Exp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Object logic handling and method creation functions
;;

;;(define-module (advent object) :use-module (oop goops))

;;(export <adv:object> adv:get-hotspots adv:on-click adv:bind adv:name)
;;(export-syntax adv:defobj)

(define-class <adv:object> ()
  ;; The name of the object, which is shown on the screen
  (adv:name
   #:init-value "<name-not-set>" 
   #:init-keyword #:name
   #:accessor adv:name)

  ;; A binding to a c++ object (drawable and collideable)
  (adv:bind #:accessor adv:bind
	    #:init-value #f
	    #:init-keyword #:bind)
  
  ;; A list of hotspots associated with this object
  ;; Format: (list (list INT INT [east|west|north|south]))
  (adv:hotspots #:accessor adv:hotspots
		#:init-value #f
		#:init-keyword #:hotspots)
  
  ;; The sprite which is shown in the inventory
  ;; FIXME: should probally on the c++ site
  (adv:inventory-sprite
   #:init-value   #f
   #:init-keyword #:inventory-sprite
   #:accessor     adv:inventory-sprite
   ))

(define-method (adv:get-hotspots (obj <adv:object>))
  (adv:hotspots obj))

(define-public adv:on-click-handler #f)
(define-method (adv:on-click (object <adv:object>))
  (if adv:on-click-handler
      (adv:on-click-handler object)
      (println "Object method for 'on-click' is not set")))

(define-public (adv:set-on-click-handler handler)
  (set! adv:on-click-handler handler))

(define-public (extract-members lst)
  (map (lambda (x) (list (car x) 
			 #:init-value (cadr x)
			 #:accessor (car x)))
   (cdr (assoc 'status lst))
       ))

(define-public (generate-methods classname lst)
  (if lst
      (for-each (lambda (x) 
		  (println "(define-method (" (car x) " (this " classname "))")
		  (for-each (lambda (x) (println "  " x ")"))
			    (cdr x)))
		lst)))


#!
-==:: Wannabe ::==-

(adv:combine (workplace:burning-trash) (bottle-of-wine)
	     )
!#

;; Define a singleton object (one object -> one class)
#!
(define-syntax adv:defobj
  (syntax-rules ()
    ((_ name pair ...)
     (let ((classname (symbol->class 'name)))
       (println "(define-class " classname " (<adv:object>)")
       (for-each (lambda (x) (println "  " x))
		 (extract-members '(pair ...)))
       (println ")")
       (println "(define " 'name " (make " classname " #:name \"" 'name "\"))")
       (generate-methods classname (cdr (assoc 'methods '(pair ...))))
       ))))

(define-public (adv:compact-args lst)
  (for-each (lambda (x)
	      (let ((sym  (car x))
		    (rest (cdr x)))
		(case sym 
		  ((members)
		   (println "OK"))
		  (else
		   (println "Unknown symbol: " sym)))))
	    lst))

(define-syntax adv:defobj
  (syntax-rules ()
    ((_ name pair ...)
     (adv:defobj_ 'name (symbol->classname 'name) (adv:compact-args '(pair ...)))
     )))

(define-public (adv:defobj_ name classname lst)
  )

!#

;; EOF ;;