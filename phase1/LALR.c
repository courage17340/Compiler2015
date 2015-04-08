#include "LALR.h"
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
	freopen("grammarForLR.txt","r",stdin);
	nonNum = 0;
	strcpy(nonterminals[0],"S'");
	rules[0].non = 0;
	rules[0].num = 1;
	rules[0].items[1][0] = 1;
	rules[0].items[1][1] = 1;	//S'->S
	terNum = 0;
	curLine = 0;
	nonBegins[0] = 0;
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

static struct SetOfItems closure(struct SetOfItems I){
	static struct SetOfItems J;
	static int added[100];
	static int have[200];
	J = I;
	memset(added,0,sizeof added);
	memset(have,0,sizeof have);
	int i;
	for (i = 1;i <= J.num;++i) if (J.ele[i].ptr == 0) have[J.ele[i].rule] = 1;
	while (1){
		int n,flag,i,j;
		n = J.num;
		flag = 0;
		for (i = 1;i <= n;++i) if (nonAfterDot(J.ele[i])){
			int non = rules[J.ele[i].rule].items[J.ele[i].ptr + 1][1];
			if (added[non]) continue;
			added[non] = 1;
			for (j = nonBegins[non];j <= curLine && rules[j].non == non;++j)
				if (!have[j]){
					++J.num;
					J.ele[J.num].rule = j;
					J.ele[J.num].ptr = 0;
					flag = 1;
				}
		}
		if (!flag) break;
	}
	return J;
}

static int nonAfterDot(struct Item a){
	int i = a.rule,j = a.ptr;
	return rules[i].num >= j + 1 && rules[i].items[j + 1][0] == 1;
}

static struct SetOfItems GOTO(struct SetOfItems I,int type,int ptr){
	int n,i;
	static struct SetOfItems J;
	static int v[200][15];
	J.num = 0;
	n = I.num;
	memset(v,0,sizeof v);
	for (i = 1;i <= n;++i) v[J.ele[i].rule][J.ele[i].ptr] = 1;
	for (i = 1;i <= n;++i){
		int r,j;
		r = I.ele[i].rule;
		j = I.ele[i].ptr;
		if (rules[r].num >= j + 1 && !v[r][j + 1]){
			++J.num;
			J.ele[J.num].rule = r;
			J.ele[J.num].ptr = j + 1;
			v[r][j + 1] = 1;
		}
	}
	return closure(J);
}

static void getStates(void){
	int i,j;
	static struct SetOfItems I;
	init();
	stateNum = 1;
	state[1].num = 1;
	state[1].ele[1].rule = 0;
	state[1].ele[1].ptr = 0;
	state[1] = closure(state[1]);
	for (i = 1;i <= stateNum;++i){
		for (j = 1;j <= terNum;++j){
			I = GOTO(state[i],0,j);
			if (I.num && !findItem(I)){
				++stateNum;
				state[stateNum] = I;
			}
		}
		for (j = 1;j <= nonNum;++j){
			I = GOTO(state[i],1,j);
			if (I.num && !findItem(I)){
				++stateNum;
				state[stateNum] = I;
			}
		}
	}
}

static int findItem(struct SetOfItems I){
	int i,j;
	static int v[200][15];
	memset(v,0,sizeof v);
	for (i = 1;i <= I.num;++i) v[I.ele[i].rule][I.ele[i].ptr] = 1;
	for (i = 1;i <= stateNum;++i)
		if (I.num == state[i].num){
			int flag = 1;
			for (j = 1;j <= state[i].num;++j) if (!v[I.ele[j].rule][I.ele[j].ptr]){
				flag = 0;
				break;
			}
			if (flag) return 1;
		}
	return 0;
}

static void getCores(void){
	int n,m,i,j;
	static struct SetOfItems I;
	n = stateNum;
	for (i = 1;i <= n;++i){
		m = state[i].num;
		I.num = 0;
		for (j = 1;j <= m;++j) if (state[i].ele[j].rule == 0 || state[i].ele[j].ptr){
			++I.num;
			I.ele[I.num].rule = state[i].ele[j].rule;
			I.ele[I.num].ptr = state[i].ele[j].ptr;
		}
		state[i] = I;
	}
}

int main(void){getStates();getCores();return 0;}
