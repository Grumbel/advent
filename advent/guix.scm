;; Advent
;; Copyright (C) 2019 Ingo Ruhnke <grumbel@gmail.com>
;;
;; This program is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <http://www.gnu.org/licenses/>.

(set! %load-path
  (cons* "/ipfs/QmetP3eCAM9q3VPCj9BvjFdWkTA7voycebnXjyfc2zacFE/guix-cocfree_v0.0.0-45-g0fe3c86"
         %load-path))

(use-modules (guix build-system cmake)
             ((guix licenses) #:prefix license:)
             (guix packages)
             (gnu packages guile)
             (gnu packages gl)
             (gnu packages pkg-config)
             (gnu packages bdw-gc)
             (gnu packages swig)
             (guix-cocfree utils)
             (guix-cocfree packages clanlib))

(define %source-dir (dirname (current-filename)))

(define-public advent
  (package
   (name "advent")
   (version (version-from-source %source-dir))
   (source (source-from-source %source-dir))
   (build-system cmake-build-system)
   (arguments
    `(#:tests? #f))  ; no tests
   (native-inputs
    `(("pkg-config" ,pkg-config)))
   (inputs
    `(("mesa" ,mesa)
      ("glu" ,glu)
      ("swig" ,swig)
      ("guile-2.2" ,guile-2.2)
      ("libatomic-ops" ,libatomic-ops)
      ("clanlib-1.0" ,clanlib-1.0)))
   (synopsis "")
   (description "")
   (home-page "")
   (license license:gpl3+)))

advent

;; EOF ;;
