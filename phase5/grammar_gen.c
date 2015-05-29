#include <stdio.h>
char s[100];
int i,j,terNum,nonNum,ruleNum,x,y,a,b;
int main(void){
	freopen("grammar.out","r",stdin);
	freopen("grammar.h","w",stdout);
	printf("#ifndef _GRAMMAR_H_\n");
	printf("#define _GRAMMAR_H_\n");
	printf("#include <string.h>\n");
	printf("struct ruleType{\n");
	printf("\tint non,num,items[15][2];\n");
	printf("};\n");
	printf("static int M[200][200],nonNum,terNum,ruleNum;\n");
	printf("static char terminals[200][40],nonterminals[200][40];\n");
	printf("static struct ruleType rules[300];\n");
	
	printf("static void get_grammar(void){\n");
	scanf("%d",&terNum);
	printf("\tterNum = %d;\n",terNum);

	for (i = 1;i <= terNum;++i){
		scanf("%s",s);
		printf("\tstrcpy(terminals[%d],\"%s\");\n",i,s);
	}

	scanf("%d",&nonNum);
	printf("\tnonNum = %d;\n",nonNum);
	
	for (i = 1;i <= nonNum;++i){
		scanf("%s",s);
		printf("\tstrcpy(nonterminals[%d],\"%s\");\n",i,s);
	}
	
	scanf("%d",&ruleNum);
	printf("\truleNum = %d;\n",ruleNum);
	
	for (i = 1;i <= ruleNum;++i){
		scanf("%d%d",&x,&y);
		printf("\trules[%d].non = %d;\n",i,x);
		printf("\trules[%d].num = %d;\n",i,y);
		for (j = 1;j <= y;++j){
			scanf("%d%d",&a,&b);
			printf("\trules[%d].items[%d][0] = %d;\n",i,j,a);
			printf("\trules[%d].items[%d][1] = %d;\n",i,j,b);
		}
	}
	
	for (i = 1;i <= nonNum;++i)
		for (j = 1;j <= terNum;++j){
			scanf("%d",&x);
			printf("\tM[%d][%d] = %d;\n",i,j,x);
		}
	printf("}\n");
	printf("#endif\n");
}
