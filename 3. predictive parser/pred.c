#include <stdio.h>
#include <string.h>

#define MAX 100

void getProd();
void printProd();
void displayFirstFollow(int isFirst);

void leftRecursion();

void firstIterator();
int first(int index, char ele, int isIndex);

void followIterator();
int follow(int index, char ele, int isIndex);

int getIndex(char ele);
int validTerminals(char ch);

int arrContains(char *arr, char ch);

struct PRODUCTION
{
    char l;
    char r[MAX][MAX];
    int rLen;
} PROD[MAX];

char line[MAX];
char startProd = '\0';
char prodLen = 0;
char currentFreeChar = 'A';
int firstMatrix[MAX][MAX] = {'\0'};
int followMatrix[MAX][MAX] = {'\0'};

void main()
{

    int opt = 1;

    printf("Choose:\n1.Display Production\n2.Remove Left Recursion\n3.First\n4.Follow\n\n");
    scanf("%d", &opt);

    getProd();
    printProd();
    if (opt == 2 || opt == 3 || opt == 4)
    {
        leftRecursion();
        printProd();
    }
    if (opt == 3 || opt == 4)
    {
        firstIterator();
    }
    if (opt == 4)
    {
        followIterator();
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
    printf("\nStart Symbol: %c\n\n", startProd);
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

void firstIterator()
{
    for (int i = 0; i < prodLen; ++i)
    {
        first(i, '\0', 1);
    }
    displayFirstFollow(1);
}

void followIterator()
{
    for (int i = 0; i < prodLen; ++i)
    {
        follow(i, '\0', 1);
    }
    displayFirstFollow(0);
}

int first(int index, char ele, int isIndex)
{
    int firstLength = 0;
    int newIndex = (isIndex) ? index : getIndex(ele);
    // printf("hello-%d", newIndex);
    // printf("hello");

    if (newIndex == -1)
    {
        printf("Production not Present\n");
        return -1;
    }

    for (int i = 0; i < PROD[newIndex].rLen; ++i)
    {
        // printf("\nConsidering: %c && %c\n\n", PROD[newIndex].l, PROD[newIndex].r[i][0]);
        if ((PROD[newIndex].r[i][0] == '^') || validTerminals(PROD[newIndex].r[i][0]))
        {
            firstMatrix[newIndex][firstLength++] = PROD[newIndex].r[i][0];
            // printf("\nAccept %c:%c[%d]\n", PROD[newIndex].r[i][0], firstMatrix[newIndex][i], i);
        }
        else
        {
            int childIndex = first(0, PROD[newIndex].r[i][0], 0);
            if (childIndex != -1)
            {
                int j = 0;
                while (firstMatrix[childIndex][j] != '\0')
                {
                    firstMatrix[newIndex][firstLength++] = firstMatrix[childIndex][j++];
                }
            }
        }
    }

    return newIndex;
}

int follow(int index, char ele, int isIndex)
{
    int followIndex = 0;
    int newIndex = (isIndex) ? index : getIndex(ele);

    if (newIndex == -1)
    {
        return -1;
    }

    // printf("\n\nwe're at %c\n\n", PROD[newIndex].l);

    if (PROD[newIndex].l == startProd)
    {
        followMatrix[newIndex][followIndex++] = '$';
    }

    for (int i = 0; i < prodLen; ++i)
    {
        for (int j = 0; j < PROD[i].rLen; ++j)
        {
            int k = 0;

            while (PROD[i].r[j][k] != '\0')
            {
                // printf("\twe're testing %c-%d/%d/%d\n", PROD[i].r[j][k], i, j, k);
                if (PROD[i].r[j][k] == PROD[newIndex].l)
                {

                    // printf("\nheys%c\n", PROD[i].l);
                    if (PROD[i].r[j][k + 1] == '\0')
                    {
                        // printf("hey");
                    }
                    else if (validTerminals(PROD[i].r[j][k + 1]))
                    {
                        char *array = followMatrix[newIndex];
                        // printf("Array: %c  --  %c\n", *array, followMatrix[newIndex][0]);

                        if (!arrContains(array, PROD[i].r[j][k + 1]))
                            followMatrix[newIndex][followIndex++] = PROD[i].r[j][k + 1];
                        // printf("hi%c", PROD[i].r[j][k + 1]);
                    }
                    else
                    {
                        // printf("how are u");

                        int tempIndex = 0;
                        while (followMatrix[newIndex][tempIndex] != '\0')
                        {
                            tempIndex++;
                        }
                        int nextIndex = getIndex(PROD[i].r[j][k + 1]);
                        if (nextIndex == -1)
                        {
                            printf("No Productions Found\n");
                            return -1;
                        }
                        while (firstMatrix[nextIndex][tempIndex] != '\0')
                        {
                            // printf("First of %c", PROD[nextIndex].l);
                            char *array = followMatrix[newIndex];
                            // printf("Checking through:");
                            // int x = 0;
                            // while (followMatrix[newIndex][x] != '\0')
                            // {
                            //     printf("%c", followMatrix[nextIndex][x]);
                            //     x++;
                            // }
                            // printf("\n%c-followMatrix[%d][%d]", firstMatrix[nextIndex][tempIndex], nextIndex, tempIndex);

                            if (!arrContains(array, firstMatrix[nextIndex][tempIndex]))
                            {

                                followMatrix[newIndex][followIndex++] = firstMatrix[nextIndex][tempIndex];
                            }

                            tempIndex++;
                        }
                    }
                }
                k++;
            }
        }
    }
}

void displayFirstFollow(int isFirst)
{
    if (isFirst)
        printf("First:\n");
    else
        printf("Follow:\n");

    for (int i = 0; i < prodLen; ++i)
    {
        int j = 0;
        printf("%c: ", PROD[i].l);
        while ((isFirst) ? firstMatrix[i][j] != '\0' : followMatrix[i][j] != '\0')
        {
            if (j != 0)
            {
                printf(",");
            }
            if (isFirst)
                printf("%c", firstMatrix[i][j]);
            else
                printf("%c", followMatrix[i][j]);

            j++;
        }
        printf("\n");
    }
}

int getIndex(char ele)
{
    for (int i = 0; i < prodLen; ++i)
    {
        for (int j = 0; j < PROD[i].rLen; ++j)
        {
            if (PROD[i].l == ele)
                return i;
        }
    }
    return -1;
}

int validTerminals(char ch)
{
    if (islower(ch) || ch == ',' || ch == '(' || ch == ')' || ch == '+' || ch == '*' || ch == '+' || ch == '-')
        return 1;
    return 0;
}

int arrContains(char *arr, char ch)
{
    // printf("\nChecking from: %c\n", (*arr));

    while ((*arr) != '\0')
    {
        // printf("\tChecking: %c\n", (*arr));
        if (*(arr) == ch)
        {
            // printf("Found: %c..\n", ch);
            // printf("\t\t%c is old\n", ch);
            return 1;
        }
        arr++;
    }
    // printf("\t\t%c is new\n", ch);
    return 0;
}