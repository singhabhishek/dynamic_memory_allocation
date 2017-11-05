CC=gcc
CFLAGS=-fPIC -Wall -g
LDFLAGS=-shared
SOURCES=src/allocate.c
OBJECTS=$(SOURCES:.c=.o)
EXAMPLE=examples/test.c
EXECUTABLE=test
TARGET_LIB=liballocate.so

all: $(TARGET_LIB) $(EXECUTABLE)

$(EXECUTABLE): $(TARGET_LIB)
	$(CC) $(EXAMPLE) $(CFLAGS) $(TARGET_LIB) -o $@

$(TARGET_LIB): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -rf src/*.o examples/*.o test *.so
