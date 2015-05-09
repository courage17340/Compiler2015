#include "ir.h"
/*
dest = obj op obj
ob1    ob2 op ob3

dest = op obj
ob1    op ob2

dest = obj
ob1 op ob2

param obj
op    ob1

call func num
op   ob1  ob2

dest = call func num
ob1    op   ob2  ob3

label l
op    ob1

goto l
op   ob1


*/
static int temp;
enum OpType{
	
};
enum ObjectType{
	
};
struct Op{
	int type;
	char *s;
};
struct Object{
	int type;
	union{
		int value;
		char *name;
		
	}data;
}
struct 


static void readInput(char *s){
	int t = -1,c;
	c = getchar();
	while (c != EOF){
		s[++t] = c;
		c = getchar();
	}
	s[++t] = 0;
}
static void 
static void ir(struct AstNode *ast){
	
}
int main(void){
	char *s = (char *)malloc(1000010);
	readInput(s);
	semanticCheck(s);
	
	ir(ast);
	
	astDel(ast);
	free(ast);
	free(list);
	free(s);
	return 0;
}
