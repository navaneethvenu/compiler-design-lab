// 10. Conversion of NFA to DFA
// Amal Joe R S, Roll No. 64, S7 CS2

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

// count
int nNFA, nDFA = 0, nInput;
// input symbols
char ip[MAX];
// transition tables
char nfa[MAX][MAX][MAX];
char dfa[MAX][MAX][MAX];
// dfa states
char states[MAX][MAX];
char temp[MAX];

char* goTo(char*, char);
int getIndex(char);
bool found(char*);

int main() {
	printf("Enter the number of input symbols:\n");
	scanf("%d", &nInput);
	printf("Enter the input symbols:\n");
	for (int i = 0; i < nInput; i++) {
		scanf(" %c", &ip[i]);
	}
	printf("Enter the number of states in NFA:\n");
	scanf("%d", &nNFA);
	for (int i = 0; i < nNFA; i++) {
		printf("Enter the transition table entry for q%d: ", i);
		for (int j = 0; j < nInput; j++) {
			scanf("%s", nfa[i][j]);
		}
	}
	printf("\nNFA transition table:\n");
	for (int i = 0; i < nInput; i++) {
		printf("\t%c", ip[i]);
	}
	printf("\n");
	for (int i = 0; i < nNFA; i++) {
		printf("q%d", i);
		for (int j = 0; j < nInput; j++) {
			printf("\t%s", nfa[i][j]);
		}
		printf("\n");
	}
	char pendingStack[MAX][MAX];
	int pendingTop = -1;
	strcpy(pendingStack[++pendingTop], "0");
	while(pendingTop >= 0) {
		strcpy(states[nDFA], pendingStack[pendingTop--]);
		for (int i = 0; i < nInput; i++) {
			strcpy(dfa[nDFA][i], goTo(states[nDFA], ip[i]));
			if(!found(dfa[nDFA][i])) {
				strcpy(pendingStack[++pendingTop], dfa[nDFA][i]); 
			}
		}
		nDFA++;
	}
	printf("\nDFA transition table:\n");
	for (int i = 0; i < nInput; i++) {
		printf("\t%c", ip[i]);
	}
	printf("\n");
	for (int i = 0; i < nDFA; i++) {
		printf("q%s", states[i]);
		for (int j = 0; j < nInput; j++) {
			printf("\tq%s", dfa[i][j]);
		}
		printf("\n");
	}
	return 0;
}

char* goTo(char* state, char sym) {
	int symIndex = getIndex(sym);
	temp[0] = '\0';
	for (int i = 0; i < strlen(state); i++) {
		int stateIndex = state[i] - 48;
		if(strcmp(nfa[stateIndex][symIndex], "#") == 0) continue;
		strcat(temp, nfa[stateIndex][symIndex]);
	}
	return temp;
}

// get index of symbol
int getIndex(char sym) {
	for (int i = 0; i < nInput; i++) {
		if(ip[i] == sym)
			return i;
	} 
	return -1;
}

// check if a state is found in DFA transition table
bool found(char* s) {
	// here, nDFA is index of last state (not count)
	for (int i = 0; i <= nDFA; i++) {
		if(strcmp(states[i], s) == 0)
			return true;
	}
	return false;
}

/*
Input:
2
a b
3
01 0
# 2
# #

Output:
Enter the number of input symbols:
2        
Enter the input symbols:
a
b
Enter the number of states in NFA:
3
Enter the transition table entry for q0: 01 0
Enter the transition table entry for q1: # 2
Enter the transition table entry for q2: # #

NFA transition table:
	a	b
q0	01	0
q1	#	2
q2	#	#

DFA transition table:
	a	b
q0	q01	q0
q01	q01	q02
q02	q01	q0
*/
