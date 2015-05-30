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



//======operator======

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
	s = malloc(sizeof(char) * (p + 3));
	s[0] = '_';
	s[1] = '_';
	for (i = p;i >= 1;--i) s[p + 2 - i] = f[i] + '0';
	s[p + 2] = 0;
	return s;
}
static struct RegisterList *getRegisterList(void){
	struct RegisterList *t = malloc(sizeof(struct RegisterList));
	t->e = malloc(sizeof(struct Object *) * 2);
	t->label = malloc(sizeof(int) * 2);
	t->cap = 2;
	return t;
}
static void resizeRegisterList(struct RegisterList *t){
	int i;
	struct Object **tmp;
	int *tt;
	if (t->cap > registerNum + 1) return;
	t->cap <<= 1;
	tmp = malloc(sizeof(struct Object *) * t->cap);
	for (i = 1;i <= registerNum;++i) tmp[i] = t->e[i];
	free(t->e);
	t->e = tmp;
	tt = malloc(sizeof(int) * t->cap);
	for (i = 1;i <= registerNum;++i) tt[i] = t->label[i];
	free(t->label);
	t->label = tt;
}
static struct Object *getRegister(void){
	resizeRegisterList(registers);
	++registerNum;
	registers->label[registerNum] = 0;
	return registers->e[registerNum] = getObject(IRTEMP,2,4,-1,toString(registerNum));
}
void freeRegisterList(struct RegisterList *t){
	int i;
	for (i = 1;i <= registerNum;++i) freeObject(t->e[i]);
	free(t->e);
	free(t->label);
	free(t);
}
//======object list======

static struct ObjectList *getObjectList(void){
	struct ObjectList *t = malloc(sizeof(struct ObjectList));
	t->e = malloc(sizeof(struct Object *));
	t->link = malloc(sizeof(int));
	t->tmpLink = malloc(sizeof(struct Object *));
	t->num = 0;
	t->cap = 1;
	return t;
}
static void resizeObjectList(struct ObjectList *t){
	int i;
	struct Object **tmp;
	int *temp;
	if (t->num != t->cap) return;
	t->cap <<= 1;
	tmp = malloc(sizeof(struct Object *) * t->cap);
	for (i = 0;i < t->num;++i) tmp[i] = t->e[i];
	free(t->e);
	t->e = tmp;
	
	tmp = malloc(sizeof(struct Object *) * t->cap);
	for (i = 0;i < t->num;++i) tmp[i] = t->tmpLink[i];
	free(t->tmpLink);
	t->tmpLink = tmp;
	
	temp = malloc(sizeof(int) * t->cap);
	for (i = 0;i < t->num;++i) temp[i] = t->link[i];
	free(t->link);
	t->link = temp;
}
static void pushBackObject(struct ObjectList *l,struct Object *o,int link){
	resizeObjectList(l);
	++l->num;
	l->e[l->num - 1] = o;
	l->link[l->num - 1] = link;
	l->tmpLink[l->num - 1] = NULL;
}
static void freeObjectList(struct ObjectList *t){
	int i;
	if (t == NULL) return;
	for (i = 0;i < t->num;++i) if (t->e[i] != NULL && t->e[i]->type != IRTEMP) freeObject(t->e[i]);
	free(t->e);
	free(t->link);
	free(t->tmpLink);
	free(t);
}
//======sentence======

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
	for (i = 0;i < t->num;++i) if (t->ob[i]->type != IRTEMP) freeObject(t->ob[i]);
	free(t);
}
//======sentence list======

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

static struct Function *getFunction(char *name){
	struct Function *t = malloc(sizeof(struct Function));
	t->name = strdup(name);
	t->para = t->vari = NULL;
	t->body = NULL;
	t->mainSpace = t->retnStat = t->isLeaf = 0;
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
void freeFunctionList(struct FunctionList *t){
	int i;
	if (t == NULL) return;
	for (i = 0;i < t->num;++i)
		freeFunction(t->e[i]);
	free(t->e);
	free(t);
}

//======local function decl======
static void irMain(struct AstNode *ast);
static void irFunc(struct AstNode *ast);
static void irVariList(struct AstNode *ast,struct ObjectList *list,struct Function *func);
static void irVari(struct AstNode *type,char *name,struct ObjectList *list,struct Function *func,int renamingLabel);
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
static struct Object *makeExpr(struct AstNode *ast,struct Function *func,int notUsed);
static struct Object *makeIntc(int value);
static struct String *getString(char *s);
static void freeString(struct String *s);
static struct StringList *getStringList(void);
static void resizeStringList(struct StringList *l);
static void pushBackString(struct StringList *l,struct String *s);
//======main======
static void irMain(struct AstNode *ast){
	struct Function *f;
	int i;
	funcList = getFunctionList();
	f = getFunction("$start$");
	f->vari = getObjectList();
	f->body = getSentenceList();
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
/*
	local variables
	$ra
	arguments for next function
sp->	
*/
static void irFunc(struct AstNode *ast){
	struct Function *tmp = getFunction(ast->c[1].data);
	struct AstNode *atmp;
	int i,cur,bk,sz;
	pushBackFunction(funcList,tmp);
	tmp->para = getObjectList();
	tmp->vari = getObjectList();
	tmp->body = getSentenceList();
	irVari(&ast->c[0],ast->c[1].data,tmp->para,tmp,1);
	atmp = &ast->c[2];
	for (i = 0;i < atmp->num;++i) irVari(&atmp->c[i].c[0],atmp->c[i].c[1].data,tmp->para,tmp,atmp->c[i].renamingLabel);
	bk = registerNum;
	irCompStmt(&ast->c[3],tmp,0,0);
//dangerous
	for (i = bk + 1;i <= registerNum;++i)
		if (registers->e[i]->data != -2)
			pushBackObject(tmp->vari,registers->e[i],i);
		else
			pushBackObject(funcList->e[0]->vari,registers->e[i],i);
	cur = tmp->mainSpace;
	if (cur & 3){
		cur = ((cur >> 2) + 1) << 2;
		tmp->mainSpace = cur;
	}
	tmp->retnStat = cur;
	
	if (cur){
		cur += 4;
	}else{
		tmp->isLeaf = 1;
	}
	for (i = 0;i < tmp->vari->num;++i){
		registers->e[tmp->vari->link[i]]->data = cur;
		
		if (registers->label[tmp->vari->link[i]] == 0 && registers->e[tmp->vari->link[i]]->pd == 1)
			sz = 4;
		else
			sz = tmp->vari->e[i]->size;
		cur += sz;
		if (cur & 3) cur = ((cur >> 2) + 1) << 2;
	}
	tmp->mainSpace = cur;
//	cur = 0;
	if (ast->c[0].type != VOIDTYPE){
		registers->e[tmp->para->link[0]]->data = cur;
		cur += tmp->para->e[0]->size;
		if (cur & 3) cur = ((cur >> 2) + 1) << 2;
	}
	for (i = 1;i < tmp->para->num;++i){
		registers->e[tmp->para->link[i]]->data = cur;
		cur += tmp->para->e[i]->size;
		if (cur & 3) cur = ((cur >> 2) + 1) << 2;
	}
}
static void initArra(struct Object *r,int beginAddr,struct AstNode *ast,struct AstNode *init,struct Function *func){
	int i,n,k,t;
	struct Sentence *s;
	if (init->c[0].type == STRICONS){
		n = strlen(init->c[0].data) + 1 + beginAddr;
		for (i = beginAddr;i < n;++i){
			s = getSentence();
			s->op = getOp(IRINAROP,"init");
			s->ob[0] = r;
			s->ob[1] = makeIntc(i);
			s->ob[2] = makeIntc(init->c[0].data[i - beginAddr]);
			s->num = 3;
			s->size = 1;
			pushBackSentence(func->body,s);
		}
		return;
	}
	if (ast->c[0].type == ARRATYPE){
		n = ast->c[1].value;
		if (n > init->num) n = init->num;
		t = beginAddr;
		k = ast->c[0].size;
		for (i = 0;i < n;++i){
			initArra(r,t,&ast->c[0],&init->c[i],func);
			t += k;
		}
	}else{
		n = ast->c[1].value;
		if (n > init->num) n = init->num;
		t = beginAddr;
		k = ast->c[0].size;
		for (i = 0;i < n;++i){
			s = getSentence();
			s->op = getOp(IRINAROP,"init");
			s->ob[0] = r;
			s->ob[1] = makeIntc(t);
			s->ob[2] = makeExpr(&init->c[i].c[0],func,0);
			s->num = 3;
			s->size = k;
			pushBackSentence(func->body,s);
			t += k;
		}
	}
}
static void irVariList(struct AstNode *ast,struct ObjectList *list,struct Function *func){
	int i;
	for (i = 1;i < ast->num;++i){
		irVari(&ast->c[i].c[0],ast->c[i].c[1].data,list,func,ast->c[i].renamingLabel);
		if (list == func->para && ast->c[i].c[0].type == ARRATYPE){
			list->e[list->num - 1]->size = 4;
			registers->e[list->link[list->num - 1]]->size = 4;
		}
		if (ast->c[i].num > 2){
			struct SentenceList *body;
			struct Sentence *s;
			struct Object *ob,*ob1;
			body = func->body;
			if (ast->c[i].c[0].type == ARRATYPE){
				ob = registers->e[list->link[list->num - 1]];
				ob1 = getRegister();
				ob1->data = -1;
				s = getSentence();
				s->op = getOp(IRARASOP,"=");
				s->ob[0] = ob1;
				s->ob[1] = ob;
				s->num = 2;
				pushBackSentence(func->body,s);
				initArra(ob1,0,&ast->c[i].c[0],&ast->c[i].c[2],func);
			}else{
				ob = registers->e[list->link[list->num - 1]];
				//ob = makeExpr(&ast->c[i].c[1],func);
				ob1 = makeExpr(&ast->c[i].c[2].c[0],func,0);
				s = getSentence();
				s->op = getOp(IRASSIOP,"=");
				s->ob[0] = ob;
				s->ob[1] = ob1;
				s->num = 2;
				pushBackSentence(body,s);
			}
		}
	}
}

static void irVari(struct AstNode *type,char *name,struct ObjectList *list,struct Function *func,int renamingLabel){
	struct Object *t,*r;
	int i,pd,sz;
	if (type->type == VOIDTYPE){
		pushBackObject(list,NULL,0);
		return;
	}
	if (list == funcList->e[0]->vari){
		for (i = 0;i < list->num;++i) if (strcmp(name,list->e[i]->name) == 0) return;
	}
	pd = 2;
	if (type->type == ARRATYPE && list != func->para) pd = 3;
	if (type->type == ARRATYPE && list == func->para){
		sz = 4;
	}else{
		sz = type->size;
	}
	t = getObject(IRNAME,pd,sz,0,name);
	r = getRegister();
	r->pd = pd;
	r->size = sz;
	pushBackObject(list,t,/*r->data*/registerNum);
	registers->label[registerNum] = renamingLabel;
	if (list == funcList->e[0]->vari) r->data = -1;
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
	irStmt(&ast->c[1],func,beginLabel,endLabel);
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
	makeExpr(&ast->c[0],func,1);
	makeGoto(func,t - 1);
	makeLabl(func,t - 2);
	makeExpr(&ast->c[2],func,1);
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
	if (ast->c[0].type == EMPTEXPR) return;
	makeExpr(&ast->c[0],func,1);
}
static void irRetnStmt(struct AstNode *ast,struct Function * func){
	struct Sentence *s = getSentence();
	s->op = getOp(IRRETNOP,"return");
	ast = &ast->c[0];
	if (ast->type == EMPTEXPR){
		s->num = 0;
	}else{
		struct Object *ob = makeExpr(ast,func,0);
		s->num = 1;
		s->ob[0] = ob;
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
	struct Op *op = getOp(IRITGTOP,"ifTrueGoto");
	struct Object *ob,*ob1,*ob2;
	struct Sentence *s = getSentence();
	if (ast->constant == 0 && ast->type == BINAEXPR && (strcmp(ast->data,"<=") == 0 || strcmp(ast->data,"<") == 0 || strcmp(ast->data,">=") == 0 || strcmp(ast->data,">") == 0 || strcmp(ast->data,"==") == 0 || strcmp(ast->data,"!=") == 0)){
		ob1 = makeExpr(&ast->c[0],func,0);
		ob2 = makeExpr(&ast->c[1],func,0);
		s->op = getOp(IROTGTOP,ast->data);
		s->ob[0] = ob1;
		s->ob[1] = ob2;
		s->ob[2] = makeIntc(label);
		s->num = 3;
		pushBackSentence(func->body,s);
		return;
	}
	ob = makeExpr(ast,func,0);
	s->op = op;
	s->ob[0] = ob;
	s->ob[1] = makeIntc(label);
	s->num = 2;
	pushBackSentence(func->body,s);
}
static void makeIfgt(struct AstNode *ast,struct Function *func,int label){
	struct Op *op = getOp(IRIFGTOP,"ifFalseGoto");
	struct Object *ob,*ob1,*ob2;
	struct Sentence *s = getSentence();
	if (ast->constant == 0 && ast->type == BINAEXPR && (strcmp(ast->data,"<=") == 0 || strcmp(ast->data,"<") == 0 || strcmp(ast->data,">=") == 0 || strcmp(ast->data,">") == 0 || strcmp(ast->data,"==") == 0 || strcmp(ast->data,"!=") == 0)){
		ob1 = makeExpr(&ast->c[0],func,0);
		ob2 = makeExpr(&ast->c[1],func,0);
		s->op = getOp(IROFGTOP,ast->data);
		s->ob[0] = ob1;
		s->ob[1] = ob2;
		s->ob[2] = makeIntc(label);
		s->num = 3;
		pushBackSentence(func->body,s);
		return;
	}
	ob = makeExpr(ast,func,0);
	s->op = op;
	s->ob[0] = ob;
	s->ob[1] = makeIntc(label);
	s->num = 2;
	pushBackSentence(func->body,s);
}
static struct Object *makeExpr(struct AstNode *ast,struct Function *func,int notUsed){
	struct Object *ob,*ob1,*ob2,*ob3;
	if (ast->constant){
		return makeIntc(ast->value);
	}
	if (ast->type == EMPTEXPR){
		return NULL;
	}else if (ast->type == BINAEXPR){
		struct Sentence *s;
		if (strcmp(ast->data,"&&") == 0){
			int t;
			struct Sentence *s;
			labelNum += 2;
			t = labelNum;
			makeIfgt(&ast->c[0],func,t - 1);
			ob1 = getRegister();
			ob1->data = -1;
			ob2 = makeExpr(&ast->c[1],func,0);
			s = getSentence();
			s->op = getOp(IRLGASOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob2;
			s->num = 2;
			pushBackSentence(func->body,s);
			makeGoto(func,t);
			makeLabl(func,t - 1);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = makeIntc(0);
			s->num = 2;
			pushBackSentence(func->body,s);
			makeLabl(func,t);
			return ob1;
		}else if (strcmp(ast->data,"||") == 0){
			int t;
			struct Sentence *s;
			labelNum += 2;
			t = labelNum;
			makeItgt(&ast->c[0],func,t - 1);
			ob1 = getRegister();
			ob1->data = -1;
			ob2 = makeExpr(&ast->c[1],func,0);
			s = getSentence();
			s->op = getOp(IRLGASOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob2;
			s->num = 2;
			pushBackSentence(func->body,s);
			makeGoto(func,t);
			makeLabl(func,t - 1);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = makeIntc(1);
			s->num = 2;
			pushBackSentence(func->body,s);
			makeLabl(func,t);
			return ob1;
		}
		s = getSentence();
		ob1 = makeExpr(&ast->c[0],func,0);
		ob2 = makeExpr(&ast->c[1],func,0);
		if (strcmp(ast->data,",") == 0){
			return ob2;
		}else if (strcmp(ast->data,"=") == 0){
//			if (ast->c[1].retType->type == ARRATYPE)
//				s->op = getOp(IRARASOP,"=");
//			else
				s->op = getOp(IRASSIOP,"=");
			if (ast->c[0].retType->type == INTETYPE){
				s->ob[0] = ob1;
				s->ob[1] = ob2;
				s->size = 4;
				s->num = 2;
				pushBackSentence(func->body,s);
				return ob1;
			}else if (ast->c[0].retType->type == CHARTYPE){
				s->ob[0] = ob1;
				s->ob[1] = ob2;
				s->size = 1;
				s->num = 2;
				pushBackSentence(func->body,s);
				return ob1;
			}else if (ast->c[0].retType->type == PTERTYPE){
				s->ob[0] = ob1;
				s->ob[1] = ob2;
				s->size = 4;
				s->num = 2;
				pushBackSentence(func->body,s);
				return ob1;
			}else if (ast->c[0].retType->type == ARRATYPE){
				//never
				return NULL;
			}else if (ast->c[0].retType->type == STRUTYPE){
				s->ob[0] = ob1;
				s->ob[1] = ob2;
				s->size = ast->c[0].size;
				s->num = 2;
				pushBackSentence(func->body,s);
				return ob1;
			}else if (ast->c[0].retType->type == UNIOTYPE){
				s->ob[0] = ob1;
				s->ob[1] = ob2;
				s->size = ast->c[0].size;
				s->num = 2;
				pushBackSentence(func->body,s);
				return ob1;
			}else{
				//never
				return NULL;
			}
		}else if (strcmp(ast->data,"|") == 0){
			s->op = getOp(IRBINAOP,"|");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"^") == 0){
			s->op = getOp(IRBINAOP,"^");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"&") == 0){
			s->op = getOp(IRBINAOP,"&");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"<") == 0){
			s->op = getOp(IRBINAOP,"<");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,">") == 0){
			s->op = getOp(IRBINAOP,">");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"+") == 0){
			s->op = getOp(IRBINAOP,"+");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			if (ast->c[0].retType->type == ARRATYPE || ast->c[0].retType->type == PTERTYPE){
				struct Sentence *tmp = getSentence();
				tmp->op = getOp(IRBINAOP,"*");
				tmp->ob[0] = getRegister();
				tmp->ob[0]->data = -1;
				tmp->ob[1] = ob2;
				tmp->ob[2] = makeIntc(ast->retType->c[0].size);
				tmp->num = 3;
				pushBackSentence(func->body,tmp);
				s->ob[2] = tmp->ob[0];
				s->ob[0]->pd = 2;
				s->ob[0]->size = ast->size;
			}else if (ast->c[1].retType->type == ARRATYPE || ast->c[1].retType->type == PTERTYPE){
				struct Sentence *tmp = getSentence();
				tmp->op = getOp(IRBINAOP,"*");
				tmp->ob[0] = getRegister();
				tmp->ob[0]->data = -1;
				tmp->ob[1] = ob1;
				tmp->ob[2] = makeIntc(ast->retType->c[0].size);
				tmp->num = 3;
				pushBackSentence(func->body,tmp);
				s->ob[1] = ob2;
				s->ob[2] = tmp->ob[0];
				s->ob[0]->pd = 2;
				s->ob[0]->size = ast->size;
			}
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"-") == 0){
			s->op = getOp(IRBINAOP,"-");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			if (ast->c[0].retType->type == ARRATYPE || ast->c[0].retType->type == PTERTYPE){
				if (ast->c[1].retType->type == ARRATYPE || ast->c[1].retType->type == PTERTYPE){
					s->num = 3;
					pushBackSentence(func->body,s);
					ob1 = getRegister();
					ob1->data = -1;
					ob2 = s->ob[0];
					s = getSentence();
					s->op = getOp(IRBINAOP,"/");
					s->ob[0] = ob1;
					s->ob[1] = ob2;
					s->ob[2] = makeIntc(ast->c[0].retType->c[0].size);
					s->num = 3;
					pushBackSentence(func->body,s);
					return s->ob[0];
				}else{
					struct Sentence *tmp = getSentence();
					tmp->op = getOp(IRBINAOP,"*");
					tmp->ob[0] = getRegister();
					tmp->ob[0]->data = -1;
					tmp->ob[1] = ob2;
					tmp->ob[2] = makeIntc(ast->retType->c[0].size);
					tmp->num = 3;
					pushBackSentence(func->body,s);
					s->ob[2] = tmp->ob[0];
					s->ob[0]->pd = 2;
					s->ob[0]->size = ast->size;
					s->num = 3;
					pushBackSentence(func->body,s);
					return s->ob[0];
				}
			}
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"*") == 0){
			s->op = getOp(IRBINAOP,"*");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"/") == 0){
			s->op = getOp(IRBINAOP,"/");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"%") == 0){
			s->op = getOp(IRBINAOP,"%");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"==") == 0){
			s->op = getOp(IRBINAOP,"==");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"!=") == 0){
			s->op = getOp(IRBINAOP,"!=");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"<=") == 0){
			s->op = getOp(IRBINAOP,"<=");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,">=") == 0){
			s->op = getOp(IRBINAOP,">=");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"<<") == 0){
			s->op = getOp(IRBINAOP,"<<");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,">>") == 0){
			s->op = getOp(IRBINAOP,">>");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"*=") == 0){
			ob3 = getRegister();
			ob3->data = -1;
			s->op = getOp(IRBINAOP,"*");
			s->ob[0] = ob3;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob3;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"/=") == 0){
			ob3 = getRegister();
			ob3->data = -1;
			s->op = getOp(IRBINAOP,"/");
			s->ob[0] = ob3;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob3;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"%=") == 0){
			ob3 = getRegister();
			ob3->data = -1;
			s->op = getOp(IRBINAOP,"%");
			s->ob[0] = ob3;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob3;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"<<=") == 0){
			ob3 = getRegister();
			ob3->data = -1;
			s->op = getOp(IRBINAOP,"<<");
			s->ob[0] = ob3;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob3;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,">>=") == 0){
			ob3 = getRegister();
			ob3->data = -1;
			s->op = getOp(IRBINAOP,">>");
			s->ob[0] = ob3;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob3;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"&=") == 0){
			ob3 = getRegister();
			ob3->data = -1;
			s->op = getOp(IRBINAOP,"&");
			s->ob[0] = ob3;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob3;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"|=") == 0){
			ob3 = getRegister();
			ob3->data = -1;
			s->op = getOp(IRBINAOP,"|");
			s->ob[0] = ob3;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob3;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"^=") == 0){
			ob3 = getRegister();
			ob3->data = -1;
			s->op = getOp(IRBINAOP,"^");
			s->ob[0] = ob3;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			s->num = 3;
			pushBackSentence(func->body,s);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob3;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"+=") == 0){
			ob3 = getRegister();
			ob3->data = -1;
			s->op = getOp(IRBINAOP,"+");
			s->ob[0] = ob3;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			if (ast->c[0].retType->type == PTERTYPE){
				struct Sentence *tmp = getSentence();
				struct Object *r = getRegister();
				tmp->op = getOp(IRBINAOP,"*");
				tmp->ob[0] = r;
				tmp->ob[1] = ob2;
				tmp->ob[2] = makeIntc(ast->retType->c[0].size);
				tmp->num = 3;
				pushBackSentence(func->body,tmp);
				s->ob[2] = r;
			}
			s->num = 3;
			pushBackSentence(func->body,s);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob3;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"-=") == 0){
			ob3 = getRegister();
			ob3->data = -1;
			s->op = getOp(IRBINAOP,"-");
			s->ob[0] = ob3;
			s->ob[1] = ob1;
			s->ob[2] = ob2;
			if (ast->c[0].retType->type == PTERTYPE){
				struct Sentence *tmp = getSentence();
				struct Object *r = getRegister();
				tmp->op = getOp(IRBINAOP,"*");
				tmp->ob[0] = r;
				tmp->ob[1] = ob2;
				tmp->ob[2] = makeIntc(ast->retType->c[0].size);
				tmp->num = 3;
				pushBackSentence(func->body,tmp);
				s->ob[2] = r;
			}
			s->num = 3;
			pushBackSentence(func->body,s);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob3;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else{
			//never
			return NULL;
		}
	}else if (ast->type == UNAREXPR){
		struct Sentence *s = getSentence();
		ob1 = makeExpr(&ast->c[0],func,0);
		if (strcmp(ast->data,"&") == 0){
			s->op = getOp(IRUNAROP,"&");
			ob = getRegister();
			ob->pd = 2;
			ob->size = 4;
			ob->data = -1;
			s->ob[0] = ob;
			s->ob[1] = ob1;
			s->num = 2;
			pushBackSentence(func->body,s);
			return ob;
		}else if (strcmp(ast->data,"*") == 0){
			ob = getRegister();
			ob->data = -1;
			ob->pd = 2;
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob;
			s->ob[1] = makeIntc(0);
			s->num = 2;
			pushBackSentence(func->body,s);
			s = getSentence();
//			if (ast->c[0].retType->type == ARRATYPE)
//				s->op = getOp(IRARRROP,"[]");
//			else
				s->op = getOp(IRPTRROP,"[]");
			ob2 = getRegister();
			ob2->data = -1;
			ob2->size = ast->size;
			ob2->pd = 1;
			s->ob[0] = ob2;
			s->ob[1] = ob1;
			s->ob[2] = ob;
			s->num = 3;
			pushBackSentence(func->body,s);
			return ob2;
/*	
			s->op = getOp(IRUNAROP,"*");
			ob = getRegister();
			ob->pd = 1;
			ob->size = ast->size;
			ob->data = -1;
			ob->size = ast->size;
			s->ob[0] = ob;
			s->ob[1] = ob1;
			s->num = 2;
			pushBackSentence(func->body,s);
			return ob;
*/
		}else if (strcmp(ast->data,"+") == 0){
			s->op = getOp(IRUNAROP,"+");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"-") == 0){
			s->op = getOp(IRUNAROP,"-");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"~") == 0){
			s->op = getOp(IRUNAROP,"~");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"!") == 0){
			s->op = getOp(IRUNAROP,"!");
			s->ob[0] = getRegister();
			s->ob[0]->data = -1;
			s->ob[1] = ob1;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else if (strcmp(ast->data,"++") == 0){
			if (notUsed){
				s->op = getOp(IRINCROP,"++");
				s->ob[0] = ob1;
				if (ast->retType->type == PTERTYPE)
					s->ob[1] = makeIntc(ast->retType->c[0].size);
				else
					s->ob[1] = makeIntc(1);
				s->num = 2;
				s->size = ast->size;
				pushBackSentence(func->body,s);
				return NULL;
			}
			ob = getRegister();
			ob->size = 4;
			ob->data = -1;
			s->op = getOp(IRBINAOP,"+");
			s->ob[0] = ob;
			s->ob[1] = ob1;
			if (ast->retType->type == PTERTYPE)
				s->ob[2] = makeIntc(ast->retType->c[0].size);
			else
				s->ob[2] = makeIntc(1);
			s->num = 3;
			pushBackSentence(func->body,s);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];

		}else if (strcmp(ast->data,"--") == 0){
			if (notUsed){
				s->op = getOp(IRDECROP,"--");
				s->ob[0] = ob1;
				if (ast->retType->type == PTERTYPE)
					s->ob[1] = makeIntc(ast->retType->c[0].size);
				else
					s->ob[1] = makeIntc(1);
				s->num = 2;
				s->size = ast->size;
				pushBackSentence(func->body,s);
				return NULL;
			}
			
			ob = getRegister();
			ob->size = 4;
			ob->data = -1;
			s->op = getOp(IRBINAOP,"-");
			s->ob[0] = ob;
			s->ob[1] = ob1;
			if (ast->retType->type == PTERTYPE)
				s->ob[2] = makeIntc(ast->retType->c[0].size);
			else
				s->ob[2] = makeIntc(1);
			s->num = 3;
			pushBackSentence(func->body,s);
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ob1;
			s->ob[1] = ob;
			s->num = 2;
			pushBackSentence(func->body,s);
			return s->ob[0];
		}else{
			//never
			return NULL;
		}
	}else if (ast->type == SZOFEXPR){
		ob1 = makeExpr(&ast->c[0],func,0);
		return makeIntc(ast->value);
	}else if (ast->type == CASTEXPR){
		struct Sentence *s = getSentence();
		ob = getRegister();
		ob->data = -1;
		ob->size = ast->size;
		ob->pd = 2;
//		if (ast->retType->type == PTERTYPE) ob->pd = 1;
		s->op = getOp(IRASSIOP,"=");
		s->ob[0] = ob;
		ob1 = makeExpr(&ast->c[1],func,0);
		s->ob[1] = ob1;
		s->num = 2;
		pushBackSentence(func->body,s);
		return ob;
	}else if (ast->type == PTERACSS){
		struct Sentence *s = getSentence();
		ob = getRegister();
		ob->data = -1;
		ob->size = ast->size;
		ob->pd = 1;
		
		if (ast->retType->type == ARRATYPE){
			ob->size = 4;
			ob->pd = 2;
		}
		
//		if (ast->retType->type == ARRATYPE || ast->retType->type == PTERTYPE) ob->pd = 1;
		s->op = getOp(IRPTRROP,"[]");
		s->ob[0] = ob;
		s->ob[1] = makeExpr(&ast->c[0],func,0);
		s->ob[2] = makeIntc(ast->pos);
		s->num = 3;
		pushBackSentence(func->body,s);
		return ob;
	}else if (ast->type == RECOACSS){
		struct Sentence *s = getSentence();
		ob = getRegister();
		ob->data = -1;
		ob->size = ast->size;
		ob->pd = 1;
		
		if (ast->retType->type == ARRATYPE){
			ob->size = 4;
			ob->pd = 2;
		}
		
//		if (ast->retType->type == ARRATYPE || ast->retType->type == PTERTYPE) ob->pd = 1;
		s->op = getOp(IRARRROP,"[]");
		s->ob[0] = ob;
		s->ob[1] = makeExpr(&ast->c[0],func,0);
		s->ob[2] = makeIntc(ast->pos);
		s->num = 3;
		pushBackSentence(func->body,s);
		return ob;
	}else if (ast->type == SELFINCR){
		struct Sentence *s;
		ob1 = makeExpr(&ast->c[0],func,0);
		
		if (notUsed){
			s = getSentence();
			s->op = getOp(IRINCROP,"++");
			s->ob[0] = ob1;
			if (ast->retType->type == PTERTYPE)
				s->ob[1] = makeIntc(ast->retType->c[0].size);
			else
				s->ob[1] = makeIntc(1);
			s->num = 2;
			s->size = ast->size;
			pushBackSentence(func->body,s);
			return NULL;
		}
		
		ob2 = getRegister();
		ob2->data = -1;
		ob3 = getRegister();
		ob3->data = -1;
		s = getSentence();
		s->op = getOp(IRASSIOP,"=");
		s->ob[0] = ob2;
		s->ob[1] = ob1;
		s->num = 2;
		pushBackSentence(func->body,s);
		s = getSentence();
		s->op = getOp(IRBINAOP,"+");
		s->ob[0] = ob3;
		s->ob[1] = ob1;
		if (ast->retType->type == PTERTYPE)
			s->ob[2] = makeIntc(ast->retType->c[0].size);
		else
			s->ob[2] = makeIntc(1);
		s->num = 3;
		pushBackSentence(func->body,s);
		s = getSentence();
		s->op = getOp(IRASSIOP,"=");
		s->ob[0] = ob1;
		s->ob[1] = ob3;
		s->num = 2;
		pushBackSentence(func->body,s);
		return ob2;
	}else if (ast->type == SELFDECR){
		struct Sentence *s;
		ob1 = makeExpr(&ast->c[0],func,0);
		
		if (notUsed){
			s = getSentence();
			s->op = getOp(IRDECROP,"--");
			s->ob[0] = ob1;
			if (ast->retType->type == PTERTYPE)
				s->ob[1] = makeIntc(ast->retType->c[0].size);
			else
				s->ob[1] = makeIntc(1);
			s->num = 2;
			s->size = ast->size;
			pushBackSentence(func->body,s);
			return NULL;
		}
		
		ob2 = getRegister();
		ob2->data = -1;
		ob3 = getRegister();
		ob3->data = -1;
		s = getSentence();
		s->op = getOp(IRASSIOP,"=");
		s->ob[0] = ob2;
		s->ob[1] = ob1;
		s->num = 2;
		pushBackSentence(func->body,s);
		s = getSentence();
		s->op = getOp(IRBINAOP,"-");
		s->ob[0] = ob3;
		s->ob[1] = ob1;
		if (ast->retType->type == PTERTYPE)
			s->ob[2] = makeIntc(ast->retType->c[0].size);
		else
			s->ob[2] = makeIntc(1);
		s->num = 3;
		pushBackSentence(func->body,s);
		s = getSentence();
		s->op = getOp(IRASSIOP,"=");
		s->ob[0] = ob1;
		s->ob[1] = ob3;
		s->num = 2;
		pushBackSentence(func->body,s);
		return ob2;
	}else if (ast->type == ARRAACSS){
		struct Sentence *s = getSentence();
		ob = getRegister();
		ob->data = -1;
		ob->pd = 2;
		s->op = getOp(IRBINAOP,"*");
		s->ob[0] = ob;
		s->ob[1] = makeExpr(&ast->c[1],func,0);
		s->ob[2] = makeIntc(ast->size);
		s->num = 3;
		pushBackSentence(func->body,s);
		s = getSentence();
//		if (ast->c[0].retType->type == ARRATYPE)
//			s->op = getOp(IRARRROP,"[]");
//		else
			s->op = getOp(IRPTRROP,"[]");
		ob1 = getRegister();
		ob1->data = -1;
		ob1->size = ast->size;
		ob1->pd = 1;
		
		if (ast->retType->type == ARRATYPE){
			ob1->size = 4;
			ob1->pd = 2;
		}
		
		s->ob[0] = ob1;
		s->ob[1] = makeExpr(&ast->c[0],func,0);
		s->ob[2] = ob;
		s->num = 3;
		pushBackSentence(func->body,s);
		return ob1;
	}else if (ast->type == FUNCCALL){
		struct Sentence *s;
		struct AstNode *tmp = &ast->c[1];
		struct Object **f;
		int i, cur = 0,num;
		if (tmp->type != EMPTEXPR){
			f = malloc(sizeof(struct Object *) * tmp->num);
			num = tmp->num;
		}else{
			f = NULL;
			num = 0;
		}
		for (i = 0;i < num;++i){
			struct Object *o/* = getRegister()*/;
			f[i] = makeExpr(&tmp->c[i],func,0);
			if (tmp->c[i].retType->type == ARRATYPE) f[i]->size = 4;
			
			if (tmp->c[i].type != FUNCCALL){
				continue;
			}
			
			o = getRegister();
			o->size = f[i]->size;
			if (o->size < 4) o->size = 4;
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = o;
			s->ob[1] = f[i];
			s->num = 2;
			pushBackSentence(func->body,s);
			f[i] = o;
		}
		if (ast->retType->type != VOIDTYPE){
			s = getSentence();
			s->op = getOp(IRRTSZOP,"");
			s->ob[0] = makeIntc(ast->retType->size);
			s->num = 1;
			pushBackSentence(func->body,s);
		}
		for (i = 0;i < num;++i){
/*			struct Object *o = getRegister();
			o->pd = 2;
			o->size = f[i]->size;
			if (o->size < 4) o->size = 4;
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = o;
			s->ob[1] = f[i];
			s->num = 2;
			pushBackSentence(func->body,s);
*/		
			s = getSentence();
			s->op = getOp(IRPARAOP,"param");
			s->ob[0] = f[i];
			s->num = 1;
			pushBackSentence(func->body,s);
			/*if (f[i]->pd == 1) cur += 4;else */cur += f[i]->size;
			if (cur & 3) cur = ((cur >> 2) + 1) << 2;
			s->size = f[i]->size;
		}
		if (f != NULL) free(f);
		if (ast->retType->type == VOIDTYPE){
			int i,number;
			s = getSentence();
			s->op = getOp(IRCALLOP,"call");
			for (i = 0;i < funcList->num;++i) if (strcmp(ast->c[0].data,funcList->e[i]->name) == 0){
				number = i;
				break;
			}
			s->ob[0] = makeIntc(number);
			s->ob[1] = makeIntc(tmp->num);
			s->num = 2;
			pushBackSentence(func->body,s);
			if (func->mainSpace < cur) func->mainSpace = cur;
			return NULL;
		}else{
			struct Object *ret;
			int i,number;
			
//			if (ast->retType->type == PTERTYPE) ob->pd = 1;
			s = getSentence();
			s->op = getOp(IRCALLOP,"call");
			for (i = 0;i < funcList->num;++i) if (strcmp(ast->c[0].data,funcList->e[i]->name) == 0){
				number = i;
				break;
			}
			if (funcList->e[number]->para != NULL) cur += funcList->e[number]->para->e[0]->size;else cur += 4;
			if (cur & 3) cur = ((cur >> 2) + 1) << 2;
			if (func->mainSpace < cur) func->mainSpace = cur;
			
//			if (strcmp(ast->c[0].data,"printf") == 0){
			if (notUsed){
				s->ob[0] = makeIntc(number);
				s->ob[1] = makeIntc(tmp->num);
				s->num = 2;
				pushBackSentence(func->body,s);
				return NULL;
			}
			
			ob = getRegister();
			ob->data = -1;
			ob->size = ast->size;
			ob->pd = 1;
			
			s->ob[0] = ob;
			s->ob[1] = makeIntc(number);
			s->ob[2] = makeIntc(tmp->num);
			s->num = 3;
			pushBackSentence(func->body,s);
			
			ret = getRegister();
			ret->size = ast->size;
			s = getSentence();
			s->op = getOp(IRASSIOP,"=");
			s->ob[0] = ret;
			s->ob[1] = ob;
			s->num = 2;
			pushBackSentence(func->body,s);
			
			return ret;
		}
	}else if (ast->type == IDEN){
		int i,n,t;
		struct ObjectList *l;
		l = func->para;
		if (l == NULL) n = 0;else n = l->num;
		for (i = 0;i < n;++i) if (l->e[i] != NULL && strcmp(ast->data,l->e[i]->name) == 0){
/*			if (ast->retType->type == ARRATYPE){
				struct Object *ob = getRegister(),*tmp = registers->e[l->link[i]];
				struct Sentence *s = getSentence();
				s->op = getOp(IRARASOP,"=");
				ob->pd = 2;
				ob->data = -1;
				s->ob[0] = ob;
				s->ob[1] = tmp;
				s->num = 2;
				pushBackSentence(func->body,s);
				return ob;
			}else{*/
				t = l->link[i];
				if (registers->label[t] != ast->renamingLabel) continue;
				return registers->e[t];
//			}
		}
		l = func->vari;
		if (l == NULL) n = 0;else n = l->num;
		for (i = 0;i < n;++i) if (l->e[i] != NULL && strcmp(ast->data,l->e[i]->name) == 0){
			t = l->link[i];
			if (registers->label[t] != ast->renamingLabel) continue;
			if (ast->retType != NULL && ast->retType->type == ARRATYPE){
				struct Object *ob,*tmp;
				struct Sentence *s;
//dangerous
				if (l->tmpLink[i] != NULL){
//					return l->tmpLink[i];
				}
				ob = getRegister();
//				ob->data = -2;
				tmp = registers->e[l->link[i]];
				s = getSentence();
				s->op = getOp(IRARASOP,"=");
				ob->pd = 2;
//				ob->data = -1;
				s->ob[0] = ob;
				s->ob[1] = tmp;
				s->num = 2;
				pushBackSentence(func->body,s);
//				l->tmpLink[i] = ob;
				return ob;
			}else{
				return registers->e[l->link[i]];
			}
		}
		l = funcList->e[0]->vari;
		if (l == NULL) n = 0;else n = l->num;
		for (i = 0;i < n;++i) if (l->e[i] != NULL && strcmp(ast->data,l->e[i]->name) == 0){
			t = l->link[i];
			if (registers->label[t] != ast->renamingLabel) continue;
			if (ast->retType != NULL && ast->retType->type == ARRATYPE){
				struct Object *ob,*tmp;
				struct Sentence *s;
//dangerous
				if (l->tmpLink[i] != NULL){
					return l->tmpLink[i];
				}
				ob = getRegister();
				ob->data = -2;
				tmp = registers->e[l->link[i]];
				s = getSentence();
				s->op = getOp(IRARASOP,"=");
				ob->pd = 2;
//				ob->data = -1;
				s->ob[0] = ob;
				s->ob[1] = tmp;
				s->num = 2;
				pushBackSentence(funcList->e[0]->body,s);
				l->tmpLink[i] = ob;
				return ob;
			}else{
				return registers->e[l->link[i]];
			}
		}
	}else if (ast->type == INTECONS){
		return makeIntc(ast->value);
	}else if (ast->type == CHARCONS){
		return makeIntc(ast->value);
	}else if (ast->type == STRICONS){
		int i,l;
		struct String *st;
		struct Object *o;
		struct Sentence *s;
//		for (i = 0;i < string->num;++i){
//			if (strcmp(ast->data,string->e[i]->s) == 0) return string->e[i]->link;
//		}
		st = getString(ast->data);
		l = strlen(ast->data);
		for (i = 0;i < l;++i){
			if (ast->data[i] == '%'){
				if (ast->data[i + 1] == 'c'){
					numOfFmt[0]++;
				}else if (ast->data[i + 1] == 'd'){
					numOfFmt[1]++;
				}else if (ast->data[i + 1] == 's'){
					numOfFmt[2]++;
				}else if (ast->data[i + 1] == '0' || ast->data[i + 1] == '.'){
					numOfFmt[3]++;
				}
				++i;
			}
		}
		
		o = getRegister();
		s = getSentence();
		pushBackString(string,st);
		s->op = getOp(IRASSCOP,"=");
		s->ob[0] = o;
		s->ob[1] = makeIntc(string->num - 1);
		s->num = 2;
		pushBackSentence(func->body,s);
		string->e[string->num - 1]->link = o;
		return o;
	}else{
		//never
	}
	return NULL;
}
static struct Object *makeIntc(int value){
	return getObject(IRINTC,0,4,value,"");
}


static int make4(int x){
	if (x & 3) x = ((x >> 2) + 1) << 2;
	return x;
}
static struct String *getString(char *s){
	struct String *st = malloc(sizeof(struct String));
	st->size = make4(strlen(s) + 1);
	st->s = strdup(s);
	return st;
}
static void freeString(struct String *s){
	if (s == NULL) return;
	free(s->s);
	free(s);
}
static struct StringList *getStringList(void){
	struct StringList *l = malloc(sizeof(struct StringList));
	l->e = malloc(sizeof(struct String *));
	l->num = 0;
	l->cap = 1;
	return l;
}
static void resizeStringList(struct StringList *l){
	struct String **tmp;
	int i;
	if (l->num < l->cap) return;
	l->cap <<= 1;
	tmp = malloc(sizeof(struct String *) * l->cap);
	for (i = 0;i < l->num;++i) tmp[i] = l->e[i];
	free(l->e);
	l->e = tmp;
}
static void pushBackString(struct StringList *l,struct String *s){
	resizeStringList(l);
	++l->num;
	l->e[l->num - 1] = s;
}
void freeStringList(struct StringList *l){
	int i;
	if (l == NULL) return;
	for (i = 0;i < l->num;++i) freeString(l->e[i]);
	free(l->e);
	free(l);
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

void ir(void){
	char *s = (char *)malloc(1000010);
//	int i;
	
	readInput(s);
	semanticCheck(s);
//	astPrint(NULL,ast,0);
	
	registerNum = labelNum = 0;
	numOfFmt[0] = numOfFmt[1] = numOfFmt[2] = 0;
	registers = getRegisterList();
	string = getStringList();
	irMain(ast);
	
//	freeFunctionList(funcList);
//	freeRegisterList(registers);
	
	astDel(ast);
	free(ast);
	free(list);
	free(s);
}
