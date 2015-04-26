#ifndef _HASH_H_
#define _HASH_H_
#include <stdlib.h>
#include <string.h>
#define HASH_SIZE 10007
struct Hash{
	char *name;
	void *bind;
	struct Symbol{
		char *name;
		struct Symbol *next;
	} *sym;
	struct Hash *next;
};
static struct Hash *hashTable[HASH_SIZE];
static struct Symbol *symTable[HASH_SIZE];
static int hash(char *s){
	char *t;
	int ret = 0;
	for (t = s;*t;++t)
		ret = ret * 65599 + *t;
	return ret % HASH_SIZE;
}
static struct Symbol *makeSymbol(char *s,struct Symbol *next){
	struct Symbol *ret = malloc(sizeof *ret);
	ret->name = s;
	ret->next = next;
	return ret;
}
static struct Hash *makeHash(char *s,void *bind,struct Symbol *sym,struct Hash *next){
	struct Hash *ret = malloc(sizeof *ret);
	ret->name = s;
	ret->bind = bind;
	ret->sym = sym;
	ret->next = next;
	return ret;
}
static struct Symbol *getSymbol(char *s,int flag){
	int i = hash(s);
	struct Symbol *sym;
	for (sym = symTable[i];sym != NULL;sym = sym->next)
		if (strcmp(sym->name,s) == 0) return sym;
	if (flag){
		symTable[i] = makeSymbol(s,symTable[i]);
		return symTable[i];
	}else{
		return NULL;
	}
}
void pushHash(char *s,void *bind){
	struct Symbol *sym = getSymbol(s,1);
	int i = hash(s);
	hashTable[i] = makeHash(s,bind,sym,hashTable[i]);
}
void popHash(char *s){
	int i = hash(s);
	struct Hash *tmp = hashTable[i];
	hashTable[i] = tmp->next;
	free(tmp);
}
void *getHash(char *s){
	struct Symbol* sym = getSymbol(s,0);
	int i = hash(s);
	struct Hash *t;
	for (t = hashTable[i];t != NULL;t = t->next)
		if (t->sym == sym) return t->bind;
	return NULL;
}
#endif
