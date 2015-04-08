#ifndef _PARSER_H_
#define _PARSER_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"
//This file mainly constructs the context-free-grammar for C
//The CST is in the form of left-child right-sibling binary tree
struct node{
	char *data,*flag;
	struct node *c;
	int num;//num of children
};
static int error = 0;
static struct token *makeList(char *);
static struct token *list;
struct node *parse(char *);
static int M[200][200],listSize,nonNum,terNum,ruleNum;
static char terminals[200][40],nonterminals[200][40];
struct ruleType{
	int non,num,items[15][2];
};
static struct ruleType rules[300];
static void init(void);
static int findTer(char *);
static int findNon(char *);
static void build(struct node *,int *,int,int);
static int equal(struct token,char *);
static struct node *getNode(void);
static int getType(struct token);
static void print(struct node *,int);
static void del(struct node *);
#endif
