CC = clang
CFLAGS = -Wall -g -std=gnu11 `pkg-config --cflags clutter-1.0`
LDLIBS = `pkg-config --libs clutter-1.0`
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).c life.c life.h
	$(CC) $(CFLAGS) -o $(TARGET) $(LDLIBS) $(TARGET).c life.c

*.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $(LDLIBS) $<

clean:
	$(RM) $(TARGET)
