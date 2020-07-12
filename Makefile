all: project

project: infixeval.o stack.o cstack.o num.o
	cc infixeval.o stack.o cstack.o num.o -o project

infixeval.o: infixeval.c stack.h cstack.h 
	cc -c infixeval.c

num.o: num.c num.h
	cc -c num.c

stack.o: stack.c stack.h  
	cc -c stack.c

cstack.o: cstack.c cstack.h
	cc -c cstack.c

clean:
	rm -rf *.o project
