build: src/main.c src/image.c src/const.c
	gcc -g -std=c99 -Wall -o painter_simulator src/main.c src/image.c src/const.c

run:
	./painter_simulator

clean:
	rm painter_simulator
