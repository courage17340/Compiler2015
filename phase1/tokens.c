#include "tokens.h"
//removeComments & split needed. '\n's should be replaced
//with 0 so that the buffer is composed of c-style-strs
void getTokenType(struct token *t){
	char *s = t->ptr;
//---constants: char, string, or number---
	if (s[0] == '\''){
		int n = strlen(s);
		t->tokenType = CON;
		t->tokenDetail = CON_CHAR;
		t->ptr = s + 1;
		t->ptr[n - 1] = 0;			//remove ''
		return;
	}
	if (s[0] == '"'){
		int n = strlen(s);
		t->tokenType = CON;
		t->tokenDetail = CON_STR;
		t->ptr = s + 1;
		t->ptr[n - 1] = 0;			//remove ""
		return;
	}
	if ('0' <= s[0] && s[0] <= '9'){
		t->tokenType = CON;
		t->tokenDetail = CON_NUM;
		return;
	}
//---words: identifier or keyword---
	if (s[0] == '_' || s[0] == '$' || ('a' <= s[0] && s[0] <= 'z') || ('A' <= s[0] && s[0] <= 'Z')){
		int k = check(s);
		if (k == -1){
			t->tokenType = ID;
			t->tokenDetail = IDENTIFIER;
		}else{
			t->tokenType = KEY;
			t->tokenDetail = k;
		}
		return;
	}
//---symbol---
	t->tokenType = SYM;
	t->tokenDetail = SYMBOL;
};
static int check(char *s){
	int i;
	for (i = 0;i < 13;++i) if (strcmp(s,keywordDic[i]) == 0) return i;
	return -1;
}
