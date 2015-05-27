#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_
struct AstNode *ast;
struct StackNode{
	int flag,index;
};
struct Stack{
	struct StackNode *ele;
	int num,cap;
};

void semanticCheck(char *);

#endif
