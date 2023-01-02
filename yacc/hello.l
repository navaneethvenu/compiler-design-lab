%{
	#include "y.tab.h"
	int yyerror(char *errormsg);
	int yyparse(void);
%}

%%
("hi"|"oi"|"HI")"\n" { return HI; }
("bye"|"BYE")"\n" { return BYE; }
. {
	yyerror("Unknown char");
}

%%

int main(void) {
	printf("Enter msg hi or bye: ");
	yyparse();
	return 0;
}

int yywrap(void) {
	return 0;
}

int yyerror(char *errormsg) {
	fprintf(stderr, "%s\n", errormsg);
	exit(1);
}
