#-------------Makro-Part------------------
CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c99 
LDFLAGs =
DEBUG = -DNDEBUG 


VPATH = src
#--------------Linker-Part-----------------
gpOpenHantek: main.o
	echo $@ is now linked
	$(CC) $(LDFLAGS) -o $@ $^
#--------------Compiler-Part---------------
main.o : main.c
	$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $<

clean : 
	rm -f *.o
