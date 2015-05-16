ir : parser.h parser.c hash.h hash.c semantic.h semantic.c removeComments.h removeComments.o split.h split.o tokens.h tokens.o ir.h ir.c
	gcc -Wall -g ir.c semantic.c parser.c hash.c removeComments.o split.o tokens.o -o ir
removeComments.o : removeComments.h removeComments.c
	gcc -Wall -c removeComments.c
split.o : split.h split.c
	gcc -Wall -c split.c
tokens.o : tokens.h tokens.c
	gcc -Wall -c tokens.c
clean :
	rm -f removeComments.o split.o tokens.o ir
