#include <stdio.h>
#include "removeComments.h"
#include "split.h"
//#include "tokens.h"
char s[1000010];
int p,c;
int main(){
	p = -1;
	c = getchar();
	while (c != EOF){
		s[++p] = c;
		c = getchar();
	}
	removeComments(s);
	split(s);
	puts(s);
}
