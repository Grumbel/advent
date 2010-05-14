;; $Id: stat.scm,v 1.2 2001/08/21 20:38:43 grumbel Exp $                                                             
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Routines for handling loading and saveing of the game status.
;;

(define adv:quick-save-file 
  (let ((home (getenv "HOME")))
    (if home
	(string-append home "/.advent/quicksave.scm")
	(begin (println "Error: Couldn't get HOME") (exit)))))

(define (adv:quick-load)
  (adv:load-stat adv:quick-save-file))

(define (adv:quick-save)
  (adv:save-stat adv:quick-save-file))

(define (adv:save-stat filename)
  (println "Saveing gamestat to '" filename "'")
  (let ((port (open-output-file filename)))
    (with-output-to-port port
      (lambda () 
	(println ";; Advent Save File - Don't edit by hand!")
	(cond ((is-a? *current-real-scenario* <scenario>)
	       (let ((sym (adv:symbol *current-real-scenario*)))
		 (cond ((pair? sym)
			(println "(adv:set-scenario " (symbol->string (car sym)) ")"))
		       ((symbol? sym)
			(println "(adv:set-scenario " (symbol->string sym) ")"))
		       (else
			(println ";; ERROR: senario symbol not set!")))))
	      ((pair? *current-real-scenario*)
	       (println "(adv:set-scenario " 
			(symbol->string (car *current-real-scenario*)) ")"))
	      (else
	       (println ";; ERROR - saving scenario")))
	;; Save guy position
	(println "(c:guy:set-position " (c:guy:get-x-pos) " " (c:guy:get-y-pos) ")")
	(println "(c:guy:set-direction " (c:guy:get-direction) ")")
	(inventory:save-stat)
	))
    (close-port port)))

(define (adv:load-stat filename)
  (println "Loading stat file: " filename)
  (load filename))
  ;;(println "Loading gamestat from '" filename "'")
;;  (with-input-from-file filename
;;    (lambda () (println (read-line)))

;;(define-method (adv:save-stat (scenario <scenario>))
;;  (println ";; Not implemented")
;;  )

;; EOF ;;