CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=examples/test.c src/linked_list.c src/allocate.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=test

all: $(SOURCE) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf src/*.o examples/*.o test
