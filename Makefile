GTK_LIB = `pkg-config --cflags --libs gtk+-3.0` -export-dynamic #-no-pie
OBJ = build/main_gtk.o build/body.o 
CC = gcc
CFLAGS  = -g2 -Wall  -std=c99

.PHONY: clean open gdb

bin/Frequency_analysis : $(OBJ) bin
		$(CC) $(CFLAGS) -o bin/Frequency_analysis $(OBJ) $(GTK_LIB)

build/main_gtk.o : src/main_gtk.c build
		$(CC) $(CFLAGS) -o build/main_gtk.o -c src/main_gtk.c $(GTK_LIB)

build/body.o : src/body.c build
		$(CC) $(CFLAGS) -o build/body.o -c src/body.c $(GTK_LIB)

build:
	mkdir build

bin:
	mkdir bin

clean :
	rm -rf build bin
open :
	./bin/Frequency_analysis
gdb :
	gdb ./bin/Frequency_analysis
