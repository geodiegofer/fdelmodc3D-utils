#Make cheatsheet
#out.o: src.c src.h
#  $@   # "out.o" (target)
#  $<   # "src.c" (first prerequisite)
#  $^   # "src.c src.h" (all prerequisites)

#gcc flags cheatsheet
#-I($PATH): look for headers here (besides standard dirs). 
#-L($PATH): look for libfiles here (besides standard dirs). Only exe's need libfiles.

MAIN= bin2su
OBJS= $(MAIN).o


all: $(MAIN).exe


$(MAIN).exe: $(OBJS)
	gcc -o $@ $^ -L$(CWPROOT)/lib -lsu -lpar -lcwp
	cp $@ ../bin

%.o: %.c
	gcc -c $< -I$(CWPROOT)/include

clean:
	rm *.o *.exe
