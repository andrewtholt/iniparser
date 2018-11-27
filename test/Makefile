#
# iniparser tests Makefile
#

CC      = gcc
CFLAGS  = -g -I../src
LFLAGS  = -L.. -liniparser
AR	    = ar
ARFLAGS = rcv
RM      = rm -f


default: all

all: iniexample parse gauge fred

fred: fred.c iniUtils.o
	$(CC) $(CFLAGS) -o fred fred.c iniUtils.o -o fred

iniUtils.o:	iniUtils.c iniUtils.h
	(CC) -c $(CFLAGS) iniUtils.c -o iniUtils.o

gauge: gauge.c
	$(CC) $(CFLAGS) -o gauge gauge.c -I../src -L.. -liniparser

iniexample: iniexample.c
	$(CC) $(CFLAGS) -o iniexample iniexample.c -I../src -L.. -liniparser

parse: parse.c
	$(CC) $(CFLAGS) -o parse parse.c -I../src -L.. -liniparser

clean veryclean:
	$(RM) iniexample example.ini parse



