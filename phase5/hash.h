#ifndef _HASH_H_
#define _HASH_H_
#define HASH_SIZE 10007
#include "parser.h"
struct Hash{
	char *name;
	struct AstNode *bind;
	int flag,renamingLabel;
	struct Symbol{
		char *name;
		struct Symbol *next;
		int count;
	} *sym;
	struct Hash *next;
};
struct Hash *typeHash[HASH_SIZE],*nameHash[HASH_SIZE];
struct Symbol *getSymbol(char *);
int pushHash(struct Hash **,char *,struct AstNode *,int);
void popHash(struct Hash **,int);
void *getHash(struct Hash **,char *);
int hasHash(struct Hash **,char *,int);
//int getFlagHash(char *);
void clearAll(void);
int hashCount(struct Hash **,char *);
#endif
