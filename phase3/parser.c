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
//	freopen("AST.txt","w",stdout);
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

void cstDel(struct node *s){
	int n,i;
	n = s->num;
	for (i = 0;i < n;++i) cstDel(&s->c[i]);
	free(s->c);
}

//------for------ast------

void doubleSpace(struct AstNode *a){
	struct AstNode *tmp = (struct AstNode *)malloc(sizeof(struct AstNode) * a->cap * 2);
	int i;
	for (i = 0;i < a->cap;++i)
		tmp[i] = a->c[i];
	a->cap *= 2;
	free(a->c);
	a->c = tmp;
}

struct AstNode *getAst(int n){
	return (struct AstNode *)malloc(sizeof(struct AstNode) * n);
}

static void AST(struct node *root,struct AstNode *ast){
//	ast->data = AstFlags[ast->type];
//	ast->c = NULL;
//	ast->num = ast->cap = 0;
	if (ast->type == ROOT){
		ast->data = AstFlags[ast->type];
		ast->c = getAst(1);
		ast->num = 0;
		ast->cap = 1;
		while (1){
			if (ast->cap == ast->num) doubleSpace(ast);
			++ast->num;
			ast->c[ast->num - 1].type = DECL;
			AST(&root->c[0],&ast->c[ast->num - 1]);
			if (root->num > 1) root = &root->c[1];else break;
		}
	}else if (ast->type == DECL){//dec_or_func
		struct AstNode *atmp;
		struct node *ctmp;
		ast->data = AstFlags[ast->type];
		ast->c = NULL;
		ast->num = ast->cap = 0;
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
		AST(ctmp,&ast->c[ast->num - 1]);
		root = &root->c[1];//dec_or_func2
		if (strcmp(root->c[0].data,"(") == 0){//'(' function_definition1
			while (numOfPtrs--){
				atmp = getAst(1);
				*atmp = ast->c[ast->num - 2];
				ast->c[ast->num - 2].type = PTERTYPE;
				ast->c[ast->num - 2].data = AstFlags[PTERTYPE];
				ast->c[ast->num - 2].c = atmp;
				ast->c[ast->num - 2].num = 1;
				ast->c[ast->num - 2].cap = 1;
			}
			ast->type = FUNCDECL;
			ast->data = AstFlags[ast->type];
			root = &root->c[1];//function_definition1
			if (strcmp(root->c[0].data,")") == 0){//')' compound_statement
				if (ast->num == ast->cap) doubleSpace(ast);
				++ast->num;
				ast->c[ast->num - 1].type = PARA;
				ast->c[ast->num - 1].data = AstFlags[PARA];
				ast->c[ast->num - 1].num = 0;
				ast->c[ast->num - 1].cap = 0;
				ast->c[ast->num - 1].c = NULL;
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
			AST(root,&ast->c[ast->num - 1]);
		}else{//comma_array_sizes init_declarator1 comma_init_declarators ';'
			int cptr;
			ast->type = VARIDECL;
			ast->data = AstFlags[VARIDECL];
			if (ast->num == ast->cap) doubleSpace(ast);
			++ast->num;
			ast->c[ast->num - 1] = ast->c[ast->num - 2];
			ast->c[ast->num - 2] = ast->c[0];
			if (ast->c[0].type == STRUTYPE || ast->c[0].type == UNIOTYPE){
				ast->c[ast->num - 2].c = getAst(1);
				ast->c[ast->num - 2].c[0].type = IDEN;
				ast->c[ast->num - 2].c[0].data = ast->c[0].c[0].data;
				ast->c[ast->num - 2].c[0].c = NULL;
				ast->c[ast->num - 2].c[0].num = 0;
				ast->c[ast->num - 2].c[0].cap = 0;
				ast->c[ast->num - 2].num = 1;
				ast->c[ast->num - 2].cap = 1;
			}
			while (numOfPtrs--){
				atmp = getAst(1);
				*atmp = ast->c[ast->num - 2];
				ast->c[ast->num - 2].type = PTERTYPE;
				ast->c[ast->num - 2].data = AstFlags[PTERTYPE];
				ast->c[ast->num - 2].c = atmp;
				ast->c[ast->num - 2].num = 1;
				ast->c[ast->num - 2].cap = 1;
			}
			cptr = 0;
			if (strcmp(root->c[cptr].data,"comma_array_sizes") == 0){
				struct AstNode *xxx = &ast->c[ast->num - 2];
				ctmp = &root->c[cptr];
				++cptr;
				while (1){
					atmp = getAst(2);
					atmp[0] = *xxx;
					atmp[1].type = EXPR;
					AST(&ctmp->c[1],&atmp[1]);
					xxx->type = ARRATYPE;
					xxx->data = AstFlags[ARRATYPE];
					xxx->c = atmp;
					xxx->num = 2;
					xxx->cap = 2;
					if (ctmp->num >= 4) ctmp = &ctmp->c[3];else break;
					xxx = &xxx->c[0];
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
						ast->c[ast->num - 1].c[0].c = NULL;
						ast->c[ast->num - 1].c[0].num = 0;
						ast->c[ast->num - 1].c[0].cap = 0;
						ast->c[ast->num - 1].num = 1;
						ast->c[ast->num - 1].cap = 1;
					}
					ctmp = &root->c[1];//init_declarator
					ctmp = &ctmp->c[0];//declarator
					ttmp = &ctmp->c[0];//plain_declarator
					while (ttmp->num > 1){
						ttmp = &ttmp->c[1];
						atmp = getAst(1);
						*atmp = ast->c[ast->num - 1];
						ast->c[ast->num - 1].type = PTERTYPE;
						ast->c[ast->num - 1].data = AstFlags[PTERTYPE];
						ast->c[ast->num - 1].c = atmp;
						ast->c[ast->num - 1].num = 1;
						ast->c[ast->num - 1].cap = 1;
					}
					if (ast->num == ast->cap) doubleSpace(ast);
					++ast->num;
					ast->c[ast->num - 1].type = IDEN;
					AST(&ttmp->c[0],&ast->c[ast->num - 1]);
					if (ctmp->num > 1){
						struct AstNode *xxx = &ast->c[ast->num - 2];
						ctmp = &ctmp->c[1];//comma_array_sizes
						while (1){
							atmp = getAst(2);
							atmp[0] = *xxx;
							atmp[1].type = EXPR;
							AST(&ctmp->c[1],&atmp[1]);
							xxx->type = ARRATYPE;
							xxx->data = AstFlags[ARRATYPE];
							xxx->c = atmp;
							xxx->num = 2;
							xxx->cap = 2;
							if (ctmp->num >= 4) ctmp = &ctmp->c[3];else break;
							xxx = &xxx->c[0];
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
		AST(NULL,ast);
	}else if (ast->type == FUNCDECL){
		//never
	}else if (ast->type == STRUDECL){
		//never
	}else if (ast->type == UNIODECL){
		//never
	}else if (ast->type == VARIDECL){
		struct AstNode *tmp = ast->c;
		int num = ast->num,i;
		ast->c = getAst(1);
		ast->num = ast->cap = 1;
		ast->c[0] = tmp[0];
		i = 1;
		while (i < num){
			struct AstNode *t;
			if (ast->num == ast->cap) doubleSpace(ast);
			++ast->num;
			t = &ast->c[ast->num - 1];
			t->type = VARI;
			t->data = AstFlags[VARI];
			t->c = getAst(3);
			t->num = 0;
			t->cap = 3;
			++t->num;
			t->c[t->num - 1] = tmp[i];
			++i;
			++t->num;
			t->c[t->num - 1] = tmp[i];
			++i;
			if (i < num && tmp[i].type == INIT){
				++t->num;
				t->c[t->num - 1] = tmp[i];
				++i;
			}
		}
	}else if (ast->type == TYPE){//type_specifier
		ast->data = AstFlags[ast->type];
		ast->c = NULL;
		ast->num = ast->cap = 0;
		if (strcmp(root->c[0].data,"void") == 0){
			ast->type = VOIDTYPE;
			ast->data = AstFlags[VOIDTYPE];
		}else if (strcmp(root->c[0].data,"char") == 0){
			ast->type = CHARTYPE;
			ast->data = AstFlags[CHARTYPE];
		}else if (strcmp(root->c[0].data,"int") == 0){
			ast->type = INTETYPE;
			ast->data = AstFlags[INTETYPE];
		}else{//struct_or_union type_specifier1
			if (strcmp(root->c[0].c[0].data,"struct") == 0)
				ast->type = STRUTYPE;
			else
				ast->type = UNIOTYPE;
			root = &root->c[1];//type_specifier1
			ast->data = AstFlags[ast->type];
			ast->c = getAst(1);
			ast->num = ast->cap = 1;
			ast->c[0].type = IDEN;
			if (strcmp(root->c[0].data,"identifier") == 0){
				AST(&root->c[0],&ast->c[0]);
				if (root->num > 1){
					root = &root->c[1];//type_specifier2
				}else return;
			}else{//give names for unnamed struct / union
				int t,f[10],p = 0,i;
				++nStructName;
				t = nStructName;
				structName[++pStructName] = '#';
				ast->c[0].data = &structName[pStructName];
				while (t){
					f[++p] = t % 10 + '0';
					t /= 10;
				}
				for (i = p;i >= 1;--i) structName[++pStructName] = f[i];
				structName[++pStructName] = 0;
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
		ast->data = AstFlags[ast->type];
		ast->c = NULL;
		ast->num = ast->cap = 0;
		if (strcmp(root->c[0].data,"expression_statement") == 0){
			ast->type = EXPRSTMT;
			ast->data = AstFlags[ast->type];
			root = &root->c[0];
			if (root->num == 1){
				ast->c = getAst(1);
				ast->num = ast->cap = 1;
				ast->c[0].type = EMPTEXPR;
				ast->c[0].data = AstFlags[EMPTEXPR];
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
			ast->data = AstFlags[ast->type];
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
				ast->data = AstFlags[ast->type];
			}else if (strcmp(root->c[0].data,"break") == 0){
				ast->type = BREASTMT;
				ast->data = AstFlags[ast->type];
			}else if (strcmp(root->c[0].data,"return") == 0){
				ast->type = RETNSTMT;
				ast->data = AstFlags[ast->type];
				root = &root->c[1];//jump_statement1
				ast->c = getAst(1);
				ast->num = ast->cap = 1;
				if (root->num > 1){
					ast->c[0].type = EXPR;
					AST(&root->c[0],&ast->c[0]);
				}else{
					ast->c[0].type = EMPTEXPR;
					ast->c[0].data = AstFlags[ast->c[0].type];
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
		ast->data = AstFlags[ast->type];
		ast->c = NULL;
		ast->num = ast->cap = 0;
		struct node *tmp;
		root = &root->c[2];//iteration_statement1
		ast->c = getAst(4);
		ast->num = 4;
		ast->cap = 4;
		tmp = &root->c[0];//expression_statement
		if (tmp->num == 1){
			ast->c[0].type = EMPTEXPR;
			ast->c[0].data = AstFlags[EMPTEXPR];
			ast->c[0].c = NULL;
			ast->c[0].num = 0;
			ast->c[0].cap = 0;
		}else{
			ast->c[0].type = EXPR;
			AST(&tmp->c[0],&ast->c[0]);
		}
		root = &root->c[1];//iteration_statement2
		tmp = &root->c[0];//expression_statement
		if (tmp->num == 1){
			ast->c[1].type = EMPTEXPR;
			ast->c[1].data = AstFlags[EMPTEXPR];
			ast->c[1].c = NULL;
			ast->c[1].num = 0;
			ast->c[1].cap = 0;
		}else{
			ast->c[1].type = EXPR;
			AST(&tmp->c[0],&ast->c[1]);
		}
		root = &root->c[1];//iteration_statement3
		if (strcmp(root->c[0].data,")") == 0){
			ast->c[2].type = EMPTEXPR;
			ast->c[2].data = AstFlags[EMPTEXPR];
			ast->c[2].c = NULL;
			ast->c[2].num = 0;
			ast->c[2].cap = 0;
			root = &root->c[1];
		}else{
			ast->c[2].type = EXPR;
			AST(&root->c[0],&ast->c[2]);
			root = &root->c[2];
		}
		ast->c[3].type = STMT;
		AST(root,&ast->c[3]);
	}else if (ast->type == WHILLOOP){
		ast->data = AstFlags[ast->type];
		ast->c = NULL;
		ast->num = ast->cap = 0;
		ast->c = getAst(2);
		ast->num = ast->cap = 2;
		ast->c[0].type = EXPR;
		AST(&root->c[2],&ast->c[0]);
		ast->c[1].type = STMT;
		AST(&root->c[4],&ast->c[1]);
	}else if (ast->type == RETNSTMT){
		//never
	}else if (ast->type == COMPSTMT){
		ast->data = AstFlags[ast->type];
		ast->c = NULL;
		ast->num = ast->cap = 0;
		struct node *bk;
		int ptr = 1;
		ast->c = getAst(1);
		ast->num = 0;
		ast->cap = 1;
		bk = root;
		if (strcmp(root->c[ptr].data,"comma_declarations") == 0){
			struct node *ctmp,*ctmp1,*ctmp2;
			struct AstNode *atmp,*atmp1;
			root = &root->c[ptr];//comma_declarations
			while (1){
				ctmp = &root->c[0];//declaration
				if (ast->num == ast->cap) doubleSpace(ast);
				++ast->num;
				ast->c[ast->num - 1].type = VARIDECL;
				atmp = &ast->c[ast->num - 1];
				atmp->data = AstFlags[VARIDECL];
				atmp->c = getAst(1);
				atmp->num = atmp->cap = 1;
				atmp->c[0].type = TYPE;
				AST(&ctmp->c[0],&atmp->c[0]);
				ctmp = &ctmp->c[1];//declaration1
				if (ctmp->num > 1){
					ctmp = &ctmp->c[0];//init_declarators
					while (1){
						ctmp1 = &ctmp->c[0];//init_declarator
						if (strcmp(ctmp->data,"comma_init_declarators") == 0) ctmp1 = &ctmp->c[1];
						if (atmp->num == atmp->cap) doubleSpace(atmp);
						++atmp->num;
						atmp->c[atmp->num - 1] = atmp->c[0];
						if (atmp->c[0].type == STRUTYPE || atmp->c[0].type == UNIOTYPE){
							atmp->c[atmp->num - 1].c = getAst(1);
							atmp->c[atmp->num - 1].c[0].type = IDEN;
							atmp->c[atmp->num - 1].c[0].data = atmp->c[0].c[0].data;
							atmp->c[atmp->num - 1].c[0].c = NULL;
							atmp->c[atmp->num - 1].c[0].num = 0;
							atmp->c[atmp->num - 1].c[0].cap = 0;
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
							atmp->c[atmp->num - 1].data = AstFlags[PTERTYPE];
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
							struct AstNode *xxx = &atmp->c[atmp->num - 2];
							ctmp2 = &ctmp2->c[1];//comma_array_sizes
							while (1){
								atmp1 = getAst(2);
								atmp1[0] = *xxx;
								atmp1[1].type = EXPR;
								AST(&ctmp2->c[1],&atmp1[1]);
								xxx->type = ARRATYPE;
								xxx->data = AstFlags[ARRATYPE];
								xxx->num = 2;
								xxx->cap = 2;
								xxx->c = atmp1;
								if (ctmp2->num > 3) ctmp2 = &ctmp2->c[3];else break;
								xxx = &xxx->c[0];
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
				}
				AST(NULL,atmp);
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
		struct AstNode *atmp;
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
					ast->data = AstFlags[CASTEXPR];
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
				if (root->num > 2) AST(&root->c[2],ast);
			}else if (strcmp(root->c[0].data,"--") == 0){
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = UNAREXPR;
				ast->data = root->c[0].data;
				ast->num = ast->cap = 1;
				ast->c = atmp;
				if (root->num > 2) AST(&root->c[2],ast);
			}else if (strcmp(root->c[0].data,"unary_operator") == 0){
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = UNAREXPR;
				ast->data = root->c[0].c[0].data;
				ast->num = ast->cap = 1;
				ast->c = atmp;
				if (root->num > 2) AST(&root->c[2],ast);
			}else{
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = SZOFEXPR;
				ast->data = AstFlags[SZOFEXPR];
				ast->num = ast->cap = 1;
				ast->c = atmp;
				if (root->num > 2) AST(&root->c[2],ast);
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
				ast->data = AstFlags[SZOFEXPR];
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
				ast->type = CASTEXPR;
				ast->data = AstFlags[CASTEXPR];
				ast->num = ast->cap = 2;
				ast->c = atmp;
			}
		}else if (strcmp(root->data,"type_name") == 0){
			ast->type = TYPE;
			AST(&root->c[0],ast);
			if (root->num > 1){
				root = &root->c[1];//pointers
				while (1){
					atmp = getAst(1);
					*atmp = *ast;
					ast->type = PTERTYPE;
					ast->data = AstFlags[PTERTYPE];
					ast->num = ast->cap = 1;
					ast->c = atmp;
					if (root->num > 1) root = &root->c[1];else break;
				}
			}
		}else if (strcmp(root->data,"pointers") == 0){
			//never
		}else if (strcmp(root->data,"unary_expression") == 0){
			if (strcmp(root->c[0].data,"postfix_expression") == 0){
				AST(&root->c[0],ast);
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
			}else{//sizeof
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = SZOFEXPR;
				ast->data = AstFlags[SZOFEXPR];
				ast->num = ast->cap = 1;
				ast->c = atmp;
			}
		}else if (strcmp(root->data,"unary_expression1") == 0){
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
			}else{//sizeof
				AST(&root->c[1],ast);
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = SZOFEXPR;
				ast->data = AstFlags[SZOFEXPR];
				ast->num = ast->cap = 1;
				ast->c = atmp;
			}
		}else if (strcmp(root->data,"unary_expression2") == 0){
			if (strcmp(root->c[0].data,"expression") == 0){
				AST(&root->c[0],ast);
				if (root->num > 2) AST(&root->c[2],ast);
			}else{
				AST(&root->c[0],ast);
			}
		}else if (strcmp(root->data,"postfix_expression") == 0){
			for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
		}else if (strcmp(root->data,"postfixes") == 0){
			for (i = 0;i < root->num;++i) AST(&root->c[i],ast);
		}else if (strcmp(root->data,"postfix") == 0){
			if (strcmp(root->c[0].data,"[") == 0){
				atmp = getAst(2);
				atmp[0] = *ast;
				atmp[1].type = EXPR;
				AST(&root->c[1],&atmp[1]);
				ast->type = ARRAACSS;
				ast->data = AstFlags[ARRAACSS];
				ast->num = ast->cap = 2;
				ast->c = atmp;
			}else if (strcmp(root->c[0].data,"(") == 0){
				root = &root->c[1];//postfix1
				atmp = getAst(2);
				atmp[0] = *ast;
				if (strcmp(root->c[0].data,")") == 0){
					atmp[1].type = EMPTEXPR;
					atmp[1].data = AstFlags[EMPTEXPR];
					atmp[1].num = atmp[1].cap = 0;
					atmp[1].c = 0;
				}else{
					atmp[1].type = FUNCPARA;
					AST(&root->c[0].c[0],&atmp[1]);
				}
				ast->type = FUNCCALL;
				ast->data = AstFlags[FUNCCALL];
				ast->num = ast->cap = 2;
				ast->c = atmp;
			}else if (strcmp(root->c[0].data,".") == 0){
				atmp = getAst(2);
				atmp[0] = *ast;
				atmp[1].type = EXPR;
				AST(&root->c[1],&atmp[1]);
				ast->type = RECOACSS;
				ast->data = AstFlags[RECOACSS];
				ast->num = ast->cap = 2;
				ast->c = atmp;
			}else if (strcmp(root->c[0].data,"->") == 0){
				atmp = getAst(2);
				atmp[0] = *ast;
				atmp[1].type = EXPR;
				AST(&root->c[1],&atmp[1]);
				ast->type = PTERACSS;
				ast->data = AstFlags[PTERACSS];
				ast->num = ast->cap = 2;
				ast->c = atmp;
			}else if (strcmp(root->c[0].data,"++") == 0){
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = SELFINCR;
				ast->data = AstFlags[SELFINCR];
				ast->num = ast->cap = 1;
				ast->c = atmp;
			}else{//--
				atmp = getAst(1);
				*atmp = *ast;
				ast->type = SELFDECR;
				ast->data = AstFlags[SELFDECR];
				ast->num = ast->cap = 1;
				ast->c = atmp;
			}
		}else if (strcmp(root->data,"postfix1") == 0){
			//never
		}else if (strcmp(root->data,"arguments") == 0){
			//never
		}else if (strcmp(root->data,"primary_expression") == 0){
			if (strcmp(root->c[0].data,"(") == 0){
				AST(&root->c[1],ast);
			}else{
				AST(&root->c[0],ast);
			}
		}else if (strcmp(root->data,"constant") == 0){
			AST(&root->c[0],ast);
		}else if (strcmp(root->data,"identifier") == 0){
			ast->type = IDEN;
			ast->data = root->c[0].data;
			ast->num = ast->cap = 0;
			ast->c = NULL;
		}else if (strcmp(root->data,"integer_constant") == 0){
			ast->type = INTECONS;
			ast->data = root->c[0].data;
			ast->num = ast->cap = 0;
			ast->c = NULL;
		}else if (strcmp(root->data,"character_constant") == 0){
			ast->type = CHARCONS;
			ast->data = root->c[0].data;
			ast->num = ast->cap = 0;
			ast->c = NULL;
		}else if (strcmp(root->data,"string") == 0){
			ast->type = STRICONS;
			ast->data = root->c[0].data;
			ast->num = ast->cap = 0;
			ast->c = NULL;
		}
	}else if (ast->type == PARA){
		if (strcmp(root->data,"parameters") == 0){
			ast->data = AstFlags[ast->type];
			ast->c = getAst(1);
			ast->num = ast->cap = 1;
			ast->c[0].type = PARA;
			AST(&root->c[0],&ast->c[0]);
			if (root->num > 1) AST(&root->c[1],ast);
		}else if (strcmp(root->data,"plain_declaration") == 0){
			struct node *ctmp;
			struct AstNode *atmp;
			ast->type = VARI;
			ast->data = AstFlags[ast->type];
			ast->c = getAst(2);
			ast->num = ast->cap = 2;
			ast->c[0].type = TYPE;
			AST(&root->c[0],&ast->c[0]);
			root = &root->c[1];//declarator
			ctmp = &root->c[0];//plain_declarator
			while (ctmp->num > 1){
				ctmp = &ctmp->c[1];
				atmp = getAst(1);
				*atmp = ast->c[0];
				ast->c[0].type = PTERTYPE;
				ast->c[0].data = AstFlags[PTERTYPE];
				ast->c[0].num = ast->c[0].cap = 1;
				ast->c[0].c = atmp;
			}
			ctmp = &ctmp->c[0];//identifier
			ast->c[1].type = IDEN;
			AST(ctmp,&ast->c[1]);
			if (root->num > 1){
				struct AstNode *xxx = &ast->c[0];
				ctmp = &root->c[1];//comma_array_sizes
				while (1){
					atmp = getAst(2);
					atmp[0] = *xxx;
					atmp[1].type = EXPR;
					AST(&ctmp->c[1],&atmp[1]);
					xxx->type = ARRATYPE;
					xxx->data = AstFlags[ARRATYPE];
					xxx->num = xxx->cap = 2;
					xxx->c = atmp;
					if (ctmp->num > 3) ctmp = &ctmp->c[3];else break;
					xxx = &xxx->c[0];
				}
			}
		}else{//comma_plain_declarations
			if (ast->num == ast->cap) doubleSpace(ast);
			++ast->num;
			ast->c[ast->num - 1].type = PARA;
			AST(&root->c[1],&ast->c[ast->num - 1]);
			if (root->num > 2) AST(&root->c[2],ast);
		}
	}else if (ast->type == TYPESPEC){
		if (strcmp(root->data,"type_specifiers") == 0){
			ast->data = AstFlags[ast->type];
			ast->c = getAst(1);
			ast->num = 0;
			ast->cap = 1;
		}
		if (ast->num == ast->cap) doubleSpace(ast);
		++ast->num;
		ast->c[ast->num - 1].type = DATAFILD;
		AST(root,&ast->c[ast->num - 1]);
		if (root->num > 3) AST(&root->c[3],ast);
	}else if (ast->type == DATAFILD){//comma_type_specifiers should be ignored
		struct node *ctmp;
		struct AstNode *atmp;
		ast->data = AstFlags[ast->type];
		ast->c = getAst(1);
		ast->num = ast->cap = 1;
		ast->c[0].type = TYPE;
		AST(&root->c[0],&ast->c[0]);
		root = &root->c[1];//declarators
		while (1){
			if (ast->num == ast->cap) doubleSpace(ast);
			++ast->num;
			ast->c[ast->num - 1] = ast->c[0];
			if (ast->c[0].type == STRUTYPE || ast->c[0].type == UNIOTYPE){
				ast->c[ast->num - 1].c = getAst(1);
				ast->c[ast->num - 1].c[0].type = IDEN;
				ast->c[ast->num - 1].c[0].data = ast->c[0].c[0].data;
				ast->c[ast->num - 1].c[0].c = NULL;
				ast->c[ast->num - 1].c[0].num = 0;
				ast->c[ast->num - 1].c[0].cap = 0;
				ast->c[ast->num - 1].num = 1;
				ast->c[ast->num - 1].cap = 1;
			}
			ctmp = &root->c[0];//declarator
			if (strcmp(ctmp->data,",") == 0) ctmp = &root->c[1];//declarator
			ctmp = &ctmp->c[0];//plain_declarator
			while (ctmp->num > 1){
				atmp = getAst(1);
				*atmp = ast->c[ast->num - 1];
				ast->c[ast->num - 1].type = PTERTYPE;
				ast->c[ast->num - 1].data = AstFlags[PTERTYPE];
				ast->c[ast->num - 1].c = atmp;
				ast->c[ast->num - 1].num = 1;
				ast->c[ast->num - 1].cap = 1;
				ctmp = &ctmp->c[1];
			}
			if (ast->num == ast->cap) doubleSpace(ast);
			++ast->num;
			ast->c[ast->num - 1].type = IDEN;
			AST(&ctmp->c[0],&ast->c[ast->num - 1]);
			ctmp = &root->c[0];//declarator
			if (strcmp(ctmp->data,",") == 0) ctmp = &root->c[1];
			if (ctmp->num > 1){
				struct AstNode *xxx = &ast->c[ast->num - 2];
				ctmp = &ctmp->c[1];//comma_array_sizes
				while (1){
					atmp = getAst(2);
					atmp[0] = *xxx;
					atmp[1].type = EXPR;
					AST(&ctmp->c[1],&atmp[1]);
					xxx->type = ARRATYPE;
					xxx->data = AstFlags[ARRATYPE];
					xxx->c = atmp;
					xxx->num = 2;
					xxx->cap = 2;
					if (ctmp->num > 3) ctmp = &ctmp->c[3];else break;
					xxx = &xxx->c[0];
				}
			}
			if (strcmp(root->c[root->num - 1].data,"comma_declarators") == 0) root = &root->c[root->num - 1];else break;
		}
	}else if(ast->type == INIT){//init
		if (strcmp(root->data,"initializer") == 0){
			ast->data = AstFlags[ast->type];
			ast->c = getAst(1);
			ast->num = ast->cap = 1;
			if (root->num == 1){
				ast->c[0].type = EXPR;
				AST(&root->c[0],&ast->c[0]);
			}else{
				ast->c[0].type = INIT;
				AST(&root->c[1],&ast->c[0]);
				if (root->num > 3) AST(&root->c[2],ast);
			}
		}else{//comma_initializers
			if (ast->num == ast->cap) doubleSpace(ast);
			++ast->num;
			ast->c[ast->num - 1].type = INIT;
			AST(&root->c[1],&ast->c[ast->num - 1]);
			if (root->num > 2) AST(&root->c[2],ast);
		}
	}else{//funcpara
		ast->data = AstFlags[ast->type];
		ast->c = getAst(1);
		ast->num = ast->cap = 1;
		ast->c[0].type = EXPR;
		AST(&root->c[0],&ast->c[0]);
		if (root->num > 1){
			root = &root->c[1];//comma_assignment_expressions
			while (1){
				if (ast->num == ast->cap) doubleSpace(ast);
				++ast->num;
				ast->c[ast->num - 1].type = EXPR;
				AST(&root->c[1],&ast->c[ast->num - 1]);
				if (root->num > 2) root = &root->c[2];else break;
			}
		}
	}
}
/*
check points:
getAst(...) **ast->cap = ast->num = ...**
getAst(...) **ast->c[...].**
if (...) doubleSpace(ast); ++ast->num;
*/

static void tab(int t){
	int i;
	for (i = 0;i < t;++i) printf("\t");
}

void astPrint(char *s,struct AstNode *ast,int t){
	int i;
	tab(t);
	if (s != NULL) printf("%s",s);
	if (ast->type == ROOT){
		printf("Root\n");
		for (i = 0;i < ast->num;++i)
			astPrint(NULL,&ast->c[i],t + 1);
	}else if (ast->type == DECL){
		printf("Decl\n");
		for (i = 0;i < ast->num;++i)
			astPrint(NULL,&ast->c[i],t + 1);
	}else if (ast->type == FUNCDECL){
		printf("FuncDecl\n");
		astPrint("ReturnType: ",&ast->c[0],t + 1);
		astPrint("FuncName: ",&ast->c[1],t + 1);
		astPrint("Parameters: ",&ast->c[2],t + 1);
		astPrint("Definition: ",&ast->c[3],t + 1);
	}else if (ast->type == STRUDECL){
		//never
	}else if (ast->type == UNIODECL){
		//never
	}else if (ast->type == VARIDECL){
		printf("VariDecl\n");
		astPrint("BaseType: ",&ast->c[0],t + 1);
		for (i = 1;i < ast->num;++i)
			astPrint(NULL,&ast->c[i],t + 1);
	}else if (ast->type == TYPE){
		//never
	}else if (ast->type == BASITYPE){
		//never
	}else if (ast->type == INTETYPE){
		printf("IntType\n");
	}else if (ast->type == CHARTYPE){
		printf("CharType\n");
	}else if (ast->type == VOIDTYPE){
		printf("VoidType\n");
	}else if (ast->type == STRUTYPE){
		printf("StructType\n");
		astPrint("StructName: ",&ast->c[0],t + 1);
		if (ast->num > 1) astPrint("StructMembers: ",&ast->c[1],t + 1);
	}else if (ast->type == UNIOTYPE){
		printf("UnionType\n");
		astPrint("UnionName: ",&ast->c[0],t + 1);
		if (ast->num > 1) astPrint("UnionMembers: ",&ast->c[1],t + 1);
	}else if (ast->type == PTERTYPE){
		printf("PointerType\n");
		astPrint("BaseType: ",&ast->c[0],t + 1);
	}else if (ast->type == ARRATYPE){
		printf("ArrayType\n");
		astPrint("BaseType: ",&ast->c[0],t + 1);
		astPrint("ArraySize: ",&ast->c[1],t + 1);
	}else if (ast->type == STMT){
		//never
	}else if (ast->type == BREASTMT){
		printf("BreakStmt\n");
	}else if (ast->type == CONTSTMT){
		printf("ContinueStmt\n");
	}else if (ast->type == IFTESTMT){
		printf("IfStmt\n");
		astPrint("Condition: ",&ast->c[0],t + 1);
		astPrint("Then: ",&ast->c[1],t + 1);
		if (ast->num > 2) astPrint("Else: ",&ast->c[2],t + 1);
	}else if (ast->type == FORRLOOP){
		printf("ForLoop\n");
		astPrint("Initialize: ",&ast->c[0],t + 1);
		astPrint("Condition: ",&ast->c[1],t + 1);
		astPrint("StepAction: ",&ast->c[2],t + 1);
		astPrint("Body: ",&ast->c[3],t + 1);
	}else if (ast->type == WHILLOOP){
		printf("WhileLoop\n");
		astPrint("Condition: ",&ast->c[0],t + 1);
		astPrint("Body: ",&ast->c[1],t + 1);
	}else if (ast->type == EXPRSTMT){
		printf("ExprStmt\n");
		astPrint(NULL,&ast->c[0],t + 1);
	}else if (ast->type == RETNSTMT){
		printf("ReturnStmt\n");
		astPrint(NULL,&ast->c[0],t + 1);
	}else if (ast->type == COMPSTMT){
		printf("CompoundStmt\n");
		for (i = 0;i < ast->num;++i) astPrint(NULL,&ast->c[i],t + 1);
	}else if (ast->type == EXPR){
		//never
	}else if (ast->type == EMPTEXPR){
		printf("EmptyExpr\n");
	}else if (ast->type == BINAEXPR){
		printf("BinaryExpr: %s\n",ast->data);
		astPrint(NULL,&ast->c[0],t + 1);
		astPrint(NULL,&ast->c[1],t + 1);
	}else if (ast->type == UNAREXPR){
		printf("UnaryExpr: %s\n",ast->data);
		astPrint(NULL,&ast->c[0],t + 1);
	}else if (ast->type == SZOFEXPR){
		printf("SizeofExpr\n");
		astPrint(NULL,&ast->c[0],t + 1);
	}else if (ast->type == CASTEXPR){
		printf("CastExpr\n");
		astPrint("CastType: ",&ast->c[0],t + 1);
		astPrint("BaseExpr: ",&ast->c[1],t + 1);
	}else if (ast->type == PTERACSS){
		printf("PointerAccess\n");
		astPrint("Pointer: ",&ast->c[0],t + 1);
		astPrint("Field: ",&ast->c[1],t + 1);
	}else if (ast->type == RECOACSS){
		printf("RecordAccess\n");
		astPrint("Record: ",&ast->c[0],t + 1);
		astPrint("Field: ",&ast->c[1],t + 1);
	}else if (ast->type == SELFINCR){
		printf("SelfIncrement\n");
		astPrint(NULL,&ast->c[0],t + 1);
	}else if (ast->type == SELFDECR){
		printf("SelfDecrement\n");
		astPrint(NULL,&ast->c[0],t + 1);
	}else if (ast->type == ARRAACSS){
		printf("ArrayAccess\n");
		astPrint("Array: ",&ast->c[0],t + 1);
		astPrint("Index: ",&ast->c[1],t + 1);
	}else if (ast->type == FUNCCALL){
		printf("FunctionCall\n");
		astPrint("FuncName: ",&ast->c[0],t + 1);
		astPrint("Parameters:",&ast->c[1],t + 1);
	}else if (ast->type == IDEN){
		printf("%s\n",ast->data);
	}else if (ast->type == INTECONS){
		printf("%s\n",ast->data);
	}else if (ast->type == CHARCONS){
		printf("%s\n",ast->data);
	}else if (ast->type == STRICONS){
		printf("%s\n",ast->data);
	}else if (ast->type == PARA){
		printf("%s\n",ast->data);
		for (i = 0;i < ast->num;++i) astPrint(NULL,&ast->c[i],t + 1);
	}else if (ast->type == TYPESPEC){
		printf("%s\n",ast->data);
		for (i = 0;i < ast->num;++i) astPrint(NULL,&ast->c[i],t + 1);
	}else if (ast->type == DATAFILD){
		printf("%s\n",ast->data);
		astPrint("BaseType: ",&ast->c[0],t + 1);
		for (i = 1;i < ast->num;++i){
			if (ast->c[i].type == IDEN)
				s = "Identifier: ";
			else if (TYPE <= ast->c[i].type && ast->c[i].type <= ARRATYPE)
				s = "Type: ";
			else
				s = NULL;
			astPrint(s,&ast->c[i],t + 1);
		}
	}else if (ast->type == INIT){
		printf("%s\n",ast->data);
		for (i = 0;i < ast->num;++i) astPrint(NULL,&ast->c[i],t + 1);
	}else if (ast->type == FUNCPARA){
		printf("\n");
		for (i = 0;i < ast->num;++i) astPrint(NULL,&ast->c[i],t + 1);
	}else if (ast->type == VARI){
		printf("%s\n",ast->data);
		astPrint("Type: ",&ast->c[0],t + 1);
		astPrint("Identifier: ",&ast->c[1],t + 1);
		if (ast->num > 2) astPrint(NULL,&ast->c[2],t + 1);
	}else{
		//never
	}
}

void astDel(struct AstNode *ast){
	int i;
	if (ast->c == NULL || ast->num == 0) return;
	for (i = 0;i < ast->num;++i) astDel(&ast->c[i]);
	free(ast->c);
}

struct AstNode *makeAst(char *s,int *flag,int *size,struct node **r){
	struct node *root;
	struct AstNode *ast;
	removeComments(s);
	if (strcmp(s,"CompileError") == 0){
		*flag = 0;
		free(list);
		return NULL;
	}
	split(s);
	root = parse(s);
	if (error){
		cstDel(root);
		*flag = 0;
		free(list);
		return NULL;
	}
	pStructName = -1;
	nStructName = 0;
	ast = malloc(sizeof (struct AstNode));
	ast->type = ROOT;
	AST(root,ast);
//	astPrint(NULL,ast,0);
//	astDel(ast);
//	free(ast);
//	print(root,0);
//	cstDel(root);
//	free(root);
//	free(list);
	*size = listSize;
	*r = root;
	return ast;
}

