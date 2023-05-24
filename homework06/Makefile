sources = $(wildcard *.cc)
objects = $(addsuffix .o, $(basename $(sources)))
flags = -g -W -Wall -std=c++14 -DDEBUG=1 -DTEST=1
target = cipher 


$(target) : $(objects)
	g++-13 -o $(target) $(objects)

%.o : %.cc
	g++-13 -c $(flags) $< -o $@
clean :
	rm $(target) $(objects)
