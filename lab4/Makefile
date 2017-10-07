CC = gcc
CFLAGS = -std=c99 -Wall -ggdb3 -Wextra -pedantic-errors
src = list.c main.c list_functions.c list_tests.c
objects = $(src:.c=.o)
main = main

all: $(main)

$(main): $(objects)

%.o: %.c
	$(CC) $(CFLAGS) -c  $< -o  $@
clean:
	$(RM) $(objects)
