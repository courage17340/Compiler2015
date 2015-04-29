#include "semantic.h"
static struct AstNode *ast;
static int intType,charType,voidType,pterType;
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

static void *getTypeHash(char *s){
	return getHash(typeHash,s);
}
static void *getNameHash(char *s){
	return getHash(nameHash,s);
}
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
static int canConvert(void *a,void *b){
	struct AstNode *p,*q;
	if (a == b) return 0;
	if (a == (void *)&voidType || b == (void *)&voidType) return 0;
	if (a == (void *)&intType || a == (void *)&charType || a == (void *)pterType){
		if (b == (void *)&intType || b == (void *)&charType || b == (void *)pterType) return 1;
		q = (struct AstNode *)b;
		return q->type == INTETYPE || q->type == CHARTYPE || q->type == PTERTYPE || q->type == ARRATYPE;
	}else{
		p = (struct AstNode *)a;
		if (b == (void *)&intType || b == (void *)&charType || b == (void *)pterType)
			return p->type == INTETYPE || p->type == CHARTYPE || p->type == PTERTYPE || p->type == ARRATYPE;
		q = (struct AstNode *)b;
		if (p->type == INTETYPE || p->type == CHARTYPE || p->type == PTERTYPE || p->type == ARRATYPE)
			return q->type == INTETYPE || q->type == CHARTYPE || q->type == PTERTYPE || q->type == ARRATYPE;
		return p->type == q->type && getTypeHash(p->c[0].data) == getTypeHash(q->c[0].data);
	}
}

static void astCheck(struct AstNode *ast,int isInLoop,void *retType){
	//flag for scopes
	static int flag = 0;
	int i;
	ast->lValue = 0;
	ast->constant = 0;
	if (ast->type == ROOT){
		for (i = 0;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,retType);
	}else if (ast->type == DECL){
		for (i = 0;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,retType);
	}else if (ast->type == FUNCDECL){
		if (hasName(ast->c[1].data,flag)) halt();
		addName(ast->c[1].data,(void *)ast,flag);
		astCheck(&ast->c[0],isInLoop,retType);
		ast->retType = ast->c[0].retType;
//		++flag;
		astCheck(&ast->c[2],isInLoop,retType);
		astCheck(&ast->c[3],isInLoop,ast->retType);
//		popType(flag);
//		popName(flag);
	}else if (ast->type == STRUDECL){
		//never
	}else if (ast->type == UNIODECL){
		//never
	}else if (ast->type == VARIDECL){
		astCheck(&ast->c[0],isInLoop,retType);
		for (i = 1;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,retType);
	}else if (ast->type == TYPE){
		//never
	}else if (ast->type == BASITYPE){
		//never
	}else if (ast->type == INTETYPE){
		ast->retType = (void *)&intType;
	}else if (ast->type == CHARTYPE){
		ast->retType = (void *)&charType;
	}else if (ast->type == VOIDTYPE){
		ast->retType = (void *)&voidType;
	}else if (ast->type == STRUTYPE){
		//TODO
	}else if (ast->type == UNIOTYPE){
		//TODO
	}else if (ast->type == PTERTYPE){
		ast->retType = (void *)ast;
		astCheck(&ast->c[0],isInLoop,retType);
	}else if (ast->type == ARRATYPE){
		ast->retType = (void *)ast;
		astCheck(&ast->c[0],isInLoop,retType);
		astCheck(&ast->c[1],isInLoop,retType);
		if (!ast->c[1].constant) halt();
	}else if (ast->type == STMT){
		//never
	}else if (ast->type == BREASTMT){
		if (!isInLoop) halt();
	}else if (ast->type == CONTSTMT){
		if (!isInLoop) halt();
	}else if (ast->type == IFTESTMT){
		astCheck(&ast->c[0],isInLoop,retType);
		if (!canConvert(ast->c[0].retType,(void *)&intType)) halt();
		astCheck(&ast->c[1],isInLoop,retType);
		astCheck(&ast->c[2],isInLoop,retType);
	}else if (ast->type == FORRLOOP){
		astCheck(&ast->c[0],isInLoop,retType);
		astCheck(&ast->c[1],isInLoop,retType);
		if (!canConvert(ast->c[1].retType,(void *)&intType)) halt();
		astCheck(&ast->c[2],isInLoop,retType);
		astCheck(&ast->c[3],1,retType);
	}else if (ast->type == WHILLOOP){
		astCheck(&ast->c[0],isInLoop,retType);
		if (!canConvert(ast->c[0].retType,(void *)&intType)) halt();
		astCheck(&ast->c[1],1,retType);
	}else if (ast->type == EXPRSTMT){
		astCheck(&ast->c[0],isInLoop,retType);
	}else if (ast->type == RETNSTMT){
		astCheck(&ast->c[0],isInLoop,retType);
		if (!canConvert(ast->c[0].retType,retType)) halt();
	}else if (ast->type == COMPSTMT){
		++flag;
		for (i = 0;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,retType);
		popType(flag);
		popName(flag);
		--flag;
	}else if (ast->type == EXPR){
		//never
	}else if (ast->type == EMPTEXPR){
		ast->retType = (void *)&voidType;
	}else if (ast->type == BINAEXPR){
		//TODO
	}else if (ast->type == UNAREXPR){
		//TODO
	}else if (ast->type == SZOFEXPR){
		astCheck(&ast->c[0],isInLoop,retType);
		if (ast->c[0].retType == (void *)&voidType) halt();
		ast->constant = 1;
		ast->retType = (void *)&intType;
	}else if (ast->type == CASTEXPR){
		astCheck(&ast->c[0],isInLoop,retType);
		astCheck(&ast->c[1],isInLoop,retType);
		if (!canConvert(ast->c[1].retType,ast->c[0].retType)) halt();
		ast->retType = ast->c[0].retType;
		if (ast->c[1].constant) ast->constant = 1;
	}else if (ast->type == PTERACSS){
		//TODO
	}else if (ast->type == RECOACSS){
		//TODO
	}else if (ast->type == SELFINCR){
		astCheck(&ast->c[0],isInLoop,retType);
		if (!ast->c[0].lValue) halt();
		if (!canConvert(ast->c[0].retType,(void *)&intType)) halt();
		ast->retType == (void *)&intType;
	}else if (ast->type == SELFDECR){
		astCheck(&ast->c[0],isInLoop,retType);
		if (!ast->c[0].lValue) halt();
		if (!canConvert(ast->c[0].retType,(void *)&intType)) halt();
		ast->retType == (void *)&intType;
	}else if (ast->type == ARRAACSS){
		
		//TODO
	}else if (ast->type == FUNCCALL){
		//TODO
	}else if (ast->type == IDEN){
		if (getNameHash(ast->data) == NULL) halt();
		ast->retType = getNameHash(ast->data);
		ast->lValue = 1;
	}else if (ast->type == INTECONS){
		//TODO
		ast->constant = 1;
		ast->retType = (void *)&intType;
	}else if (ast->type == CHARCONS){
		//TODO
		//deal with \ddd \xff etc.
		ast->constant = 1;
		ast->retType = (void *)&charType;
	}else if (ast->type == STRICONS){
		//TODO
		//deal with \ddd \xff etc.
		ast->constant = 1;
		ast->retType = (void *)&pterType;
	}else if (ast->type == PARA){
		//TODO
	}else if (ast->type == TYPESPEC){
		for (i = 0;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,retType);
		//TODO
	}else if (ast->type == DATAFILD){
		//TODO
	}else if (ast->type == INIT){
		//TODO
	}else if (ast->type == FUNCPARA){
		//TODO
	}else if (ast->type == VARI){
		astCheck(&ast->c[0],isInLoop,retType);
		if (flag && hasName(ast->c[1].data,flag)) halt();
		if (!flag && hasName(ast->c[1].data,flag)){
			struct AstNode *t = getNameHash(ast->c[1].data);
			if (t->retType != ast->c[0].retType) halt();//TODO
			if (t->num == 3 && ast->num == 3) halt();
			if (t->num == 2) addName(ast->c[1].data,(void *)ast,flag);
		}else{
		
		}
		//TODO
	}else{
		//never
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
