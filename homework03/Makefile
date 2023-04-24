cc = gcc

sources = main.c mmio.c
objects = $(addsuffix .o, $(basename $(sources)))

flags = -g -std=c11 

target = spmv

all: $(target) 

$(target) : $(objects)
	$(cc) $(flags) -o $(target) $(objects)

%.o : %.c
	$(cc) -c $(flags) $< -o $@

clean:
	rm -rf $(target) $(objects) 
