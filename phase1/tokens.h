#ifndef _TOKENS_H_
#define _TOKENS_H_
#include <string.h>
enum TokenType{
	ID,CON,KEY,SYM
};
enum TokenDetail{
	IDENTIFIER = 1,
	CON_NUM,CON_CHAR,CON_STR,
	VOID,CHAR,INT,STRUCT,UNION,IF,ELSE,WHILE,FOR,CONTINUE,BREAK,RETURN,SIZEOF,
	SYMBOL,
	END
};
struct token{
	int tokenType,tokenDetail,type;
	char *ptr;
};
static char keywordDic[20][10] = {"void","char","int","struct","union","if","else","while","for","continue","break","return","sizeof"};
void getTokenType(struct token *);
static int check(char *);
#endif
