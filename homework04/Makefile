CC=gcc
sources = $(wildcard *.c)
objects = $(addsuffix .o, $(basename $(sources)))
flags = -g -W -Wall -std=c11 -DDEBUG=0 -DTEST=0
target = bfs 


$(target) : $(objects)
	$(CC) -o $(target) $(objects)

%.o : %.c
	$(CC) -c $(flags) $< -o $@
clean :
	rm $(target) $(objects)
