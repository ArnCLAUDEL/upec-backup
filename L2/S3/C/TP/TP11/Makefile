.PHONY: default clean debug

default: main.exe

image.o: image.c image.h
		gcc -o image.o -c image.c

main.o: main.c image.h
		gcc -o main.o -c main.c

main.exe: main.o image.o
		gcc -Wall -g -o main image.o main.o

clean: 
		rm main.exe image.o main.o

debug: main.o image.o
		gcc -g -o main main.c image.o 