#Make cheatsheet
#out.o: src.c src.h
#  $@   # "out.o" (target)
#  $<   # "src.c" (first prerequisite)
#  $^   # "src.c src.h" (all prerequisites)

#gcc flags cheatsheet
#-I($PATH): look for headers here (besides standard dirs). 
#-L($PATH): look for libfiles here (besides standard dirs). Only exe's need libfiles.

MAIN= tester-bin2su_2d
OBJS= bin2su_2d.o atopkge.o docpkge.o getpars.o 
MOBJ= $(MAIN).o

all: $(MAIN).exe


$(MAIN).exe: $(MOBJ) $(OBJS)
	gcc -o $@ $^ 

%.o: %.c
	gcc -c $< 


clean:
	rm *.o *.exe
