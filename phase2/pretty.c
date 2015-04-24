#include "parser.h"
#include <stdio.h>
#include <string.h>
int n,c,flag,size;
char s[1000010];
void readInput(void){
	n = -1;
	c = getchar();
	while (c != EOF){
		s[++n] = c;
		c = getchar();
	}
	s[++n] = 0;
}
void tab(int t){
	int i;
	for (i = 0;i < t;++i) printf("\t");
}
void prettyPrint(struct node *root,int t,int newLine){
	int i;
	if (strcmp(root->data,"program") == 0){
		prettyPrint(&root->c[0],t,1);
		if (root->num > 1){
			printf("\n");
			prettyPrint(&root->c[1],t,1);
		}
	}else if (strcmp(root->data,"dec_or_funcs") == 0){
		prettyPrint(&root->c[0],t,1);
		if (root->num > 1){
			printf("\n");
			prettyPrint(&root->c[1],t,1);
		}
	}else if (strcmp(root->data,"dec_or_func") == 0){
		prettyPrint(&root->c[0],t,1);
		prettyPrint(&root->c[1],t,0);
		printf("\n");
	}else if (strcmp(root->data,"dec_or_func1") == 0){
		if (strcmp(root->c[0].data,";") == 0){
			printf(";");
			return;
		}else{
			printf(" ");
			prettyPrint(&root->c[0],t,0);
			if (root->num > 1) prettyPrint(&root->c[1],t,0);
		}
	}else if (strcmp(root->data,"dec_or_func2") == 0){
		if (strcmp(root->c[0].data,"(") == 0){
			printf("(");
			prettyPrint(&root->c[1],t,0);
		}else{
			for (i = 0;i < root->num - 1;++i) prettyPrint(&root->c[i],t,0);
			printf(";");
		}
	}else if (strcmp(root->data,"declaration") == 0){
		prettyPrint(&root->c[0],t,1);
		prettyPrint(&root->c[1],t,0);
		printf("\n");
	}else if (strcmp(root->data,"declaration1") == 0){
		if (strcmp(root->c[0].data,";") == 0){
			printf(";");
		}else{
			printf(" ");
			prettyPrint(&root->c[0],t,0);
			printf(";");
		}
	}else if (strcmp(root->data,"function_definition1") == 0){
		if (strcmp(root->c[0].data,")") == 0){
			printf(") ");
			prettyPrint(&root->c[1],t,0);
		}else{
			prettyPrint(&root->c[0],t,0);
			printf(")");
			prettyPrint(&root->c[2],t,0);
		}
	}else if (strcmp(root->data,"parameters") == 0){
		prettyPrint(&root->c[0],t,0);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_plain_declarations") == 0){
		printf(", ");
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"declarators") == 0){
		prettyPrint(&root->c[0],t,0);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_declarators") == 0){
		printf(", ");
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"init_declarators") == 0){
		prettyPrint(&root->c[0],t,0);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_init_declarators") == 0){
		printf(", ");
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"init_declarator") == 0){
		prettyPrint(&root->c[0],t,0);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"init_declarator1") == 0){
		printf(" = ");
		prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"initializer") == 0){
		if (strcmp(root->c[0].data,"{") == 0){
			printf("{");
			prettyPrint(&root->c[1],t,0);
			prettyPrint(&root->c[2],t,0);
			printf("}");
		}else{
			prettyPrint(&root->c[0],t,0);
		}
	}else if (strcmp(root->data,"comma_initializers") == 0){
		printf(", ");
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"type_specifier") == 0){
		if (strcmp(root->c[0].data,"struct_or_union") == 0){
			prettyPrint(&root->c[0],t,newLine);
			printf(" ");
			prettyPrint(&root->c[1],t,0);
		}else{
			if (newLine) tab(t);
			printf("%s",root->c[0].data);
		}
	}else if (strcmp(root->data,"type_specifier1") == 0){
		if (strcmp(root->c[0].data,"{") == 0){
			printf("{\n");
			prettyPrint(&root->c[1],t + 1,1);
			tab(t);
			printf("}");
		}else{
			prettyPrint(&root->c[0],t,0);
			if (root->num > 1) prettyPrint(&root->c[1],t,0);
		}
	}else if (strcmp(root->data,"type_specifier2") == 0){
		printf("{\n");
		prettyPrint(&root->c[1],t + 1,1);
		tab(t);
		printf("}");
	}else if (strcmp(root->data,"type_specifiers") == 0){
		prettyPrint(&root->c[0],t,newLine);
		printf(" ");
		prettyPrint(&root->c[1],t,0);
		printf(";\n");
		if (root->num > 3) prettyPrint(&root->c[3],t,1);
	}else if (strcmp(root->data,"comma_type_specifiers") == 0){
		prettyPrint(&root->c[0],t,newLine);
		printf(" ");
		prettyPrint(&root->c[1],t,0);
		printf(";\n");
		if (root->num > 3) prettyPrint(&root->c[3],t,1);
	}else if (strcmp(root->data,"struct_or_union") == 0){
		if (newLine) tab(t);
		printf(root->c[0].data);
	}else if (strcmp(root->data,"plain_declaration") == 0){
		prettyPrint(&root->c[0],t,0);
		printf(" ");
		prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"declarator") == 0){
		prettyPrint(&root->c[0],t,0);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_array_sizes") == 0){
		printf("[");
		prettyPrint(&root->c[1],t,0);
		printf("]");
		if (root->num > 3) prettyPrint(&root->c[3],t,0);
	}else if (strcmp(root->data,"plain_declarator") == 0){
		if (strcmp(root->c[0].data,"*") == 0){
			if (newLine) tab(t);
			printf("*");
			prettyPrint(&root->c[1],t,0);
		}else{
			prettyPrint(&root->c[0],t,newLine);
		}
	}else if (strcmp(root->data,"statement") == 0){
		prettyPrint(&root->c[0],t,newLine);
	}else if (strcmp(root->data,"selection_statement") == 0){
		if (newLine) tab(t);
		printf("if (");
		prettyPrint(&root->c[2],t,0);
		printf(")");
		if (strcmp(root->c[4].c[0].data,"compound_statement") == 0){
			printf(" ");
			prettyPrint(&root->c[4],t,0);
		}else{
			printf("\n");
			prettyPrint(&root->c[4],t + 1,1);
		}
		if (root->num > 5){
			printf("\n");
			tab(t);
			printf("else");
			if (strcmp(root->c[5].c[1].c[0].data,"compound_statement") == 0){
				printf(" ");
				prettyPrint(&root->c[5].c[1],t,0);
			}else{
				printf("\n");
				prettyPrint(&root->c[5].c[1],t + 1,1);
			}
		}
	}else if (strcmp(root->data,"expression_statement") == 0){
		if (root->num == 1){
			if (newLine) tab(t);
			printf(";");
		}else{
			prettyPrint(&root->c[0],t,newLine);
			printf(";");
		}
	}else if (strcmp(root->data,"compound_statement") == 0){
		if (newLine) tab(t);
		printf("{\n");
		i = 1;
		if (strcmp(root->c[i].data,"}") != 0){
			prettyPrint(&root->c[i],t + 1,1);
			++i;
		}
		if (strcmp(root->c[i].data,"}") != 0){
			prettyPrint(&root->c[i],t + 1,1);
			++i;
		}
		tab(t);
		printf("}");
	}else if (strcmp(root->data,"comma_declarations") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,1);
	}else if (strcmp(root->data,"comma_statements") == 0){
		prettyPrint(&root->c[0],t,newLine);
		printf("\n");
		if (root->num > 1) prettyPrint(&root->c[1],t,1);
	}else if (strcmp(root->data,"iteration_statement") == 0){
		if (strcmp(root->c[0].data,"while") == 0){
			if (newLine) tab(t);
			printf("while (");
			prettyPrint(&root->c[2],t,0);
			printf(")");
			if (strcmp(root->c[4].c[0].data,"compound_statement") == 0){
				printf(" ");
				prettyPrint(&root->c[4],t,0);
			}else{
				printf("\n");
				prettyPrint(&root->c[4],t + 1,1);
			}
		}else{
			if (newLine) tab(t);
			printf("for (");
			prettyPrint(&root->c[2],t,0);
		}
	}else if (strcmp(root->data,"iteration_statement1") == 0){
		prettyPrint(&root->c[0],t,0);
		prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"iteration_statement2") == 0){
		prettyPrint(&root->c[0],t,0);
		prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"iteration_statement3") == 0){
		i = 0;
		if (root->num == 3){
			prettyPrint(&root->c[i],t,0);
			++i;
		}
		++i;
		printf(")");
		if (strcmp(root->c[i].c[0].data,"compound_statement") == 0){
			printf(" ");
			prettyPrint(&root->c[i],t,0);
		}else{
			printf("\n");
			prettyPrint(&root->c[i],t + 1,1);
		}
	}else if (strcmp(root->data,"jump_statement") == 0){
		if (newLine) tab(t);
		printf("%s",root->c[0].data);
		if (strcmp(root->c[1].data,";") == 0){
			printf(";");
		}else{
			root = &root->c[1];
			if (root->num == 1){
				printf(";");
			}else{
				printf(" ");
				prettyPrint(&root->c[0],t,0);
				printf(";");
			}
		}
	}else if (strcmp(root->data,"expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_assignment_expressions") == 0){
		printf(", ");
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"assignment_expression") == 0){
		if (strcmp(root->c[0].data,"(") == 0){
			if (newLine) tab(t);
			printf("(");
			prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"identifier") == 0){
			prettyPrint(&root->c[0],t,newLine);
			for (i = 1;i < root->num;++i) prettyPrint(&root->c[i],t,0);
		}else if (strcmp(root->c[0].data,"constant") == 0){
			prettyPrint(&root->c[0],t,newLine);
			for (i = 1;i < root->num;++i) prettyPrint(&root->c[i],t,0);
		}else if (strcmp(root->c[0].data,"string") == 0){
			prettyPrint(&root->c[0],t,newLine);
			for (i = 1;i < root->num;++i) prettyPrint(&root->c[i],t,0);
		}else if (strcmp(root->c[0].data,"++") == 0){
			if (newLine) tab(t);
			printf("++");
			for (i = 1;i < root->num;++i) prettyPrint(&root->c[i],t,0);
		}else if (strcmp(root->c[0].data,"--") == 0){
			if (newLine) tab(t);
			printf("--");
			for (i = 1;i < root->num;++i) prettyPrint(&root->c[i],t,0);
		}else if (strcmp(root->c[0].data,"unary_operator") == 0){
			prettyPrint(&root->c[0],t,newLine);
			for (i = 1;i < root->num;++i) prettyPrint(&root->c[i],t,0);
		}else if (strcmp(root->c[0].data,"sizeof") == 0){
			if (newLine) tab(t);
			printf("sizeof");
			for (i = 1;i < root->num;++i) prettyPrint(&root->c[i],t,0);
		}
	}else if (strcmp(root->data,"assignment_expression1") == 0){
		for (i = 0;i < root->num;++i) prettyPrint(&root->c[i],t,0);
	}else if (strcmp(root->data,"assignment_expression2") == 0){
		prettyPrint(&root->c[0],t,0);
		printf(")");
		for (i = 2;i < root->num;++i) prettyPrint(&root->c[i],t,0);
	}else if (strcmp(root->data,"assignment_operator") == 0){
		printf(" %s ",root->c[0].data);
	}else if (strcmp(root->data,"constant_expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
	}else if (strcmp(root->data,"logical_or_expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_logical_and_expressions") == 0){
		printf(" || ");
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"logical_and_expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_inclusive_or_expressions") == 0){
		printf(" && ");
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"inclusive_or_expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_exclusive_or_expressions") == 0){
		printf(" | ");
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"exclusive_or_expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_and_expressions") == 0){
		printf(" ^ ");
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"and_expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_equality_expressions") == 0){
		printf(" & ");
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"equality_expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_relational_expressions") == 0){
		printf(" %s ",root->c[0].c[0].data);
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"relational_expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_shift_expressions") == 0){
		printf(" %s ",root->c[0].c[0].data);
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"shift_expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_additive_expressions") == 0){
		printf(" %s ",root->c[0].c[0].data);
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"additive_expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_multiplicative_expressions") == 0){
		printf(" %s ",root->c[0].c[0].data);
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"multiplicative_expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"comma_cast_expressions") == 0){
		printf(" %s ",root->c[0].c[0].data);
		prettyPrint(&root->c[1],t,0);
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"cast_expression") == 0){
		if (strcmp(root->c[0].data,"identifier") == 0){
			prettyPrint(&root->c[0],t,newLine);
			if (root->num > 1) prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"constant") == 0){
			prettyPrint(&root->c[0],t,newLine);
			if (root->num > 1) prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"string") == 0){
			prettyPrint(&root->c[0],t,newLine);
			if (root->num > 1) prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"(") == 0){
			if (newLine) tab(t);
			printf("(");
			prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"++") == 0){
			if (newLine) tab(t);
			printf("++");
			prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"--") == 0){
			if (newLine) tab(t);
			printf("--");
			prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"unary_operator") == 0){
			prettyPrint(&root->c[0],t,newLine);
			prettyPrint(&root->c[1],t,0);
		}else{
			if (newLine) tab(t);
			printf("sizeof");
			prettyPrint(&root->c[1],t,0);
		}
	}else if (strcmp(root->data,"cast_expression1") == 0){
		prettyPrint(&root->c[0],t,0);
		printf(")");
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"type_name") == 0){
		prettyPrint(&root->c[0],t,0);
		if (root->num > 1){
			printf(" ");
			prettyPrint(&root->c[1],t,0);
		}
	}else if (strcmp(root->data,"pointers") == 0){
		printf("*");
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"unary_expression") == 0){
		if (strcmp(root->c[0].data,"postfix_expression") == 0){
			prettyPrint(&root->c[0],t,newLine);
		}else if (strcmp(root->c[0].data,"++") == 0){
			if (newLine) tab(t);
			printf("++");
			prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"--") == 0){
			if (newLine) tab(t);
			printf("--");
			prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"unary_operator") == 0){
			prettyPrint(&root->c[0],t,newLine);
			prettyPrint(&root->c[1],t,0);
		}else{
			if (newLine) tab(t);
			printf("sizeof");
			prettyPrint(&root->c[1],t,0);
		}
	}else if (strcmp(root->data,"unary_expression1") == 0){
		if (strcmp(root->c[0].data,"(") != 0) printf(" ");
		if (strcmp(root->c[0].data,"identifier") == 0){
			prettyPrint(&root->c[0],t,newLine);
			if (root->num > 1) prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"constant") == 0){
			prettyPrint(&root->c[0],t,newLine);
			if (root->num > 1) prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"string") == 0){
			prettyPrint(&root->c[0],t,newLine);
			if (root->num > 1) prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"(") == 0){
			if (newLine) tab(t);
			printf("(");
			prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"++") == 0){
			if (newLine) tab(t);
			printf("++");
			prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"--") == 0){
			if (newLine) tab(t);
			printf("--");
			prettyPrint(&root->c[1],t,0);
		}else if (strcmp(root->c[0].data,"unary_operator") == 0){
			prettyPrint(&root->c[0],t,newLine);
			prettyPrint(&root->c[1],t,0);
		}else{
			if (newLine) tab(t);
			prettyPrint(&root->c[1],t,0);
		}
	}else if (strcmp(root->data,"unary_expression2") == 0){
		prettyPrint(&root->c[0],t,0);
		printf(")");
		if (root->num > 2) prettyPrint(&root->c[2],t,0);
	}else if (strcmp(root->data,"unary_operator") == 0){
		if (newLine) tab(t);
		printf("%s",root->c[0].data);
	}else if (strcmp(root->data,"postfix_expression") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"postfixes") == 0){
		prettyPrint(&root->c[0],t,newLine);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
	}else if (strcmp(root->data,"postfix") == 0){
		if (newLine) tab(t);
		printf("%s",root->c[0].data);
		if (root->num > 1) prettyPrint(&root->c[1],t,0);
		if (root->num > 2) printf("]");
	}else if (strcmp(root->data,"postfix1") == 0){
		if (root->num == 0){
			printf(")");
		}else{
			prettyPrint(&root->c[0],t,newLine);
			printf(")");
		}
	}else if (strcmp(root->data,"arguments") == 0){
		prettyPrint(&root->c[0],t,newLine);
	}else if (strcmp(root->data,"primary_expression") == 0){
		if (root->num == 1){
			prettyPrint(&root->c[0],t,newLine);
		}else{
			printf("(");
			prettyPrint(&root->c[1],t,0);
			printf(")");
		}
	}else if (strcmp(root->data,"constant") == 0){
		prettyPrint(&root->c[0],t,newLine);
	}else if (strcmp(root->data,"identifier") == 0){
		if (newLine) tab(t);
		printf("%s",root->c[0].data);
	}else if (strcmp(root->data,"integer_constant") == 0){
		if (newLine) tab(t);
		printf("%s",root->c[0].data);
	}else if (strcmp(root->data,"character_constant") == 0){
		if (newLine) tab(t);
		printf("%s",root->c[0].data);
	}else if (strcmp(root->data,"string") == 0){
		if (newLine) tab(t);
		printf("%s",root->c[0].data);
	}
}
int main(void){
	struct ASTNode *tmp;
	struct node *root;
	flag = 1;
	readInput();
	tmp = makeAst(s,&flag,&size,&root);
	if (!flag){
		printf("CompileError\n");
	}else{
		astDel(tmp);
		free(tmp);
		prettyPrint(root,0,1);
		cstDel(root);
		free(root);
		free(list);
	}
	return 0;
}

