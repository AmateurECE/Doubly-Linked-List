###############################################################################
# NAME:		    makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    Makefile for the Doubly-Linked-List test code.
#
# CREATED:	    06/06/2017
#
# LAST EDITED:	    01/02/2018
###

P = dlinkedlist
OBJECTS = dlinkedlist.c
CFLAGS = -Wall -O3
LDLIBS=
CC=gcc

$(P):
	$(CC) $(CFLAGS) -o $(P) $(OBJECTS) $(LDLIBS)

.PHONY: debug clean

CFLAGS_DEBUG = -g -O0 -Wall -D CONFIG_DEBUG_DLIST

debug:
	$(CC) $(CFLAGS_DEBUG) -o $(P) $(OBJECTS) $(LDLIBS)

clean:
	rm -rf *.c~
	rm -rf *.h~
	rm -rf makefile~

###############################################################################
