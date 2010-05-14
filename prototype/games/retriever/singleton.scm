(use-modules (ice-9 syncase)
	     (oop goops))

(define-syntax define-singleton
  (syntax-rules ()
    ((_ obj objclass super)
     (define-class objclass super)
     (define obj (make objclass))
     )))

(define-class <advent:object> ())
(define-singleton box <box> (<advent:object>))


;; EOF ;;