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
struct token *list;
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
//for ast
enum ASTType{
	ROOT,DECL,FUNCDECL,STRUDECL,UNIODECL,VARIDECL,TYPE,BASITYPE,
	INTETYPE,CHARTYPE,VOIDTYPE,STRUTYPE,UNIOTYPE,PTERTYPE,
	ARRATYPE,STMT,BREASTMT,CONTSTMT,IFTESTMT,FORRLOOP,WHILLOOP,EXPRSTMT,
	RETNSTMT,COMPSTMT,EXPR,EMPTEXPR,BINAEXPR,UNAREXPR,SZOFEXPR,
	CASTEXPR,PTERACSS,RECOACSS,SELFINCR,SELFDECR,ARRAACSS,
	FUNCCALL,IDEN,INTECONS,CHARCONS,STRICONS,
	PARA,TYPESPEC,DATAFILD,INIT
};
static char ASTFlags[50][30] = {
	"Root","Decl","FunctionDecl","StructDecl","UnionDecl","VarDecl","Type","BasicType",
	"IntType","CharType","VoidType","StructType","UnionType","PointerType",
	"ArrayType","Stmt","BreakStmt","ContinueStmt","IfStmt","ForLoop","WhileLoop","ExprStmt",
	"ReturnStmt","CompoundStmt","Expr","EmptyExpr","BinaryExpr","UnaryExpr","SizeofExpr",
	"CastExpr","PointerAccess","RecordAccess","SelfIncrement","SelfDecrement","ArrayAccess",
	"FunctionCall","Identifier","IntConst","CharConst","StringConst",
	"Parameters","TypeSpecifiers","DataField","Initializer"
};
struct ASTNode{
	int type;
	char *data;
	int num,cap;
	struct ASTNode *c;
};
static void doubleSpace(struct ASTNode *);
static struct ASTNode *getAst(int);
static void AST(struct node *,struct ASTNode *);
static void tab(int);
void astPrint(char *,struct ASTNode *,int);
void astDel(struct ASTNode *);
struct ASTNode *makeAst(char *,int *);
#endif
