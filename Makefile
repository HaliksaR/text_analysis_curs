GTK_LIB = `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
OBJ = build/main_gtk.o build/body.o 
CC = gcc
CFLAGS  = -Wall -Werror -std=c99

.PHONY: clean open icon delete

all: build bin bin/Frequency_analysis_make

.Frequency_analysis : $(OBJ)
		$(CC) $(CFLAGS) -o .Frequency_analysis $(OBJ) $(GTK_LIB)

bin/Frequency_analysis_make : $(OBJ)
		$(CC) $(CFLAGS) -o bin/Frequency_analysis_make $(OBJ) $(GTK_LIB)

build/main_gtk.o : src/main_gtk.c
		$(CC) $(CFLAGS) -o build/main_gtk.o -c src/main_gtk.c $(GTK_LIB)

build/body.o : src/body.c
		$(CC) $(CFLAGS) -o build/body.o -c src/body.c $(GTK_LIB)

build :
	mkdir build

bin :
	mkdir bin

icon : .Frequency_analysis
	chmod +x icon.sh
	./icon.sh

clean :
	rm .Frequency_analysis
	rm -rf build bin

open :
	./bin/Frequency_analysis_make #./test_text ./analize.txt

delete :
	chmod +x .rm_dir.sh
	./.rm_dir.sh
