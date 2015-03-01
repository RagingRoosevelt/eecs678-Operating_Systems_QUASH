quash: quash.o
	g++ -o quash main.o

quash.o: main.c
	g++ -g -c main.c

clean:
	rm -f *.o *~ quash