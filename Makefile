CC=gcc
CFLAGS=-fPIC -g
LDFLAGS=-shared
SOURCES=src/allocate.c
OBJECTS=$(SOURCES:.c=.o)
EXAMPLE1=examples/test.c
EXECUTABLE1=test
EXAMPLE2=examples/test2.c
EXECUTABLE2=test2
EXAMPLE3=examples/test3.c
EXECUTABLE3=test3
TARGET_LIB=liballocate.so

all: $(TARGET_LIB) $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

$(EXECUTABLE3): $(TARGET_LIB)
	$(CC) $(EXAMPLE3) $(CFLAGS) $(TARGET_LIB) -o $@

$(EXECUTABLE2): $(TARGET_LIB)
	$(CC) $(EXAMPLE2) $(CFLAGS) $(TARGET_LIB) -o $@

$(EXECUTABLE1): $(TARGET_LIB)
	$(CC) $(EXAMPLE1) $(CFLAGS) $(TARGET_LIB) -o $@

$(TARGET_LIB): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -rf src/*.o examples/*.o test test2 test3 *.so
