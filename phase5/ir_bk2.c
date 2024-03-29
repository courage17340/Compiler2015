#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ir.h"
#include "semantic.h"
#include "parser.h"
/*
dest = obj op obj
ob1    ob2 op ob3

dest = op obj
ob1    op ob2

dest = obj
ob1 op ob2

param obj
op    ob1

call func num
op   ob1  ob2

dest = call func num
ob1    op   ob2  ob3

label l
op    ob1

goto l
op   ob1

ifTrueGoto expr l
op         ob1  ob2

ifFalseGoto expr l
op          ob1  ob2

a = b      [x], 4
ob1 ob2 op ob3  size

a      [x] = b,  4
ob1 op ob2   ob3 size

t0 =  *a, 4
ob1 op ob2 size

   *a = t0, 4
op ob1  ob2 size

ret (xxx)
op  (ob1)

*/
enum OpType{
	IRUNAROP,IRBINAOP,IRASSIOP,IRPARAOP,IRCALLOP,IRLABLOP,IRGOTOOP,IRITGTOP,IRIFGTOP,IRARRROP,IRARRWOP,IRPTRROP,IRPTRWOP,IRFENDOP,IRRETNOP
//	unary    binary   =        param    call     label    goto     ifTgoto  ifFgoto  a=b[x],4 a[x]=b,4 t0=*a,4  *a=t0,4  nop      ret
};
enum ObjectType{
	IRSTRC,IRINTC,IRNAME,IRTEMP
};

//======operator======
struct Op{
	int type;
	char *name;
};
static struct Op *getOp(int type,char *name){
	struct Op *t = malloc(sizeof(struct Op));
	t->type = type;
	t->name = strdup(name);
	return t;
}
static void freeOp(struct Op *t){
	if (t == NULL) return;
	free(t->name);
	free(t);
}
//======object======
struct Object{
	int type,pd,size,data;//pd -- 0 pointer or 1 data
	char *name;
};
static struct Object *getObject(int type,int pd,int size,int data,char *name){
	struct Object *t = malloc(sizeof(struct Object));
	t->type = type;
	t->pd = pd;
	t->size = size;
	t->data = data;
	t->name = strdup(name);
	return t;
}
static void freeObject(struct Object *t){
	if (t == NULL) return;
	free(t->name);
	free(t);
}
static struct Object *dupeObject(struct Object *ob){
	return getObject(ob->type,ob->pd,ob->size,ob->data,ob->name);
}
//======object list======
struct ObjectList{
	struct Object **e;
	int num,cap;
};
static struct ObjectList *getObjectList(void){
	struct ObjectList *t = malloc(sizeof(struct ObjectList));
	t->e = malloc(sizeof(struct Object *));
	t->num = 0;
	t->cap = 1;
	return t;
}
static void resizeObjectList(struct ObjectList *t){
	int i;
	struct Object **tmp;
	if (t->num != t->cap) return;
	t->cap <<= 1;
	tmp = malloc(sizeof(struct Object *) * t->cap);
	for (i = 0;i < t->num;++i) tmp[i] = t->e[i];
	free(t->e);
	t->e = tmp;
}
static void pushBackObject(struct ObjectList *l,struct Object *o){
	resizeObjectList(l);
	++l->num;
	l->e[l->num - 1] = o;
}
static void freeObjectList(struct ObjectList *t){
	int i;
	if (t == NULL) return;
	for (i = 0;i < t->num;++i) freeObject(t->e[i]);
	free(t->e);
	free(t);
}
//======sentence======
struct Sentence{
	struct Object *ob[3];
	struct Op *op;
	int size,num;
};
static struct Sentence *getSentence(void){
	struct Sentence *t = malloc(sizeof(struct Sentence));
	t->ob[0] = t->ob[1] = t->ob[2] = NULL;
	t->op = NULL;
	t->size = t->num = 0;
	return t;
}
static void freeSentence(struct Sentence *t){
	int i;
	if (t == NULL) return;
	freeOp(t->op);
	for (i = 0;i < t->num;++i) freeObject(t->ob[i]);
	free(t);
}
//======sentence list======
struct SentenceList{
	struct Sentence **e;
	int num,cap;
};
static struct SentenceList *getSentenceList(void){
	struct SentenceList *t = malloc(sizeof(struct SentenceList));
	t->e = malloc(sizeof(struct Sentence *));
	t->num = 0;
	t->cap = 1;
	return t;
}
static void resizeSentenceList(struct SentenceList *t){
	int i;
	struct Sentence **tmp;
	if (t->num != t->cap) return;
	t->cap <<= 1;
	tmp = malloc(sizeof(struct Sentence *) * t->cap);
	for (i = 0;i < t->num;++i) tmp[i] = t->e[i];
	free(t->e);
	t->e = tmp;
}
static void pushBackSentence(struct SentenceList *l,struct Sentence *s){
	resizeSentenceList(l);
	++l->num;
	l->e[l->num - 1] = s;
}
static void freeSentenceList(struct SentenceList *t){
	int i;
	if (t == NULL) return;
	for (i = 0;i < t->num;++i) freeSentence(t->e[i]);
	free(t->e);
	free(t);
}
//======function======
struct Function{
	char *name;
	struct ObjectList *para,*vari;
	struct SentenceList *body;
};
static struct Function *getFunction(char *name){
	struct Function *t = malloc(sizeof(struct Function));
	t->name = strdup(name);
	t->para = t->vari = NULL;
	t->body = NULL;
	return t;
}
static void freeFunction(struct Function *t){
	if (t == NULL) return;
	free(t->name);
	freeObjectList(t->para);
	freeObjectList(t->vari);
	freeSentenceList(t->body);
	free(t);
}
//======function list======
struct FunctionList{
	struct Function **e;
	int num,cap;
};
static struct FunctionList *getFunctionList(void){
	struct FunctionList *t = malloc(sizeof(struct FunctionList));
	t->e = malloc(sizeof(struct Function *));
	t->num = 0;
	t->cap = 1;
	return t;
}
static void resizeFunctionList(struct FunctionList *t){
	int i;
	struct Function **tmp;
	if (t->num != t->cap) return;
	t->cap <<= 1;
	tmp = malloc(sizeof(struct Function *) * t->cap);
	for (i = 0;i < t->num;++i) tmp[i] = t->e[i];
	free(t->e);
	t->e = tmp;
}
static void pushBackFunction(struct FunctionList *l,struct Function *f){
	resizeFunctionList(l);
	++l->num;
	l->e[l->num - 1] = f;
}
static void freeFunctionList(struct FunctionList *t){
	int i;
	if (t == NULL) return;
	for (i = 0;i < t->num;++i)
		freeFunction(t->e[i]);
	free(t->e);
	free(t);
}
//======static variables======
static struct FunctionList *funcList;
static int registerNum,labelNum;
//======registers======
static char *toString(int t){
	int f[33],p = 0,i;
	char *s;
	if (!t){
		f[++p] = 0;
	}
	while (t){
		f[++p] = t % 10;
		t /= 10;
	}
	s = malloc(sizeof(char) * (p + 2));
	s[0] = '$';
	for (i = p;i >= 1;--i) s[p + 1 - i] = f[p] + '0';
	s[p + 1] = 0;
	return s;
}
static struct Object *getRegister(void){
	++registerNum;
	return getObject(IRTEMP,1,4,registerNum,toString(registerNum));
}
//======local function decl======
static void irMain(struct AstNode *ast);
static void irFunc(struct AstNode *ast);
static void irVariList(struct AstNode *ast,struct ObjectList *list,struct Function *func);
static void irVari(struct AstNode *type,char *name,struct ObjectList *list);
static void irCompStmt(struct AstNode *ast,struct Function *func,int beginLabel,int endLabel);
static void irStmt(struct AstNode *ast,struct Function *func,int beginLabel,int endLabel);
static void irBreaStmt(struct Function *func,int label);
static void irContStmt(struct Function *func,int label);
static void irIfteStmt(struct AstNode *ast,struct Function *func,int beginLabel,int endLabel);
static void irForLoop(struct AstNode *ast,struct Function *func,int beginLabel,int endLabel);
static void irWhileLoop(struct AstNode *ast,struct Function *func,int beginLabel,int endLabel);
static void irExprStmt(struct AstNode *ast,struct Function *func);
static void irRetnStmt(struct AstNode *ast,struct Function * func);
static void makeGoto(struct Function *func,int label);
static void makeLabl(struct Function *func,int label);
static void makeItgt(struct AstNode *ast,struct Function *func,int label);
static void makeIfgt(struct AstNode *ast,struct Function *func,int label);
static struct Object *makeExpr(struct AstNode *ast,struct Function *func,int *mode);//mode 1-used 0-not used
static struct Object *makeIntc(int value);

//======main======
static void irMain(struct AstNode *ast){
	struct Function *f;
	int i;
	funcList = getFunctionList();
	f = getFunction("$start$");
	pushBackFunction(funcList,f);
	f = getFunction("getchar");
	pushBackFunction(funcList,f);
	f = getFunction("malloc");
	pushBackFunction(funcList,f);
	f = getFunction("printf");
	pushBackFunction(funcList,f);
	for (i = 0;i < ast->num;++i)
		if (ast->c[i].type == FUNCDECL)
			irFunc(&ast->c[i]);
		else if (ast->c[i].type == VARIDECL)
			irVariList(&ast->c[i],funcList->e[0]->vari,funcList->e[0]);
		else{
			//nop
		}
}
static void irFunc(struct AstNode *ast){
	struct Function *tmp = getFunction(ast->c[1].data);
	struct AstNode *atmp;
	int i;
	pushBackFunction(funcList,tmp);
	tmp->para = getObjectList();
	tmp->vari = getObjectList();
	tmp->body = getSentenceList();
	irVari(&ast->c[0],ast->c[1].data,tmp->para);
	atmp = &ast->c[2];
	for (i = 0;i < atmp->num;++i) irVari(&atmp->c[i].c[0],atmp->c[i].c[1].data,tmp->para);
	irCompStmt(&ast->c[3],tmp,0,0);
}
static void irVariList(struct AstNode *ast,struct ObjectList *list,struct Function *func){
	int i;
	for (i = 1;i < ast->num;++i){
		irVari(&ast->c[i].c[0],ast->c[i].c[1].data,list);
		if (ast->c[i].num > 2){
			//TODO INIT
		}
	}
}
static void irVari(struct AstNode *type,char *name,struct ObjectList *list){
	struct Object *t;
	int pd;
	if (type->type == ARRATYPE || type->type == PTERTYPE) pd = 0;else pd = 1;
	t = getObject(IRNAME,pd,type->size,0,name);
	pushBackObject(list,t);
}
static void irCompStmt(struct AstNode *ast,struct Function *func,int beginLabel,int endLabel){
	int i;
	for (i = 0;i < ast->num;++i) if (ast->c[i].type == VARIDECL){
		irVariList(&ast->c[i],func->vari,func);
	}else{
		irStmt(&ast->c[i],func,beginLabel,endLabel);
	}
}
static void irStmt(struct AstNode *ast,struct Function *func,int beginLabel,int endLabel){
	if (ast->type == BREASTMT){
		irBreaStmt(func,endLabel);
	}else if (ast->type == CONTSTMT){
		irContStmt(func,beginLabel);
	}else if (ast->type == IFTESTMT){
		irIfteStmt(ast,func,beginLabel,endLabel);
	}else if (ast->type == FORRLOOP){
		irForLoop(ast,func,beginLabel,endLabel);
	}else if (ast->type == WHILLOOP){
		irWhileLoop(ast,func,beginLabel,endLabel);
	}else if (ast->type == EXPRSTMT){
		irExprStmt(ast,func);
	}else if (ast->type == RETNSTMT){
		irRetnStmt(ast,func);
	}else if (ast->type == COMPSTMT){
		irCompStmt(ast,func,beginLabel,endLabel);
	}else{
		//never
	}
}
static void irBreaStmt(struct Function *func,int label){
	makeGoto(func,label);
}
static void irContStmt(struct Function *func,int label){
	makeGoto(func,label);
}
static void irIfteStmt(struct AstNode *ast,struct Function *func,int beginLabel,int endLabel){
/*
if (cond)
	thenStmt
------------
if (cond)
	thenStmt
else
	elseStmt
************
two labels:
begin
end
------------
ifTrue(cond) goto next
(optional) elseStmt
goto end
label next
thenStmt
label end
*/
	int t;
	labelNum += 2;
	t = labelNum;
	makeItgt(&ast->c[0],func,t - 1);
	if (ast->num > 2) irStmt(&ast->c[2],func,beginLabel,endLabel);
	makeGoto(func,t);
	makeLabl(func,t - 1);
	irStmt(&ast->c[2],func,beginLabel,endLabel);
	makeLabl(func,t);
}
static void irForLoop(struct AstNode *ast,struct Function *func,int beginLabel,int endLabel){
/*
for (init;cond;modi)
	stmt
************
three labels:
begin
main
end
------------
init
goto main
label begin
modi
label main
ifFalse(cond) goto end
stmt
goto begin
label end
*/
	int t;
	labelNum += 3;
	t = labelNum;
	irExprStmt(&ast->c[0],func);
	makeGoto(func,t - 1);
	makeLabl(func,t - 2);
	irExprStmt(&ast->c[2],func);
	makeLabl(func,t - 1);
	if (ast->c[1].type == EMPTEXPR){
		//nop
	}else{
		makeIfgt(&ast->c[1],func,t);
	}
	irStmt(&ast->c[3],func,t - 2,t);
	makeGoto(func,t - 2);
	makeLabl(func,t);
}
static void irWhileLoop(struct AstNode *ast,struct Function *func,int beginLabel,int endLabel){
/*
while (cond)
	stmt
************
two labels:
begin
end
------------
label begin
ifFalse(cond) goto end
stmt
goto begin
label end
*/
	int t;
	labelNum += 2;
	t = labelNum;
	makeLabl(func,t - 1);
	makeIfgt(&ast->c[0],func,t);
	irStmt(&ast->c[1],func,t - 1,t);
	makeGoto(func,t - 1);
	makeLabl(func,t);
}
static void irExprStmt(struct AstNode *ast,struct Function *func){
	int mode = 0;
	struct Object *ob;
	if (ast->c[0].type == EMPTEXPR) return;
	ob = makeExpr(&ast->c[0],func,&mode);
	if (!mode) freeObject(ob);
}
static void irRetnStmt(struct AstNode *ast,struct Function * func){
	struct Sentence *s = getSentence();
	s->op = getOp(IRRETNOP,"return");
	ast = &ast->c[0];
	if (ast->c[0].type == EMPTEXPR){
		s->num = 0;
	}else{
		int mode = 0;
		struct Object *ob = makeExpr(ast,func,&mode);
		s->num = 1;
		if (mode) s->ob[0] = dupeObject(ob);else s->ob[0] = ob;
	}
	pushBackSentence(func->body,s);
}
static void makeGoto(struct Function *func,int label){
	struct Op *op = getOp(IRGOTOOP,"goto");
	struct Sentence *s = getSentence();
	s->op = op;
	s->ob[0] = makeIntc(label);
	s->num = 1;
	pushBackSentence(func->body,s);
}
static void makeLabl(struct Function *func,int label){
	struct Op *op = getOp(IRLABLOP,"label");
	struct Sentence *s = getSentence();
	s->op = op;
	s->ob[0] = makeIntc(label);
	s->num = 1;
	pushBackSentence(func->body,s);
}
static void makeItgt(struct AstNode *ast,struct Function *func,int label){
	int mode = 0;
	struct Op *op = getOp(IRITGTOP,"ifTrueGoto");
	struct Object *ob = makeExpr(ast,func,&mode);
	struct Sentence *s = getSentence();
	s->op = op;
	if (mode) s->ob[0] = dupeObject(ob);else s->ob[0] = ob;
	s->ob[1] = makeIntc(label);
	s->num = 2;
	pushBackSentence(func->body,s);
}
static void makeIfgt(struct AstNode *ast,struct Function *func,int label){
	int mode = 0;
	struct Op *op = getOp(IRIFGTOP,"ifFalseGoto");
	struct Object *ob = makeExpr(ast,func,&mode);
	struct Sentence *s = getSentence();
	s->op = op;
	if (mode) s->ob[0] = dupeObject(ob);else s->ob[0] = ob;
	s->ob[1] = makeIntc(label);
	s->num = 2;
	pushBackSentence(func->body,s);
}
static struct Object *makeExpr(struct AstNode *ast,struct Function *func,int *mode){
	struct Object *ob,*ob1,*ob2,*ob3;
	if (ast->type == EMPTEXPR){
		//nop
	}else if (ast->type == BINAEXPR){
		//TODO
		if (strcmp(ast->data,"&&") == 0){
			//TODO
			return NULL;
		}else if (strcmp(ast->data,"||") == 0){
			//TODO
			return NULL;
		}
		int m1 = 0,m2 = 0;
		struct Sentence *s = getSentence();
		ob1 = makeExpr(&ast->c[0],func,&m1);
		if (m1) ob1 = dupeObject(ob1);
		ob2 = makeExpr(&ast->c[1],func,&m2);
		if (m2) ob2 = dupeObject(ob2);
		*mode = 1;
		if (strcmp(ast->data,",") == 0){
			*mode = 0;
			freeObject(ob1);
			freeSentence(s);
			return ob2;
		}else if (strcmp(ast->data,"=") == 0){
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob2;
			s->num = 2;
			pushBackSentence(func->body,s);
			return ob1;
		}else if (strcmp(ast->data,"|") == 0){
			s->op = getOp(IRBINAOP,"|");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"^") == 0){
			s->op = getOp(IRBINAOP,"^");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"&") == 0){
			s->op = getOp(IRBINAOP,"&");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"<") == 0){
			s->op = getOp(IRBINAOP,"<");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,">") == 0){
			s->op = getOp(IRBINAOP,">");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"+") == 0){
			s->op = getOp(IRBINAOP,"+");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"-") == 0){
			s->op = getOp(IRBINAOP,"-");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"*") == 0){
			s->op = getOp(IRBINAOP,"*");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"/") == 0){
			s->op = getOp(IRBINAOP,"/");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"%") == 0){
			s->op = getOp(IRBINAOP,"%");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"==") == 0){
			s->op = getOp(IRBINAOP,"==");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"!=") == 0){
			s->op = getOp(IRBINAOP,"!=");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"<=") == 0){
			s->op = getOp(IRBINAOP,"<=");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,">=") == 0){
			s->op = getOp(IRBINAOP,">=");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"<<") == 0){
			s->op = getOp(IRBINAOP,"<<");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,">>") == 0){
			s->op = getOp(IRBINAOP,">>");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"*=") == 0){
			s->op = getOp(IRBINAOP,"*");
			s->ob[0] = dupeObject(ob1);
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"/=") == 0){
			s->op = getOp(IRBINAOP,"/");
			s->ob[0] = dupeObject(ob1);
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"%=") == 0){
			s->op = getOp(IRBINAOP,"%");
			s->ob[0] = dupeObject(ob1);
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"<<=") == 0){
			s->op = getOp(IRBINAOP,"<<");
			s->ob[0] = dupeObject(ob1);
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,">>=") == 0){
			s->op = getOp(IRBINAOP,">>");
			s->ob[0] = dupeObject(ob1);
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"&=") == 0){
			s->op = getOp(IRBINAOP,"&");
			s->ob[0] = dupeObject(ob1);
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"|=") == 0){
			s->op = getOp(IRBINAOP,"|");
			s->ob[0] = dupeObject(ob1);
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"^=") == 0){
			s->op = getOp(IRBINAOP,"^");
			s->ob[0] = dupeObject(ob1);
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"+=") == 0){
			s->op = getOp(IRBINAOP,"+");
			s->ob[0] = dupeObject(ob1);
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"-=") == 0){
			s->op = getOp(IRBINAOP,"-");
			s->ob[0] = dupeObject(ob1);
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else{
			//never
		}
	}else if (ast->type == UNAREXPR){
		int m = 0;
		struct Sentence *s = getSentence();
		*mode = 1;
		ob1 = makeExpr(&ast->c[0],func,&m);
		if (m) ob1 = dupeObject(ob1);
		if (strcmp(ast->data,"&") == 0){
			s->op = getOp(IRUNAROP,"&");
			ob = getRegister();
			ob->pd = 0;
			s->ob[0] = ob;
			s->ob[1] = ob1;
			pushBackSentence(func->body,s);
			return ob;
		}else if (strcmp(ast->data,"*") == 0){
			//TODO
		}else if (strcmp(ast->data,"+") == 0){
			s->op = getOp(IRUNAROP,"+");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"-") == 0){
			s->op = getOp(IRUNAROP,"-");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"~") == 0){
			s->op = getOp(IRUNAROP,"~");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"!") == 0){
			s->op = getOp(IRUNAROP,"!");
			s->ob[0] = getRegister();
			s->ob[1] = ob1;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"++") == 0){
			s->op = getOp(IRUNAROP,"+");
			s->ob[0] = dupeObject(ob1);
			s->ob[1] = ob1;
			s->ob[2] = makeIntc(1);
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"--") == 0){
			s->op = getOp(IRUNAROP,"-");
			s->ob[0] = dupeObject(ob1);
			s->ob[1] = ob1;
			s->ob[2] = makeIntc(1);
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else{
			//never
		}
	}else if (ast->type == SZOFEXPR){
		int m = 0;
		ob1 = makeExpr(&ast->c[0],func,&m);
		if (!m) freeObject(ob1);
		return makeIntc(ast->value);
	}else if (ast->type == CASTEXPR){
		//TODO
	}else if (ast->type == PTERACSS){
		//TODO
	}else if (ast->type == RECOACSS){
		//TODO
	}else if (ast->type == SELFINCR){
		int m = 0;
		struct Sentence *s;
		*mode = 1;
		ob1 = makeExpr(&ast->c[0],func,&m);
		if (m) ob1 = dupeObject(ob1);
		ob2 = dupeObject(ob1);
		ob3 = getRegister();
		s = getSentence();
		s->op = getOp(IRASSIOP,"=");
		s->ob[0] = ob3;
		s->ob[1] = dupeObject(ob1);
		s->num = 2;
		pushBackSentence(func->body,s);
		s = getSentence();
		s->op = getOp(IRBINAOP,"+");
		s->ob[0] = ob1;
		s->ob[1] = ob2;
		s->ob[2] = makeIntc(1);
		s->num = 2;
		pushBackSentence(func->body,s);
		return ob3;
	}else if (ast->type == SELFDECR){
		int m = 0;
		struct Sentence *s;
		*mode = 1;
		ob1 = makeExpr(&ast->c[0],func,&m);
		if (m) ob1 = dupeObject(ob1);
		ob2 = dupeObject(ob1);
		ob3 = getRegister();
		s = getSentence();
		s->op = getOp(IRASSIOP,"=");
		s->ob[0] = ob3;
		s->ob[1] = dupeObject(ob1);
		s->num = 2;
		pushBackSentence(func->body,s);
		s = getSentence();
		s->op = getOp(IRBINAOP,"-");
		s->ob[0] = ob1;
		s->ob[1] = ob2;
		s->ob[2] = makeIntc(1);
		s->num = 2;
		pushBackSentence(func->body,s);
		return ob3;
	}else if (ast->type == ARRAACSS){
		//TODO
	}else if (ast->type == FUNCCALL){
		//TODO
	}else if (ast->type == IDEN){
		struct AstNode *t = ast->retType;
		int pd,size,data;
		if (t->type == ARRATYPE || t->type == PTERTYPE) pd = 0;else pd = 1;
		size = t->size;
		data = 0;
		return getObject(IRNAME,pd,size,data,ast->data);
	}else if (ast->type == INTECONS){
		return makeIntc(ast->value);
	}else if (ast->type == CHARCONS){
		return makeIntc(ast->value);
	}else if (ast->type == STRICONS){
		return getObject(IRSTRC,0,4,0,ast->data);
	}else{
		//never
	}
	return NULL;
}
static struct Object *makeIntc(int value){
	return getObject(IRINTC,1,4,value,"");
}
//======others======
static void readInput(char *s){
	int t = -1,c;
	c = getchar();
	while (c != EOF){
		s[++t] = c;
		c = getchar();
	}
	s[++t] = 0;
}

int main(void){
	char *s = (char *)malloc(1000010);
//	int i;
	
	readInput(s);
	semanticCheck(s);
//	astPrint(NULL,ast,0);
	
	registerNum = labelNum = 0;
	irMain(ast);
	
	freeFunctionList(funcList);
	
	astDel(ast);
	free(ast);
	free(list);
	free(s);
	return 0;
}
