#include "semantic.h"
static void readInput(char *s){
	int n = -1,c = getchar();
	while (c != EOF){
		s[++n] = c;
		c = getchar();
	}
	s[++n] = 0;
}
int main(int args,char **argv){
	struct ASTNode *ast;
	struct node *root;
	static char s[1000010];
	int flag,size;
	freopen(argv[0],"r",stdin);
	flag = 1;
	readInput(s);
	ast = makeAst(s,&flag,&size,&root);
	if (!flag){
		exit(1);
	}else{
		cstDel(root);
		free(root);
	}
	
	astDel(ast);
	free(ast);
	free(list);
	if (flag) exit(0);else exit(1);
}
