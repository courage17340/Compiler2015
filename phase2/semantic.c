#include "semantic.h"
static struct AstNode *ast;
static void readInput(char *s){
	int n = -1,c = getchar();
	while (c != EOF){
		s[++n] = c;
		c = getchar();
	}
	s[++n] = 0;
}
static void halt(void){
	clearAll();
	astDel(ast);
	free(ast);
	free(list);
	exit(1);
}
static void check(struct AstNode *ast){
	
}


int main(int args,char **argv){
	struct node *root;
	static char s[1000010];
	int flag,size;
	freopen(argv[1],"r",stdin);
	flag = 1;
	readInput(s);
	ast = makeAst(s,&flag,&size,&root);
	if (!flag){
		return 1;
	}else{
		cstDel(root);
		free(root);
	}
	check(ast);
//	semantic(ast);
	clearAll();
	astDel(ast);
	free(ast);
	free(list);
	if (flag) return 0;else return 1;
}
