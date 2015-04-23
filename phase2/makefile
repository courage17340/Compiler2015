test : parser.h parser.c removeComments.h removeComments.o split.h split.o tokens.h tokens.o test.c
	gcc -g parser.c removeComments.o split.o tokens.o test.c -o test
removeComments.o : removeComments.h removeComments.c
	gcc -c removeComments.c
split.o : split.h split.c
	gcc -c split.c
tokens.o : tokens.h tokens.c
	gcc -c tokens.c
clean :
	del *.o