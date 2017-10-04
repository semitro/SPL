CC=gcc
CFLAGS= -std=c99 -Wall -ggdb


src = strangeRunner.c main.c FileInteraction.c
objects = $(src:.c=.o)
main=main

all: $(main)

$(main): $(objects)
	$(CC) $(CFLAGS) $(objects) -o $(main)

#%.some == *.some, but %1 == %2
# $@ - название правила
# $< - первое требование
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(objects) $(main)


tests:
	make -C runnable/	
