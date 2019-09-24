
FLAGS = -O3

all: rmserr.exe

rmserr.exe: rmserr.o
	gcc $(FLAGS) -o $@ $^ -lm
	mv $@ ../bin
	
%.o: %.c
	gcc -c $(FLAGS) $<	
	
clean:
	rm *.o *.exe	
