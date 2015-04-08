#include "parser.h"
static struct token *makeList(char *s,int *N){	//Remember to free the memory!!!
	int n,m,l,r;
	token *list;
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
		r = l;
		while (s[r] != 0) ++r;
		list[i].ptr = s + l;
		getTokenType(&(list[i].ptr));
		l = r + 1;
	}
	list[m].ptr = s + r;//add END
	list[m].tokenType = SYM;
	list[m].tokenDetail = END;
	*N = m + 1;
	return list;
}

