#-------------Makro-Part------------------
CC = gcc
CFLAGS = -Wall -pedantic -std=c99 #-Werror 
LDFLAGs =
DEBUG = -DNDEBUG 


VPATH = src
#--------------Linker-Part-----------------
gpOskar: main.o
	echo $@ is now linked
	$(CC) $(LDFLAGS) -o $@ $^
#--------------Compiler-Part---------------
main.o : main.c
	$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $<

clean : 
	rm -f *.o *.txt
