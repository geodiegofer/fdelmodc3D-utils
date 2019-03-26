#Make cheatsheet
#out.o: src.c src.h
#  $@   # "out.o" (target)
#  $<   # "src.c" (first prerequisite)
#  $^   # "src.c src.h" (all prerequisites)

#gcc flags cheatsheet
#-I($PATH): look for headers here (besides standard dirs). 
#-L($PATH): look for libfiles here (besides standard dirs). Only exe's need libfiles.

MAIN= tester-bin2su_2d
OBJS= bin2su_2d


all: $(MAIN).exe


$(MAIN).exe: $(MAIN).o $(OBJS).o
	gcc -o $@ $^ -L$(CWPROOT)/lib -lsu -lpar -lcwp

%.o: %.c
	gcc -c $< -I$(CWPROOT)/include




clean:
	rm *.o *.exe
