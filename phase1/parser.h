#ifndef _PARSER_H_
#define _PARSER_H
#include <string.h>
#include <stdlib.h>
#include "tokens.h"
//This file mainly constructs the context-free-grammar for C
//The CST is in the form of left-child right-sibling binary tree
struct node{
	char *data;
};
static struct token *makeList(char *,int *);
#endif
