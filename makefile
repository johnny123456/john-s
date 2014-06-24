obj:main.o stat.o test.o print_env.o getenv.o fork.o pipe.o\
	tcp_cli.o tcp_ser.o cli.o serfork.o udpser.o udpcli.o

CC=cc -Wall -g 
RM=rm 
MV=cp -f
HOME=$(shell pwd)/sbin
CFLAGS=-I./inc

.SUFFIXES: .c .o .h

all : $(obj)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $*.o
#	$(CC) -o $(CFLAGS) $*.o -o $*.out 
	$(CC) -o $*.out $(CFLAGS) $*.o
	$(MV) $*.out $(HOME)

clean:
	$(RM) -f *.o

clear:
	$(RM) -f *.out
