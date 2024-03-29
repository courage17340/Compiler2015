#include <stdlib.h>
#include <string.h>
#include "hash.h"
//======local function declarations======

static int hash(char *);
static struct Symbol *makeSymbol(char *,struct Symbol *);
static struct Hash *makeHash(char *,struct AstNode *,struct Symbol *,struct Hash *,int);

//======local variables======
static struct Symbol *symTable[HASH_SIZE];

//======main======

static int hash(char *s){
	char *t;
	int ret = 0;
	for (t = s;*t;++t)
		ret = ret * 65599 + *t;
	ret %= HASH_SIZE;
	if (ret < 0) ret += HASH_SIZE;
	return ret;
}

static struct Symbol *makeSymbol(char *s,struct Symbol *next){
	struct Symbol *ret = malloc(sizeof *ret);
	ret->name = s;
	ret->next = next;
	ret->count = 0;
	return ret;
}

static struct Hash *makeHash(char *s,struct AstNode *bind,struct Symbol *sym,struct Hash *next,int flag){
	struct Hash *ret = malloc(sizeof *ret);
	ret->name = s;
	ret->bind = bind;
	ret->sym = sym;
	ret->next = next;
	ret->flag = flag;
	sym->count++;
	ret->renamingLabel = sym->count;
	if (bind != NULL) bind->renamingLabel = sym->count;
	return ret;
}

struct Symbol *getSymbol(char *s){
	int i = hash(s);
	struct Symbol *sym;
	for (sym = symTable[i];sym != NULL;sym = sym->next)
		if (strcmp(sym->name,s) == 0) return sym;
	symTable[i] = makeSymbol(s,symTable[i]);
	return symTable[i];
}

int pushHash(struct Hash **h,char *s,struct AstNode *bind,int flag){
	struct Symbol *sym = getSymbol(s);
	int i = hash(s);
	h[i] = makeHash(s,bind,sym,h[i],flag);
	return i;
}

void popHash(struct Hash **h,int i){
	struct Hash *tmp = h[i];
	h[i] = h[i]->next;
	free(tmp);
}

void *getHash(struct Hash **h,char *s){
	struct Symbol* sym = getSymbol(s);
	int i = hash(s);
	struct Hash *t;
	for (t = h[i];t != NULL;t = t->next)
		if (t->sym == sym) return t->bind;
	return NULL;
}

int hasHash(struct Hash **h,char *s,int flag){
	struct Symbol* sym = getSymbol(s);
	int i = hash(s);
	struct Hash *t;
	for (t = h[i];t != NULL;t = t->next)
		if (t->flag == flag && t->sym == sym) return 1;
	return 0;
}
/*
int getFlagHash(char *s){
	struct Symbol* sym = getSymbol(s);
	int i = hash(s);
	struct Hash *t;
	for (t = h[i];t != NULL;t = t->next)
		if (t->sym == sym) return t->flag;
	return -1;
}
*/
void clearAll(void){
	struct Hash *h;
	struct Symbol *s;
	void *t;
	int i;
	for (i = 0;i < HASH_SIZE;++i){
		h = typeHash[i];
		while (h != NULL){
			t = h;
			h = h->next;
			free(t);
		}
		h = nameHash[i];
		while (h != NULL){
			t = h;
			h = h->next;
			free(t);
		}
		s = symTable[i];
		while (s != NULL){
			t = s;
			s = s->next;
			free(t);
		}
	}
}

int hashCount(struct Hash **h,char *s){
	struct Symbol* sym = getSymbol(s);
	int i = hash(s),ret = 0;
	struct Hash *t;
	for (t = h[i];t != NULL;t = t->next)
		if (t->sym == sym) ++ret;
	return ret;
}
