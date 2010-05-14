;; Currently not implemented
(define-method (use (obj1 <advent:object>) (obj2 <advent:object>))
  (dialog:add "Don't know how to combine " (name obj1) " and " (name obj2) "."))

(define-method (use (obj <advent:object>))
  (dialog:add "Don't know what I should do with " (name obj)))

(define-method (look (obj <advent:object>))
  (dialog:add (string-append "You see a " (name obj) ", nothing special.")))

(define-method (speak (obj <advent:object>))
  (dialog:add "Nobody to speak to."))

(define-method (pickup (obj <advent:object>))
  (dialog:add "Don't know how to pick that up."))

(define-method (walk (obj <advent:object>))
  (println "WALK NOT IMPLEMENTED")
  #f)

