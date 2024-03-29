#ifndef _IR_H_
#define _IR_H_
enum OpType{
	IRUNAROP,IRBINAOP,IRASSIOP,IRPARAOP,IRCALLOP,IRLABLOP,IRGOTOOP,IRITGTOP,IRIFGTOP,IRARRROP,IRARRWOP,IRPTRROP,IRPTRWOP,IRRTSZOP,IRRETNOP,
//	unary    binary   =        param    call     label    goto     ifTgoto  ifFgoto  a=b[x],4 a[x]=b,4 t0=*a,4  *a=t0,4  ...      ret
	IRLGASOP,IRARASOP,IRASSCOP,IRINAROP,IROTGTOP,IROFGTOP,IRINCROP,IRDECROP
//	...      =        =        =        sge...   ...      ++       --
};
enum ObjectType{
	IRSTRC,IRINTC,IRNAME,IRTEMP
};
struct Op{
	int type;
	char *name;
};
struct Object{
	int type,pd,size,data;//pd -- 0 data, 1 pointer, 2 memblock
	char *name;
};
struct RegisterList{
	struct Object **e;
	int *label;
	int cap;
};
struct ObjectList{
	struct Object **e;
	int *link;
	struct Object **tmpLink;
	int num,cap;
};
struct Sentence{
	struct Object *ob[3];
	struct Op *op;
	int size,num;
};
struct SentenceList{
	struct Sentence **e;
	int num,cap;
};
struct Function{
	char *name;
	struct ObjectList *para,*vari;
	struct SentenceList *body;
	int mainSpace,retnStat,isLeaf;
};
struct FunctionList{
	struct Function **e;
	int num,cap;
};
struct String{
	int size;
	char *s;
	struct Object *link;
};
struct StringList{
	struct String **e;
	int num,cap;
};
//======global variables======
int registerNum,labelNum;
struct RegisterList *registers;
struct FunctionList *funcList;
struct StringList *string;
int numOfFmt[4];
//======functions======
void freeFunctionList(struct FunctionList *);
void freeRegisterList(struct RegisterList *);
void freeStringList(struct StringList *);
void ir(void);
#endif
