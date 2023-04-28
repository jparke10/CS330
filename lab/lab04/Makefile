#
# CIS330: Lab 3
#
# Makefile to build libraries and test applications.
#

CC=gcc
AR=ar

CFLAGS=-g -O2 -I./include -L./lib
# rpath for linker to recognize the lab4 lib
LIBS=-Wl,-rpath=./lib/ -llab4 -lm

all: lab4_dyn

obj:
	mkdir -p obj

lib:
	mkdir -p lib

# fPIC on libraries for position independent code
obj/stats.o: src/stats.c include/stats.h obj
	$(CC) $(CFLAGS) -c -o $@ $< -fPIC

obj/ohno.o: src/ohno.c include/ohno.h obj
	$(CC) $(CFLAGS) -c -o $@ $< -fPIC

# lib/liblab4.a: obj/stats.o obj/ohno.o lib
# 	$(AR) rc lib/liblab4.a obj/stats.o obj/ohno.o

# I couldn't figure out why only obj/stats.o prerequisite was being
# passed in so I had to hardcode ohno.o. Would appreciate help with
# this
lib/liblab4.so: obj/stats.o obj/ohno.o lib
	$(CC) -shared -o $@ $< obj/ohno.o

lab4_dyn: src/lab4.c lib/liblab4.so lib
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm lab4_dyn lib/liblab4.so obj/ohno.o obj/stats.o
	rmdir obj
	rmdir lib
