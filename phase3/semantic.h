#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "hash.h"
#include "semantic.h"
struct AstNode *ast;
static int intType;
struct StackNode{
	int flag,index;
};
struct Stack{
	struct StackNode *ele;
	int num,cap;
};
static struct Stack typeStack,nameStack;
static void doubleStack(struct Stack *s);
static void addType(char *s,void *bind,int flag);
static void addName(char *s,void *bind,int flag);
static void popType(int flag);
static void popName(int flag);
static int hasType(char *s,int flag);
static int hasName(char *s,int flag);
static void *getTypeHash(char *s);
static void *getNameHash(char *s);
static void halt(void);
static int canConvert(struct AstNode *a,void *t);
static int sameType(struct AstNode *a,struct AstNode *b);
static int charToInt(char c);
static void conToChar(char *s);
static void conToStr(char *s);
static void addAno(struct AstNode *ast,struct AstNode *t);
static void makeInt(struct AstNode *ast);
static void checkInit(struct AstNode *type,struct AstNode *init);

#endif
