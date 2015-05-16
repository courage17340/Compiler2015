#ifndef _PARSER_H_
#define _PARSER_H
struct node{
	char *data;
	struct node *c;
	int num,flag;//num of children
};
struct token *list;
struct node *parse(char *);
struct ruleType{
	int non,num,items[15][2];
};
//for ast
enum ASTType{
	ROOT,DECL,FUNCDECL,STRUDECL,UNIODECL,VARIDECL,TYPE,BASITYPE,
	INTETYPE,CHARTYPE,VOIDTYPE,STRUTYPE,UNIOTYPE,PTERTYPE,
	ARRATYPE,STMT,BREASTMT,CONTSTMT,IFTESTMT,FORRLOOP,WHILLOOP,EXPRSTMT,
	RETNSTMT,COMPSTMT,EXPR,EMPTEXPR,BINAEXPR,UNAREXPR,SZOFEXPR,
	CASTEXPR,PTERACSS,RECOACSS,SELFINCR,SELFDECR,ARRAACSS,
	FUNCCALL,IDEN,INTECONS,CHARCONS,STRICONS,
	PARA,TYPESPEC,DATAFILD,INIT,FUNCPARA,VARI
};
struct AstNode{
	int type;
	char *data;
	int num,cap;
	struct AstNode *c;
	//following are added for semantic check
	int lValue,constant,value,size,pos;
	void *retType;
};
void cstDel(struct node *);
void doubleSpace(struct AstNode *);
struct AstNode *getAst(int);
void astPrint(char *,struct AstNode *,int);
void astDel(struct AstNode *);
struct AstNode *makeAst(char *,int *,int *,struct node **);
#endif
