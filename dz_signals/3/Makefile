CFLAGS = -Wall -Wextra -lrt
res: loop.o send.o
	gcc loop.o -o loop $(CFLAGS)
	gcc send.o -o send $(CFLAGS)
loop.o: loop.c
	gcc loop.c -c 
send.o: send.c 
	gcc send.c -c
clean:
	rm -rf loop.o send.o loop send