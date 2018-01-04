###############################################################################
# NAME:		    makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    Makefile for the Doubly-Linked-List test code.
#
# CREATED:	    06/06/2017
#
# LAST EDITED:	    01/03/2018
###

CC=gcc
ifeq ($(MAKECMDGOALS),debug)
	CFLAGS = -g -O0 -Wall -D CONFIG_DEBUG_DLIST
else
	CFLAGS = -Wall -O3
endif

dlist:

.PHONY: debug clean

debug: dlist

clean:
	rm -rf *.c~
	rm -rf *.h~
	rm -rf makefile~

###############################################################################
