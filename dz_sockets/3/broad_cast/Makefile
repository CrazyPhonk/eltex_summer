CFLAGS = -Wall -Wextra
res: client.o server.o
	gcc client.o -o Client $(CFLAGS)
	gcc server.o -o Server $(CFLAGS)
client.o: client.c
	gcc client.c -c 
server.o: server.c 
	gcc server.c -c
clean:
	rm -rf client.o server.o Client Server