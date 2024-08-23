CFLAGS = -Wall -Wextra 
res: clientSysV.o serverSysV.o
	gcc clientSysV.o -o Client $(CFLAGS)
	gcc serverSysV.o -o Server $(CFLAGS)
clientSysV.o: clientSysV.c
	gcc clientSysV.c -c 
serverSysV.o: serverSysV.c 
	gcc serverSysV.c -c
clean:
	rm -rf clientSysV.o serverSysV.o Client Server