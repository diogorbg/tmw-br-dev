# Makefile

all clean: gen-sprite-base/Makefile
	make -C gen-sprite-base $@
	cp gen-sprite-base/gen-sprite-base gen-sprite-base_`uname -m`

install: gen-sprite-base/Makefile
	make -C gen-sprite-base $@
	cp arquivos/logo.png ~/.gimp-2.6/plug-ins/
