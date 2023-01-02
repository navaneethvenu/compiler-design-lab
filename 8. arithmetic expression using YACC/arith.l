// 8. YACC specification to recognise a valid arithmetic expression
// Amal Joe R S, Roll No. 64, S7 CS2

// arith.y

%{
	#include <stdio.h>
	#include "y.tab.h"
	extern int yylval;
%}
%%
[0-9]+ { return NUMBER; }
[a-zA-Z]+ { return ID; }
[\t]+ {;} /* for skipping whitespace */
\n { return 0; }
. { return yytext[0];}
%%
int yywrap() {
	return 1;
}
