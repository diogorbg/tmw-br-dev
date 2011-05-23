# Makefile

all: tmwbr-hello

tmwbr-hello: tmwbr-hello.c
	gcc $^ -o $@ `gimptool-2.0 --cflags --libs`

%.o: %.c %.h
	gcc -c $< -o $@ `gimptool-2.0 --cflags`

clean:
	rm *.o

install: tmwbr-hello
	cp tmwbr-hello ~/.gimp-2.6/plug-ins/
	cp logo.png ~/.gimp-2.6/plug-ins/
