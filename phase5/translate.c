#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "translate.h"
#include "ir.h"
static int initArraBegin;
static char t[100],buffer[100],t0[100],t1[100]/*,t2[100]*/;


static char mips[100010][100];
static int senLen[100010];
static int numOfLines,ptrOfBuffer;

static void pushBuffer(void){
	int n = strlen(t);
	sprintf(buffer + ptrOfBuffer,"%s",t);
	ptrOfBuffer += n;
}
static void pushLine(void){
	++numOfLines;
	sprintf(mips[numOfLines],"%s",buffer);
	ptrOfBuffer = 0;
}
static void printMips(void){
	int i;
	for (i = 1;i <= numOfLines;++i) printf("%s",mips[i]);
}

static int make4(int x){
	int t = x;
	if (t & 3) t = ((t >> 2) + 1) << 2;
	return t;
}
static void printGlobal(struct Function *func){
	int i,j;
	sprintf(buffer,"\t.data\n");
	pushLine();
	for (i = 1;i <= registerNum;++i)
		if (registers->e[i]->data < 0){
			sprintf(buffer,"%s:\t.space %d\n",registers->e[i]->name,make4(registers->e[i]->size));
			pushLine();
		}
	for (i = 0;i < string->num;++i){
		struct String *s = string->e[i];
		int n;
		n = strlen(s->s);
		sprintf(buffer,"__s%d:\n",i);
		pushLine();
		for (j = 0;j < n;++j){
			sprintf(buffer,"\t.byte %d\n",s->s[j]);
			pushLine();
		}
		for (j = n;j < s->size;++j){
			sprintf(buffer,"\t.byte 0\n");
			pushLine();
		}
	}
	sprintf(buffer,"\t.text\n");
	pushLine();
}
static void printObject(struct Object *o){
	if (o->type == IRSTRC){
		//nop
	}else if (o->type == IRINTC){
		sprintf(t,"%d",o->data);
		pushBuffer();
	}else if (o->type == IRTEMP){
		if (o->data < 0){
			sprintf(t,"%s",o->name);
			pushBuffer();
		}else{
			sprintf(t,"%d($sp)",o->data);
			pushBuffer();
		}
	}else{
		//never
	}
}

static void sPrintObject(char *s,struct Object *o){
	if (o->type == IRSTRC){
		//nop
	}else if (o->type == IRINTC){
		sprintf(s,"%d",o->data);
	}else if (o->type == IRTEMP){
		if (o->data < 0)
			sprintf(s,"%s",o->name);
		else
			sprintf(s,"%d($sp)",o->data);
	}else{
		//never
	}
}
static void printSentence(struct Sentence *s,int *cur,struct Function *func){
	int i;
	if (s->op->type == IRUNAROP){
		if (strcmp(s->op->name,"&") == 0){
			if (s->ob[1]->pd == 2){
				sprintf(t,"\tla $t0, ");pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}else{
				sprintf(t,"\tlw $t0, ");pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}
		}else if (strcmp(s->op->name,"*") == 0){
			if (s->ob[1]->pd == 1){
				sprintf(t,"\tlw $t0, ");pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}else{
				sprintf(t,"\tla $t0, ");pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}
			sprintf(buffer,"\tlw $t0, 0($t0)\n");
			pushLine();
		}else{
			sprintf(t0,"$t0");
			if (s->ob[1]->type == IRINTC){
				if (s->ob[1]->data == 0){
					sprintf(t0,"$0");
				}else{
					sprintf(buffer,"\tli $t0, %d\n",s->ob[1]->data);
					pushLine();
				}
			}else if (s->ob[1]->pd == 1){
				sprintf(t,"\tlw $t0, ");pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				if (s->ob[1]->size == 4){
					sprintf(buffer,"\tlw $t0, 0($t0)\n");
					pushLine();
				}else{
					sprintf(buffer,"\tlb $t0, 0($t0)\n");
					pushLine();
				}
			}else{
				if (s->ob[1]->size == 4)
					sprintf(t,"\tlw $t0, ");
				else
					sprintf(t,"\tlb $t0, ");
				pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}
			if (strcmp(s->op->name,"+") == 0){
				//nop
			}else if (strcmp(s->op->name,"-") == 0){
				sprintf(buffer,"\tnegu $t0, %s\n",t0);
				pushLine();
			}else if (strcmp(s->op->name,"~") == 0){
				sprintf(buffer,"\tnot $t0, %s\n",t0);
				pushLine();
			}else if (strcmp(s->op->name,"!") == 0){
				sprintf(buffer,"\tseq $t0, %s, 0\n",t0);
				pushLine();
			}else{
				//never
			}
		}
		sprintf(t,"\tsw $t0, ");pushBuffer();
		printObject(s->ob[0]);
		sprintf(t,"\n");pushBuffer();
		pushLine();
	}else if (s->op->type == IRBINAOP){
		sprintf(t0,"$t0");
		if (s->ob[1]->type == IRINTC){
			if (s->ob[1]->data == 0){
				sprintf(t0,"$0");
			}else{
				sprintf(buffer,"\tli $t0, %d\n",s->ob[1]->data);
				pushLine();
			}
		}else if (s->ob[1]->pd == 1){
			sprintf(t,"\tlw $t0, ");pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			if (s->ob[1]->size == 4){
				sprintf(buffer,"\tlw $t0, 0($t0)\n");
				pushLine();
			}else{
				sprintf(buffer,"\tlb $t0, 0($t0)\n");
				pushLine();
			}
		}else{
			if (s->ob[1]->size == 4)
				sprintf(t,"\tlw $t0, ");
			else
				sprintf(t,"\tlb $t0, ");
			pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}
		sprintf(t1,"$t1");
		if (s->ob[2]->type == IRINTC){
//			printf("\tli $t1, %d\n",s->ob[2]->data);
			sprintf(t1,"%d",s->ob[2]->data);
		}else if (s->ob[2]->pd == 1){
			sprintf(t,"\tlw $t1, ");pushBuffer();
			printObject(s->ob[2]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			if (s->ob[2]->size == 4)
				sprintf(buffer,"\tlw $t1, 0($t1)\n");
			else
				sprintf(buffer,"\tlb $t1, 0($t1)\n");
			pushLine();
		}else{
			if (s->ob[2]->size == 4)
				sprintf(t,"\tlw $t1, ");
			else
				sprintf(t,"\tlb $t1, ");
			pushBuffer();
			printObject(s->ob[2]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}
		
		if (strcmp(s->op->name,"|") == 0){
			sprintf(buffer,"\tor $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,"^") == 0){
			sprintf(buffer,"\txor $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,"&") == 0){
			sprintf(buffer,"\tand $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,"<") == 0){
			sprintf(buffer,"\tslt $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,">") == 0){
			sprintf(buffer,"\tsgt $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,"+") == 0){
			sprintf(buffer,"\taddu $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,"-") == 0){
			sprintf(buffer,"\tsubu $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,"*") == 0){
			sprintf(buffer,"\tmul $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,"/") == 0){
			sprintf(buffer,"\tdiv $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,"%") == 0){
			sprintf(buffer,"\trem $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,"==") == 0){
			sprintf(buffer,"\tseq $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,"!=") == 0){
			sprintf(buffer,"\tsne $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,"<=") == 0){
			sprintf(buffer,"\tsle $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,">=") == 0){
			sprintf(buffer,"\tsge $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,"<<") == 0){
			sprintf(buffer,"\tsll $t2, %s, %s\n",t0,t1);
		}else if (strcmp(s->op->name,">>") == 0){
			sprintf(buffer,"\tsra $t2, %s, %s\n",t0,t1);
		}
		pushLine();
		sprintf(t,"\tsw $t2, ");pushBuffer();
		printObject(s->ob[0]);
		sprintf(t,"\n");pushBuffer();
		pushLine();
	}else if (s->op->type == IRARASOP){
		if (s->ob[0]->size == 1){
			if (s->ob[0]->pd == 1){
				sprintf(t,"\tlw $t1, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}else{
//				printf("\tla $t1, ");
//				printObject(s->ob[0]);
//				printf("\n");
				sprintf(t,"\tla $t0, ");pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(t,"\tsb $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				return;
			}
			sprintf(t,"\tla $t0, ");pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			sprintf(buffer,"\tsb $t0, 0($t1)\n");
			pushLine();
		}else if (s->ob[0]->size == 4){
			if (s->ob[0]->pd == 1){
				sprintf(t,"\tlw $t1, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}else{
//				printf("\tla $t1, ");
//				printObject(s->ob[0]);
//				printf("\n");
				sprintf(t,"\tla $t0, ");pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(t,"\tsw $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				return;
			}
			sprintf(t,"\tla $t0, ");pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			sprintf(buffer,"\tsw $t0, 0($t1)\n");
			pushLine();
		}else{
			//never
		}
	}else if (s->op->type == IRASSIOP){
		if (s->ob[0]->size == 1){
			sprintf(t0,"0($t0)");
			if (s->ob[0]->pd == 1){
				sprintf(t,"\tlw $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}else{
//				printf("\tla $t0, ");
//				printObject(s->ob[0]);
//				printf("\n");
				sPrintObject(t0,s->ob[0]);
			}
			if (s->ob[1]->type == IRINTC){
				sprintf(t1,"$t1");
				if (s->ob[1]->data == 0){
					sprintf(t1,"$0");
				}else{
					sprintf(buffer,"\tli $t1, %d\n",s->ob[1]->data);
					pushLine();
				}
				sprintf(buffer,"\tsb %s, %s\n",t1,t0);
				pushLine();
			}else if (s->ob[1]->pd == 2){
				if (s->ob[1]->size == 1)
					sprintf(t,"\tlb $t1, ");
				else
					sprintf(t,"\tlw $t1, ");
				pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(buffer,"\tsb $t1, %s\n",t0);
				pushLine();
			}else if (s->ob[1]->pd == 1){
				sprintf(t,"\tlw $t1, ");pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				if (s->ob[1]->size == 1)
					sprintf(buffer,"\tlb $t1, 0($t1)\n");
				else
					sprintf(buffer,"\tlw $t1, 0($t1)\n");
				pushLine();
				sprintf(buffer,"\tsb $t1, %s\n",t0);
				pushLine();
			}else{
				sprintf(t,"la $t1, ");pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(buffer,"\tsb $t1, %s\n",t0);
				pushLine();
			}
		}else if (s->ob[0]->size == 4){
			sprintf(t0,"0($t0)");
			if (s->ob[0]->pd == 1){
				sprintf(t,"\tlw $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}else{
//				printf("\tla $t0, ");
//				printObject(s->ob[0]);
//				printf("\n");
				sPrintObject(t0,s->ob[0]);
			}
			if (s->ob[1]->type == IRINTC){
				sprintf(t1,"$t1");
				if (s->ob[1]->data == 0){
					sprintf(t1,"$0");
				}else{
					sprintf(buffer,"\tli $t1, %d\n",s->ob[1]->data);
					pushLine();
				}
				sprintf(buffer,"\tsw %s, %s\n",t1,t0);
				pushLine();
			}else if (s->ob[1]->pd == 2){
				if (s->ob[1]->size == 1)
					sprintf(t,"\tlb $t1, ");
				else
					sprintf(t,"\tlw $t1, ");
				pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(buffer,"\tsw $t1, %s\n",t0);
				pushLine();
			}else if (s->ob[1]->pd == 1){
				sprintf(t,"\tlw $t1, ");pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				if (s->ob[1]->size == 1)
					sprintf(buffer,"\tlb $t1, 0($t1)\n");
				else
					sprintf(buffer,"\tlw $t1, 0($t1)\n");
				pushLine();
				sprintf(buffer,"\tsw $t1, %s\n",t0);
				pushLine();
			}else{
				sprintf(t,"\tla $t1, ");pushBuffer();
				printObject(s->ob[1]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(buffer,"\tsw $t1, %s\n",t0);
				pushLine();
			}
		}else{
			int k;
			if (s->ob[0]->pd == 1){
				sprintf(t,"\tlw $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}else{
				sprintf(t,"\tla $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}
			
			if (s->ob[1]->pd == 1)
				sprintf(t,"\tlw $t1, ");
			else
				sprintf(t,"\tla $t1, ");
			pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			for (k = 0;k < s->ob[0]->size;k += 4){
				sprintf(buffer,"\tlw $t2, %d($t1)\n",k);
				pushLine();
				sprintf(buffer,"\tsw $t2, %d($t0)\n",k);
				pushLine();
			}
		}
	}else if (s->op->type == IRPARAOP){
		if (s->size == 1){
			if (s->ob[0]->type == IRINTC){
				sprintf(buffer,"\tli $t0, %d\n",s->ob[0]->data);
				pushLine();
				sprintf(buffer,"\tsb $t0, %d($sp)\n",*cur);
				pushLine();
			}else if (s->ob[0]->pd == 1){
				sprintf(t,"\tlw $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(buffer,"\tlb $t0, 0($t0)\n");
				pushLine();
				sprintf(buffer,"\tsb $t0, %d($sp)\n",*cur);
				pushLine();
			}else if (s->ob[0]->pd == 2){
				sprintf(t,"\tlb $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(buffer,"\tsb $t0, %d($sp)\n",*cur);
				pushLine();
			}else{
			
			}
			*cur += 4;
		}else if (s->size == 4){
			if (s->ob[0]->type == IRINTC){
				sprintf(buffer,"\tli $t0, %d\n",s->ob[0]->data);
				pushLine();
				sprintf(buffer,"\tsw $t0, %d($sp)\n",*cur);
				pushLine();
			}else if (s->ob[0]->pd == 1){
				sprintf(t,"\tlw $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(buffer,"\tlw $t0, 0($t0)\n");
				pushLine();
				sprintf(buffer,"\tsw $t0, %d($sp)\n",*cur);
				pushLine();
			}else{
				sprintf(t,"\tlw $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(buffer,"\tsw $t0, %d($sp)\n",*cur);
				pushLine();
			}
			*cur += 4;
		}else{
			if (s->ob[0]->pd == 2)
				sprintf(t,"\tla $t0, ");
			else
				sprintf(t,"\tlw $t0, ");
			pushBuffer();
			printObject(s->ob[0]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			for (i = 0;i < s->size;i += 4){
				sprintf(buffer,"\tlw $t1, %d($t0)\n",i);
				pushLine();
				sprintf(buffer,"\tsw $t1, %d($sp)\n",*cur);
				pushLine();
				*cur += 4;
			}
		}
	}else if (s->op->type == IRCALLOP){
		*cur = 0;
		sprintf(buffer,"\tjal _%s\n",funcList->e[s->ob[s->num - 2]->data]->name);
		pushLine();
		if (s->num > 2){
//			printf("\tla $t0, ");
//			printObject(s->ob[0]);
//			printf("\n");
			sPrintObject(t0,s->ob[0]);
			
			if (s->ob[0]->size <= 4 && s->ob[0]->pd == 2){
				if (s->ob[0]->size == 4)
					sprintf(buffer,"\tsw $v0, %s\n",t0);
				else
					sprintf(buffer,"\tsb $v0, %s\n",t0);
				pushLine();
			}else{
				sprintf(buffer,"\tla $t1, 0($sp)\n");
				pushLine();
				sprintf(buffer,"\tsw $t1, %s\n",t0);
				pushLine();
			}
		}
	}else if (s->op->type == IRLABLOP){
		sprintf(buffer,"label%d:\n",s->ob[0]->data);
		pushLine();
	}else if (s->op->type == IRGOTOOP){
		sprintf(buffer,"\tj label%d\n",s->ob[0]->data);
		pushLine();
	}else if (s->op->type == IRITGTOP){
		if (s->ob[0]->type == IRINTC){
			sprintf(buffer,"\tli $t0, %d\n",s->ob[0]->data);
			pushLine();
		}else if (s->ob[0]->pd == 2){
			if (s->ob[0]->size == 4)
				sprintf(t,"\tlw $t0, ");
			else
				sprintf(t,"\tlb $t0, ");
			pushBuffer();
			printObject(s->ob[0]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}else{
			sprintf(t,"\tlw $t0, ");pushBuffer();
			printObject(s->ob[0]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			if (s->ob[0]->size == 4)
				sprintf(buffer,"\tlw $t0, 0($t0)\n");
			else
				sprintf(buffer,"\tlb $t0, 0($t0)\n");
			pushLine();
		}
		sprintf(buffer,"\tbne $t0, 0, label%d\n",s->ob[1]->data);
		pushLine();
	}else if (s->op->type == IRIFGTOP){
		if (s->ob[0]->type == IRINTC){
			sprintf(buffer,"\tli $t0, %d\n",s->ob[0]->data);
			pushLine();
		}else if (s->ob[0]->pd == 2){
			if (s->ob[0]->size == 4)
				sprintf(t,"\tlw $t0, ");
			else
				sprintf(t,"\tlb $t0, ");
			pushBuffer();
			printObject(s->ob[0]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}else{
			sprintf(t,"\tlw $t0, ");pushBuffer();
			printObject(s->ob[0]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			if (s->ob[0]->size == 4)
				sprintf(buffer,"\tlw $t0, 0($t0)\n");
			else
				sprintf(buffer,"\tlb $t0, 0($t0)\n");
			pushLine();
		}
		sprintf(buffer,"\tbeq $t0, 0, label%d\n",s->ob[1]->data);
		pushLine();
	}else if (s->op->type == IRARRROP){
		if (s->ob[1]->pd == 2){
			sprintf(t,"\tla $t0, ");pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}else{
			sprintf(t,"\tlw $t0, ");pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}
		
		if (s->ob[2]->type == IRINTC){
			sprintf(buffer,"\tli $t1, %d\n",s->ob[2]->data);
			pushLine();
		}else if (s->ob[2]->pd == 2){
			sprintf(t,"\tlw $t1, ");pushBuffer();
			printObject(s->ob[2]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}else{
//			printf("nizaidouwo\n");
		}
		
		sprintf(buffer,"\taddu $t1, $t0, $t1\n");
		pushLine();
		sprintf(t,"\tsw $t1, ");pushBuffer();
		printObject(s->ob[0]);
		sprintf(t,"\n");pushBuffer();
		pushLine();
	}else if (s->op->type == IRARRWOP){
		//never
	}else if (s->op->type == IRPTRROP){
		if (s->ob[1]->pd == 2){
			sprintf(t,"\tlw $t0, ");pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}else{
			sprintf(t,"\tlw $t0, ");pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			sprintf(buffer,"\tlw $t0, 0($t0)\n");
			pushLine();
		}
		
		if (s->ob[2]->type == IRINTC){
			sprintf(buffer,"\tli $t1, %d\n",s->ob[2]->data);
			pushLine();
		}else if (s->ob[2]->pd == 2){
			sprintf(t,"\tlw $t1, ");pushBuffer();
			printObject(s->ob[2]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}else{
//			printf("nizaidouwo\n");
		}
		
		sprintf(buffer,"\taddu $t1, $t0, $t1\n");
		pushLine();
		sprintf(t,"\tsw $t1, ");pushBuffer();
		printObject(s->ob[0]);
		sprintf(t,"\n");pushBuffer();
		pushLine();
	}else if (s->op->type == IRPTRWOP){
		//never
	}else if (s->op->type == IRRTSZOP){
		*cur = make4(s->ob[0]->data);
	}else if (s->op->type == IRRETNOP){
		if (s->num){
			if (s->ob[0]->type == IRINTC){
				sprintf(buffer,"\tli $v0, %d\n",s->ob[0]->data);
				pushLine();
//				printf("\tsw $v0, ");
//				printObject(registers->e[func->para->link[0]]);
//				printf("\n");
			}else if (s->ob[0]->size == 4){
				if (s->ob[0]->pd == 2){
					sprintf(t,"\tlw $v0, ");pushBuffer();
					printObject(s->ob[0]);
					sprintf(t,"\n");pushBuffer();
					pushLine();
				}else{
					sprintf(t,"\tlw $v0, ");pushBuffer();
					printObject(s->ob[0]);
					sprintf(t,"\n");pushBuffer();
					pushLine();
					sprintf(buffer,"\tlw $v0, 0($v0)\n");
					pushLine();
				}
//				printf("\tsw $v0, ");
//				printObject(registers->e[func->para->link[0]]);
//				printf("\n");
			}else if (s->ob[0]->size == 1){
				if (s->ob[0]->pd == 2){
					sprintf(t,"\tlb $v0, ");pushBuffer();
					printObject(s->ob[0]);
					sprintf(t,"\n");pushBuffer();
					pushLine();
				}else{
					sprintf(t,"\tlw $v0, ");pushBuffer();
					printObject(s->ob[0]);
					sprintf(t,"\n");pushBuffer();
					pushLine();
					sprintf(buffer,"\tlb $v0, 0($v0)\n");
					pushLine();
				}
//				printf("\tsb $v0, ");
//				printObject(registers->e[func->para->link[0]]);
//				printf("\n");
			}else{
				int k;
				if (s->ob[0]->pd == 2)
					sprintf(t,"\tla $t0, ");
				else
					sprintf(t,"\tlw $t0, ");
				pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(t,"\tla $v0, ");pushBuffer();
				printObject(registers->e[func->para->link[0]]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				for (k = 0;k < s->ob[0]->size;k += 4){
					sprintf(buffer,"\tlw $t1, %d($t0)\n",k);
					pushLine();
					sprintf(buffer,"\tsw $t1, %d($v0)\n",k);
					pushLine();
				}
			}
		}
		sprintf(buffer,"\tj __end__%s\n",func->name);
		pushLine();
	}else if (s->op->type == IRLGASOP){
		sPrintObject(t0,s->ob[0]);
//		printf("\tla $t0, ");
//		printObject(s->ob[0]);
//		printf("\n");
		if (s->ob[1]->type == IRINTC){
			sprintf(buffer,"\tli $t1, %d\n",s->ob[1]->data != 0);
			pushLine();
			sprintf(buffer,"\tsw $t1, %s\n",t0);
			pushLine();
		}else if (s->ob[1]->pd == 2){
			if (s->ob[1]->size == 4)
				sprintf(t,"\tlw $t1, ");
			else
				sprintf(t,"\tlb $t1, ");
			pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			sprintf(buffer,"\tsne $t1, $t1, 0\n");
			pushLine();
			sprintf(buffer,"\tsw $t1, %s\n",t0);
			pushLine();
		}else{
			sprintf(t,"\tlw $t1, ");pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			if (s->ob[1]->size == 4)
				sprintf(buffer,"\tlw $t1, 0($t1)\n");
			else
				sprintf(buffer,"\tlb $t1, 0($t1)\n");
			pushLine();
			sprintf(buffer,"\tsne $t1, $t1, 0\n");
			pushLine();
			sprintf(buffer,"\tsw $t1, %s\n",t0);
			pushLine();
		}
	}else if (s->op->type == IRASSCOP){
//		printf("\tla $t0, ");
//		printObject(s->ob[0]);
//		printf("\n");
		sPrintObject(t0,s->ob[0]);
		sprintf(buffer,"\tla $t1, __s%d\n",s->ob[1]->data);
		pushLine();
		sprintf(buffer,"\tsw $t1, %s\n",t0);
		pushLine();
	}else if (s->op->type == IRINAROP){
		sprintf(t,"\tlw $t0, ");pushBuffer();
		printObject(s->ob[0]);
		sprintf(t,"\n");pushBuffer();
		pushLine();
		if (s->ob[2]->type == IRINTC){
			sprintf(buffer,"\tli $t1, %d\n",s->ob[2]->data);
			pushLine();
		}else{
			sprintf(t,"\tlw $t1, ");pushBuffer();
			printObject(s->ob[2]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}
		if (s->size == 1)
			sprintf(buffer,"\tsb $t1, %d($t0)\n",s->ob[1]->data);
		else
			sprintf(buffer,"\tsw $t1, %d($t0)\n",s->ob[1]->data);
		pushLine();
	}else if (s->op->type == IROFGTOP){
		if (s->ob[0]->type == IRINTC){
			sprintf(buffer,"\tli $t0, %d\n",s->ob[0]->data);
			pushLine();
		}else if (s->ob[0]->pd == 2){
			if (s->ob[0]->size == 4)
				sprintf(t,"\tlw $t0, ");
			else
				sprintf(t,"\tlb $t0, ");
			pushBuffer();
			printObject(s->ob[0]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}else{
			sprintf(t,"\tlw $t0, ");pushBuffer();
			printObject(s->ob[0]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			if (s->ob[0]->size == 4)
				sprintf(buffer,"\tlw $t0, 0($t0)\n");
			else
				sprintf(buffer,"\tlb $t0, 0($t0)\n");
			pushLine();
		}
		sprintf(t1,"$t1");
		if (s->ob[1]->type == IRINTC){
//			printf("\tli $t1, %d\n",s->ob[1]->data);
			sprintf(t1,"%d",s->ob[1]->data);
		}else if (s->ob[1]->pd == 2){
			if (s->ob[1]->size == 4)
				sprintf(t,"\tlw $t1, ");
			else
				sprintf(t,"\tlb $t1, ");
			pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}else{
			sprintf(t,"\tlw $t1, ");pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			if (s->ob[1]->size == 4)
				sprintf(buffer,"\tlw $t1, 0($t1)\n");
			else
				sprintf(buffer,"\tlb $t1, 0($t1)\n");
			pushLine();
		}
		if (strcmp(s->op->name,"<=") == 0){
			sprintf(buffer,"\tbgt $t0, %s, label%d\n",t1,s->ob[2]->data);
		}else if (strcmp(s->op->name,"<") == 0){
			sprintf(buffer,"\tbge $t0, %s, label%d\n",t1,s->ob[2]->data);
		}else if (strcmp(s->op->name,">=") == 0){
			sprintf(buffer,"\tblt $t0, %s, label%d\n",t1,s->ob[2]->data);
		}else if (strcmp(s->op->name,">") == 0){
			sprintf(buffer,"\tble $t0, %s, label%d\n",t1,s->ob[2]->data);
		}else if (strcmp(s->op->name,"==") == 0){
			sprintf(buffer,"\tbne $t0, %s, label%d\n",t1,s->ob[2]->data);
		}else if (strcmp(s->op->name,"!=") == 0){
			sprintf(buffer,"\tbeq $t0, %s, label%d\n",t1,s->ob[2]->data);
		}else{
			//never
		}
		pushLine();
	}else if (s->op->type == IROTGTOP){
		if (s->ob[0]->type == IRINTC){
			sprintf(buffer,"\tli $t0, %d\n",s->ob[0]->data);
			pushLine();
		}else if (s->ob[0]->pd == 2){
			if (s->ob[0]->size == 4)
				sprintf(t,"\tlw $t0, ");
			else
				sprintf(t,"\tlb $t0, ");
			pushBuffer();
			printObject(s->ob[0]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}else{
			sprintf(t,"\tlw $t0, ");pushBuffer();
			printObject(s->ob[0]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			if (s->ob[0]->size == 4)
				sprintf(buffer,"\tlw $t0, 0($t0)\n");
			else
				sprintf(buffer,"\tlb $t0, 0($t0)\n");
			pushLine();
		}
		sprintf(t1,"$t1");
		if (s->ob[1]->type == IRINTC){
//			printf("\tli $t1, %d\n",s->ob[1]->data);
			sprintf(t1,"%d",s->ob[1]->data);
		}else if (s->ob[1]->pd == 2){
			if (s->ob[1]->size == 4)
				sprintf(t,"\tlw $t1, ");
			else
				sprintf(t,"\tlb $t1, ");
			pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
		}else{
			sprintf(t,"\tlw $t1, ");pushBuffer();
			printObject(s->ob[1]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			if (s->ob[1]->size == 4)
				sprintf(buffer,"\tlw $t1, 0($t1)\n");
			else
				sprintf(buffer,"\tlb $t1, 0($t1)\n");
			pushLine();
		}
		if (strcmp(s->op->name,"<=") == 0){
			sprintf(buffer,"\tble $t0, %s, label%d\n",t1,s->ob[2]->data);
		}else if (strcmp(s->op->name,"<") == 0){
			sprintf(buffer,"\tblt $t0, %s, label%d\n",t1,s->ob[2]->data);
		}else if (strcmp(s->op->name,">=") == 0){
			sprintf(buffer,"\tbge $t0, %s, label%d\n",t1,s->ob[2]->data);
		}else if (strcmp(s->op->name,">") == 0){
			sprintf(buffer,"\tbgt $t0, %s, label%d\n",t1,s->ob[2]->data);
		}else if (strcmp(s->op->name,"==") == 0){
			sprintf(buffer,"\tbeq $t0, %s, label%d\n",t1,s->ob[2]->data);
		}else if (strcmp(s->op->name,"!=") == 0){
			sprintf(buffer,"\tbne $t0, %s, label%d\n",t1,s->ob[2]->data);
		}else{
			//never
		}
		pushLine();
	}else if (s->op->type == IRINCROP){
		if (s->ob[0]->pd == 2){
			if (s->size == 1){
				sprintf(t,"\tlb $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(buffer,"\taddu $t0, $t0, %d\n",s->ob[1]->data);
				pushLine();
				sprintf(t,"\tsb $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}else{
				sprintf(t,"\tlw $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(buffer,"\taddu $t0, $t0, %d\n",s->ob[1]->data);
				pushLine();
				sprintf(t,"\tsw $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}
		}else{
			sprintf(t,"\tlw $t0, ");pushBuffer();
			printObject(s->ob[0]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			if (s->size == 1){
				sprintf(buffer,"\tlb $t1, 0($t0)\n");
				pushLine();
				sprintf(buffer,"\taddu $t1, $t1, %d\n",s->ob[1]->data);
				pushLine();
				sprintf(buffer,"\tsb $t1, 0($t0)\n");
				pushLine();
			}else{
				sprintf(buffer,"\tlw $t1, 0($t0)\n");
				pushLine();
				sprintf(buffer,"\taddu $t1, $t1, %d\n",s->ob[1]->data);
				pushLine();
				sprintf(buffer,"\tsw $t1, 0($t0)\n");
				pushLine();
			}
		}
	}else if (s->op->type == IRDECROP){
		if (s->ob[0]->pd == 2){
			if (s->size == 1){
				sprintf(t,"\tlb $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(buffer,"\tsubu $t0, $t0, %d\n",s->ob[1]->data);
				pushLine();
				sprintf(t,"\tsb $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}else{
				sprintf(t,"\tlw $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
				sprintf(buffer,"\tsubu $t0, $t0, %d\n",s->ob[1]->data);
				pushLine();
				sprintf(t,"\tsw $t0, ");pushBuffer();
				printObject(s->ob[0]);
				sprintf(t,"\n");pushBuffer();
				pushLine();
			}
		}else{
			sprintf(t,"\tlw $t0, ");pushBuffer();
			printObject(s->ob[0]);
			sprintf(t,"\n");pushBuffer();
			pushLine();
			if (s->size == 1){
				sprintf(buffer,"\tlb $t1, 0($t0)\n");
				pushLine();
				sprintf(buffer,"\tsubu $t1, $t1, %d\n",s->ob[1]->data);
				pushLine();
				sprintf(buffer,"\tsb $t1, 0($t0)\n");
				pushLine();
			}else{
				sprintf(buffer,"\tlw $t1, 0($t0)\n");
				pushLine();
				sprintf(buffer,"\tsubu $t1, $t1, %d\n",s->ob[1]->data);
				pushLine();
				sprintf(buffer,"\tsw $t1, 0($t0)\n");
				pushLine();
			}
		}
	}else{
		//never
	}
}
static void printFunc(struct Function *func){
	int i,cur = 0;
	struct SentenceList *l = func->body;
	if (strcmp(func->name,"main") == 0)
		sprintf(buffer,"%s:\n",func->name);
	else
		sprintf(buffer,"_%s:\n",func->name);
	pushLine();
	sprintf(buffer,"\tsubu $sp, $sp, %d\n",func->mainSpace);
	pushLine();
	
	if (!func->isLeaf){
		sprintf(buffer,"\tsw $ra, %d($sp)\n",func->retnStat);
		pushLine();
	}
	if (strcmp(func->name,"main") == 0){
		struct SentenceList *l = funcList->e[0]->body;
		for (i = 0;i < l->num;++i) printSentence(l->e[i],&cur,func);
	}
	
	for (i = 0;i < l->num;++i){
		printSentence(l->e[i],&cur,func);
	}
	sprintf(buffer,"__end__%s:\n",func->name);
	pushLine();
	if (!func->isLeaf){
		sprintf(buffer,"\tlw $ra, %d($sp)\n",func->retnStat);
		pushLine();
	}
	sprintf(buffer,"\taddu $sp, $sp, %d\n",func->mainSpace);
	pushLine();
	if (strcmp(func->name,"main") == 0){
		sprintf(buffer,"\tli $v0, 10\n");
		pushLine();
		sprintf(buffer,"\tsyscall\n");
		pushLine();
	}else{
		sprintf(buffer,"\tj $ra\n");
		pushLine();
	}
}
static void printPrintf(){
	char *a[3];
	int f[3],i,j,t;
	sprintf(buffer,"_printf:\n");
	pushLine();
	sprintf(buffer,"\tla $a1, 4($sp)\n");
	pushLine();
	sprintf(buffer,"\tlw $a2, 4($sp)\n");
	pushLine();
//	printf("\tj _printf_loop\n");
	
	sprintf(buffer,"_printf_loop:\n");
	pushLine();
	sprintf(buffer,"\tlb $a0, 0($a2)\n");
	pushLine();
	sprintf(buffer,"\tbeq $a0, 0, _printf_end\n");
	pushLine();
	sprintf(buffer,"\taddu $a2, $a2, 1\n");
	pushLine();
	sprintf(buffer,"\tbeq $a0, '%%', _printf_fmt\n");
	pushLine();
	sprintf(buffer,"\tli $v0, 11\n");
	pushLine();
	sprintf(buffer,"\tsyscall\n");
	pushLine();
	sprintf(buffer,"\tj _printf_loop\n");
	pushLine();
	
	sprintf(buffer,"_printf_fmt:\n");
	pushLine();
	sprintf(buffer,"\tlb $a0, 0($a2)\n");
	pushLine();
	sprintf(buffer,"\taddu $a2, $a2, 1\n");
	pushLine();
	
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
		if (numOfFmt[f[1]] || numOfFmt[f[2]] || numOfFmt[3]){
			sprintf(buffer,"%s",a[f[0]]);
			pushLine();
		}else{
			//nop;
		}
	}
	if (numOfFmt[f[1]]){
		sprintf(buffer,"%s",a[f[1]]);
		pushLine();
	}
	if (numOfFmt[f[2]]){
		sprintf(buffer,"%s",a[f[2]]);
		pushLine();
	}
	
	if (numOfFmt[3]){
		sprintf(buffer,"_printf_width:\n");
		pushLine();
		sprintf(buffer,"\taddu $a1, $a1, 4\n");
		pushLine();
		sprintf(buffer,"\tlb $t0, 0($a2)\n");
		pushLine();
		sprintf(buffer,"\tsubu $t0, $t0, '0'\n");
		pushLine();
		sprintf(buffer,"\taddu $a2, $a2, 2\n");
		pushLine();
		sprintf(buffer,"\tlw $t1, 0($a1)\n");
		pushLine();
		sprintf(buffer,"\tli $t2, 1\n");
		pushLine();
		sprintf(buffer,"\tblt $t0, 2, _printf_width_end\n");
		pushLine();
		sprintf(buffer,"_label_width_1:\n");
		pushLine();
		sprintf(buffer,"\tsubu $t0, $t0, 1\n");
		pushLine();
		sprintf(buffer,"\tmul $t2, $t2, 10\n");
		pushLine();
		sprintf(buffer,"\tbgt $t0, 1, _label_width_1\n");
		pushLine();
		sprintf(buffer,"\tli $a0, 0\n");
		pushLine();
		sprintf(buffer,"\tli $v0, 1\n");
		pushLine();
		sprintf(buffer,"_label_width_2:\n");
		pushLine();
		sprintf(buffer,"\tbge $t1, $t2, _printf_width_end\n");
		pushLine();
		sprintf(buffer,"\tsyscall\n");
		pushLine();
		sprintf(buffer,"\tdiv $t2, $t2, 10\n");
		pushLine();
		sprintf(buffer,"\tj _label_width_2\n");
		pushLine();
		
		sprintf(buffer,"_printf_width_end:\n");
		pushLine();
		sprintf(buffer,"\tlw $a0, 0($a1)\n");
		pushLine();
		sprintf(buffer,"\tli $v0, 1\n");
		pushLine();
		sprintf(buffer,"\tsyscall\n");
		pushLine();
		sprintf(buffer,"\tj _printf_loop\n");
		pushLine();
	}
	if (numOfFmt[0]){
		sprintf(buffer,"_printf_char:\n");
		pushLine();
		sprintf(buffer,"\taddu $a1, $a1, 4\n");
		pushLine();
		sprintf(buffer,"\tlb $a0, 0($a1)\n");
		pushLine();
		sprintf(buffer,"\tli $v0, 11\n");
		pushLine();
		sprintf(buffer,"\tsyscall\n");
		pushLine();
		sprintf(buffer,"\tj _printf_loop\n");
		pushLine();
	}
	
	if (numOfFmt[1]){
		sprintf(buffer,"_printf_int:\n");
		pushLine();
		sprintf(buffer,"\taddu $a1, $a1, 4\n");
		pushLine();
		sprintf(buffer,"\tlw $a0, 0($a1)\n");
		pushLine();
		sprintf(buffer,"\tli $v0, 1\n");
		pushLine();
		sprintf(buffer,"\tsyscall\n");
		pushLine();
		sprintf(buffer,"\tj _printf_loop\n");
		pushLine();
	}
	
	if (numOfFmt[2]){
		sprintf(buffer,"_printf_str:\n");
		pushLine();
		sprintf(buffer,"\taddu $a1, $a1, 4\n");
		pushLine();
		sprintf(buffer,"\tlw $a0, 0($a1)\n");
		pushLine();
		sprintf(buffer,"\tli $v0, 4\n");
		pushLine();
		sprintf(buffer,"\tsyscall\n");
		pushLine();
		sprintf(buffer,"\tj _printf_loop\n");
		pushLine();
	}
	
	sprintf(buffer,"_printf_end:\n");
	pushLine();
	sprintf(buffer,"\tj $ra\n");
	pushLine();
	
	
}
static void printMalloc(){
	sprintf(buffer,"_malloc:\n");
	pushLine();
	sprintf(buffer,"\tli $v0, 9\n");
	pushLine();
	sprintf(buffer,"\tlw $a0, 4($sp)\n");
	pushLine();
	sprintf(buffer,"\tsyscall\n");
	pushLine();
	sprintf(buffer,"\tsw $v0, 0($sp)\n");
	pushLine();
	sprintf(buffer,"\tj $ra\n");
	pushLine();
}
static void printGetchar(){
	sprintf(buffer,"_getchar:\n");
	pushLine();
	sprintf(buffer,"\tli $v0, 12\n");
	pushLine();
	sprintf(buffer,"\tsyscall\n");
	pushLine();
	sprintf(buffer,"\tsw $v0, 0($sp)\n");
	pushLine();
	sprintf(buffer,"\tj $ra\n");
	pushLine();
}


int main(void){
	int i;
	initArraBegin = 0;
	numOfLines = 0;
	ptrOfBuffer = 0;
	ir();
	printGlobal(funcList->e[0]);
	for (i = 4;i < funcList->num;++i) printFunc(funcList->e[i]);
	printPrintf();
	printMalloc();
	printGetchar();
	freeFunctionList(funcList);
	freeRegisterList(registers);
	freeStringList(string);
	printMips();
	return 0;
}
