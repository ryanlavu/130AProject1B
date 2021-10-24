
project1b: dictionary.o hash24.o main.o
	gcc -o project1b dictionary.o hash24.o main.o -lstdc++ -lm -ldl

clean:
	$(RM) project1b dictionary.o hash24.o main.o
