(use-modules (ice-9 popen))

(println "Loading festival")

(define *festival-port* (open-pipe "/usr/bin/festival --pipe" OPEN_WRITE))

(define-method (festival:talk (str <string>))
  (println "Festival port: " *festival-port*)
  (display "(SayText \"" *festival-port*)
  (display str *festival-port*)
  (display "\")\n" *festival-port*))

;; EOF ;;