CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror -pedantic -g -fsanitize=address

all: src/main.o src/fifo.o src/stack.o src/evalexpr.o src/my_strcmp.o
	$(CC) $(CFLAGS) -o evalexpr src/main.o src/fifo.o src/stack.o src/evalexpr.o src/my_strcmp.o 

evalexpr: src/main.o src/fifo.o src/stack.o src/evalexpr.o src/my_strcmp.o
	$(CC) $(CFLAGS) -o evalexpr src/main.o src/fifo.o src/stack.o src/evalexpr.o src/my_strcmp.o 

check :
	echo test
clean:
	$(RM) src/*.o
