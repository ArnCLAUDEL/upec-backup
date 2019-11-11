EXEC=serialize.exe
SOURCES=graph.c map.c serialization.c main.c
OBJECTS=$(SOURCES:.c=.o)
CC=gcc
CFLAGS=-Wall
.PHONY: default clean

default: $(EXEC)

graph.o: graph.c graph.h
map.o: map.c map.h
serialization.o: serialization.c serialization.h map.h graph.h
main.o: main.c serialization.h graph.h

%.o: %.c
		$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^

clean: rm $(EXEC) $(OBJECTS) $(SOURCES:.c=.c~) $(SOURCES:.c=.h)