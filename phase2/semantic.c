#include "semantic.h"
static struct AstNode *ast;
static int intType,charType;
struct StackNode{
	int flag,index;
};
struct Stack{
	struct StackNode *ele;
	int num,cap;
};
static struct Stack typeStack,nameStack;
static void doubleStack(struct Stack *s){
	int i;
	s->cap *= 2;
	struct StackNode *tmp = (struct StackNode *)malloc(s->cap * sizeof(struct StackNode));
	for (i = 0;i < s->num;++i) tmp[i] = s->ele[i];
	free(s->ele);
	s->ele = tmp;
}
static void addtype(char *s,void *bind,int flag){
	if (typeStack.num == typeStack.cap) doubleStack(&typeStack);
	++typeStack.num;
	typeStack.ele[typeStack.num - 1].flag = flag;
	typeStack.ele[typeStack.num - 1].index = pushHash(typeHash,s,bind,flag);
}
static void addName(char *s,void *bind,int flag){
	if (nameStack.num == nameStack.cap) doubleStack(&nameStack);
	++nameStack.num;
	nameStack.ele[nameStack.num - 1].flag = flag;
	nameStack.ele[nameStack.num - 1].index = pushHash(nameHash,s,bind,flag);
}
static void popType(int flag){
	while (typeStack.num && typeStack.ele[typeStack.num - 1].flag == flag){
		int i = typeStack.ele[typeStack.num - 1].index;
		popHash(typeHash,i);
		--typeStack.num;
	}
}
static void popName(int flag){
	while (nameStack.num && nameStack.ele[nameStack.num - 1].flag == flag){
		int i = nameStack.ele[nameStack.num - 1].index;
		popHash(nameHash,i);
		--nameStack.num;
	}
}
static int hasType(char *s,int flag){
	return hasHash(typeHash,s,flag);
}
static int hasName(char *s,int flag){
	return hasHash(nameHash,s,flag);
}
/*
static void *getType(char *s){
	return getHash(typeHash,s);
}
static void *getName(char *s){
	return getHash(nameHash,s);
}
*/
static void readInput(char *s){
	int n = -1,c = getchar();
	while (c != EOF){
		s[++n] = c;
		c = getchar();
	}
	s[++n] = 0;
}
static void halt(void){
	clearAll();
	astDel(ast);
	free(ast);
	free(list);
	free(typeStack.ele);
	free(nameStack.ele);
	exit(1);
}
static void astCheck(struct AstNode *ast,int isInLoop,void *retType){
	//flag for scopes
	static int flag = 0;
	int i;
	ast->lValue = 0;
	ast->constant = 0;
	if (ast->type == ROOT){
		for (i = 0;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,NULL);
	}else if (ast->type == DECL){
		for (i = 0;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,NULL);
	}else if (ast->type == FUNCDECL){
		if (hasName(ast->c[1].data,flag)) halt();
		addName(ast->c[1].data,(void *)ast,flag);
		astCheck(&ast->c[0],isInLoop,NULL);
		ast->retType = ast->c[0].retType;
		++flag;
		astCheck(&ast->c[2],isInLoop,NULL);
		astCheck(&ast->c[3],isInLoop,ast->retType);
		popType(flag);
		popName(flag);
	}else if (ast->type == STRUDECL){
		//never
	}else if (ast->type == UNIODECL){
		//never
	}else if (ast->type == VARIDECL){
		astCheck(&ast->c[0],isInLoop,NULL);
		for (i = 1;i < ast->num;++i)
			if (ast->c[i].type == IDEN){
				if (flag && hasName(ast->c[i].data,flag)) halt;
			}
	}
}

int main(int args,char **argv){
	struct node *root;
	static char s[1000010];
	int flag,size;
	freopen(argv[1],"r",stdin);
	flag = 1;
	readInput(s);
	ast = makeAst(s,&flag,&size,&root);
	if (!flag){
		return 1;
	}else{
		cstDel(root);
		free(root);
	}
	typeStack.ele = (struct StackNode *)malloc(sizeof(struct StackNode));
	typeStack.num = 0;
	typeStack.cap = 1;
	nameStack.ele = (struct StackNode *)malloc(sizeof(struct StackNode));
	nameStack.num = 0;
	nameStack.cap = 1;
//	astPrint(NULL,ast,0);
	astCheck(ast,0,NULL);
//	semantic(ast);
	clearAll();
	astDel(ast);
	free(ast);
	free(list);
	free(typeStack.ele);
	free(nameStack.ele);
	return 0;
//	if (flag) return 0;else return 1;
}
