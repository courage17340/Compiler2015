//This program removes all comments from the raw input.
//Note that 'in/**/t' doesn't equal to 'int' but 'in t'.
//Lines started with # will also be removed, which may be changed in the future.
#include "removeComments.h"
//flag1 - '
//flag2 - "
static void warn(char *s,const char* t){
	strcpy(s,t);
}

static void deal(char *in,char *out){
	int i,cur,q,flag0,flag1,p;
	p = strlen(in);
	q = -1;
	flag0 = flag1 = 0;
	for (i = 0;i < p;++i){
		cur = in[i];
		if (flag0){
			if (cur == '\'')
				flag0 = 0;
			else if (cur == '\\'){
				out[++q] = cur;
				cur = in[++i];
			}else if (cur == '\n'){
				warn(out,"CompileError");
				return;
			}
		}else if (flag1){
			if (cur == '"')
				flag1 = 0;
			else if (cur == '\\'){
				out[++q] = cur;
				cur = in[++i];
			}else if (cur == '\n'){
				warn(out,"CompileError");
				return;
			}
		}else{
			if (cur == '\'')
				flag0 = 1;
			else if (cur == '"')
				flag1 = 1;
			else if (cur == '#'){//Ignore # now. Maybe I won't ignore it in the future.
				cur = '\n';
				while (i < p && in[i] != '\n') ++i;
			}else if (cur == '/'){
				if (in[i + 1] == '/'){
					cur = '\n';
					while (i < p && in[i] != '\n') ++i;
				}else if (in[i + 1] == '*'){
					cur = '\n';
					i += 2;
					while (i < p && (in[i] != '*' || in[i + 1] != '/')) ++i;
					++i;
					if (in[i] != '/'){
						warn(out,"CompileError");
						return;
					}
				}
			}
		}
		out[++q] = cur;
	}
	out[++q] = 0;
}

void removeComments(char *in){
	int L = strlen(in);
	static char out[1000010];
	deal(in,out);
	strcpy(in,out);
}

