test : split.o removeComments.o test.c
	gcc split.o removeComments.o test.c -o test
split.o : split.h split.c
	gcc -c split.c
removeComments.o : removeComments.h removeComments.c
	gcc -c removeComments.c