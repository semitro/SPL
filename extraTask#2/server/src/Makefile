CC=gcc
CFLAGS= -std=c99 -Wall -Wextra -pedantic-errors -ggdb3 -I ../include

src = list/list.c list/list_functions.c  list/list_serialize.c main.c
objects = $(src:.c=.o)

main=main

all: $(main)

$(main): $(objects)
	$(CC) $(CFLAGS) $(objects) -o $(main)
clean:
	$(RM) $(objects) $(main)

