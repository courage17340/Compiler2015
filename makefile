semantic : parser.h parser.c hash.h hash.c semantic.h semantic.c removeComments.h removeComments.o split.h split.o tokens.h tokens.o
	gcc -g semantic.c parser.c hash.c removeComments.o split.o tokens.o -o semantic
	mkdir bin
	cp semantic bin/semantic
removeComments.o : removeComments.h removeComments.c
	gcc -c removeComments.c
split.o : split.h split.c
	gcc -c split.c
tokens.o : tokens.h tokens.c
	gcc -c tokens.c
clean :
	rm semantic removeComments.o split.o tokens.o
	rm -rf bin/
