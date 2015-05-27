#ifndef _HASH_H_
#define _HASH_H_
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
struct Symbol *getSymbol(char *);
int pushHash(struct Hash **,char *,void *,int);
void popHash(struct Hash **,int);
void *getHash(struct Hash **,char *);
int hasHash(struct Hash **,char *,int);
//int getFlagHash(char *);
void clearAll(void);
#endif
