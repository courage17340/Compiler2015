#ifndef _PARSER_H_
#define _PARSER_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"
struct node{
	char *data;
	struct node *c;
	int num,flag;//num of children
};
static int error = 0;
static struct token *makeList(char *);
static struct token *list;
struct node *parse(char *);
static int M[200][200],listSize,nonNum,terNum,ruleNum;
static char terminals[200][40],nonterminals[200][40];
struct ruleType{
	int non,num,items[15][2];
};
static struct ruleType rules[300];
static void init(void);
static int findTer(char *);
static int findNon(char *);
static void build(struct node *,int *,int,int);
static int equal(struct token,char *);
static struct node *getNode(void);
static int getType(struct token);
static void print(struct node *,int);
static void del(struct node *);


//------struct------definitions------

struct Iden{
	char *iden;
};

struct BasiType{
	int type;
	union{
		struct InteType{} *intt;
		struct CharType{} *chrt;
		struct VoidType{} *voit;
		struct StruType{struct Iden *name;} *strt;
		struct UnioType{struct Iden *name;} *unit;
	}v;
};

struct Expr{
	int type;
	union{
		struct EmptExpr{} *empt;
		struct BinaExpr{
			struct Expr *left;
			struct BinaOprt{char biop[4];} *biop;
			struct Expr *rigt;
		}*bina;
		struct UnarExpr{
			struct UnarOprt{char unop[4];} *unop;
			struct Expr *expr;
		}*unar;
		struct SzofExpr{
			struct Type{
				int type;
				union{
					struct BasiType *bast;
					struct PterType{struct Type *base;} *ptrt;
					struct ArraType{
						struct Type *base;
						struct Expr *size;
					}*arrt;
				}v;
			}*type;
		}*szof;
		struct CastExpr{
			struct Type *cast;
			struct Expr *expr;
		}*cast;
		struct PterAcss{
			struct Expr *body;
			struct Iden *arrt;
		}*ptac;
		struct RecoAcss{
			struct Expr *body;
			struct Iden *arrt;
		}*reac;
		struct SelfIncr{struct Expr *body;} *sinc;
		struct SelfDecr{struct Expr *body;} *sdec;
		struct ArraAcss{
			struct Expr *body;
			struct Expr *indx;
		}*arac;
		struct FuncCall{
			int argv;
			struct Iden *iden;
			struct Expr *args;
		}*fccl;
		struct Iden *iden;
		struct InteCons{int valu;} *intc;
		struct CharCons{char valu;} *chrc;
		struct StriCons{char *valu;} *stri;
	}v;
};

struct Stmt{
	int type;
	union{
		struct BreaStmt{} *brea;
		struct ContStmt{} *cont;
		struct IfteStmt{
			struct Expr *cond;
			struct Stmt *cons;
			struct Stmt *alte;
		}*ifte;
		struct ForrLoop{
			struct Expr *init;
			struct Expr *cond;
			struct Expr *step;
			struct Stmt *body;
		}*forr;
		struct WhilLoop{
			struct Expr *cond;
			struct Stmt *body;
		}*whil;
		struct RetnStmt{struct Expr *expr;} *retn;
		struct CompStmt{
			int numd,nums;
			struct Decl{
				int type;
				union{
					struct FuncDecl{
						struct Type *retu;
						struct Iden *name;
						struct Para *para;
						struct CompStmt *body;
					}*func;
					struct StruDecl{
						int numm;
						struct Iden *name;
						struct VariDecl **memb;
					}*stru;
					struct UnioDecl{
						int numm;
						struct Iden *name;
						struct VariDecl **memb;
					}*unio;
					struct VariDecl{
						struct Type *type;
						struct Iden *name;
						struct Init *init;
					}*vari;
				}v;
			}**decl;
			struct Stmt **stmt;
		}*comp;
		struct Expr *expr;
	};
};



#endif
