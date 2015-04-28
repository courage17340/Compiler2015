#include "hash.h"
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

static struct Symbol *getSymbol(char *s){
	int i = hash(s);
	struct Symbol *sym;
	for (sym = symTable[i];sym != NULL;sym = sym->next)
		if (strcmp(sym->name,s) == 0) return sym;
	symTable[i] = makeSymbol(s,symTable[i]);
	return symTable[i];
}

int pushHash(struct Hash **h,char *s,void *bind){
	struct Symbol *sym = getSymbol(s);
	int i = hash(s);
	h[i] = makeHash(s,bind,sym,h[i]);
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
