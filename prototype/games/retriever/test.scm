(load "syntax-ext.scm")

(define *some-var* #f)

(catch 'adv:assert
       (lambda ()
	 (adv:assert *some-var*))
       (lambda (exception . lst)
	 (display "Catched:")
	 (display "'")
	 (display exception)
	 (for-each (lambda (x)
		     (display "'")
		     (display x)
		     (display "'")) lst)
	 (newline)))
       
 



