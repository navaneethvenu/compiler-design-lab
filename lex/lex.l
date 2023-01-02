string [a-zA-Z]+
%%
[0-9]+ printf("Digit %s\n", yytext);
{string} printf("String %s\n", yytext);
%%
int main() {
	yylex();
}

int yywrap() {
	return 1;
}
