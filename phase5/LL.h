#ifndef _LL_H_
#define _LL_H_
#include <stdio.h>
#include <string.h>
#define LL_STR_LEN 40
#define LL_SYM_NUM 200
static char terminals[LL_SYM_NUM][LL_STR_LEN],nonterminals[LL_SYM_NUM][LL_STR_LEN],s[LL_STR_LEN];
static int terNum,nonNum,curLine,nonBegins[LL_SYM_NUM];
struct LLrule{
	int non,items[20][2],num;
};
static struct LLrule rules[LL_SYM_NUM * 4];
static int findTer(char *);
static int findNon(char *);
static void init(void);
struct setType{
	int have[LL_SYM_NUM],visited;
};
struct setType firstSet[2][LL_SYM_NUM];
static void getFirst(void);
static struct setType first(int,int);
struct setType followSet[LL_SYM_NUM];
static void getFollow(void);
static struct setType first1(int,int);
static void makeTable(void);
static int M[LL_SYM_NUM][LL_SYM_NUM];
#endif
