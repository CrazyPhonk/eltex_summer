CFLAGS = -Wall -Wextra -pthread
res: 1.o 2.o 3.o
	gcc 1.o -o 1 $(CFLAGS)
	gcc 2.o -o 2 $(CFLAGS)
	gcc 3.o -o 3 -pthread
1.o: 1.c
	gcc 1.c -c 
2.o: 2.c 
	gcc 2.c -c
3.o: 3.c
	gcc 3.c -c
clean:
	rm -rf 1.o 2.o 3.o 1 2 3