rm config.cache

aclocal
autoheader
automake --add-missing
autoconf
