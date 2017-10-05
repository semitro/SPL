CC = gcc
CFLAGS = -std=c99 -Wall -ggdb3 -Wextra -pedantic-errors
src = list.c main.c
objects = $(src:.c=.o)
main = main

all: $(main)

$(main): $(objects)

%.o: %.c
	$(CC) $(CFLAGS) -c  $< -o  $@
clean:
	$(RM) $(objects)
