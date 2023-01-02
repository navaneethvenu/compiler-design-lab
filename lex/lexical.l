%{
#include <stdio.h>
int comment = 0, cnt = 0;
%}
identifier [a-zA-Z][a-zA-Z0-9]*
constant [0-9]*
%%
#.* if(!comment) printf("Preprocessor directive: %s\n", yytext);
int |
main |
return |
if |
switch |
case |
long |
typedef |
else |
void |
continue |
break |
goto |
for |
while { if(!comment) printf("Keyword: %s\n", yytext); }
"/*" {comment = 1;}
"*/" {comment = 0; cnt++;}
\".*\" if(!comment) printf("String: %s\n", yytext);
{constant} if(!comment) printf("Constant: %s\n", yytext);
{identifier} if(!comment) printf("Identifier: %s\n", yytext);
{identifier}\( if(!comment) printf("Function: %s\n", yytext);
\{ if(!comment) printf("Block begins\n");
\} if(!comment) printf("Block ends\n");
\= if(!comment) printf("Assignment operator: %s\n", yytext);
\<= |
\>= |
\< |
\> |
\== if(!comment) printf("Relational operator: %s\n", yytext);
\+ |
\- |
\/ |
\* |
\++ |
\-- if(!comment) printf("Arithmetic operator: %s\n", yytext);
. {}
%%
int main() {
	yyin  = fopen("pgm.txt", "r");
	yylex();
	printf("Total no of comments: %d\n", cnt);
}

int yywrap() {
	return 1;
}
