CC = gcc
CFLAGS = -Wall -Wextra 
LIBS = -lm
all: prolab21
assembly:prolab21.s



prolab21.o: prolab21.c
	$(CC) $(CFLAGS) -c prolab21.c

prolab21.s: prolab21.c
	rm -f *.s
	$(CC)   -S -masm=intel -o assembly.s  prolab21.c 

prolab21: prolab21.o
	$(CC) $(CFLAGS) $(LIBS) -o prolab21 prolab21.o




clean_s:
	rm -f *.s

clean:
	rm -f test *.o
	rm -f *.s