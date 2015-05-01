#ifndef _HASH_H_
#define _HASH_H_
#include <stdlib.h>
#include <string.h>
#define HASH_SIZE 10007
struct Hash{
	char *name;
	void *bind;
	int flag;
	struct Symbol{
		char *name;
		struct Symbol *next;
	} *sym;
	struct Hash *next;
};
struct Hash *typeHash[HASH_SIZE],*nameHash[HASH_SIZE];
static struct Symbol *symTable[HASH_SIZE];
static int hash(char *);
static struct Symbol *makeSymbol(char *,struct Symbol *);
static struct Hash *makeHash(char *,void *,struct Symbol *,struct Hash *,int);
struct Symbol *getSymbol(char *);
int pushHash(struct Hash **,char *,void *,int);
void popHash(struct Hash **,int);
void *getHash(struct Hash **,char *);
int hasHash(struct Hash **,char *,int);
//int getFlagHash(char *);
void clearAll(void);
#endif
