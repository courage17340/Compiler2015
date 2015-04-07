#include "LR1.h"
static int findTer(char *s){
	int i;
	for (i = 1;i <= terNum;++i) if (strcmp(s,terminals[i]) == 0) return i;
	return 0;
}
static int findNon(char *s){
	int i;
	for (i = 1;i <= nonNum;++i) if (strcmp(s,nonterminals[i]) == 0) return i;
	return 0;
}
static void init(){
	int non;
	freopen("1.txt","r",stdin);
	freopen("grammar.out","w",stdout);
	terNum = nonNum = 0;
	curLine = 0;
	while (scanf("%s",s) != EOF){
		non = findNon(s);
		if (!non){
			++nonNum;
			strcpy(nonterminals[nonNum],s);
			non = nonNum;
		}
		nonBegins[non] = curLine + 1;
		while (1){
			++curLine;
			rules[curLine].non = non;
			rules[curLine].num = 0;
			while (1){
				scanf("%s",s);
				if (s[0] == '\\') break;
				if (s[0] == '\''){
					int i = findTer(s);
					if (!i){
						++terNum;
						strcpy(terminals[terNum],s);
						i = terNum;
					}
					++rules[curLine].num;
					rules[curLine].items[rules[curLine].num][0] = 0;
					rules[curLine].items[rules[curLine].num][1] = i;
				}else{
					int i = findNon(s);
					if (!i){
						++nonNum;
						strcpy(nonterminals[nonNum],s);
						i = nonNum;
					}
					++rules[curLine].num;
					rules[curLine].items[rules[curLine].num][0] = 1;
					rules[curLine].items[rules[curLine].num][1] = i;
				}
			}
			if (strcmp(s,"\\\\") == 0) break;
		}
	}
}

