# Makefile

all: gen-sprite-base

gen-sprite-base: gen-sprite-base.c
	gcc $^ -o $@ `gimptool-2.0 --cflags --libs`

%.o: %.c %.h
	gcc -c $< -o $@ `gimptool-2.0 --cflags`

clean:
	rm *.o

install: gen-sprite-base
	cp gen-sprite-base ~/.gimp-2.6/plug-ins/
