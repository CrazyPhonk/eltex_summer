CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses
result: 1.c 2.c
	gcc 2.c -o ex2 $(CFLAGS) $(LDFLAGS)
	gcc 1.c -o ex1 $(CFLAGS) 
clean:
	rm -rf ex1 ex2 output.txt