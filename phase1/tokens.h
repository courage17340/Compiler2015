#ifndef _TOKENS_H_
#define _TOKENS_H_
#include <string.h>
enum TokenType{
	ID,CON,KEY,SYM
};
enum IdentifierType{
	IDENTIFIER
};
enum ConstantType{
	CON_NUM,CON_CHAR,CON_STR
};
enum KeywordType{
	VOID,CHAR,INT,STRUCT,UNION,IF,ELSE,WHILE,FOR,CONTINUE,BREAK,RETURN,SIZEOF
};
enum SymbolType{
	SYMBOL
};
struct token{
	int tokenType,tokenDetail;
	char *ptr;
};
static char keywordDic[20][10] = {"void","char","int","struct","union","if","else","while","for","continue","break","return","sizeof"};
void getTokenType(struct token *);
static int check(char *);
#endif
