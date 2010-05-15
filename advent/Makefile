DESTDIR  = 
PREFIX   = "/usr/local"
DATADIR  = "${PREFIX}/share/advent"
LIBDIR   = "${PREFIX}/lib"
MANDIR   = "${PREFIX}/share/man"
BINDIR   = "${PREFIX}/bin"

src/libadvent.so:
	scons

clean:
	scons -c
	rm -rf .sconf_temp/
	rm -f .sconsign.dblite
	rm -f config.log

install: install-exec install-data install-man

install-exec: src/libadvent.so
	install -D src/libadvent.so ${DESTDIR}${LIBDIR}/advent/advent/libcore.so
	install -d ${DESTDIR}${BINDIR}
	echo \
	'#!/usr/bin/guile-1.6 \\\n-s\n!#\n\n'\
	'(set! %load-path (cons "'${LIBDIR}/advent'" %load-path))\n'\
	'(set! %load-path (cons "'${DATADIR}'" %load-path))\n'\
	'(chdir "'"${DATADIR}/cosmos"'")\n'\
	'(primitive-load "cosmos.scm")\n'\
	'\n;; EOF ;;'\
	> ${DESTDIR}${BINDIR}/advent-cosmos
	chmod 755 ${DESTDIR}${BINDIR}/advent-cosmos

install-man:

install-data:
	cd doc/examples/; \
	find -type f \( \
	-name "*.scm" -o \
	-name "*.png" -o \
	-name "*.jpg" \) \
	-exec install -m 644 -D {} ${DESTDIR}${DATADIR}/{} \;

	cd src/; \
	find advent/ -type f \( \
	-name "*.scm" \) \
	-exec install -m 644 -D {} ${DESTDIR}${DATADIR}/{} \;

.PHONY : clean install install-exec install-man install-data

# EOF #
