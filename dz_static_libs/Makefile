
static: libmyLib.a 1.o
	gcc 1.o -L. -lmyLib -o static
libmyLib.a: plus.o plus.o minus.o multiply.o devide.o
	ar rc libmyLib.a plus.o plus.o minus.o multiply.o devide.o
	ranlib libmyLib.a

1.o: 
	gcc -c 1.c
plus.o: 
	gcc -c plus.c 
minus.o: 
	gcc -c minus.c 
multiply.o: 
	gcc -c multiply.c 
devide.o: 
	gcc -c devide.c 
clean:
	rm -f 1.o plus.o minus.o multiply.o devide.o res static libmyLib.a