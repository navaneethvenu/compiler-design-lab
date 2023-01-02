// 9. Calculator using LEX and YACC
// Amal Joe R S, Roll No. 64, S7 CS2

// cal.l

%{
	#include <stdio.h>
	#include "y.tab.h"
	extern int yylval;
%}
%%
[0-9]+ { 
yylval = atoi(yytext);
return NUMBER; }
[a-zA-Z]+ { return ID; }
[\t]+ {;} /* for skipping whitespace */
\n { return 0; }
. { return yytext[0];}
%%
int yywrap() {
	return 1;
}
