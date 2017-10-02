CC = gcc
CFLAGS = -std=c99 -c

src = 1.c 
objects = $(src:.c=.o)

all: $(objects)
	
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(objects)
