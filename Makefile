#
# iniparser Makefile
#

# Compiler settings
CC      = gcc
# CFLAGS  = -O2 -fPIC -Wall # -pedantic -ansi
CFLAGS  = -g -fPIC -Wall -DLINUX # -pedantic -ansi

# Ar settings to build the library
AR	    = ar
ARFLAGS = rcv

SHLD = ${CC} ${CFLAGS}
LDSHFLAGS = -shared -Wl,-Bsymbolic  -Wl,-rpath -Wl,/usr/lib -Wl,-rpath,/usr/lib
LDFLAGS = -Wl,-rpath -Wl,/usr/lib -Wl,-rpath,/usr/lib

# Set RANLIB to ranlib on systems that require it (Sun OS < 4, Mac OSX)
# RANLIB  = ranlib
RANLIB = true

RM      = rm -f


# Implicit rules

SUFFIXES = .o .c .h .a .so .sl

COMPILE.c=$(CC) $(CFLAGS) -c
.c.o:
	@(echo "compiling $< ...")
	$(COMPILE.c) -o $@ $<


SRCS = src/iniparser.c \
	   src/dictionary.c \
	   src/iniUtils.c

OBJS = $(SRCS:.c=.o)
LIBOBJS = dictionary.o  iniparser.o  iniUtils.o

default:	libiniparser.a libiniparser.so

libiniparser.a:	$(OBJS)
	@($(AR) $(ARFLAGS) libiniparser.a $(OBJS))
	@($(RANLIB) libiniparser.a)

libiniparser.so:	$(OBJS)
	@$(SHLD) $(LDSHFLAGS) -o $@.0 $(OBJS) $(LDFLAGS) \
		-Wl,-soname=`basename $@`.0

clean:
	$(RM) $(OBJS) libiniparser.a libiniparser.so*

veryclean:
	$(RM) $(OBJS) libiniparser.a libiniparser.so*
	rm -rf ./html ; mkdir html
	cd test ; $(MAKE) veryclean

docs:
	@(cd doc ; $(MAKE))
	
check:
	@(cd test ; $(MAKE))

install:	libiniparser.a libiniparser.so.0
	cp libiniparser.a libiniparser.so.0 $(DESTDIR)/usr/local/lib
	cp src/iniparser.h /usr/local/include
	cp src/dictionary.h /usr/local/include
	ldconfig
