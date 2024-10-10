CFLAGS = -Wall -Wextra -lrt
res: recv.o send.o
	gcc recv.o -o recv $(CFLAGS)
	gcc send.o -o send $(CFLAGS)
recv.o: recv.c
	gcc recv.c -c 
send.o: send.c 
	gcc send.c -c
clean:
	rm -rf recv.o send.o recv send