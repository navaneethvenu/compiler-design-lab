#include <stdio.h>
#include <string.h>

#define MAX 100

void getProd();
void printProd();
void leftRecursion();

struct PRODUCTION
{
    char l;
    char r[MAX][MAX];
    int rLen;
} PROD[MAX];

char line[MAX];
char startProd = '\0';
char prodLen = 0;
char currentFreeChar = 'E';

void main()
{

    int opt = 1;

    printf("Choose:\n1.Display Production\n2.Remove Left Recursion\n");
    scanf("%d", &opt);

    getProd();
    printProd();
    if (opt == 2)
    {
        leftRecursion();
        printProd();
    }
}

void getProd()
{
    FILE *fp = fopen("gram.txt", "r");
    while (fscanf(fp, "%s", line) != EOF)
    {
        // set start production
        if (startProd == '\0')
            startProd = line[0];

        // set left
        PROD[prodLen].l = line[0];

        // set right
        int rightLen = 1;
        int i = 3;
        int j = 0;
        while (line[i] != '\0')
        {
            if (line[i] != '|')
            {
                PROD[prodLen]
                    .r[rightLen - 1][j++] = line[i];
            }
            else
            {
                rightLen++;
                PROD[prodLen].rLen = rightLen;
                j = 0;
            }
            if (line[i + 1] == '\0')
            {
                PROD[prodLen].rLen = rightLen;
                j = 0;
            }
            i++;
        }

        prodLen++;
    }
    printf("Start Symbol: %c\n\n", startProd);
}

void printProd()
{
    printf("Productions:\n");
    for (int i = 0; i < prodLen; ++i)
    {
        printf("%c -> ", PROD[i].l);
        for (int j = 0; j < PROD[i].rLen; ++j)
        {
            printf("%s", PROD[i].r[j]);
            if (j + 1 != PROD[i].rLen)
            {
                printf(" | ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void leftRecursion()
{
    printf("Removing Left Recursion:\n\n");

    for (int i = 0; i < prodLen; ++i)
    {
        int flag[MAX] = {0};
        int isRecursive = 0;

        // find Recursion
        for (int j = 0; j < PROD[i].rLen; ++j)
        {
            if (PROD[i].l == PROD[i].r[j][0])
            {
                flag[j] = 1;
                isRecursive = 1;
            }
        }

        //
        if (isRecursive)
        {
            int rIndexNew = 0;
            int rIndexOld = 0;
            struct PRODUCTION *newProd = &PROD[prodLen];
            struct PRODUCTION oldProd;
            prodLen++;
            newProd->l = currentFreeChar;
            for (int j = 0; j < PROD[i].rLen; ++j)
            {
                char tempChar[2];
                tempChar[0] = currentFreeChar;
                tempChar[1] = '\0';

                oldProd.l = PROD[i].l;
                oldProd.rLen = 0;

                if (flag[j] == 1)
                {
                    strcpy(newProd->r[rIndexNew], PROD[i].r[j] + 1);
                    strcat(newProd->r[rIndexNew], tempChar);
                    newProd->rLen = rIndexNew + 1;
                    rIndexNew++;
                }
                else
                {
                    // A - > Aa | B A - > BA' A ' - > aA' | ^
                    strcat(PROD[i].r[j], tempChar);
                    strcpy(oldProd.r[rIndexOld], PROD[i].r[j]);
                    rIndexOld++;
                }
            }

            oldProd.rLen = rIndexOld;
            PROD[i] = oldProd;

            strcpy(newProd->r[rIndexNew], "^");
            newProd->rLen++;

            currentFreeChar++;
        }
    }
}