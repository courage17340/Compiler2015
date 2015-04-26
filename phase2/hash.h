#ifndef _HASH_H_
#define _HASH_H_
#include <stdlib.h>
#include <string.h>
static int SIZE = 109;
struct node{
	char *key;
	void *bind;
	struct node *next;
};
static struct node *table[SIZE];
static unsigned int hash(char *s0){
	unsigned int ret = 0;
	char *s;
	for (s = s0;*s;++s) ret = ret * 65599 + *s;//natural exceed
	return ret;
}
static node *getNode(char *key,void *bind,struct node *next){
	struct node *b = malloc(sizeof(*b));
	b->key = key;
	b->bind = bind;
	b->next = next;
	return b;
}
void insert(char *key,void *bind){
	int i = hash(key) % SIZE;
	table[i] = getNode(key,bind,table[i]);
}
void *find(char *key){
	int i = hash(key) % SIZE;
	struct node *b;
	for (b = table[i];b != NULL;b = b->next)
		if (strcmp(b->key,key) == 0) return b->bind;
	return NULL;
}
void pop(char *key){
	int i = hash(key) % SIZE;
	struct node *t = table[i];
	if (t != NULL){
		table[i] = t->next;
		free(t);
	}
}
#endif
