#ifndef _LALR_H_
#define _LALR_H_
#include <stdio.h>
#include <string.h>
#define LR_STR_LEN 30
#define LR_SYM_NUM 100
static char terminals[LR_SYM_NUM][LR_STR_LEN],nonterminals[LR_SYM_NUM][LR_STR_LEN],s[LR_STR_LEN];
static int terNum,nonNum,curLine,nonBegins[LR_SYM_NUM],stateNum;
struct LRrule{
	int non,items[20][2],num;
};
static struct LRrule rules[LR_SYM_NUM * 4];
static int findTer(char *);
static int findNon(char *);
static void init();
struct Item{
	int rule,ptr;
};
struct ItemNew{
	int rule,ptr,ter;
}
struct SetOfItems{
	struct Item ele[600];
	int num;
};
struct SetOfItemsNew{
	struct ItemNew ele[600];
	
}
static struct SetOfItems state[1000];
static struct SetOfItems closure(struct SetOfItems);
static int nonAfterDot(struct Item);
static struct SetOfItems GOTO(struct SetOfItems,int,int);
static void getStates(void);
static int findItem(struct SetOfItems);
static void getCores(void);
#endif
