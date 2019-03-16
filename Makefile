lsr: main.o lsr.o
	gcc -o lsr main.o
	rm *.o

lsr.o: lsr.c lsr.h
	gcc -c lsr.c

main.o: main.c lsr.h
	gcc -c main.c

clean:
	rm *.o lsr

init:
	touch lsr.c lsr.h main.c
