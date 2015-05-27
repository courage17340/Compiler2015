#ifndef _TOKENS_H_
#define _TOKENS_H_
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
void getTokenType(struct token *);
#endif
