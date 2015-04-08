parser : parser.h parser.c removeComments.h removeComments.o split.h split.o tokens.h tokens.o
	gcc parser.c removeComments.o split.o tokens.o -o parser
removeComments.o : removeComments.h removeComments.c
	gcc -c removeComments.c
split.o : split.h split.c
	gcc -c split.c
tokens.o : tokens.h tokens.c
	gcc -c tokens.c
