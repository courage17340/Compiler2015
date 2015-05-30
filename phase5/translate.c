#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "translate.h"
#include "ir.h"
static int initArraBegin;
static int make4(int x){
	int t = x;
	if (t & 3) t = ((t >> 2) + 1) << 2;
	return t;
}
static void printGlobal(struct Function *func){
	int i,j;
	printf("\t.data\n");
	for (i = 1;i <= registerNum;++i)
		if (registers->e[i]->data == -1){
			printf("%s:\t.space %d\n",registers->e[i]->name,make4(registers->e[i]->size));
		}
	for (i = 0;i < string->num;++i){
		struct String *s = string->e[i];
		int n;
		n = strlen(s->s);
		printf("__s%d:\n",i);
		for (j = 0;j < n;++j) printf("\t.byte %d\n",s->s[j]);
		for (j = n;j < s->size;++j) printf("\t.byte 0\n");
	}
	printf("\t.text\n");
}
static void printObject(struct Object *o){
	if (o->type == IRSTRC){
		//nop
	}else if (o->type == IRINTC){
		printf("%d",o->data);
	}else if (o->type == IRTEMP){
		if (o->data == -1)
			printf("%s",o->name);
		else
			printf("%d($sp)",o->data);
	}else{
		//never
	}
}
static void printSentence(struct Sentence *s,int *cur,struct Function *func){
	int i;
	if (s->op->type == IRUNAROP){
		if (strcmp(s->op->name,"&") == 0){
			if (s->ob[1]->pd == 2){
				printf("\tla $t0, ");
				printObject(s->ob[1]);
				printf("\n");
			}else{
				printf("\tlw $t0, ");
				printObject(s->ob[1]);
				printf("\n");
			}
		}else if (strcmp(s->op->name,"*") == 0){
			if (s->ob[1]->pd == 1){
				printf("\tlw $t0, ");
				printObject(s->ob[1]);
				printf("\n");
			}else{
				printf("\tla $t0, ");
				printObject(s->ob[1]);
				printf("\n");
			}
			printf("\tlw $t0, 0($t0)\n");
		}else{
			if (s->ob[1]->type == IRINTC){
				printf("\tli $t0, %d\n",s->ob[1]->data);
			}else if (s->ob[1]->pd == 1){
				printf("\tlw $t0, ");
				printObject(s->ob[1]);
				printf("\n");
				if (s->ob[1]->size == 4)
					printf("\tlw $t0, 0($t0)\n");
				else
					printf("\tlb $t0, 0($t0)\n");
			}else{
				if (s->ob[1]->size == 4)
					printf("\tlw $t0, ");
				else
					printf("\tlb $t0, ");
				printObject(s->ob[1]);
				printf("\n");
			}
			if (strcmp(s->op->name,"+") == 0){
				//nop
			}else if (strcmp(s->op->name,"-") == 0){
				printf("\tnegu $t0, $t0\n");
			}else if (strcmp(s->op->name,"~") == 0){
				printf("\tnot $t0, $t0\n");
			}else if (strcmp(s->op->name,"!") == 0){
				printf("\tseq $t0, $t0, 0\n");
			}else{
				//never
			}
		}
		printf("\tsw $t0, ");
		printObject(s->ob[0]);
		printf("\n");
	}else if (s->op->type == IRBINAOP){
		if (s->ob[1]->type == IRINTC){
			printf("\tli $t0, %d\n",s->ob[1]->data);
		}else if (s->ob[1]->pd == 1){
			printf("\tlw $t0, ");
			printObject(s->ob[1]);
			printf("\n");
			if (s->ob[1]->size == 4)
				printf("\tlw $t0, 0($t0)\n");
			else
				printf("\tlb $t0, 0($t0)\n");
		}else{
			if (s->ob[1]->size == 4)
				printf("\tlw $t0, ");
			else
				printf("\tlb $t0, ");
			printObject(s->ob[1]);
			printf("\n");
		}
		if (s->ob[2]->type == IRINTC){
			printf("\tli $t1, %d\n",s->ob[2]->data);
		}else if (s->ob[2]->pd == 1){
			printf("\tlw $t1, ");
			printObject(s->ob[2]);
			printf("\n");
			if (s->ob[2]->size == 4)
				printf("\tlw $t1, 0($t1)\n");
			else
				printf("\tlb $t1, 0($t1)\n");
		}else{
			if (s->ob[2]->size == 4)
				printf("\tlw $t1, ");
			else
				printf("\tlb $t1, ");
			printObject(s->ob[2]);
			printf("\n");
		}
		
		if (strcmp(s->op->name,"|") == 0){
			printf("\tor $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,"^") == 0){
			printf("\txor $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,"&") == 0){
			printf("\tand $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,"<") == 0){
			printf("\tslt $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,">") == 0){
			printf("\tsgt $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,"+") == 0){
			printf("\taddu $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,"-") == 0){
			printf("\tsubu $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,"*") == 0){
			printf("\tmul $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,"/") == 0){
			printf("\tdiv $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,"%") == 0){
			printf("\trem $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,"==") == 0){
			printf("\tseq $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,"!=") == 0){
			printf("\tsne $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,"<=") == 0){
			printf("\tsle $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,">=") == 0){
			printf("\tsge $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,"<<") == 0){
			printf("\tsll $t2, $t0, $t1\n");
		}else if (strcmp(s->op->name,">>") == 0){
			printf("\tsra $t2, $t0, $t1\n");
		}
		printf("\tsw $t2, ");
		printObject(s->ob[0]);
		printf("\n");
	}else if (s->op->type == IRARASOP){
		if (s->ob[0]->size == 1){
			if (s->ob[0]->pd == 1){
				printf("\tlw $t0, ");
				printObject(s->ob[0]);
				printf("\n");
			}else{
				printf("\tla $t0, ");
				printObject(s->ob[0]);
				printf("\n");
			}
			printf("\tla $t1, ");
			printObject(s->ob[1]);
			printf("\n");
			printf("\tsb $t1, 0($t0)\n");
		}else if (s->ob[0]->size == 4){
			if (s->ob[0]->pd == 1){
				printf("\tlw $t0, ");
				printObject(s->ob[0]);
				printf("\n");
			}else{
				printf("\tla $t0, ");
				printObject(s->ob[0]);
				printf("\n");
			}
			printf("\tla $t1, ");
			printObject(s->ob[1]);
			printf("\n");
			printf("\tsw $t1, 0($t0)\n");
		}else{
			//never
		}
	}else if (s->op->type == IRASSIOP){
		if (s->ob[0]->size == 1){
			if (s->ob[0]->pd == 1){
				printf("\tlw $t0, ");
				printObject(s->ob[0]);
				printf("\n");
			}else{
				printf("\tla $t0, ");
				printObject(s->ob[0]);
				printf("\n");
			}
			if (s->ob[1]->type == IRINTC){
				printf("\tli $t1, %d\n",s->ob[1]->data);
				printf("\tsb $t1, 0($t0)\n");
			}else if (s->ob[1]->pd == 2){
				if (s->ob[1]->size == 1)
					printf("\tlb $t1, ");
				else
					printf("\tlw $t1, ");
				printObject(s->ob[1]);
				printf("\n");
				printf("\tsb $t1, 0($t0)\n");
			}else if (s->ob[1]->pd == 1){
				printf("\tlw $t1, ");
				printObject(s->ob[1]);
				printf("\n");
				if (s->ob[1]->size == 1)
					printf("\tlb $t1, 0($t1)\n");
				else
					printf("\tlw $t1, 0($t1)\n");
				printf("\tsb $t1, 0($t0)\n");
			}else{
				printf("la $t1, ");
				printObject(s->ob[1]);
				printf("\n");
				printf("\tsb $t1, 0($t0)\n");
			}
		}else if (s->ob[0]->size == 4){
			if (s->ob[0]->pd == 1){
				printf("\tlw $t0, ");
				printObject(s->ob[0]);
				printf("\n");
			}else{
				printf("\tla $t0, ");
				printObject(s->ob[0]);
				printf("\n");
			}
			if (s->ob[1]->type == IRINTC){
				printf("\tli $t1, %d\n",s->ob[1]->data);
				printf("\tsw $t1, 0($t0)\n");
			}else if (s->ob[1]->pd == 2){
				if (s->ob[1]->size == 1)
					printf("\tlb $t1, ");
				else
					printf("\tlw $t1, ");
				printObject(s->ob[1]);
				printf("\n");
				printf("\tsw $t1, 0($t0)\n");
			}else if (s->ob[1]->pd == 1){
				printf("\tlw $t1, ");
				printObject(s->ob[1]);
				printf("\n");
				if (s->ob[1]->size == 1)
					printf("\tlb $t1, 0($t1)\n");
				else
					printf("\tlw $t1, 0($t1)\n");
				printf("\tsw $t1, 0($t0)\n");
			}else{
				printf("\tla $t1, ");
				printObject(s->ob[1]);
				printf("\n");
				printf("\tsw $t1, 0($t0)\n");
			}
		}else{
			int k;
			if (s->ob[0]->pd == 1)
				printf("\tlw $t0, ");
			else
				printf("\tla $t0, ");
			printObject(s->ob[0]);
			printf("\n");
			
			if (s->ob[1]->pd == 1)
				printf("\tlw $t1, ");
			else
				printf("\tla $t1, ");
			printObject(s->ob[1]);
			printf("\n");
			for (k = 0;k < s->ob[0]->size;k += 4){
				printf("\tlw $t2, %d($t1)\n",k);
				printf("\tsw $t2, %d($t0)\n",k);
			}
		}
	}else if (s->op->type == IRPARAOP){
		if (s->size == 1){
			if (s->ob[0]->type == IRINTC){
				printf("\tli $t0, %d\n",s->ob[0]->data);
				printf("\tsb $t0, %d($sp)\n",*cur);
			}else if (s->ob[0]->pd == 1){
				printf("\tlw $t0, ");
				printObject(s->ob[0]);
				printf("\n");
				printf("\tlb $t0, 0($t0)\n");
				printf("\tsb $t0, %d($sp)\n",*cur);
			}else if (s->ob[0]->pd == 2){
				printf("\tlb $t0, ");
				printObject(s->ob[0]);
				printf("\n");
				printf("\tsb $t0, %d($sp)\n",*cur);
			}else{
			
			}
			*cur += 4;
		}else if (s->size == 4){
			if (s->ob[0]->type == IRINTC){
				printf("\tli $t0, %d\n",s->ob[0]->data);
				printf("\tsw $t0, %d($sp)\n",*cur);
			}else if (s->ob[0]->pd == 1){
				printf("\tlw $t0, ");
				printObject(s->ob[0]);
				printf("\n");
				printf("\tlw $t0, 0($t0)\n");
				printf("\tsw $t0, %d($sp)\n",*cur);
			}else{
				printf("\tlw $t0, ");
				printObject(s->ob[0]);
				printf("\n");
				printf("\tsw $t0, %d($sp)\n",*cur);
			}
			*cur += 4;
		}else{
			if (s->ob[0]->pd == 2)
				printf("\tla $t0, ");
			else
				printf("\tlw $t0, ");
			printObject(s->ob[0]);
			printf("\n");
			for (i = 0;i < s->size;i += 4){
				printf("\tlw $t1, %d($t0)\n",i);
				printf("\tsw $t1, %d($sp)\n",*cur);
				*cur += 4;
			}
		}
	}else if (s->op->type == IRCALLOP){
		*cur = 0;
		printf("\tjal _%s\n",funcList->e[s->ob[s->num - 2]->data]->name);
		if (s->num > 2){
			printf("\tla $t0, ");
			printObject(s->ob[0]);
			printf("\n");
			printf("\tla $t1, 0($sp)\n");
			printf("\tsw $t1, 0($t0)\n");
		}
	}else if (s->op->type == IRLABLOP){
		printf("label%d:\n",s->ob[0]->data);
	}else if (s->op->type == IRGOTOOP){
		printf("\tj label%d\n",s->ob[0]->data);
	}else if (s->op->type == IRITGTOP){
		if (s->ob[0]->type == IRINTC){
			printf("\tli $t0, %d\n",s->ob[0]->data);
		}else if (s->ob[0]->pd == 2){
			if (s->ob[0]->size == 4)
				printf("\tlw $t0, ");
			else
				printf("\tlb $t0, ");
			printObject(s->ob[0]);
			printf("\n");
		}else{
			printf("\tlw $t0, ");
			printObject(s->ob[0]);
			printf("\n");
			if (s->ob[0]->size == 4)
				printf("\tlw $t0, 0($t0)\n");
			else
				printf("\tlb $t0, 0($t0)\n");
		}
		printf("\tbne $t0, 0, label%d\n",s->ob[1]->data);
	}else if (s->op->type == IRIFGTOP){
		if (s->ob[0]->type == IRINTC){
			printf("\tli $t0, %d\n",s->ob[0]->data);
		}else if (s->ob[0]->pd == 2){
			if (s->ob[0]->size == 4)
				printf("\tlw $t0, ");
			else
				printf("\tlb $t0, ");
			printObject(s->ob[0]);
			printf("\n");
		}else{
			printf("\tlw $t0, ");
			printObject(s->ob[0]);
			printf("\n");
			if (s->ob[0]->size == 4)
				printf("\tlw $t0, 0($t0)\n");
			else
				printf("\tlb $t0, 0($t0)\n");
		}
		printf("\tbeq $t0, 0, label%d\n",s->ob[1]->data);
	}else if (s->op->type == IRARRROP){
		if (s->ob[1]->pd == 2){
			printf("\tla $t0, ");
			printObject(s->ob[1]);
			printf("\n");
		}else{
			printf("\tlw $t0, ");
			printObject(s->ob[1]);
			printf("\n");
		}
		
		if (s->ob[2]->type == IRINTC){
			printf("\tli $t1, %d\n",s->ob[2]->data);
		}else if (s->ob[2]->pd == 2){
			printf("\tlw $t1, ");
			printObject(s->ob[2]);
			printf("\n");
		}else{
			printf("nizaidouwo\n");
		}
		
		printf("\taddu $t1, $t0, $t1\n");
		printf("\tsw $t1, ");
		printObject(s->ob[0]);
		printf("\n");
	}else if (s->op->type == IRARRWOP){
		//never
	}else if (s->op->type == IRPTRROP){
		if (s->ob[1]->pd == 2){
			printf("\tlw $t0, ");
			printObject(s->ob[1]);
			printf("\n");
		}else{
			printf("\tlw $t0, ");
			printObject(s->ob[1]);
			printf("\n");
			printf("\tlw $t0, 0($t0)\n");
		}
		
		if (s->ob[2]->type == IRINTC){
			printf("\tli $t1, %d\n",s->ob[2]->data);
		}else if (s->ob[2]->pd == 2){
			printf("\tlw $t1, ");
			printObject(s->ob[2]);
			printf("\n");
		}else{
			printf("nizaidouwo\n");
		}
		
		printf("\taddu $t1, $t0, $t1\n");
		printf("\tsw $t1, ");
		printObject(s->ob[0]);
		printf("\n");
	}else if (s->op->type == IRPTRWOP){
		//never
	}else if (s->op->type == IRRTSZOP){
		*cur = make4(s->ob[0]->data);
	}else if (s->op->type == IRRETNOP){
		if (s->num){
			if (s->ob[0]->type == IRINTC){
				printf("\tli $v0, %d\n",s->ob[0]->data);
				printf("\tsw $v0, ");
				printObject(registers->e[func->para->link[0]]);
				printf("\n");
			}else if (s->ob[0]->size == 4){
				if (s->ob[0]->pd == 2){
					printf("\tlw $v0, ");
					printObject(s->ob[0]);
					printf("\n");
				}else{
					printf("\tlw $v0, ");
					printObject(s->ob[0]);
					printf("\n");
					printf("\tlw $v0, 0($v0)\n");
				}
				printf("\tsw $v0, ");
				printObject(registers->e[func->para->link[0]]);
				printf("\n");
			}else if (s->ob[0]->size == 1){
				if (s->ob[0]->pd == 2){
					printf("\tlb $v0, ");
					printObject(s->ob[0]);
					printf("\n");
				}else{
					printf("\tlw $v0, ");
					printObject(s->ob[0]);
					printf("\n");
					printf("\tlb $v0, 0($v0)\n");
				}
				printf("\tsb $v0, ");
				printObject(registers->e[func->para->link[0]]);
				printf("\n");
			}else{
				int k;
				if (s->ob[0]->pd == 2)
					printf("\tla $t0, ");
				else
					printf("\tlw $t0, ");
				printObject(s->ob[0]);
				printf("\n");
				printf("\tla $v0, ");
				printObject(registers->e[func->para->link[0]]);
				printf("\n");
				for (k = 0;k < s->ob[0]->size;k += 4){
					printf("\tlw $t1, %d($t0)\n",k);
					printf("\tsw $t1, %d($v0)\n",k);
				}
			}
		}
		printf("\tj __end__%s\n",func->name);
	}else if (s->op->type == IRLGASOP){
		printf("\tla $t0, ");
		printObject(s->ob[0]);
		printf("\n");
		if (s->ob[1]->type == IRINTC){
			printf("\tli $t1, %d\n",s->ob[1]->data != 0);
			printf("\tsw $t1, 0($t0)\n");
		}else if (s->ob[1]->pd == 2){
			if (s->ob[1]->size == 4)
				printf("\tlw $t1, ");
			else
				printf("\tlb $t1, ");
			printObject(s->ob[1]);
			printf("\n");
			printf("\tsne $t1, $t1, 0\n");
			printf("\tsw $t1, 0($t0)\n");
		}else{
			printf("\tlw $t1, ");
			printObject(s->ob[1]);
			printf("\n");
			if (s->ob[1]->size == 4)
				printf("\tlw $t1, 0($t1)\n");
			else
				printf("\tlb $t1, 0($t1)\n");
			printf("\tsne $t1, $t1, 0\n");
			printf("\tsw $t1, 0($t0)\n");
		}
	}else if (s->op->type == IRASSCOP){
		printf("\tla $t0, ");
		printObject(s->ob[0]);
		printf("\n");
		printf("\tla $t1, __s%d\n",s->ob[1]->data);
		printf("\tsw $t1, 0($t0)\n");
	}else if (s->op->type == IRINAROP){
		printf("\tlw $t0, ");
		printObject(s->ob[0]);
		printf("\n");
		if (s->ob[2]->type == IRINTC)
			printf("\tli $t1, %d\n",s->ob[2]->data);
		else{
			printf("\tlw $t1, ");
			printObject(s->ob[2]);
			printf("\n");
		}
		if (s->size == 1)
			printf("\tsb $t1, %d($t0)\n",s->ob[1]->data);
		else
			printf("\tsw $t1, %d($t0)\n",s->ob[1]->data);
	}else{
		//never
	}
}
static void printFunc(struct Function *func){
	int i,cur = 0;
	struct SentenceList *l = func->body;
	if (strcmp(func->name,"main") == 0)
		printf("%s:\n",func->name);
	else
		printf("_%s:\n",func->name);
	printf("\taddu $sp, $sp, -%d\n",func->mainSpace);
	printf("\tsw $ra, %d($sp)\n",func->retnStat);
	
	if (strcmp(func->name,"main") == 0){
		struct SentenceList *l = funcList->e[0]->body;
		for (i = 0;i < l->num;++i) printSentence(l->e[i],&cur,func);
	}
	
	for (i = 0;i < l->num;++i){
		printSentence(l->e[i],&cur,func);
	}
	printf("__end__%s:\n",func->name);
	printf("\tlw $ra, %d($sp)\n",func->retnStat);
	printf("\taddu $sp, $sp, %d\n",func->mainSpace);
	if (strcmp(func->name,"main") == 0){
		printf("\tli $v0, 10\n");
		printf("\tsyscall\n");
	}else{
		printf("\tj $ra\n");
	}
}
static void printPrintf(){
	char *a[3];
	int f[3],i,j,t;
	printf("_printf:\n");
	printf("\tla $a1, 4($sp)\n");
	printf("\tlw $a2, 4($sp)\n");
//	printf("\tj _printf_loop\n");
	
	printf("_printf_loop:\n");
	printf("\tlb $a0, 0($a2)\n");
	printf("\tbeq $a0, 0, _printf_end\n");
	printf("\taddu $a2, $a2, 1\n");
	printf("\tbeq $a0, '%%', _printf_fmt\n");
	printf("\tli $v0, 11\n");
	printf("\tsyscall\n");
	printf("\tj _printf_loop\n");
	
	printf("_printf_fmt:\n");
	printf("\tlb $a0, 0($a2)\n");
	printf("\taddu $a2, $a2, 1\n");
	
	a[0] = "\tbeq $a0, 'c', _printf_char\n";
	a[1] = "\tbeq $a0, 'd', _printf_int\n";
	a[2] = "\tbeq $a0, 's', _printf_str\n";
	f[0] = 0;
	f[1] = 1;
	f[2] = 2;
	for (i = 0;i < 2;++i)
		for (j = i + 1;j < 3;++j)
			if (numOfFmt[f[i]] < numOfFmt[f[j]]){
				t = f[i];
				f[i] = f[j];
				f[j] = t;
			}
	if (numOfFmt[f[0]]){
		if (numOfFmt[f[1]] || numOfFmt[f[2]] || numOfFmt[3])
			printf("%s",a[f[0]]);
		else{
			//nop;
		}
	}
	if (numOfFmt[f[1]])
		printf("%s",a[f[1]]);
	if (numOfFmt[f[2]])
		printf("%s",a[f[2]]);
	
	if (numOfFmt[3]){
		printf("_printf_width:\n");
		printf("\taddu $a1, $a1, 4\n");
		printf("\tlb $t0, 0($a2)\n");
		printf("\tsubu $t0, $t0, '0'\n");
		printf("\taddu $a2, $a2, 2\n");
		printf("\tlw $t1, 0($a1)\n");
		printf("\tli $t2, 1\n");
		printf("\tblt $t0, 2, _printf_width_end\n");
		printf("_label_width_1:\n");
		printf("\tsubu $t0, $t0, 1\n");
		printf("\tmul $t2, $t2, 10\n");
		printf("\tbgt $t0, 1, _label_width_1\n");
		printf("\tli $a0, 0\n");
		printf("\tli $v0, 1\n");
		printf("_label_width_2:\n");
		printf("\tbge $t1, $t2, _printf_width_end\n");
		printf("\tsyscall\n");
		printf("\tdiv $t2, $t2, 10\n");
		printf("\tj _label_width_2\n");
		
		printf("_printf_width_end:\n");
		printf("\tlw $a0, 0($a1)\n");
		printf("\tli $v0, 1\n");
		printf("\tsyscall\n");
		printf("\tj _printf_loop\n");
	}
	if (numOfFmt[0]){
		printf("_printf_char:\n");
		printf("\taddu $a1, $a1, 4\n");
		printf("\tlb $a0, 0($a1)\n");
		printf("\tli $v0, 11\n");
		printf("\tsyscall\n");
		printf("\tj _printf_loop\n");
	}
	
	if (numOfFmt[1]){
		printf("_printf_int:\n");
		printf("\taddu $a1, $a1, 4\n");
		printf("\tlw $a0, 0($a1)\n");
		printf("\tli $v0, 1\n");
		printf("\tsyscall\n");
		printf("\tj _printf_loop\n");
	}
	
	if (numOfFmt[2]){
		printf("_printf_str:\n");
		printf("\taddu $a1, $a1, 4\n");
		printf("\tlw $a0, 0($a1)\n");
		printf("\tli $v0, 4\n");
		printf("\tsyscall\n");
		printf("\tj _printf_loop\n");
	}
	
	printf("_printf_end:\n");
	printf("\tj $ra\n");
	
	
}
static void printMalloc(){
	printf("_malloc:\n");
	printf("\tli $v0, 9\n");
	printf("\tlw $a0, 4($sp)\n");
	printf("\tsyscall\n");
	printf("\tsw $v0, 0($sp)\n");
	printf("\tj $ra\n");
}
static void printGetchar(){
	printf("_getchar:\n");
	printf("\tli $v0, 12\n");
	printf("\tsyscall\n");
	printf("\tsw $v0, 0($sp)\n");
	printf("\tj $ra\n");
}
int main(void){
	int i;
	initArraBegin = 0;
	ir();
	printGlobal(funcList->e[0]);
	for (i = 4;i < funcList->num;++i) printFunc(funcList->e[i]);
	printPrintf();
	printMalloc();
	printGetchar();
	freeFunctionList(funcList);
	freeRegisterList(registers);
	freeStringList(string);
	return 0;
}
