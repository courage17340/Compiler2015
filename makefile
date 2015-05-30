all : translate

translate : translate.h translate.c parser.h parser.c hash.h hash.c semantic.h semantic.c removeComments.h removeComments.o \
	split.h split.o tokens.h tokens.o ir.h ir.c grammar.h
	gcc -Wall -g translate.c ir.c semantic.c parser.c hash.c removeComments.o split.o tokens.o -o translate
	mkdir -p bin
	cp translate bin/translate
removeComments.o : removeComments.h removeComments.c
	gcc -c removeComments.c
split.o : split.h split.c
	gcc -c split.c
tokens.o : tokens.h tokens.c
	gcc -c tokens.c
clean :
	rm -f removeComments.o split.o tokens.o translate
