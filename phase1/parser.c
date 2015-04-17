#include "parser.h"
#include "removeComments.h"
#include "split.h"
static struct token *makeList(char *s){	//Remember to free the memory!!
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
	RETNSTMT,COMPSTMT,EXPR,EMPTEXPR,BINAEXPR,UNAREXPR,SZOFEXPR,
	CASTEXPR,PTERACSS,RECOACSS,SELFINCR,SELFDECR,ARRAACSS,
	FUNCCALL,IDEN,INTECONS,CHARCONS,STRICONS,
	PARA,TYPESPEC,INIT
};

static char ASTFlags[50][30] = {
	"Root","Decl","FunctionDecl","StructDecl","UnionDecl","VarDecl","Type","BasicType",
	"IntType","CharType","VoidType","StructType","UnionType","PointerType",
	"ArrayType","Stmt","BreakStmt","ContinueStmt","IfStmt","ForLoop","WhileLoop",
	"ReturnStmt","CompoundStmt","Expr","EmptyExpr","BinaryExpr","UnaryExpr","SizeofExpr",
	"CastExpr","PointerAccess","RecordAccess","SelfIncrement","SelfDecrement","ArrayAccess",
	"FunctionCall","Identifier","IntConst","CharConst","StringConst",
	"Parameters","TypeSpecifiers","Initializer"
};

struct ASTNode{
	int type;
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
	ast->data = ASTFlags[ast->type];
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
		struct ASTNode *atmp;
		struct node *ctmp;
		int numOfPtrs = 0;
		ast->c = getAst(1);
		ast->num = 1;
		ast->cap = 1;
		ast->c[0].type = TYPE;
		AST(&root->c[0],&ast->c[0]);
		root = &root->c[1];//dec_or_func1
		if (strcmp(root->c[0].data,";") == 0){
			return;
		}
		ctmp = &root->c[0];//plain_declarator
		while (ctmp->num > 1){
			ctmp = &ctmp->c[1];
			++numOfPtrs;
		}
		ctmp = &ctmp->c[0];//identifier
		if (ast->cap == ast->num) doubleSpace(ast);
		++ast->num;
		ast->c[ast->num - 1].type = IDEN;
		AST(&ctmp->c[0],&ast->c[ast->num - 1]);
		root = &root->c[1];//dec_or_func2
		if (strcmp(root->c[0].data,"(") == 0){//'(' function_definition1
			while (numOfPtrs--){
				atmp = getAst(1);
				*atmp = ast->c[ast->num - 2];
				ast->c[ast->num - 2].type = PTERTYPE;
				ast->c[ast->num - 2].data = ASTFlags[PTERTYPE];
				ast->c[ast->num - 2].c = atmp;
				ast->c[ast->num - 2].num = 1;
				ast->c[ast->num - 2].cap = 1;
			}
			ast->type = FUNCDECL;
			root = &root->c[1];//function_definition1
			if (strcmp(root->c[0].data,")") == 0){//')' compound_statement
				if (ast->num == ast->cap) doubleSpace(ast);
				++ast->num;
				ast->c[ast->num - 1].type = PARA;
				ast->c[ast->num - 1].data = ASTFlags[PARA];
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
			int cptr;
			ast->type = VARIDECL;
			ast->data = ASTFlags[VARIDECL];
			if (ast->num == ast->cap) doubleSpace(ast);
			++ast->num;
			ast->c[ast->num - 1] = ast->c[ast->num - 2];
			ast->c[ast->num - 2] = ast->c[0];
			if (ast->c[0].type == STRUTYPE || ast->c[0].type == UNIOTYPE){
				ast->c[ast->num - 2].c = getAst(1);
				ast->c[ast->num - 2].c[0].type = IDEN;
				ast->c[ast->num - 2].c[0].data = ast->c[0].c[0].data;
				ast->c[ast->num - 2].num = 1;
				ast->c[ast->num - 2].cap = 1;
			}
			while (numOfPtrs--){
				atmp = getAst(1);
				*atmp = ast->c[ast->num - 2];
				ast->c[ast->num - 2].type = PTERTYPE;
				ast->c[ast->num - 2].data = ASTFlags[PTERTYPE];
				ast->c[ast->num - 2].c = atmp;
				ast->c[ast->num - 2].num = 1;
				ast->c[ast->num - 2].cap = 1;
			}
			cptr = 0;
			if (strcmp(root->c[cptr].data,"comma_array_sizes") == 0){
				ctmp = &root->c[cptr];
				++cptr;
				while (1){
					atmp = getAst(2);
					atmp[0] = ast->c[ast->num - 2];
					atmp[1].type = EXPR;
					AST(&ctmp->c[1],&atmp[1]);
					ast->c[ast->num - 2].type = ARRATYPE;
					ast->c[ast->num - 2].data = ASTFlags[ARRATYPE];
					ast->c[ast->num - 2].c = atmp;
					ast->c[ast->num - 2].num = 2;
					ast->c[ast->num - 2].cap = 2;
					if (ctmp->num >= 4) ctmp = &ctmp->c[3];else break;
				}
			}
			if (strcmp(root->c[cptr].data,"init_declarator1") == 0){
				ctmp = &root->c[cptr];
				++cptr;
				if (ast->num == ast->cap) doubleSpace(ast);
				++ast->num;
				ast->c[ast->num - 1].type = INIT;
				AST(&ctmp->c[1],&ast->c[ast->num - 1]);
			}
			if (strcmp(root->c[cptr].data,"comma_init_declarators") == 0){
				struct node *ttmp;
				root = &root->c[cptr];
				while (1){
					if (ast->num == ast->cap) doubleSpace(ast);
					++ast->num;
					ast->c[ast->num - 1] = ast->c[0];
					if (ast->c[0].type == STRUTYPE || ast->c[0].type == UNIOTYPE){
						ast->c[ast->num - 1].c = getAst(1);
						ast->c[ast->num - 1].c[0].type = IDEN;
						ast->c[ast->num - 1].c[0].data = ast->c[0].c[0].data;
						ast->c[ast->num - 1].num = 1;
						ast->c[ast->num - 1].cap = 1;
					}
					ctmp = &root->c[1];//init_declarator
					ctmp = &root->c[0];//declarator
					ttmp = &ctmp->c[0];//plain_declarator
					while (ttmp->num > 1){
						ttmp = &ttmp->c[1];
						atmp = getAst(1);
						*atmp = ast->c[ast->num - 1];
						ast->c[ast->num - 1].type = PTERTYPE;
						ast->c[ast->num - 1].data = ASTFlags[PTERTYPE];
						ast->c[ast->num - 1].c = atmp;
						ast->c[ast->num - 1].num = 1;
						ast->c[ast->num - 1].cap = 1;
					}
					if (ast->num == ast->cap) doubleSpace(ast);
					++ast->num;
					ast->c[ast->num - 1].type = IDEN;
					AST(&ttmp->c[0],&ast->c[ast->num - 1]);
					if (ctmp->num > 1){
						ctmp = &ctmp->c[1];//comma_array_sizes
						while (1){
							atmp = getAst(2);
							atmp[0] = ast->c[ast->num - 2];
							atmp[1].type = EXPR;
							AST(&ctmp->c[1],&atmp[1]);
							ast->c[ast->num - 2].type = ARRATYPE;
							ast->c[ast->num - 2].data = ASTFlags[ARRATYPE];
							ast->c[ast->num - 2].c = atmp;
							ast->c[ast->num - 2].num = 2;
							ast->c[ast->num - 2].cap = 2;
							if (ctmp->num >= 4) ctmp = &ctmp->c[3];else break;
						}
					}
					ctmp = &root->c[1];//init_decrator
					if (ctmp->num > 1){
						ctmp = &ctmp->c[1];//init_declarator1
						if (ast->num == ast->cap) doubleSpace(ast);
						++ast->num;
						ast->c[ast->num - 1].type = INIT;
						AST(&ctmp->c[1],&ast->c[ast->num - 1]);
					}
					if (root->num >= 3) root = &root->c[2];else break;
				}
			}
		}
	}else if (ast->type == FUNCDECL){
		//never
	}else if (ast->type == STRUDECL){
		//never
	}else if (ast->type == UNIODECL){
		//never
	}else if (ast->type == VARIDECL){
		//never
	}else if (ast->type == TYPE){//type_specifier
		if (strcmp(root->c[0].data,"void") == 0){
			ast->type = VOIDTYPE;
			ast->data = ASTFlags[VOIDTYPE];
		}else if (strcmp(root->c[0].data,"char") == 0){
			ast->type = CHARTYPE;
			ast->data = ASTFlags[CHARTYPE];
		}else if (strcmp(root->c[0].data,"int") == 0){
			ast->type = INTETYPE;
			ast->data = ASTFlags[INTETYPE];
		}else{//struct_or_union type_specifier1
			if (strcmp(root->c[0].c[0].data,"struct") == 0)
				ast->type = STRUTYPE;
			else
				ast->type = UNIOTYPE;
			root = &root->c[1];//type_specifier1
			ast->data = ASTFlags[ast->type];
			ast->c = getAst(1);
			ast->num = ast->cap = 1;
			ast->c[0].type = IDEN;
			if (strcmp(root->c[0].data,"identifier") == 0){
				AST(&root->c[0],&ast->c[0]);
				if (root->num > 1){
					root = &root->c[1];//type_specifier2
				}else return;
			}else{
				ast->c[0].data = "";
				ast->c[0].num = 0;
				ast->c[0].cap = 0;
			}
			root = &root->c[1];//type_specifiers
			if (ast->num == ast->cap) doubleSpace(ast);
			++ast->num;
			ast->c[ast->num - 1].type = TYPESPEC;
			AST(root,&ast->c[ast->num - 1]);
		}
	}else if (ast->type == BASITYPE){
		//never
	}else if (ast->type == INTETYPE){
		//never
	}else if (ast->type == CHARTYPE){
		//never
	}else if (ast->type == VOIDTYPE){
		//never
	}else if (ast->type == STRUTYPE){
		//never
	}else if (ast->type == UNIOTYPE){
		//never
	}else if (ast->type == PTERTYPE){
		//never
	}else if (ast->type == ARRATYPE){
		//never
	}else if (ast->type == STMT){
		if (strcmp(root->c[0].data,"expression_statement") == 0){
			root = &root->c[0];
			if (root->num == 1){
				ast->c = getAst(1);
				ast->num = ast->cap = 1;
				ast->c[0].type = EMPTEXPR;
				ast->c[0].data = ASTFlags[EMPTEXPR];
				ast->c[0].num = 0;
				ast->c[0].cap = 0;
				ast->c[0].c = NULL;
			}else{
				ast->c = getAst(1);
				ast->num = ast->cap = 1;
				ast->c[0].type = EXPR;
				AST(&root->c[0],&ast->c[0]);
			}
		}else if (strcmp(root->c[0].data,"compound_statement") == 0){
			root = &root->c[0];
			ast->type = COMPSTMT;
			AST(root,ast);
		}else if (strcmp(root->c[0].data,"selection_statement") == 0){
			root = &root->c[0];
			ast->type = IFTESTMT;
			ast->c = getAst(2);
			ast->num = ast->cap = 2;
			ast->c[0].type = EXPR;
			AST(&root->c[2],&ast->c[0]);
			ast->c[1].type = STMT;
			AST(&root->c[4],&ast->c[1]);
			if (root->num > 5){
				root = &root->c[5];//selection_statement1
				if (ast->num == ast->cap) doubleSpace(ast);
				++ast->num;
				ast->c[ast->num - 1].type = STMT;
				AST(&root->c[1],&ast->c[ast->num - 1]);
			}
		}else if (strcmp(root->c[0].data,"iteration_statement") == 0){
			root = &root->c[0];
			if (strcmp(root->c[0].data,"while") == 0){
				ast->type = WHILLOOP;
				AST(root,ast);
			}else{
				ast->type = FORRLOOP;
				AST(root,ast);
			}
		}else if (strcmp(root->c[0].data,"jump_statement") == 0){
			root = &root->c[0];
			if (strcmp(root->c[0].data,"continue") == 0){
				ast->type = CONTSTMT;
				ast->data = ASTFlags[ast->type];
			}else if (strcmp(root->c[0].data,"break") == 0){
				ast->type = BREASTMT;
				ast->data = ASTFlags[ast->type];
			}else if (strcmp(root->c[0].data,"return") == 0){
				ast->type = RETNSTMT;
				ast->data = ASTFlags[ast->type];
				root = &root->c[1];//jump_statement1
				ast->c = getAst(1);
				ast->num = ast->cap = 1;
				if (root->num > 1){
					ast->c[0].type = EXPR;
					AST(&root->c[0],&ast->c[0]);
				}else{
					ast->c[0].type = EMPTEXPR;
					ast->c[0].data = ASTFlags[ast->c[0].type];
					ast->c[0].num = 0;
					ast->c[0].cap = 0;
					ast->c[0].c = NULL;
				}
			}
		}
	}else if (ast->type == BREASTMT){
		//never
	}else if (ast->type == CONTSTMT){
		//never
	}else if (ast->type == IFTESTMT){
		//never
	}else if (ast->type == FORRLOOP){
		struct node *tmp;
		root = &root->c[2];//iteration_statement1
		ast->c = getAst(4);
		ast->num = 0;
		ast->cap = 4;
		tmp = &root->c[0];//expression_statement
		if (tmp->num == 1){
			ast->c[0].type = EMPTEXPR;
			ast->c[0].data = ASTFlags[EMPTEXPR];
		}else{
			ast->c[0].type = EXPR;
			AST(&tmp->c[0],&ast->c[0]);
		}
		root = &root->c[1];//iteration_statement2
		tmp = &root->c[0];//expression_statement
		if (tmp->num == 1){
			ast->c[1].type = EMPTEXPR;
			ast->c[1].data = ASTFlags[EMPTEXPR];
		}else{
			ast->c[1].type = EXPR;
			AST(&tmp->c[0],&ast->c[1]);
		}
		root = &root->c[2];//iteration_statement3
		if (strcmp(root->c[0].data,")") == 0){
			ast->c[2].type = EMPTEXPR;
			ast->c[2].data = ASTFlags[EMPTEXPR];
			root = &root->c[1];
		}else{
			ast->c[2].type = EXPR;
			AST(&root->c[0],&ast->c[2]);
			root = &root->c[2];
		}
		ast->c[3].type = STMT;
		AST(root,&ast->c[3]);
	}else if (ast->type == WHILLOOP){
		ast->c = getAst(2);
		ast->num = ast->cap = 2;
		ast->c[0].type = EXPR;
		AST(&root->c[2],&ast->c[0]);
		ast->c[1].type = STMT;
		AST(&root->c[4],&ast->c[1]);
	}else if (ast->type == RETNSTMT){
		//never
	}else if (ast->type == COMPSTMT){
		struct node *bk;
		int ptr = 1;
		ast->c = getAst(1);
		ast->num = 0;
		ast->cap = 1;
		bk = root;
		if (strcmp(root->c[ptr].data,"comma_declarations") == 0){
			struct node *ctmp,*ctmp1,*ctmp2;
			struct ASTNode *atmp,*atmp1;
			int numOfPtrs;
			root = &root->c[ptr];//comma_declarations
			while (1){
				ctmp = &root->c[0];//declaration
				if (ast->num == ast->cap) doubleSpace(ast);
				++ast->num;
				ast->c[ast->num - 1].type = DECL;
				atmp = &ast->c[ast->num - 1];
				atmp->c = getAst(1);
				atmp->num = atmp->cap = 1;
				atmp->c[0].type = TYPE;
				AST(&ctmp->c[0],&atmp->c[0]);
				ctmp = &ctmp->c[1];//declaration1
				while (ctmp->num > 1){
					char *name;
					ctmp = &ctmp->c[0];//init_declarators or comma_init_declarators
					ctmp1 = &ctmp->c[0];//init_declarator
					if (ctmp->c[0].data[0] == 'c') ctmp1 = &ctmp->c[1];
					if (atmp->num == atmp->cap) doubleSpace(atmp);
					atmp->c[atmp->num - 1] = atmp->c[0];
					if (atmp->c[0].type == STRUTYPE || atmp->c[0].type == UNIOTYPE){
						atmp->c[atmp->num - 1].c = getAst(1);
						atmp->c[atmp->num - 1].c[0].type = IDEN;
						atmp->c[atmp->num - 1].c[0].data = atmp->c[0].c[0].data;
						atmp->c[atmp->num - 1].num = 1;
						atmp->c[atmp->num - 1].cap = 1;
					}
					ctmp2 = &ctmp1->c[0];//declarator
					ctmp2 = &ctmp2->c[0];//plain_declarator
					while (ctmp2->num > 1){
						ctmp2 = &ctmp2->c[1];
						atmp1 = getAst(1);
						*atmp1 = atmp->c[atmp->num - 1];
						atmp->c[atmp->num - 1].type = PTERTYPE;
						atmp->c[atmp->num - 1].data = ASTFlags[PTERTYPE];
						atmp->c[atmp->num - 1].num = 1;
						atmp->c[atmp->num - 1].cap = 1;
						atmp->c[atmp->num - 1].c = atmp1;
					}
					ctmp2 = &ctmp2->c[0];//identifier
					if (atmp->num == atmp->cap) doubleSpace(atmp);
					++atmp->num;
					atmp->c[atmp->num - 1].type = IDEN;
					AST(ctmp2,&atmp->c[atmp->num - 1]);
					ctmp2 = &ctmp1->c[0];//declarator
					if (ctmp2->num > 1){
						ctmp2 = &ctmp2->c[1];//comma_array_sizes
						while (1){
							atmp1 = getAst(2);
							atmp1[0] = atmp->c[atmp->num - 2];
							atmp1[1].type = EXPR;
							AST(&ctmp2->c[1],&atmp1[1]);
							atmp->c[atmp->num - 2].type = ARRATYPE;
							atmp->c[atmp->num - 2].data = ASTFlags[ARRATYPE];
							atmp->c[atmp->num - 2].num = 2;
							atmp->c[atmp->num - 2].cap = 2;
							atmp->c[atmp->num - 2].c = atmp1;
							if (ctmp2->num > 3) ctmp2 = &ctmp2->c[3];else break;
						}
					}
					if (ctmp1->num > 1){
						ctmp2 = &ctmp1->c[1];//init_declarator1
						if (atmp->num == atmp->cap) doubleSpace(atmp);
						++atmp->num;
						atmp->c[atmp->num - 1].type = INIT;
						AST(&ctmp2->c[1],&atmp->c[atmp->num - 1]);
					}
					if (strcmp(ctmp->c[ctmp->num - 1].data,"comma_init_declarators") == 0)
						ctmp = &ctmp->c[ctmp->num - 1];
					else
						break;
				}
				if (root->num > 1) root = &root->c[1];else break;
			}
			++ptr;
		}
		root = bk;
		if (strcmp(root->c[ptr].data,"comma_statements") == 0){
			root = &root->c[ptr];//comma_statements
			while (1){
				if (ast->num == ast->cap) doubleSpace(ast);
				++ast->num;
				ast->c[ast->num - 1].type = STMT;
				AST(&root->c[0],&ast->c[ast->num - 1]);
				if (root->num > 1) root = &root->c[1];else break;
			}
		}
	}else if (EXPR <= ast->type && ast->type <= STRICONS){
		int i;
		struct node *ctmp;
		struct ASTNode *atmp,*atmp1;
		if (strcmp(root->data,"expression") == 0){
			AST(&root->c[0],ast);
			if (root->num > 1){
				root = &root->c[1];
				AST(root,ast);
			}
		}else if (strcmp(root->data,"comma_assignment_expressions") == 0){
			atmp = getAst(2);
			atmp[0] = *ast;
			atmp[1].type = EXPR;
			AST(&root->c[1],&atmp[1]);
			ast->type = BINAEXPR;
			ast->data = root->c[0].data;
			ast->num = ast->cap = 2;
			ast->c = atmp;
			if (root->num > 2) AST(&root->c[2],ast);
		}else if (strcmp(root->data,"assignment_expression") == 0){
			if (strcmp(root->c[0].data,"(") == 0){
				root = &root->c[1];//assignment_expression2
				if (strcmp(root->c[0].data,"type_name") == 0){
					atmp = getAst(2);
					atmp[0].type = EXPR;
					AST(&root->c[0],&atmp[0]);
					atmp[1].type = EXPR;
					for (i = 2;i < root->num;++i) AST(&root->c[i],&atmp[1]);
					ast->type = CASTEXPR;
					ast->data = ASTFlags[CASTEXPR];
					ast->c = atmp;
					ast->num = ast->cap = 2;
				}else{
					AST(&root->c[0],ast);
					for (i = 2;i < root->num;++i) AST(&root->c[i],ast);
				}
			}else if (strcmp(root->c[0].data,"identifier") == 0){
				for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
			}else if (strcmp(root->c[0].data,"constant") == 0){
				for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
			}else if (strcmp(root->c[0].data,"string") == 0){
				for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
			}else if (strcmp(root->c[0].data,"++") == 0){
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = UNAREXPR;
				ast->data = root->c[0].data;
				ast->num = ast->cap = 1;
				ast->c = atmp;
				AST(&root->c[2],ast);
			}else if (strcmp(root->c[0].data,"--") == 0){
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = UNAREXPR;
				ast->data = root->c[0].data;
				ast->num = ast->cap = 1;
				ast->c = atmp;
				AST(&root->c[2],ast);
			}else if (strcmp(root->c[0].data,"unary_operator") == 0){
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = UNAREXPR;
				ast->data = root->c[0].c[0].data;
				ast->num = ast->cap = 1;
				ast->c = atmp;
				AST(&root->c[2],ast);
			}else{
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = SZOFEXPR;
				ast->data = ASTFlags[SZOFEXPR];
				ast->num = ast->cap = 1;
				ast->c = atmp;
				AST(&root->c[2],ast);
			}
		}else if (strcmp(root->data,"assignment_expression1") == 0){
			if (strcmp(root->c[0].data,"assignment_operator") == 0){
				atmp = getAst(2);
				atmp[0] = *ast;
				atmp[1].type = EXPR;
				AST(&root->c[1],&atmp[1]);
				ast->type = BINAEXPR;
				ast->data = root->c[0].c[0].data;
				ast->num = ast->cap = 2;
				ast->c = atmp;
			}else{
				for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
			}
		}else if (strcmp(root->data,"assignment_expression2") == 0){
			//never
		}else if (strcmp(root->data,"constant_expression") == 0){
			AST(&root->c[0],ast);
		}else if (strcmp(root->data,"logical_or_expression") == 0){
			for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
		}else if (strcmp(root->data,"comma_logical_and_expressions") == 0){
			atmp = getAst(2);
			atmp[0] = *ast;
			atmp[1].type = EXPR;
			AST(&root->c[1],&atmp[1]);
			ast->type = BINAEXPR;
			ast->data = root->c[0].data;
			ast->num = ast->cap = 2;
			ast->c = atmp;
			if (root->num > 2) AST(&root->c[2],ast);
		}else if (strcmp(root->data,"logical_and_expression") == 0){
			for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
		}else if (strcmp(root->data,"comma_inclusive_or_expressions") == 0){
			atmp = getAst(2);
			atmp[0] = *ast;
			atmp[1].type = EXPR;
			AST(&root->c[1],&atmp[1]);
			ast->type = BINAEXPR;
			ast->data = root->c[0].data;
			ast->num = ast->cap = 2;
			ast->c = atmp;
			if (root->num > 2) AST(&root->c[2],ast);
		}else if (strcmp(root->data,"inclusive_or_expression") == 0){
			for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
		}else if (strcmp(root->data,"comma_exclusive_or_expressions") == 0){
			atmp = getAst(2);
			atmp[0] = *ast;
			atmp[1].type = EXPR;
			AST(&root->c[1],&atmp[1]);
			ast->type = BINAEXPR;
			ast->data = root->c[0].data;
			ast->num = ast->cap = 2;
			ast->c = atmp;
			if (root->num > 2) AST(&root->c[2],ast);
		}else if (strcmp(root->data,"exclusive_or_expression") == 0){
			for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
		}else if (strcmp(root->data,"comma_and_expressions") == 0){
			atmp = getAst(2);
			atmp[0] = *ast;
			atmp[1].type = EXPR;
			AST(&root->c[1],&atmp[1]);
			ast->type = BINAEXPR;
			ast->data = root->c[0].data;
			ast->num = ast->cap = 2;
			ast->c = atmp;
			if (root->num > 2) AST(&root->c[2],ast);
		}else if (strcmp(root->data,"and_expression") == 0){
			for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
		}else if (strcmp(root->data,"comma_equality_expressions") == 0){
			atmp = getAst(2);
			atmp[0] = *ast;
			atmp[1].type = EXPR;
			AST(&root->c[1],&atmp[1]);
			ast->type = BINAEXPR;
			ast->data = root->c[0].data;
			ast->num = ast->cap = 2;
			ast->c = atmp;
			if (root->num > 2) AST(&root->c[2],ast);
		}else if (strcmp(root->data,"equality_expression") == 0){
			for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
		}else if (strcmp(root->data,"comma_relational_expressions") == 0){
			atmp = getAst(2);
			atmp[0] = *ast;
			atmp[1].type = EXPR;
			AST(&root->c[1],&atmp[1]);
			ast->type = BINAEXPR;
			ast->data = root->c[0].c[0].data;
			ast->num = ast->cap = 2;
			ast->c = atmp;
			if (root->num > 2) AST(&root->c[2],ast);
		}else if (strcmp(root->data,"relational_expression") == 0){
			for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
		}else if (strcmp(root->data,"comma_shift_expressions") == 0){
			atmp = getAst(2);
			atmp[0] = *ast;
			atmp[1].type = EXPR;
			AST(&root->c[1],&atmp[1]);
			ast->type = BINAEXPR;
			ast->data = root->c[0].c[0].data;
			ast->num = ast->cap = 2;
			ast->c = atmp;
			if (root->num > 2) AST(&root->c[2],ast);
		}else if (strcmp(root->data,"shift_expression") == 0){
			for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
		}else if (strcmp(root->data,"comma_additive_expressions") == 0){
			atmp = getAst(2);
			atmp[0] = *ast;
			atmp[1].type = EXPR;
			AST(&root->c[1],&atmp[1]);
			ast->type = BINAEXPR;
			ast->data = root->c[0].c[0].data;
			ast->num = ast->cap = 2;
			ast->c = atmp;
			if (root->num > 2) AST(&root->c[2],ast);
		}else if (strcmp(root->data,"additive_expression") == 0){
			for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
		}else if (strcmp(root->data,"comma_multiplicative_expressions") == 0){
			atmp = getAst(2);
			atmp[0] = *ast;
			atmp[1].type = EXPR;
			AST(&root->c[1],&atmp[1]);
			ast->type = BINAEXPR;
			ast->data = root->c[0].c[0].data;
			ast->num = ast->cap = 2;
			ast->c = atmp;
			if (root->num > 2) AST(&root->c[2],ast);
		}else if (strcmp(root->data,"multiplicative_expression") == 0){
			for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
		}else if (strcmp(root->data,"comma_cast_expressions") == 0){
			atmp = getAst(2);
			atmp[0] = *ast;
			atmp[1].type = EXPR;
			AST(&root->c[1],&atmp[1]);
			ast->type = BINAEXPR;
			ast->data = root->c[0].c[0].data;
			ast->num = ast->cap = 2;
			ast->c = atmp;
			if (root->num > 2) AST(&root->c[2],ast);
		}else if (strcmp(root->data,"cast_expression") == 0){
			if (strcmp(root->c[0].data,"identifier") == 0){
				for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
			}else if (strcmp(root->c[0].data,"constant") == 0){
				for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
			}else if (strcmp(root->c[0].data,"string") == 0){
				for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
			}else if (strcmp(root->c[0].data,"(") == 0){
				AST(&root->c[1],ast);
			}else if (strcmp(root->c[0].data,"++") == 0){
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = UNAREXPR;
				ast->data = root->c[0].data;
				ast->num = ast->cap = 1;
				ast->c = atmp;
			}else if (strcmp(root->c[0].data,"--") == 0){
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = UNAREXPR;
				ast->data = root->c[0].data;
				ast->num = ast->cap = 1;
				ast->c = atmp;
			}else if (strcmp(root->c[0].data,"unary_operator") == 0){
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = UNAREXPR;
				ast->data = root->c[0].c[0].data;
				ast->num = ast->cap = 1;
				ast->c = atmp;
			}else{//sizeof ...
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = SZOFEXPR;
				ast->data = ASTFlags[SZOFEXPR];
				ast->num = ast->cap = 1;
				ast->c = atmp;
			}
		}else if (strcmp(root->data,"cast_expression1") == 0){
			if (strcmp(root->c[0].data,"expression") == 0){
				AST(&root->c[0],ast);
				if (root->num > 2) AST(&root->c[2],ast);
			}else{
				atmp = getAst(2);
				atmp[0].type = EXPR;
				AST(&root->c[0],&atmp[0]);
				atmp[1].type = EXPR;
				AST(&root->c[2],&atmp[1]);
				ast.type = CASTEXPR;
				ast->data = ASTFlags[CASTEXPR];
				ast->num = ast->cap = 2;
				ast->c = atmp;
			}
		}else if (strcmp(root->data,"type_name") == 0){
			
		}
	}else{}
}
/*
check points:
getAst(...) **ast->cap = ast->num = ...**
getAst(...) **ast->c[...].**
if (...) doubleSpace(ast); ++ast->num;
*/
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
//	AST(root,ast);
//	del(ast);
//	free(ast);
	print(root,0);
	del(root);
	free(root);
	free(list);
	return 0;
}

