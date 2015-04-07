#ifndef _LR1_H_
#define _LR1_H_
#include <stdio.h>
#include <string.h>
#define LR_STR_LEN 30
#define LR_SYM_NUM 100
static char terminals[LR_SYM_NUM][LR_STR_LEN],nonterminals[LR_SYM_NUM][LR_STR_LEN],s[LR_STR_LEN];
static int terNum,nonNum,curLine,nonBegins[LR_SYM_NUM];
struct LRrule{
	int non,items[20][2],num;
};
static struct LRrule rules[LR_SYM_NUM * 4];
static int findTer(char *);
static int findNon(char *);
static void init();

#endif
