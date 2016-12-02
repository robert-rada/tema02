EXE=paint_simulator

build: main image error const
	gcc -g -std=c99 -Wall -o $(EXE) obj/main.o obj/image.o obj/const.o obj/error.o

main: src/main.c
	gcc -g -c -std=c99 -Wall -o obj/main.o src/main.c

image: src/image.c
	gcc -g -c -std=c99 -Wall -o obj/image.o src/image.c

const: src/const.c
	gcc -g -c -std=c99 -Wall -o obj/const.o src/const.c

error: src/error.c
	gcc -g -c -std=c99 -Wall -o obj/error.o src/error.c

run:
	./$(EXE)

clean:
	rm obj/*
	rm $(EXE)
