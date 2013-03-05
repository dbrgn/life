CC = clang
CFLAGS = -Wall -g -std=gnu11 `pkg-config --cflags clutter-1.0`
LDLIBS = `pkg-config --libs clutter-1.0`
TARGET = main
DEPS = life

all: $(TARGET)

$(TARGET): $(TARGET).c $(DEPS).c
	$(CC) $(CFLAGS) -o $(TARGET) $(LDLIBS) $(TARGET).c $(DEPS).c

*.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $(LDLIBS) $<

clean:
	$(RM) $(TARGET)
