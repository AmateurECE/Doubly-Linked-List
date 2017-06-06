################################################################################
# NAME: makefile
# AUTHOR: Ethan D. Twardy
# DESCRIPTION: makefile for the executable C code contained in dlinkedlist.c
# CREATED: 06/06/17
# LAST EDITED: 06/06/17
################################################################################

P = dlinkedlist
OBJECTS = dlinkedlist.c
CFLAGS = -Wall -O3
LDLIBS=
CC=gcc

$(P):
	$(CC) $(CFLAGS) -o $(P) $(OBJECTS) $(LDLIBS)

.PHONY: debug clean

CFLAGS_DEBUG = -g -O0 -Wall -D CONFIG_DEBUG_CLIST

debug:
	$(CC) $(CFLAGS_DEBUG) -o $(P) $(OBJECTS) $(LDLIBS)

clean:
	rm -rf *.c~
	rm -rf *.h~
	rm -rf makefile~