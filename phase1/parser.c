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
	ROOT,DECL,FUNCDECL,STRUDECL,UNIODECL,VARIDECL,TYPE,BASITYPE,
	INTETYPE,CHARTYPE,VOIDTYPE,STRUTYPE,UNIOTYPE,PTERTYPE,
	ARRATYPE,STMT,BREASTMT,CONTSTMT,IFTESTMT,FORRLOOP,WHILLOOP,
	RETNSTMT,COMPSTMT,EXPR,EMPTSTMT,BINAEXPR,UNARSTMT,SZOFSTMT,
	CASTEXPR,PTERACSS,RECOACSS,SELFINCR,SELFDECR,ARRAACSS,
	FUNCCALL,IDEN,INTECONS,CHARCONS,STRICONS,
	PARA,VARILIST
};

static char ASTflags[50][30] = {
	"Root","Decl","FunctionDecl","StructDecl","UnionDecl","VarDecl","Type","BasicType",
	"IntType","CharType","VoidType","StructType","UnionType","PointerType",
	"ArrayType","Stmt","BreakStmt","ContinueStmt","IfStmt","ForLoop","WhileLoop",
	"ReturnStmt","CompoundStmt","Expr","EmptyExpr","BinaryExpr","UnaryExpr","SizeofExpr",
	"CastExpr","PointerAccess","RecordAccess","SelfIncrement","SelfDecrement","ArrayAccess",
	"FunctionCall","Identifier","IntConst","CharConst","StringConst",
	"Parameters","VariableList"
};

struct ASTNode{
	enum ASTType type;
	char *data;
	int num,cap;
	struct ASTNode *c;
};

static void doubleSpace(struct ASTNode *a){
	struct ASTNode *tmp = (struct ASTNode *)malloc(sizeof(struct ASTNode) * a->cap * 2);
	int i;
	for (i = 0;i < a->cap;++i)
		tmp[i] = a->c[i];
	a->cap *= 2;
	free(a->c);
	a->c = tmp;
}

static struct ASTNode *getAst(int n){
	return (struct ASTNode *)malloc(sizeof(struct ASTNode) * n);
}

static void AST(struct node *root,struct ASTNode *ast){
	ast->data = ASTflags[ast->type];
	ast->c = NULL;
	ast->num = ast->cap = 0;
	if (ast->type == ROOT){
		while (root->data != NULL){
			if (ast->cap == 0){
				ast->c = getAst(1);
				ast->num = 0;
				ast->cap = 1;
			}
			if (ast->cap == ast->num) doubleSpace(ast);
			++ast->num;
			ast->c[ast->num - 1].type = DECL;
			AST(&root->c[0],&ast->c[ast->num - 1]);
			if (root->num > 1) root = &root->c[1];else return;
		}
	}else if (ast->type == DECL){//dec_or_func
		ast->c = getAst(1);
		ast->num = 1;
		ast->cap = 1;
		ast->c[0].type = TYPE;
		AST(&root->c[0],&ast->c[0]);
		root = &root->c[1];//dec_or_func1
		if (strcmp(root->c[0].data,";") == 0){
			
		}
		if (ast->cap == ast->num) doubleSpace(ast);
		++ast->num;
		ast->c[ast->num - 1].type = IDEN;
		AST(&root->c[0],&ast->c[ast->num - 1]);
		root = &root->c[1];//dec_or_func2
		if (strcmp(root->c[0].data,"(") == 0){//'(' function_definition1
			ast->type = FUNCDECL;
			root = &root->c[1];//function_definition1
			if (strcmp(root->c[0].data,")") == 0){//')' compound_statement
				if (ast->num == ast->cap) doubleSpace(ast);
				++ast->num;
				ast->c[ast->num - 1].type = PARA;
				ast->c[ast->num - 1].data = NULL;
				ast->c[ast->num - 1].num = 0;
				ast->c[ast->num - 1].cap = 0;
				root = &root->c[1];
			}else{//parameters ')' compound_statement
				if (ast->num == ast->cap) doubleSpace(ast);
				++ast->num;
				ast->c[ast->num - 1].type = PARA;
				AST(&root->c[0],&ast->c[ast->num - 1]);
				root = &root->c[2];
			}
			//compound_statement
			//func dec not supported
			if (ast->num == ast->cap) doubleSpace(ast);
			++ast->num;
			ast->c[ast->num - 1].type = COMPSTMT;
			AST(&root->c[0],&ast->c[ast->num - 1]);
		}else{//comma_array_sizes init_declarator1 comma_init_declarators ';'
			
		}
	}else if (ast->type == FUNCDECL){
		//never
	}else if (ast->type == STRUDECL){
		//never
	}else if (ast->type == UNIODECL){
		//never
	}else if (ast->type == VARIDECL){
		//init_declarator
		
	}else{}
}

int main(void){
	static char s[1000010];
	struct node *root;
	struct ASTNode *ast;
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
	ast = malloc(sizeof (struct ASTNode));
	ast->type = ROOT;
	AST(root,ast);
//	del(ast);
//	free(ast);
//	print(root,0);
	del(root);
	free(root);
	free(list);
	return 0;
}

