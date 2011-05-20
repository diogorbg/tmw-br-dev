# Makefile

all: tmwbr-gen-sprite-base tmw-br-plugin

tmwbr-gen-sprite-base: gen-sprite-base/main.o gen-sprite-base/interface.o gen-sprite-base/render.o
	g++ $^ -o $@ `gimptool-2.0 --cflags --libs`

tmw-br-plugin: main.o interface.o render.o
	gcc $^ -o $@ `gimptool-2.0 --cflags --libs`

%.o: %.c %.h
	gcc -c $< -o $@ `gimptool-2.0 --cflags`

clean:
	rm */*.o
	rm *.o

install: tmwbr-gen-sprite-base
	cp tmwbr-gen-sprite-base ~/.gimp-2.6/plug-ins/
#	cp tmw-br-plugin ~/.gimp-2.6/plug-ins/
