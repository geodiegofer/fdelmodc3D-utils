EXEC=mysurange.exe
MOBJ=mysurange.o
OBJS=

all: $(EXEC)

$(EXEC): $(MOBJ) $(OBJS)
	gcc -o $@ $^
	cp $@ ../bin
	
%.o: %.c
	gcc -c $<
	
clean:
	rm *.o *.exe | true
