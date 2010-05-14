;; $Id: guy.scm,v 1.1 2001/07/02 10:27:13 grumbel Exp $                                                             
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Guy manipulation functions.
;;

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

;; EOF ;;