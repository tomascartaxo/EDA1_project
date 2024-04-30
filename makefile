all: main.c
	gcc -c main.c
	gcc -c hash.c
	gcc -c board.c
	gcc -o main main.o hash.o board.o
	rm main.o hash.o board.o
