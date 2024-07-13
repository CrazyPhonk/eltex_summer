res: minus.o plus.o multiply.o devide.o 1.o
	gcc -shared -o libfsdyn.so minus.o plus.o multiply.o devide.o
	gcc 1.o -L. -lfsdyn -o rezultdyn
plus.o: 
	gcc -fPIC -c plus.c 
minus.o: 
	gcc -fPIC -c minus.c 
multiply.o: 
	gcc -fPIC -c multiply.c 
devide.o: 
	gcc -fPIC -c devide.c 
1.o: minus.o plus.o multiply.o devide.o 1.o
	gcc -c 1.c
clean:
	rm -f 1.o plus.o minus.o multiply.o devide.o res static libfsdyn.so rezultdyn