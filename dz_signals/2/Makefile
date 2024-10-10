CFLAGS = -Wall -Wextra -lrt
res: block.o send.o
	gcc block.o -o block $(CFLAGS)
	gcc send.o -o send $(CFLAGS)
block.o: block.c
	gcc block.c -c 
send.o: send.c 
	gcc send.c -c
clean:
	rm -rf block.o send.o block send