CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -Werror
SOURCE = null.c
TARGET = app
FILE = test.txt
RM = rm -rf

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(FILE)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $^ -o $@
