GTK_LIB = `pkg-config --cflags --libs gtk+-3.0` -export-dynamic #-no-pie
OBJ = build/main.o
CC = gcc
CFLAGS  = -Wall -Werror -std=c99

.PHONY: clean open gdb

bin/Frequency_analysis : $(OBJ) bin
		$(CC) $(CFLAGS) -o bin/Frequency_analysis $(OBJ) $(GTK_LIB)

build/main.o : src/main.c build
		$(CC) $(CFLAGS) -o build/main.o -c src/main.c $(GTK_LIB)

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
