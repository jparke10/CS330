CC=gcc-13
sources = $(wildcard *.c)
objects = $(addsuffix .o, $(basename $(sources)))
flags = -g -W -Wall -std=c11 -DDEBUG=1 -DTEST=0
target = bfs 


$(target) : $(objects)
	gcc -o $(target) $(objects)

%.o : %.c
	gcc -c $(flags) $< -o $@
clean :
	rm $(target) $(objects)
