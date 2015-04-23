#include "parser.h"
#include <stdio.h>
int n,c,flag;
char s[1000010];
int main(void){
	n = -1;
	c = getchar();
	while (c != EOF){
		s[++n] = c;
		c = getchar();
	}
	s[++n] = 0;
	flag = 1;
	struct ASTNode *tmp = makeAst(s,&flag);
	if (!flag){
		printf("CompileError\n");
	}else{
		astPrint(NULL,tmp,0);
		astDel(tmp);
		free(tmp);
		free(list);
	}
}
