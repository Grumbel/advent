(define-method (adv:knowledge:clear (person <person>))
  (set! (adv:knowledge person) '()))

(define-method (adv:knowledge:clear)
  (adv:knowledge:clear (person:current)))

(define-method (adv:knowledge:add (person <person>) know)
  (if (not (adv:knowledge:has person know))
      (set! (adv:knowledge person) (cons know (adv:knowledge person)))))

(define-method (adv:knowledge:add know)
  (adv:knowledge:add (person:current) know))

(define-method (adv:knowledge:has (person <person>) know)
  (member know (adv:knowledge person)))

(define-method (adv:knowledge:has know)
  (adv:knowledge:has (person:current) know))

;; EOF ;;