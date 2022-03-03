CC = gcc
CFLAGS = -Wall -Wextra 
LIBS = -lm
all: prolab21 
assembly: prolab21.s
input1: input

prolab21.o: prolab21.c
	$(CC) $(CFLAGS) -g -c prolab21.c

code_check.o: code_check.c
	$(CC) $(CFLAGS) -g -c code_check.c

prolab21.s: prolab21.c
	rm -f *.s
	$(CC)   -S -masm=intel -o assembly.s  prolab21.c 

prolab21: prolab21.o code_check.o
	$(CC) $(CFLAGS) $(LIBS)  -o prolab21 prolab21.o code_check.o

input.o: input.c
	$(CC) $(CFLAGS) -c input.c

input: input.o
	$(CC) $(CFLAGS) -o input input.o


clean_s:
	rm -f *.s

clean_all:
	rm -f test *.o
	rm -f *.s