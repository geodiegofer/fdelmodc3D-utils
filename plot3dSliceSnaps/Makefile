#Make cheatsheet
#out.o: src.c src.h
#  $@   # "out.o" (target)
#  $<   # "src.c" (first prerequisite)
#  $^   # "src.c src.h" (all prerequisites)

#gcc flags cheatsheet
#-I($PATH): look for headers here (besides standard dirs). 
#-L($PATH): look for libfiles here (besides standard dirs). Only exe's need libfiles.

## Print stuff
# $(warning MOBJ is $(MOBJ))
CC = gcc
FLAGS = -O3
EXEC = plot3dSliceSnaps.exe
MOBJ = plot3dSliceSnaps.o
OBJS = 


all: $(EXEC)

# Executable
$(EXEC): $(MOBJ) $(OBJS)
	$(CC) $(FLAGS) -o $@ $^
	cp $@ ../bin

# Objects
%.o: %.c
	$(CC) $(FLAGS) -c $< 

clean:
	rm *.o *.exe
	
PHONY: clean



