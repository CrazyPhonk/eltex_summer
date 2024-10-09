CFLAGS = -Wall -Wextra
res: client.o server.o
	gcc clientTCP.o -o ClientTCP $(CFLAGS)
	gcc clientUDP.c -o ClientUDP
	gcc server.o -o Server $(CFLAGS)
client.o: clientTCP.c clientUDP.c
	gcc clientUDP.c -c 
	gcc clientTCP.c -c
server.o: server.c 
	gcc server.c -c
clean:
	rm -rf clientTCP.o server.o ClientTCP Server ClientUDP clientUDP.o