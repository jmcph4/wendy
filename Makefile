CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -pedantic -std=c11 -g3

TARGET = wendy
SRC = src/*.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY: test
test:
	valgrind ./$(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
