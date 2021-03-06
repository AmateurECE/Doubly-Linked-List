###############################################################################
# NAME:		    makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    Makefile for the Doubly-Linked-List test code.
#
# CREATED:	    06/06/2017
#
# LAST EDITED:	    02/12/2018
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
	rm -f dlist
	rm -rf dlist.dSYM

###############################################################################
