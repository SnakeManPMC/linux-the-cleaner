#
# The Cleaner makefile (c) PMC 1996 - 2015
#

CC	= g++


CFLAGS = -static

LIBS	= 

all:		cleaner

cleaner:        cleaner.cpp
	        $(CC) $(CFLAGS) -o $@ $<
