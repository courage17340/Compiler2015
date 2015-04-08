#include "LL.h"
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
static void init(void){
	int non;
	freopen("grammar1.txt","r",stdin);
	nonNum = 0;
	terNum = 2;
	strcpy(terminals[1],"''"); //epsilon
	strcpy(terminals[2],".."); //EOF
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

static void getFirst(void){
	int i;
	for (i = 1;i <= terNum;++i){
		firstSet[0][i].visited = 1;
		firstSet[0][i].have[i] = 1;
	}
	for (i = 1;i <= nonNum;++i) firstSet[1][i].visited = 0;
	for (i = 1;i <= nonNum;++i) firstSet[1][i] = first(1,i);
}

static struct setType first(int k,int x){//first(X)
	int p;
	struct setType ret;
	memset(&ret,0,sizeof ret);
	if (firstSet[k][x].visited) return firstSet[k][x];
	p = nonBegins[x];
	while (p <= curLine && rules[p].non == x){
		int n = rules[p].num,j;
		for (j = 1;j <= n;++j){
			int i;
			struct setType tmp;
			tmp = first(rules[p].items[j][0],rules[p].items[j][1]);
			for (i = 2;i <= terNum;++i) ret.have[i] |= tmp.have[i];//note epsilon
			if (!tmp.have[1]) break;
			if (j == n){//epsilon \in all of first(X_i) 
				tmp.have[1] = 1;
			}
		}
		++p;
	}
	ret.visited = 1;
	return ret;
}

static void getFollow(void){
	struct setType tmp;
	followSet[1].have[2] = 1;//FOLLOW(S) = {EOF}
	while (1){
		int flag = 0,i,j,k;
		for (i = 1;i <= curLine;++i){
			int n = rules[i].num;
			for (j = 1;j < n;++j) if (rules[i].items[j][0]){
				int A = rules[i].non,B = rules[i].items[j][1];
				tmp = first1(i,j + 1);
				for (k = 2;k <= terNum;++k) if (!followSet[B].have[k] && tmp.have[k]){
					flag = 1;
					followSet[B].have[k] = 1;
				}
				if (tmp.have[1]){
					for (k = 1;k <= terNum;++k) if (!followSet[B].have[k] && followSet[A].have[k]){
						flag = 1;
						followSet[B].have[k] = 1;
					}
				}
			}//A->\alpha B \beta
			if (rules[i].items[n][0]){
				int A = rules[i].non,B = rules[i].items[n][1],k;
				for (k = 1;k <= terNum;++k) if (!followSet[B].have[k] && followSet[A].have[k]){
					flag = 1;
					followSet[B].have[k] = 1;
				}
			}
		}
		if (!flag) break;
	}
}

static struct setType first1(int r,int s){//first(X_s...X_n) from rule r
	struct setType ret,tmp;
	int i;
	memset(&ret,0,sizeof ret);
	for (i = s;i <= rules[r].num;++i){
		int j;
		tmp = first(rules[r].items[i][0],rules[r].items[i][1]);
		for (j = 2;j <= terNum;++j) ret.have[j] |= tmp.have[j];//note epsilon
		if (!tmp.have[1]) break;
		if (i == rules[r].num) ret.have[1] = 1;
	}
	return ret;
}

static void makeTable(void){
	int i,j,k;
	struct setType tmp;
	memset(M,0,sizeof M);
	init();
	getFirst();
	getFollow();
	for (i = 1;i <= curLine;++i){
		int A = rules[i].non;
		tmp = first1(i,1);
		for (j = 1;j <= terNum;++j) if (tmp.have[j]) M[A][j] = i;
		if (tmp.have[1]){
			int b;
			for (b = 1;b <= terNum;++b) if (followSet[A].have[b]) M[A][b] = i;
		}
	}
	//deal with if statement
	k = findNon("selection_statement1");
	j = nonBegins[k] + 1;
	M[k][findTer("'else'")] = j;
	//write file
	freopen("grammar.out","w",stdout);
	printf("%d\n",terNum);
	for (i = 1;i <= terNum;++i) printf("%s\n",terminals[i]);
	printf("%d\n",nonNum);
	for (i = 1;i <= nonNum;++i) printf("%s\n",nonterminals[i]);
	for (i = 1;i <= nonNum;++i){
		for (j = 1;j <= terNum;++j) printf("%d ",M[i][j]);
		printf("\n");
	}
}

int main(void){
	makeTable();
	return 0;
}
