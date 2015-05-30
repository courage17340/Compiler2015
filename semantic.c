#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "hash.h"
#include "semantic.h"
//======local function declarations======
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

//======local variables======
static struct Stack typeStack,nameStack;
static int intType;

//======main======

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
static void halt(void){
	clearAll();
	astDel(ast);
	free(ast);
	free(list);
	free(typeStack.ele);
	free(nameStack.ele);
	exit(1);
}
static int canConvert(struct AstNode *a,void *t){
	struct AstNode *b;
	if (a == t) return 1;
	if (t == (void *)&intType)
		return a->type == INTETYPE || a->type == CHARTYPE || a->type == PTERTYPE || a->type == ARRATYPE;
	b = t;
	if (a->type == VOIDTYPE){
		if (b->type == VOIDTYPE) return 1;
		return 0;
	}else if (a->type == INTETYPE || a->type == CHARTYPE || a->type == PTERTYPE || a->type == ARRATYPE){
		if (b->type == INTETYPE || b->type == CHARTYPE || b->type == PTERTYPE || b->type == ARRATYPE) return 1;
		return 0;
	}else{
		if (a->type != b->type) return 0;
		return strcmp(a->c[0].data,b->c[0].data) == 0;
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
	for (i = 0;i < l - 2;++i) s[i] = s[i + 1];
	s[l - 2] = 0;
	l -= 2;
	i = 0;
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
	for (i = 0;i < l - 2;++i) s[i] = s[i + 1];
	s[l - 2] = 0;
	l -= 2;
	i = 0;
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

static void addAno(struct AstNode *ast,struct AstNode *t){
	if (ast->num == ast->cap) doubleSpace(ast);
	++ast->num;
	ast->c[ast->num - 1].type = PTERTYPE;
	ast->c[ast->num - 1].num = 0;//TO avoid the second deletion
	ast->c[ast->num - 1].cap = 0;
	ast->c[ast->num - 1].data = NULL;
	ast->c[ast->num - 1].c = t;
	ast->retType = &ast->c[ast->num - 1];
}

static void makeInt(struct AstNode *ast){
	if (ast->num == ast->cap) doubleSpace(ast);
	++ast->num;
	ast->c[ast->num - 1].type = INTETYPE;
	ast->c[ast->num - 1].data = NULL;
	ast->c[ast->num - 1].c = NULL;
	ast->c[ast->num - 1].num = 0;
	ast->c[ast->num - 1].cap = 0;
	ast->c[ast->num - 1].size = 4;
	ast->retType = &ast->c[ast->num - 1];
}

static void checkInit(struct AstNode *type,struct AstNode *init){
	int n,i;
	if (init->type == INIT && init->c[0].type != INIT) init = &init->c[0];
	if (type->type != ARRATYPE){
		struct AstNode *t;
		while (init->type == INIT) init = &init->c[0];
		if (!canConvert(type,init->retType)) halt();
		t = init->retType;
		if (!init->constant && !((t->type == ARRATYPE || init->type == STRICONS) && type->type == PTERTYPE && sameType(&type->c[0],&t->c[0]))) halt();
		return;
	}
	if (type->c[0].type == CHARTYPE){
		struct AstNode *tmp = init;
		while (init->type == INIT) init = &init->c[0];
		if (init->type == STRICONS){
			return;
		}
		init = tmp;
	}
	if (init->type == STRICONS){
		if (type->c[0].type != CHARTYPE) halt();
		return;
	}
	if (init->type != INIT){
		while (type->type == ARRATYPE) type = &type->c[0];
		if (!canConvert(type,init->retType)) halt();
		if (!init->constant) halt();
		return;
	}
	n = type->c[1].value;
	if (n > init->num) n = init->num;
	for (i = 0;i < n;++i) checkInit(&type->c[0],&init->c[i]);

}

static void astCheck(struct AstNode *ast,int isInLoop,void *retType){
	//flag for scopes
	static int flag = 0;
	int i;
	ast->lValue = 0;
	ast->constant = 0;
	ast->size = 0;
	ast->pos = 0;
	if (ast->type == ROOT){
		for (i = 0;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,retType);
	}else if (ast->type == DECL){
		for (i = 0;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,retType);
	}else if (ast->type == FUNCDECL){
		if (hasName(ast->c[1].data,flag)) halt();
		addName(ast->c[1].data,(void *)ast,flag);
		astCheck(&ast->c[0],isInLoop,retType);
		if (ast->c[0].type == STRUTYPE || ast->c[0].type == UNIOTYPE){
			struct AstNode *t = getTypeHash(ast->c[0].c[0].data);
			if (t->num == 1) halt();
		}
//		ast->retType = &ast->c[0];
		++flag;
		astCheck(&ast->c[2],isInLoop,retType);
		--flag;
		astCheck(&ast->c[3],isInLoop,&ast->c[0]);
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
		ast->size = 4;
	}else if (ast->type == CHARTYPE){
		ast->size = 1;
	}else if (ast->type == VOIDTYPE){
		//nop
	}else if (ast->type == STRUTYPE){
		struct AstNode *tmp;
		if (hasType(ast->c[0].data,flag)){
			tmp = getTypeHash(ast->c[0].data);
			if (ast->type != tmp->type) halt();
		}
		if (ast->num > 1){
			struct AstNode *t;
			int j,cur,sz;
			if (hasType(ast->c[0].data,flag)){
				if (tmp->num > 1) halt();
			}
			astCheck(&ast->c[1],isInLoop,retType);
			t = &ast->c[1];
			cur = 0;
			for (i = 0;i < t->num;++i)
				for (j = 1;j < t->c[i].num;j += 2){
					sz = t->c[i].c[j].size;
					t->c[i].c[j].pos = cur;
					cur += (sz >> 2) << 2;
					if (sz & 3) cur += 4;
				}
			ast->size = cur;
			
			addType(ast->c[0].data,(void *)ast,flag);
		}else{
			if (getTypeHash(ast->c[0].data) == NULL){
				addType(ast->c[0].data,(void *)ast,flag);
//				astCheck(&ast->c[1],isInLoop,retType);
			}else{
				tmp = getTypeHash(ast->c[0].data);
				ast->size = tmp->size;
			}
		}
	}else if (ast->type == UNIOTYPE){
		struct AstNode *tmp;
		if (hasType(ast->c[0].data,flag)){
			tmp = getTypeHash(ast->c[0].data);
			if (ast->type != tmp->type) halt();
		}
		if (ast->num > 1){
			struct AstNode *t;
			int j,sz;
			if (hasType(ast->c[0].data,flag)){
				if (tmp->num > 1) halt();
			}
			astCheck(&ast->c[1],isInLoop,retType);
			t = &ast->c[1];
			for (i = 0;i < t->num;++i)
				for (j = 1;j < t->c[i].num;j += 2){
					sz = t->c[i].c[j].size;
					if (sz & 3) sz = ((sz >> 2) + 1) << 2;
					if (ast->size < sz) ast->size = sz;
				}
			
			addType(ast->c[0].data,(void *)ast,flag);
		}else{
			if (getTypeHash(ast->c[0].data) == NULL){
				addType(ast->c[0].data,(void *)ast,flag);
//				astCheck(&ast->c[1],isInLoop,retType);
			}else{
				tmp = getTypeHash(ast->c[0].data);
				ast->size = tmp->size;
			}
		}
	}else if (ast->type == PTERTYPE){
//		ast->retType = (void *)ast;
		ast->size = 4;
		astCheck(&ast->c[0],isInLoop,retType);
	}else if (ast->type == ARRATYPE){
//		ast->retType = (void *)ast;
		astCheck(&ast->c[0],isInLoop,retType);
		astCheck(&ast->c[1],isInLoop,retType);
		if (!ast->c[1].constant) halt();
		if (ast->c[1].value < 0) halt();
		ast->size = ast->c[0].size * ast->c[1].value;
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
		if (ast->num > 2) astCheck(&ast->c[2],isInLoop,retType);
	}else if (ast->type == FORRLOOP){
		astCheck(&ast->c[0],isInLoop,retType);
		astCheck(&ast->c[1],isInLoop,retType);
		if (ast->c[1].type != EMPTEXPR && !canConvert(ast->c[1].retType,(void *)&intType)) halt();
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
		ast->c = getAst(1);
		ast->num = ast->cap = 1;
		ast->c[0].type = VOIDTYPE;
		ast->c[0].data = NULL;
		ast->c[0].cap = ast->c[0].num = 0;
		ast->c[0].c = NULL;
		ast->retType = (void *)&ast->c[0];
		ast->size = 0;
	}else if (ast->type == BINAEXPR){	//Pointers here are specially designed so that they won't be freed twice
		struct AstNode *a,*b;
		astCheck(&ast->c[0],isInLoop,retType);
		astCheck(&ast->c[1],isInLoop,retType);
		a = ast->c[0].retType;
		b = ast->c[1].retType;
		if (strcmp(ast->data,",") == 0){
			ast->retType = b;
			if (ast->c[1].constant) ast->constant = 1;
			ast->size = ast->c[1].size;
		}else if (strcmp(ast->data,"=") == 0){
			if (!ast->c[0].lValue) halt();
			if (!canConvert(a,b)) halt();
			ast->retType = a;
			ast->size = ast->c[0].size;
		}else if (strcmp(ast->data,"|") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value | ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"^") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value ^ ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"&") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value & ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"<") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE && a->type != PTERTYPE && a->type != ARRATYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE && b->type != PTERTYPE && b->type != ARRATYPE) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value < ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,">") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE && a->type != PTERTYPE && a->type != ARRATYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE && b->type != PTERTYPE && b->type != ARRATYPE) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value > ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"+") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE && a->type != PTERTYPE && a->type != ARRATYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE && b->type != PTERTYPE && b->type != ARRATYPE) halt();
			if (a->type != INTETYPE && a->type != CHARTYPE && b->type != INTETYPE && b->type != CHARTYPE) halt();
			if ((a->type == INTETYPE || a->type == CHARTYPE) && (b->type == INTETYPE || b->type == CHARTYPE)){
				makeInt(ast);
			}else{
				if (a->type == INTETYPE || a->type == CHARTYPE) ast->retType = b;else ast->retType = a;
			}
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value + ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"-") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE && a->type != PTERTYPE && a->type != ARRATYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE && b->type != PTERTYPE && b->type != ARRATYPE) halt();
			if ((a->type == INTETYPE || a->type == CHARTYPE) && (b->type == INTETYPE || b->type == CHARTYPE)){
				makeInt(ast);
			}else{
				if (a->type == INTETYPE || a->type == CHARTYPE){
					halt();
				}else if (b->type == INTETYPE || b->type == CHARTYPE){
					addAno(ast,&a->c[0]);
				}else{
					if (!sameType(&a->c[0],&b->c[0])) halt();
					makeInt(ast);
				}
			}
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value - ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"*") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value * ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"/") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			makeInt(ast);
			if (ast->c[1].constant && ast->c[1].value == 0) halt();//divide by 0
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value / ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"%") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			makeInt(ast);
			if (ast->c[1].constant && ast->c[1].value == 0) halt();//divide by 0
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value % ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"||") == 0){
			if (!canConvert(a,(void *)&intType)) halt();
			if (!canConvert(b,(void *)&intType)) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[0].value){// 1 || x == 1
				ast->constant = 1;
				ast->value = 1;
			}else if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value || ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"&&") == 0){
			if (!canConvert(a,(void *)&intType)) halt();
			if (!canConvert(b,(void *)&intType)) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[0].value == 0){// 0 && x == 0
				ast->constant = 1;
				ast->value = 1;
			}else if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value && ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"==") == 0){
			if (!canConvert(a,(void *)&intType)) halt();
			if (!canConvert(b,(void *)&intType)) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value == ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"!=") == 0){
			if (!canConvert(a,(void *)&intType)) halt();
			if (!canConvert(b,(void *)&intType)) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value != ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"<=") == 0){
			if (!canConvert(a,(void *)&intType)) halt();
			if (!canConvert(b,(void *)&intType)) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value <= ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,">=") == 0){
			if (!canConvert(a,(void *)&intType)) halt();
			if (!canConvert(b,(void *)&intType)) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value >= ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"<<") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value << ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,">>") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			makeInt(ast);
			if (ast->c[0].constant && ast->c[1].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value >> ast->c[1].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"*=") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			if (!ast->c[0].lValue) halt();
			makeInt(ast);
			ast->size = ast->c[0].size;
		}else if (strcmp(ast->data,"/=") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			if (!ast->c[0].lValue) halt();
			makeInt(ast);
			if (ast->c[1].constant && ast->c[1].value == 0) halt();//a /= 0;
			ast->size = ast->c[0].size;
		}else if (strcmp(ast->data,"%=") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			if (!ast->c[0].lValue) halt();
			makeInt(ast);
			if (ast->c[1].constant && ast->c[1].value == 0) halt();//a %= 0;
			ast->size = ast->c[0].size;
		}else if (strcmp(ast->data,"<<=") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			if (!ast->c[0].lValue) halt();
			makeInt(ast);
			ast->size = ast->c[0].size;
		}else if (strcmp(ast->data,">>=") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			if (!ast->c[0].lValue) halt();
			makeInt(ast);
			ast->size = ast->c[0].size;
		}else if (strcmp(ast->data,"&=") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			if (!ast->c[0].lValue) halt();
			makeInt(ast);
			ast->size = ast->c[0].size;
		}else if (strcmp(ast->data,"|=") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			if (!ast->c[0].lValue) halt();
			makeInt(ast);
			ast->size = ast->c[0].size;
		}else if (strcmp(ast->data,"^=") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE) halt();
			if (!ast->c[0].lValue) halt();
			makeInt(ast);
			ast->size = ast->c[0].size;
		}else if (strcmp(ast->data,"+=") == 0){
			if (!ast->c[0].lValue) halt();
			if (a->type != INTETYPE && a->type != CHARTYPE && a->type != PTERTYPE && a->type != ARRATYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE && b->type != PTERTYPE && b->type != ARRATYPE) halt();
			if (a->type != INTETYPE && a->type != CHARTYPE && b->type != INTETYPE && b->type != CHARTYPE) halt();
			if ((a->type == INTETYPE || a->type == CHARTYPE) && (b->type == INTETYPE || b->type == CHARTYPE)){
				makeInt(ast);
			}else{
				if (a->type == INTETYPE || a->type == CHARTYPE){
					makeInt(ast);
				}else{
					addAno(ast,&a->c[0]);
				}
			}
			ast->size = ast->c[0].size;
		}else if (strcmp(ast->data,"-=") == 0){
			if (!ast->c[0].lValue) halt();
			if (a->type != INTETYPE && a->type != CHARTYPE && a->type != PTERTYPE && a->type != ARRATYPE) halt();
			if (b->type != INTETYPE && b->type != CHARTYPE && b->type != PTERTYPE && b->type != ARRATYPE) halt();
			if ((a->type == INTETYPE || a->type == CHARTYPE) && (b->type == INTETYPE || b->type == CHARTYPE)){
				makeInt(ast);
			}else{
				if (a->type == INTETYPE || a->type == CHARTYPE){
					halt();
				}else{
					if (b->type == INTETYPE || b->type == CHARTYPE){
						addAno(ast,&a->c[0]);
					}else{
						if (!sameType(&a->c[0],&b->c[0])) halt();
						makeInt(ast);
					}
				}
			}
			ast->size = ast->c[0].size;
		}else{
			//never
		}
	}else if (ast->type == UNAREXPR){
		struct AstNode *a;
		astCheck(&ast->c[0],isInLoop,retType);
		a = ast->c[0].retType;
		if (strcmp(ast->data,"&") == 0){
			if (!ast->c[0].lValue) halt();
			addAno(ast,a);
			ast->size = 4;
		}else if (strcmp(ast->data,"*") == 0){
			if (a->type != ARRATYPE && a->type != PTERTYPE) halt();
			ast->retType = &a->c[0];
			if (a->c[0].type != ARRATYPE) ast->lValue = 1;
			ast->size = a->c[0].size;
		}else if (strcmp(ast->data,"+") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			makeInt(ast);
			if (ast->c[0].constant){
				ast->constant = 1;
				ast->value = ast->c[0].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"-") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			makeInt(ast);
			if (ast->c[0].constant){
				ast->constant = 1;
				ast->value = -ast->c[0].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"~") == 0){
			if (a->type != INTETYPE && a->type != CHARTYPE) halt();
			makeInt(ast);
			if (ast->c[0].constant){
				ast->constant = 1;
				ast->value = ~ast->c[0].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"!") == 0){
			if (!canConvert(a,(void *)&intType)) halt();
			makeInt(ast);
			if (ast->c[0].constant){
				ast->constant = 1;
				ast->value = !ast->c[0].value;
			}
			ast->size = 4;
		}else if (strcmp(ast->data,"++") == 0){
			if (!ast->c[0].lValue) halt();
			if (!canConvert(a,(void *)&intType)) halt();
			ast->retType = a;
			ast->size = ast->c[0].size;
		}else if (strcmp(ast->data,"--") == 0){
			if (!ast->c[0].lValue) halt();
			if (!canConvert(a,(void *)&intType)) halt();
			ast->retType = a;
			ast->size = ast->c[0].size;
		}else{
			//never
		}
	}else if (ast->type == SZOFEXPR){
		struct AstNode *tmp;
		astCheck(&ast->c[0],isInLoop,retType);
		if (TYPE <= ast->c[0].type && ast->c[0].type <= ARRATYPE){
			tmp = &ast->c[0];
		}else{
			tmp = ast->c[0].retType;
		}
		if (tmp == NULL) tmp = &ast->c[0];
		if (tmp->type == VOIDTYPE) halt();
		ast->constant = 1;
		makeInt(ast);
		ast->value = ast->c[0].size;
	}else if (ast->type == CASTEXPR){
		astCheck(&ast->c[0],isInLoop,retType);
		if (ast->c[0].type < TYPE || ast->c[0].type > ARRATYPE) halt();
		astCheck(&ast->c[1],isInLoop,retType);
		if (!canConvert(ast->c[1].retType,&ast->c[0])) halt();
		ast->retType = (void *)&ast->c[0];
		if (ast->c[1].constant) ast->constant = 1;
		ast->size = ast->c[0].size;
	}else if (ast->type == PTERACSS){
		struct AstNode *tmp;
		int j;
		astCheck(&ast->c[0],isInLoop,retType);
		tmp = ast->c[0].retType;
		if (tmp->type != PTERTYPE && tmp->type != ARRATYPE) halt();
		tmp = &tmp->c[0];
		if (tmp->type != STRUTYPE && tmp->type != UNIOTYPE) halt();
		tmp = getTypeHash(tmp->c[0].data);
		if (tmp->num == 1) halt();
		if (ast->c[1].type != IDEN) halt();
		tmp = &tmp->c[1];
		for (i = 0;i < tmp->num;++i)
			for (j = 2;j < tmp->c[i].num;++j)
				if (strcmp(ast->c[1].data,tmp->c[i].c[j].data) == 0){
					ast->retType = &tmp->c[i].c[j - 1];
					if (tmp->c[i].c[j - 1].type != ARRATYPE) ast->lValue = 1;
					ast->size = tmp->c[i].c[j - 1].size;
					ast->pos = tmp->c[i].c[j - 1].pos;
					return;
				}
		halt();
	}else if (ast->type == RECOACSS){
		struct AstNode *tmp;
		int j;
		astCheck(&ast->c[0],isInLoop,retType);
		tmp = ast->c[0].retType;
		if (tmp->type != STRUTYPE && tmp->type != UNIOTYPE) halt();
		tmp = getTypeHash(tmp->c[0].data);
		if (tmp->num == 1) halt();
		if (ast->c[1].type != IDEN) halt();
		tmp = &tmp->c[1];
		for (i = 0;i < tmp->num;++i)
			for (j = 2;j < tmp->c[i].num;++j)
				if (strcmp(ast->c[1].data,tmp->c[i].c[j].data) == 0){
					ast->retType = &tmp->c[i].c[j - 1];
					if (tmp->c[i].c[j - 1].type != ARRATYPE) ast->lValue = 1;
					ast->size = tmp->c[i].c[j - 1].size;
					ast->pos = tmp->c[i].c[j - 1].pos;
					return;
				}
		halt();
	}else if (ast->type == SELFINCR){
		astCheck(&ast->c[0],isInLoop,retType);
		if (!ast->c[0].lValue) halt();
		if (!canConvert(ast->c[0].retType,(void *)&intType)) halt();
		ast->retType = ast->c[0].retType;
		ast->size = ast->c[0].size;
	}else if (ast->type == SELFDECR){
		astCheck(&ast->c[0],isInLoop,retType);
		if (!ast->c[0].lValue) halt();
		if (!canConvert(ast->c[0].retType,(void *)&intType)) halt();
		ast->retType = ast->c[0].retType;
		ast->size = ast->c[0].size;
	}else if (ast->type == ARRAACSS){
		struct AstNode *tmp;
		astCheck(&ast->c[0],isInLoop,retType);
		astCheck(&ast->c[1],isInLoop,retType);
		if (!canConvert(ast->c[1].retType,(void *)&intType)) halt();
		tmp = ast->c[0].retType;
		if (tmp->type != ARRATYPE && tmp->type != PTERTYPE) halt();
		ast->retType = &tmp->c[0];
		if (tmp->type == ARRATYPE){
			if (tmp->c[0].type != ARRATYPE){
				ast->lValue = 1;
			}
		}else{
			ast->lValue = 1;
		}
		ast->size = tmp->c[0].size;
	}else if (ast->type == FUNCCALL){
		struct AstNode *tmp = getNameHash(ast->c[0].data);
		ast->bind = tmp;
		astCheck(&ast->c[1],isInLoop,retType);
		if (strcmp(ast->c[0].data,"printf") == 0){
			if (tmp != NULL) halt();
			if (ast->c[1].type == EMPTEXPR) halt();
			if (!canConvert(ast->c[1].c[0].retType,(void *)&intType)) halt();
			makeInt(ast);
			ast->size = 4;
			return;
		}else if (strcmp(ast->c[0].data,"getchar") == 0){
			if (tmp != NULL) halt();
			if (ast->c[1].type != EMPTEXPR) halt();
			makeInt(ast);
			ast->size = 4;
			return;
		}else if (strcmp(ast->c[0].data,"malloc") == 0){
			if (tmp != NULL) halt();
			if (ast->c[1].type == EMPTEXPR) halt();
			if (ast->c[1].type != FUNCPARA || ast->c[1].num > 1 || !canConvert(ast->c[1].c[0].retType,(void *)&intType)) halt();
			/*
			if (ast->num == ast->cap) doubleSpace(ast);
			++ast->num;
			ast->c[ast->num - 1].type = PTERTYPE;
			ast->c[ast->num - 1].data = NULL;
			ast->c[ast->num - 1].c = getAst(1);
			ast->c[ast->num - 1].c[0].type = VOIDTYPE;
			ast->c[ast->num - 1].c[0].data = NULL;
			ast->c[ast->num - 1].c[0].c = NULL;
			ast->c[ast->num - 1].c[0].num = 0;
			ast->c[ast->num - 1].c[0].cap = 0;
			ast->c[ast->num - 1].num = 1;
			ast->c[ast->num - 1].cap = 1;
			ast->retType = (void *)&ast->c[ast->num - 1];
			*/
			makeInt(ast);
			ast->size = 4;
			return;
		}
		if (tmp == NULL) halt();
		if (tmp->type != FUNCDECL) halt();
		if (tmp->c[2].num == 0){
			if (ast->c[1].type != EMPTEXPR) halt();
		}else{
			if (ast->c[1].type == EMPTEXPR) halt();
			if (ast->c[1].num != tmp->c[2].num) halt();
			for (i = 0;i < ast->c[1].num;++i) if (!canConvert(&tmp->c[2].c[i].c[0],ast->c[1].c[i].retType)) halt();
		}
		ast->retType = &tmp->c[0];
		ast->size = tmp->c[0].size;
	}else if (ast->type == IDEN){
		struct AstNode *tmp = getNameHash(ast->data);
		if (tmp == NULL) halt();
		if (tmp->type == FUNCDECL) halt();
		ast->bind = tmp;
		ast->retType = &tmp->c[0];
		if (tmp->c[0].type != ARRATYPE) ast->lValue = 1;
		ast->size = tmp->c[0].size;
		ast->renamingLabel = tmp->renamingLabel;
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
		ast->c = getAst(1);
		ast->num = ast->cap = 1;
		ast->c[0].type = INTETYPE;
		ast->c[0].data = NULL;
		ast->c[0].c = NULL;
		ast->c[0].num = ast->c[0].cap = 0;
		ast->retType = (void *)&ast->c[0];
		ast->value = t;
		ast->size = 4;
	}else if (ast->type == CHARCONS){
		ast->constant = 1;
		conToChar(ast->data);
		ast->c = getAst(1);
		ast->num = ast->cap = 1;
		ast->c[0].type = CHARTYPE;
		ast->c[0].data = NULL;
		ast->c[0].c = NULL;
		ast->c[0].num = ast->c[0].cap = 0;
		ast->retType = (void *)&ast->c[0];
		ast->value = (int)ast->data[0];
		ast->size = 1;
	}else if (ast->type == STRICONS){
		conToStr(ast->data);
		ast->c = getAst(1);
		ast->num = ast->cap = 1;
		ast->c[0].type = PTERTYPE;
		ast->c[0].data = NULL;
		ast->c[0].c = getAst(1);
		ast->c[0].c[0].type = CHARTYPE;
		ast->c[0].c[0].data = NULL;
		ast->c[0].c[0].c = NULL;
		ast->c[0].c[0].num = 0;
		ast->c[0].c[0].cap = 0;
		ast->c[0].num = ast->c[0].cap = 1;
		ast->retType = (void *)&ast->c[0];
		ast->size = 4;
	}else if (ast->type == PARA){
		for (i = 0;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,retType);
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
//		int k;
		astCheck(&ast->c[0],isInLoop,retType);
		if (ast->c[0].type != STRUTYPE && ast->c[0].type != UNIOTYPE){
			for (i = 1;i < ast->num;i += 2) astCheck(&ast->c[i],isInLoop,retType);
			return;
		}
		for (i = 1;i < ast->num;i += 2){
			tmp = &ast->c[i];
			while (tmp->type == ARRATYPE){
				tmp = &tmp->c[0];
			}
			if (tmp->type != PTERTYPE){
				struct AstNode *t = getTypeHash(ast->c[0].c[0].data);
				if (t->num == 1) halt();
				break;
			}
		}
		for (i = 1;i < ast->num;i += 2) astCheck(&ast->c[i],isInLoop,retType);
	}else if (ast->type == INIT){
		for (i = 0;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,retType);
		if (ast->num == 1) ast->retType = ast->c[0].retType;
	}else if (ast->type == FUNCPARA){
		for (i = 0;i < ast->num;++i) astCheck(&ast->c[i],isInLoop,retType);
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
			if (t->num == 2 && ast->num == 3){
//				addName(ast->c[1].data,(void *)ast,flag);
				if (t->num == t->cap) doubleSpace(t);
				++t->num;
				t->c[2] = ast->c[2];
				--ast->num;
				astCheck(&ast->c[2],isInLoop,retType);
				checkInit(&ast->c[0],&ast->c[2]);
				
				ast->renamingLabel = t->renamingLabel;
				ast->c[1].renamingLabel = t->renamingLabel;
				
				return;
			}
		}else{
			addName(ast->c[1].data,(void *)ast,flag);
			
			ast->c[1].renamingLabel = ast->renamingLabel;
		}
		if (ast->num == 3){
			astCheck(&ast->c[2],isInLoop,retType);
			if (flag == 0) checkInit(&ast->c[0],&ast->c[2]);
		}
	}else{
		//never
	}
}

void semanticCheck(char *s){
	struct node *root;
	int flag,size;
	flag = 1;
	ast = makeAst(s,&flag,&size,&root);
	if (!flag){
		exit(1);
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
	addName("printf",NULL,0);
	addName("getchar",NULL,0);
	addName("malloc",NULL,0);
	astCheck(ast,0,NULL);
	clearAll();
//	astDel(ast);
//	free(ast);
//	free(list);
	free(typeStack.ele);
	free(nameStack.ele);
}
