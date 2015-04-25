#include "parser.h"
#include <stdio.h>
int n,c,flag;
char s[1000010];
int main(void){
	struct ASTNode *tmp;
	struct node *root;
	int size;
	n = -1;
	c = getchar();
	while (c != EOF){
		s[++n] = c;
		c = getchar();
	}
	s[++n] = 0;
	flag = 1;
	tmp = makeAst(s,&flag,&size,&root);
	if (!flag){
		printf("CompileError\n");
	}else{
		astPrint(NULL,tmp,0);
		astDel(tmp);
		free(tmp);
		cstDel(root);
		free(root);
		free(list);
	}
}
