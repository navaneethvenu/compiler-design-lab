#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXINPUT 1000
#define MAX 100

char input[MAXINPUT];
int i = 0;

bool isDelimiter(char);
void checkId();
void getToken();

int main() {
	FILE *inputFile = fopen("input.txt", "r");
	fscanf(inputFile, "%[^EOF]s", input);
	int count = 0;
	while(i < strlen(input)) {
		getToken();
	}
	return 0;
}

void getToken() {
	int j;
	switch(input[++i]) {
		case 'i':
			switch(input[++i]) {
				case 'f':
					i++;
					printf("Valid Keyword: if\n");
					return;
				case 'n':
					if(input[++i] == 't') {
						printf("Valid Keyword: int\n");
						return;
					} else {
						//checkId();
					}
				default:
					printf(" ");
					//checkId();
			}
			break;
		case 'm':
			if(input[++i] == 'a' || input[++i] == 'i' || input[++i] == 'n') {
				printf("Valid Keyword: main\n");
				return;
			} else {
				//checkId();
			}
		case '(':
		case ')':
		case '{':
		case '}':
		case ';':
			printf("Valid punctuator: %c\n", input[i]);
			return;
		case ' ':
		case '\n':
		case '\t':
			i++;
			break;
		default:
			i++;
			checkId();
	}
}

void checkId() {
	printf("Identifier: %c\n", input[i]);
}
