CC=nasm
CFLAGS=-felf64

all: link
	
link: dict.o lib.o main.o
	ld dict.o lib.o main.o -o main

lib.o: lib.asm
	$(CC) $(CFLAGS) lib.asm

dict.o: lib.o
	$(CC) $(CFLAGS) dict.asm

main.o: main.asm
	$(CC) $(CFLAGS) main.asm

main.asm: colon.inc

colon.inc: words.inc

clean:
	rm dict.o main.o main
test:	
	make macroCheck
	./main
macroCheck: main.asm
	nasm -E words.inc
