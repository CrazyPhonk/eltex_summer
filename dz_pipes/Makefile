CFLAGS = -Wall -Wextra
DIR = /home/egor/VSCode/C/eltex_summer/dz_pipes/2
res: 1.o client.o server.o 3.o
	gcc 1.o -o 1 $(CFLAGS)
	gcc client.o -o 2exClient $(CFLAGS)
	gcc server.o -o 2exServer $(CFLAGS)
	gcc 3.o -o 3 $(CFLAGS)
1.o: 1.c
	gcc 1.c -c
client.o: $(DIR)/client.c
	gcc $(DIR)/client.c -c 
server.o: $(DIR)/server.c 
	gcc $(DIR)/server.c -c
3.o: 3.c 
	gcc 3.c -c
clean:
	rm -rf out 1.o 1 client.o server.o 2exClient 2exServer 3.o 3