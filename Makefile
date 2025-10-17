CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJS = main.o utils.o
TARGET = programa

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c utils.h
utils.o: utils.c utils.h

clean:
	rm -f $(OBJS) $(TARGET)

