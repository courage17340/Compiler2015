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
		while (s[l] == 0) ++l;
		r = l;
		while (s[r] != 0) ++r;
		list[i].ptr = s + l;
		getTokenType(&(list[i]));
		l = r;
		++i;
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
	int r,i,n,m;
	t = list[*next];
	if (error) return;
	if (k == 0){
		if (x == 1){
			return;
		}
		if (!equal(t,terminals[x])) error = *next + 1;
		root->data = t.ptr;
		root->flag = t.tokenDetail;
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
		root->c[i].flag = 0;
		root->c[i].c = NULL;
		root->c[i].num = 0;
		build(&root->c[i],next,rules[r].items[i + 1][0],rules[r].items[i + 1][1]);
	}
	root->data = nonterminals[x];
//	simplify
	m = 0;
	for (i = 0;i < n;++i) if (root->c[i].data != NULL) ++m;
	if (m < n && m){
		struct node *tmp = (struct node *)malloc(m * sizeof(struct node));
		int p = -1;
		for (i = 0;i < n;++i) if (root->c[i].data != NULL){
			++p;
			tmp[p].data = root->c[i].data;
			tmp[p].flag = root->c[i].flag;
			tmp[p].c = root->c[i].c;
			tmp[p].num = root->c[i].num;
		}
		free(root->c);
		root->c = tmp;
	}
	root->num = m;
/*	if (m == 1 && strcmp(root->data,"program")){
		struct node *tmp = root->c;
		root->data = tmp->data;
		root->flag = tmp->flag;
		root->c = tmp->c;
		root->num = tmp->num;
		free(tmp);
	}*/
	if (m == 0){
		free(root->c);
		root->c = NULL;
		root->num = 0;
		root->data = NULL;
		return;
	}
	
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
	ret->num = ret->flag = 0;
	ret->data = NULL;
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
	if (root->data == NULL) return;
//	if (root->num == 1){
//		print(&root->c[0],col);
//		return;
//	}
//	if (root->data[0] == ',' || root->data[0] == ';') return;
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

//------for------ast------

enum ASTType{
	ROOT,DECL,FUNCDECL,STRUDECL,UNIODECL,VARIDECL,BASITYPE,
	INTETYPE,CHARTYPE,VOIDTYPE,STRUTYPE,UNIOTYPE,PTERTYPE,
	ARRATYPE,STMT,BREASTMT,CONTSTMT,IFTESTMT,FORRLOOP,WHILSTMT,
	RETNSTMT,COMPSTMT,EXPR,EMPTSTMT,BINAEXPR,UNARSTMT,SZOFSTMT,
	CASTEXPR,PTERACSS,RECOACSS,SELFINCR,SELFDECR,ARRAACSS,
	FUNCCALL,IDEN,INTECONS,CHARCONS,STRICONS
};

struct ASTNode{
	enum ASTType type;
	char *data;
	int num;
	struct ASTnode *c;
};

static void AST(struct node *root){
	
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
	if (strcmp(s,"CompileError") == 0){
		puts(s);
		free(list);
		return 0;
	}
	split(s);
	root = parse(s);
	if (error){
		del(root);
		printf("Compile Error at token \"%s\"\n",list[error - 1].ptr);
		free(list);
		return 0;
	}
//	root = makeAST(root);
	print(root,0);
	del(root);
	free(root);
	free(list);
	return 0;
}

