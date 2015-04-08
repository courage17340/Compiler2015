#include "parser.h"
#include "removeComments.h"
#include "split.h"
static struct token *makeList(char *s){	//Remember to free the memory!!!
	int n,m,l,r,i;
	struct token *list;
	n = strlen(s);
	m = 0;
	for (i = 0;i < n;++i) if (s[i] == '\n'){
		s[i] = 0;
		++m;
	}
	list = (struct token *)malloc((m + 10) * sizeof (struct token));
	i = 0;
	l = 0;
	while (i < m){
		r = l;
		while (s[r] != 0) ++r;
		list[i].ptr = s + l;
		getTokenType(&(list[i]));
		l = r + 1;
	}
	list[m].ptr = s + r;//add END
	list[m].tokenType = SYM;
	list[m].tokenDetail = END;
	listSize = m + 1;
	return list;
}

struct node *parse(char *s){
	int i,j,ptr;
	list = makeList(s);
	freopen("grammar.out","r",stdin);
	freopen("CST.txt","w",stdout);
	scanf("%d",&terNum);
	for (i = 1;i <= terNum;++i) scanf("%s",terminals[i]);
	scanf("%d",&nonNum);
	for (i = 1;i <= nonNum;++i) scanf("%s",nonterminals[i]);
	scanf("%d",&ruleNum);
	for (i = 1;i <= ruleNum;++i){
		scanf("%d%d",&rules[i].non,&rules[i].num);
		for (j = 1;j <= rules[i].num;++j) scanf("%d%d",&rules[i].items[j][0],&rules[i].items[j][1]);

	}
	for (i = 1;i <= nonNum;++i)
		for (j = 1;j <= terNum;++j) scanf("%d",&M[i][j]);
	init();
	ptr = 0;
	struct node *CST = getNode();
	build(CST,&ptr,1,1);
	return CST;
}

static void init(void){
	int i;
	for (i = 0;i < listSize;++i) list[i].type = getType(list[i]);
}

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

static void build(struct node *root,int *next,int k,int x){
	struct token t;
	int r,i,n;
	t = list[*next];
	if (error) return;
	if (k == 0){
		if (!equal(t,terminals[x])) error = *next + 1;
		root->data = t.ptr;
		++*next;
		return;
	}
	if (M[x][t.type] == 0){
		error = *next + 1;
		return;
	}
	r = M[x][t.type];
	n = rules[r].num;
	root->num = n;
	root->c = (struct node *)malloc(n * sizeof(struct node));
	for (i = 0;i < n;++i){
		root->c[i].data = NULL;
		root->c[i].flag = NULL;
		root->c[i].c = NULL;
		root->c[i].num = 0;
		build(&root->c[i],next,rules[r].items[i][0],rules[r].items[i][1]);
	}
	root->data = nonterminals[x];
}

static int equal(struct token t,char *s){
	if (t.tokenDetail == END) return strcmp(s,"..") == 0;
	if (t.tokenDetail == CON_NUM) return strcmp(s,"integer_constant") == 0;
	if (t.tokenDetail == CON_CHAR) return strcmp(s,"character_constant") == 0;
	if (t.tokenDetail == CON_STR) return strcmp(s,"string") == 0;
	if (t.tokenDetail == IDENTIFIER) return strcmp(s,"identifier") == 0;
	return strcmp(t.ptr,s) == 0;
}

static struct node *getNode(void){
	struct node *ret = (struct node *)malloc(sizeof(struct node));
	ret->c = NULL;
	ret->num = 0;
	ret->data = ret->flag = NULL;
	return ret;
}

static int getType(struct token t){
	if (t.tokenDetail == END) return findTer("..");
	if (t.tokenDetail == CON_NUM) return findTer("integer_constant");
	if (t.tokenDetail == CON_CHAR) return findTer("character_constant");
	if (t.tokenDetail == CON_STR) return findTer("string");
	if (t.tokenDetail == IDENTIFIER) return findTer("identifier");
	return findTer(t.ptr);
}

static void print(struct node *root,int col){
	int i;
	for (i = 1;i <= col;++i) printf("\t");
	printf("%s\n",root->data);
	for (i = 0;i < root->num;++i) print(&root->c[i],col + 1);
}

static void del(struct node *s){
	int n,i;
	n = s->num;
	for (i = 0;i < n;++i) del(&s->c[i]);
	free(s->c);
}

int main(void){
	static char s[1000010];
	struct node *root;
	int c,p;
	p = -1;
	c = getchar();
	while (c != EOF){
		s[++p] = c;
		c = getchar();
	}
	removeComments(s);
	split(s);
	root = parse(s);
	print(root,0);
	del(root);
	free(root);
	return 0;
}

