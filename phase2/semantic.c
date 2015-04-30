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
static void addType(char *s,void *bind,int flag){
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

static int sameType(struct AstNode *a,struct AstNode *b){
	if (a->type != b->type) return 0;
	if (a->type == INTETYPE || a->type == CHARTYPE || a->type == VOIDTYPE) return 1;
	if (a->type == ARRATYPE){
		if (!sameType(&a->c[0],&b->c[0])) return 0;
		if (a->c[1].value != b->c[1].value) return 0;
	}else if (a->type == PTERTYPE){
		return sameType(&a->c[0],&b->c[0]);
	}else{
		return strcmp(a->c[0].data,b->c[0].data) == 0;
	}
	return 1;
}

static int charToInt(char c){
	if ('0' <= c && c <= '9') return c - '0';
	if ('a' <= c && c <= 'f') return c - 'a' + 10;
	if ('A' <= c && c <= 'F') return c - 'A' + 10;
	return -1;
}

static void conToChar(char *s){
	int ret = 0,l = strlen(s),i = 0;
	while (i < l){
		ret = 0;
		if (s[i] != '\\'){
			ret = s[i];
		}else{
			++i;
			if (s[i] == 'a'){
				ret = '\a';
			}else if (s[i] == 'b'){
				ret = '\b';
			}else if (s[i] == 'f'){
				ret = '\f';
			}else if (s[i] == 'n'){
				ret = '\n';
			}else if (s[i] == 'r'){
				ret = '\r';
			}else if (s[i] == 't'){
				ret = '\t';
			}else if (s[i] == 'v'){
				ret = '\v';
			}else if (s[i] == '\\'){
				ret = '\\';
			}else if (s[i] == '\''){
				ret = '\'';
			}else if (s[i] == '"'){
				ret = '"';
			}else if ('0' <= s[i] && s[i] <= '7'){
				ret = s[i] - '0';
				if (i + 1 < l && '0' <= s[i + 1] && s[i + 1] <= '7'){
					++i;
					ret = ret * 8 + s[i + 1] - '0';
				}
				if (i + 1 < l && '0' <= s[i + 1] && s[i + 1] <= '7'){
					++i;
					ret = ret * 8 + s[i + 1] - '0';
				}
			}else if (s[i] == 'x'){
				ret = 0;
				++i;
				if (i >= l || charToInt(s[i]) == -1) halt();
				ret = ret * 16 + charToInt(s[i]);
				++i;
				if (i >= l || charToInt(s[i]) == -1) halt();
				ret = ret * 16 + charToInt(s[i]);
			}else{
				ret = s[i];
			}
		}
		++i;
	}
	s[0] = ret;
	s[1] = 0;
}

static void conToStr(char *s){
	int ret = 0,l = strlen(s),i = 0,t = -1;
	while (i < l){
		ret = 0;
		if (s[i] != '\\'){
			ret = s[i];
		}else{
			++i;
			if (s[i] == 'a'){
				ret = '\a';
			}else if (s[i] == 'b'){
				ret = '\b';
			}else if (s[i] == 'f'){
				ret = '\f';
			}else if (s[i] == 'n'){
				ret = '\n';
			}else if (s[i] == 'r'){
				ret = '\r';
			}else if (s[i] == 't'){
				ret = '\t';
			}else if (s[i] == 'v'){
				ret = '\v';
			}else if (s[i] == '\\'){
				ret = '\\';
			}else if (s[i] == '\''){
				ret = '\'';
			}else if (s[i] == '"'){
				ret = '"';
			}else if ('0' <= s[i] && s[i] <= '7'){
				ret = s[i] - '0';
				if (i + 1 < l && '0' <= s[i + 1] && s[i + 1] <= '7'){
					++i;
					ret = ret * 8 + s[i + 1] - '0';
				}
				if (i + 1 < l && '0' <= s[i + 1] && s[i + 1] <= '7'){
					++i;
					ret = ret * 8 + s[i + 1] - '0';
				}
			}else if (s[i] == 'x'){
				ret = 0;
				++i;
				if (i >= l || charToInt(s[i]) == -1) halt();
				ret = ret * 16 + charToInt(s[i]);
				++i;
				if (i >= l || charToInt(s[i]) == -1) halt();
				ret = ret * 16 + charToInt(s[i]);
			}else{
				ret = s[i];
			}
		}
		++i;
		s[++t] = ret;
	}
	s[++t] = 0;
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
		struct AstNode *tmp;
		if (hasType(ast->c[0].data,flag)){
			tmp = getTypeHash(ast->c[0].data);
			if (ast->type != tmp->type) halt();
		}
		if (ast->num > 1){
			if (hasType(ast->c[0].data,flag)){
				if (tmp->num > 1) halt();
			}
			astCheck(&ast->c[1],isInLoop,retType);
			addType(ast->c[0].data,(void *)ast,flag);
		}else{
			if (!hasType(ast->c[0].data,flag)){
				astCheck(&ast->c[1],isInLoop,retType);
				addType(ast->c[0].data,(void *)ast,flag);
			}
		}
	}else if (ast->type == UNIOTYPE){
		struct AstNode *tmp;
		if (hasType(ast->c[0].data,flag)){
			tmp = getTypeHash(ast->c[0].data);
			if (ast->type != tmp->type) halt();
		}
		if (ast->num > 1){
			if (hasType(ast->c[0].data,flag)){
				if (tmp->num > 1) halt();
				addType(ast->c[0].data,(void *)ast,flag);
			}
			astCheck(&ast->c[1]);
		}else{
			if (!hasType(ast->c[0].data,flag)){
				addType(ast->c[0].data,(void *)ast,flag);
			}
		}
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
		void *t;
		struct AstNode *tmp;
		int j;
		astCheck(&ast->c[0],isInLoop,retType);
		t = ast->c[0].retType;
		if (t == (void *)&intType || t == (void *)&charType || t == (void *)&voidType || t == (void *)&pterType) halt();
		tmp = t;
		if (tmp->type != STRUTYPE && tmp->type != UNIOTYPE) halt();
		tmp = getTypeHash(tmp->c[0].data);
		if (tmp->num == 1) halt();
		if (ast->c[1].type != IDEN) halt();
		for (i = 0;i < tmp->num;++i)
			for (j = 2;j < tmp->c[i].num;++j)
				if (strcmp(ast->c[1].data,tmp->c[i].c[j].data) == 0){
					ast->retType = &tmp->c[i].c[j - 1];
					if (tmp->c[i].c[j - 1].type != ARRATYPE) ast->lValue = 1;
					return;
				}
		halt();
	}else if (ast->type == SELFINCR){
		astCheck(&ast->c[0],isInLoop,retType);
		if (!ast->c[0].lValue) halt();
		if (!canConvert(ast->c[0].retType,(void *)&intType)) halt();
		ast->retType == ast->c[0].retType;
	}else if (ast->type == SELFDECR){
		astCheck(&ast->c[0],isInLoop,retType);
		if (!ast->c[0].lValue) halt();
		if (!canConvert(ast->c[0].retType,(void *)&intType)) halt();
		ast->retType == ast->c[0].retType;
	}else if (ast->type == ARRAACSS){
		void *t;
		struct AstNode *tmp;
		astCheck(&ast->c[0],isInLoop,retType);
		astCheck(&ast->c[1],isInLoop,retType);
		if (!canConvert(ast->c[1].retType,(void *)&intType)) halt();
		t = ast->c[0].retType;
		if (t == (void *)&intType || t == (void *)&charType || t == (void *)&voidType) halt();
		if (t == (void *)&pterType){
			if (flag == 0) halt();//int a["11"[0]]; ERROR int f(){int a["11"[0]];} RIGHT
			ast->retType = (void *)&charType;
			ast->constant = 1;
		}
		tmp = t;
		if (tmp->type != ARRATYPE && tmp->type != PTERTYPE) halt();
		ast->retType = tmp->c[0].retType;
		if (tmp->type == ARRATYPE){
			if (tmp->c[0].type != ARRATYPE){
				ast->lValue = 1;
			}
		}else{
			ast->lValue = 1;
		}
	}else if (ast->type == FUNCCALL){
		//TODO
	}else if (ast->type == IDEN){
		struct AstNode *tmp = getNameHash(ast->data);
		if (tmp == NULL) halt();
		ast->retType = tmp;
		if (tmp->type == FUNCDECL) halt();
		ast->lValue = 1;
	}else if (ast->type == INTECONS){
		int t = 0,b,k,l;
		char *s = ast->data;
		l = strlen(s);
		if (s[0] != '0'){
			b = 10;
			for (i = 0;i < l;++i){
				k = charToInt(s[i]);
				if (k == -1 || k > 9) halt();
				t = t * b + k;
			}
		}else if (l > 1 && (s[1] == 'x' || s[1] == 'X')){
			b = 16;
			if (l == 2) halt();
			for (i = 2;i < l;++i){
				k = charToInt(s[i]);
				if (k == -1) halt();
				t = t * b + k;
			}
		}else{
			b = 8;
			for (i = 1;i < l;++i){
				k = charToInt(s[i]);
				if (k == -1 || k > 7) halt();
				t = t * b + k;
			}
		}
		ast->constant = 1;
		ast->retType = (void *)&intType;
		ast->value = t;
	}else if (ast->type == CHARCONS){
		ast->constant = 1;
		conToChar(ast->data);
		ast->retType = (void *)&charType;
	}else if (ast->type == STRICONS){
		ast->constant = 1;
		conToStr(ast->data);
		ast->retType = (void *)&pterType;
	}else if (ast->type == PARA){
		//TODO
	}else if (ast->type == TYPESPEC){
		int n = 0,j,k = -1;
		struct Symbol ** f;
		for (i = 0;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,retType);
		for (i = 0;i < ast->num;++i) n += ast->c[i].num / 2;
		f = malloc(n * sizeof(struct Symbol *));
		for (i = 0;i < ast->num;++i)
			for (j = 2;j < ast->c[i].num;j += 2) f[++k] = getSymbol(ast->c[i].c[j].data);
		for (i = 0;i < n;++i)
			for (j = i + 1;j < n;++j)
				if (f[i] == f[j]){
					free(f);
					halt();
				}
		free(f);
	}else if (ast->type == DATAFILD){
		struct AstNode *tmp;
		astCheck(&ast->c[0],isInLoop,retType);
		if (ast->c[0].type != STRUTYPE && ast->c[0].type != UNIOTYPE) return;
		for (i = 1;i < ast->num;i += 2){
			tmp = &ast->c[i];
			while (tmp->type == ARRATYPE){
				tmp = &tmp->c[0];
			}
			if (tmp->type != PTERTYPE){
				struct AstNode *t = getTypeHash(ast->c[0].data);
				if (t->num == 1) halt();
			}
		}
	}else if (ast->type == INIT){
		//TODO
	}else if (ast->type == FUNCPARA){
		//TODO
	}else if (ast->type == VARI){
		astCheck(&ast->c[0],isInLoop,retType);
		if (ast->c[0].type == VOIDTYPE) halt();
		if (flag && hasName(ast->c[1].data,flag)) halt();
		if (!flag && hasName(ast->c[1].data,flag)){
			struct AstNode *t = getNameHash(ast->c[1].data);
			if (t->type == FUNCDECL) halt();
			if (!sameType(&t->c[0],&ast->c[0])) halt();
//			if (t->c[0].type == STRUTYPE || t->c[0].type == UNIOTYPE){
//			
//			}
			if (t->num == 3 && ast->num == 3) halt();
			if (t->num == 2) addName(ast->c[1].data,(void *)ast,flag);
		}else{
			addName(ast->c[1].data,(void *)ast,flag);
		}
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
	addName("print",NULL,0);
	addName("getchar",NULL,0);
	addName("malloc",NULL,0);
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
