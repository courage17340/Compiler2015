#include <string.h>
#include <stdlib.h>
#include "split.h"

#define MAX_STR 1000010
//local function declaration
static int isWhite(char);
static int isDigit(char);
static int isLetter(char);
static int isSingle(char);

static int isWhite(char c){
	return c == ' ' || c == '\t' || c == '\n';
}
static int isDigit(char c){
	return '0' <= c && c <= '9';
}
static int isLetter(char c){
	return c == '_' || c == '$' || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}
static int isSingle(char c){
	char *s = "();,{}[]~.";
	int i,n;
	n = strlen(s);
	for (i = 0;i < n;++i) if (s[i] == c) return 1;
	return 0;
}
void split(char *s){
	char cur;
	static char t[MAX_STR];
	int n,i,k,q,j,flag0,flag1;// flags for ' & "
	n = strlen(s);
	q = -1;
	flag0 = flag1 = 0;
	for (i = 0;i < n;++i){
		cur = s[i];
		if (flag0){
			if (cur == '\''){
				flag0 = 0;
				t[++q] = cur;
				cur = '\n';
			}else if (cur == '\\'){
				t[++q] = cur;
				cur = s[++i];
			}
		}else if (flag1){
			if (cur == '"'){
				flag1 = 0;
				t[++q] = cur;
				cur = '\n';
			}else if (cur == '\\'){
				t[++q] = cur;
				cur = s[++i];
			}
		}else{
			while (i < n && isWhite(cur)) cur = s[++i];
			if (i >= n) break;
			if (cur == '\''){
				flag0 = 1;
			}else if (cur == '"'){
				flag1 = 1;
			}else if (isDigit(cur)){
				j = i;
				while (j + 1 < n && (isDigit(s[j + 1]) || isLetter(s[j + 1]))) ++j;
				for (k = i;k <= j;k++) t[++q] = s[k];
				i = j;
				cur = '\n';
			}else if (isLetter(cur)){
				j = i;
				while (j + 1 < n && (isDigit(s[j + 1]) || isLetter(s[j + 1]))) ++j;
				for (k = i;k <= j;k++) t[++q] = s[k];
				i = j;
				cur = '\n';
			}else if (cur == '='){
				t[++q] = cur;
				if (s[i + 1] == '='){
					++i;
					t[++q] = s[i];
				}
				cur = '\n';
			}else if (cur == '*'){
				t[++q] = cur;
				if (s[i + 1] == '='){
					++i;
					t[++q] = s[i];
				}
				cur = '\n';
			}else if (cur == '|'){
				t[++q] = cur;
				if (s[i + 1] == '=' || s[i + 1] == '|'){
					++i;
					t[++q] = s[i];
				}
				cur = '\n';
			}else if (cur == '^'){
				t[++q] = cur;
				if (s[i + 1] == '='){
					++i;
					t[++q] = s[i];
				}
				cur = '\n';
			}else if (cur == '&'){
				t[++q] = cur;
				if (s[i + 1] == '=' || s[i + 1] == '&'){
					++i;
					t[++q] = s[i];
				}
				cur = '\n';
			}else if (cur == '<'){
				t[++q] = cur;
				if (s[i + 1] == '=' || s[i + 1] == '<'){
					++i;
					t[++q] = s[i];
					if (s[i] == '<' && s[i + 1] == '='){
						++i;
						t[++q] = s[i];
					}
				}
				cur = '\n';
			}else if (cur == '>'){
				t[++q] = cur;
				if (s[i + 1] == '=' || s[i + 1] == '>'){
					++i;
					t[++q] = s[i];
					if (s[i] == '>' && s[i + 1] == '='){
						++i;
						t[++q] = s[i];
					}
				}
				cur = '\n';
			}else if (cur == '+'){
				t[++q] = cur;
				if (s[i + 1] == '=' || s[i + 1] == '+'){
					++i;
					t[++q] = s[i];
				}
				cur = '\n';
			}else if (cur == '-'){
				t[++q] = cur;
				if (s[i + 1] == '=' || s[i + 1] == '-' || s[i + 1] == '>'){
					++i;
					t[++q] = s[i];
				}
				cur = '\n';
			}else if (cur == '*'){
				t[++q] = cur;
				if (s[i + 1] == '='){
					++i;
					t[++q] = s[i];
				}
				cur = '\n';
			}else if (cur == '/'){
				t[++q] = cur;
				if (s[i + 1] == '='){
					++i;
					t[++q] = s[i];
				}
				cur = '\n';
			}else if (cur == '%'){
				t[++q] = cur;
				if (s[i + 1] == '='){
					++i;
					t[++q] = s[i];
				}
				cur = '\n';
			}else if (cur == '!'){
				t[++q] = cur;
				if (s[i + 1] == '='){
					++i;
					t[++q] = s[i];
				}
				cur = '\n';
			}else if (isSingle(cur)){
				t[++q] = cur;
				cur = '\n';
			}else{
				strcpy(s,"CompileError");
				return;
			}
		}
		t[++q] = cur;
	}
	t[++q] = 0;
	strcpy(s,t);
}
/*
int main(void){
	char s[10010];
	int p,c;
	p = -1;
	c = getchar();
	while (c != EOF){
		s[++p] = c;
		c = getchar();
	}
	s[++p] = 0;
	split(s);
	puts(s);
	return 0;
}
*/
