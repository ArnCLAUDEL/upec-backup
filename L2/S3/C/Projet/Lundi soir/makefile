SORTIE 	= app
CC 		= gcc
W 		= -Wall
DB 		= -g
SOURCES = main.c args.c menu.c image.c
OBJETS  = main.o args.o menu.o image.o

.PHONY: default clean

default: $(SORTIE)

image.o: image.c image.h
args.o: args.c args.h
menu.o: menu.c menu.h
main.o: main.c menu.h args.h image.h

%.o: %.c
	$(CC) $(W) -o $@ -c $<

$(SORTIE): $(OBJETS)
	$(CC) $(W) $(DB) -o $@ $^ -lm

clean: 
	rm $(SORTIE) $(OBJETS)