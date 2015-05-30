#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int n,c,flag,size;
char s[1000010];
void readInput(void){
	n = -1;
	c = getchar();
	while (c != EOF){
		s[++n] = c;
		c = getchar();
	}
	s[++n] = 0;
}
int main(void){
	struct AstNode *tmp;
	struct node *root;
	flag = 1;
	readInput();
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
	return 0;
}
