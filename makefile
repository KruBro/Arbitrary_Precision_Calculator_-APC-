OBJ = $(patsubst %.c, %.o, $(wildcard *.c))

calculator: $(OBJ)
	gcc -o $@ $^

clean:
	rm -f *.o calculator

