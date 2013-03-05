CC = clang
CFLAGS = `pkg-config --cflags clutter-1.0` -g -Wall -std=gnu11
LDLIBS = `pkg-config --libs clutter-1.0`
TARGET = life

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(LDLIBS) $(TARGET).c

*.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $(LDLIBS) $<

clean:
	$(RM) $(TARGET)
