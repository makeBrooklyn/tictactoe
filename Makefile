CC = gcc
CFLAGS = -Wall -W -pedantic -std=c99
LDFLAGS =
OBJFILES = ttt.o
TARGET = ttt

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~

