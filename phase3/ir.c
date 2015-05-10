#include "ir.h"
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

nop
do_nothing
*/
static int temp,IRNum,labelNum;
//started by 1
enum OpType{
	IRUNAROP,IRBINAOP,IRASSIOP,IRPARAOP,IRCALLOP,IRLABLOP,IRGOTOOP,IRITGTOP,IRIFGTOP,IRARRROP,IRARRWOP,IRPTRROP,IRPTRWOP,IRNOPPOP
//	unary    binary   =        param    call     label    goto     ifTgoto  ifFgoto  a=b[x],4 a[x]=b,4 t0=*a,4  *a=t0,4  nop
};
enum ObjectType{
	IRSTRC,IRINTC,IRNAME,IRTEMP
};
struct Op{
	int type;
	char *s;
};
struct Object{
	int type,tempNum;
	union{
		char *str;
		int value;
		struct AstNode *bind;
	}data;
};
struct Sentence{
	struct Object ob1,ob2,ob3;
	struct Op op;
	int size,num;
};
static struct Sentence IRList[100010];

static void readInput(char *s){
	int t = -1,c;
	c = getchar();
	while (c != EOF){
		s[++t] = c;
		c = getchar();
	}
	s[++t] = 0;
}
static void pushSentence(struct Sentence *x){
	++IRNum;
	IRList[IRNum] = *x;
}
static struct Object addIntc(int x){
	struct Object t;
	t.type = IRINTC;
	t.data.value = x;
	return t;
}
static struct Object addExpr(struct AstNode *ast){
	//TODO
	struct Object t;
	return t;
}
static void addItgt(struct AstNode *ast,int label){
	struct Object t = addExpr(ast);
	struct Sentence tmp;
	tmp.op.type = IRITGTOP;
	tmp.ob1 = t;
	tmp.ob2 = addIntc(label);
	tmp.num = 2;
	pushSentence(&tmp);
}
static void addIfgt(struct AstNode *ast,int label){
	struct Object t = addExpr(ast);
	struct Sentence tmp;
	tmp.op.type = IRIFGTOP;
	tmp.ob1 = t;
	tmp.ob2 = addIntc(label);
	tmp.num = 2;
	pushSentence(&tmp);
}
static void addGoto(int label){
	struct Sentence tmp;
	tmp.op.type = IRGOTOOP;
	tmp.ob1 = addIntc(label);
	tmp.num = 1;
	pushSentence(&tmp);
}
static void addLabl(int label){
	struct Sentence tmp;
	tmp.op.type = IRLABLOP;
	tmp.ob1 = addIntc(label);
	tmp.num = 1;
	pushSentence(&tmp);
}

static void addStmt(struct AstNode *ast,int beginLabel,int endLabel,int returnLabel);
static void addIfteStmt(struct AstNode *ast,int beginLabel,int endLabel,int returnLabel){
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
	t = labelNum;//labelNum may be modified by other functions, backup for correctness
	addItgt(&ast->c[0],t - 1);
	if (ast->num > 2) addStmt(&ast->c[2],beginLabel,endLabel,returnLabel);
	addGoto(t);
	addLabl(t - 1);
	addStmt(&ast->c[1],beginLabel,endLabel,returnLabel);
	addLabl(t);
}
static void addForLoop(struct AstNode *ast,int beginLabel,int endLabel,int returnLabel){
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
	addExpr(&ast->c[0]);
	addGoto(t - 1);
	addLabl(t - 2);
	addExpr(&ast->c[2]);
	addLabl(t - 1);
	addIfgt(&ast->c[1],t);
	addStmt(&ast->c[3],t - 2,t,returnLabel);
	addGoto(t - 2);
	addLabl(t);
}
static void addWhileLoop(struct AstNode *ast,int beginLabel,int endLabel,int returnLabel){
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
	addLabl(t - 1);
	addIfgt(&ast->c[0],t);
	addStmt(&ast->c[1],t - 1,t,returnLabel);
	addGoto(t - 1);
	addLabl(t);
}
static void addBreakStmt(int label){
	addGoto(label);
}
static void addContStmt(int label){
	addGoto(label);
}
static void addExprStmt(struct AstNode *ast){
	addExpr(&ast->c[0]);
}
static void addReturnStmt(struct AstNode *ast,int label){
	//TODO
}
static void addCompStmt(struct AstNode *ast,int beginLabel,int endLabel,int returnLabel){
	int i;
	for (i = 0;i < ast->num;++i) addStmt(&ast->c[i],beginLabel,endLabel,returnLabel);
}


static void addStmt(struct AstNode *ast,int beginLabel,int endLabel,int returnLabel){
	//TODO
	int i;
	if (ast->type == BREASTMT){
		addBreakStmt(endLabel);
	}else if (ast->type == CONTSTMT){
		addContStmt(beginLabel);
	}else if (ast->type == IFTESTMT){
		addIfteStmt(ast,beginLabel,endLabel,returnLabel);
	}
}




static void addFunc(struct AstNode *ast){
	//TODO
}
static void addVari(struct AstNode *ast,int beginLabel,int endLabel,int returnLabel){
	//TODO
}

static void irMain(struct AstNode *ast){
	int i;
	if (ast->type == ROOT){
		for (i = 0;i < ast->num;++i) irMain(&ast->c[i]);
	}else if (ast->type == DECL){
		for (i = 0;i < ast->num;++i) addVari(&ast->c[i],0,0,0);
	}else if (ast->type == FUNCDECL){
		addFunc(ast);
		if (strcmp(ast->c[1].data,"main") == 0){
			//TODO
		}
	}else if (ast->type == STRUDECL){
		//never
	}else if (ast->type == UNIODECL){
		//never
	}else if (ast->type == VARIDECL){
		for (i = 1;i < ast->num;++i) addVari(&ast->c[i],0,0,0);
	}else{
		//never
	}
}
static void printSentence(struct Sentence *s){
	
}
int main(void){
	char *s = (char *)malloc(1000010);
	int i;
	
	readInput(s);
	semanticCheck(s);
	
	IRNum = 0;
	temp = 0;
	labelNum = 0;
	irMain(ast);
	
	for (i = 1;i <= IRNum;++i) printSentence(IRList + i);
	
	astDel(ast);
	free(ast);
	free(list);
	free(s);
	return 0;
}
