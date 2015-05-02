#include<stdio.h>
char *_ = "#include <stdio.h>%cchar* recurse=%c%s%c;%cint main(){printf(recurse,10,34,recurse,34,10,10);}%c";
char *s = "123";
char c = '123';
