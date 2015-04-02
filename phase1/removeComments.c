//This program removes all comments from the raw input.
//Note that 'in/**/t' doesn't equal to 'int' but 'in t'.
//Lines started with # will also be removed, which may be changed in the future.
#include <stdio.h>
#include <string.h>
#define MAX 1000010
//MAX denotes the maximum size of the raw input
char in[MAX],out[MAX];
int p;
//flag1 - '
//flag2 - "
void readString(void){
	int c;
	p = -1;
	c = getchar();
	while (c != EOF){
		in[++p] = c;
		c = getchar();
	}
	in[++p] = 0;
}
void writeString(void){
	int i,cur,q,flag0,flag1;
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
			}
		}else if (flag1){
			if (cur == '"')
				flag1 = 0;
			else if (cur == '\\'){
				out[++q] = cur;
				cur = in[++i];
			}
		}else{
			if (cur == '\'')
				flag0 = 1;
			else if (cur == '"')
				flag1 = 1;
			else if (cur == '#'){//Ignore # now. Maybe I won't ignore it in the future.
				cur = '\n';
				while (i < p && in[i] != '\n') ++i;
			}else if (cur == '/')
				if (in[i + 1] == '/'){
					cur = '\n';
					while (i < p && in[i] != '\n') ++i;
				}else if (in[i + 1] == '*'){
					cur = '\n';
					i += 2;
					while (i < p && (in[i] != '*' || in[i + 1] != '/')) ++i;
					++i;
					if (in[i] != '/'){//In this case, ' .' is added to return a CE code
						out[++q] = ' ';
						cur = '.';
					}
				}
			
		}
		out[++q] = cur;
	}
	out[++q] = 0;
}
int main(){
	readString();
	writeString();
	puts(out);
	return 0;
}
