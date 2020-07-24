// CQuiz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int random(int, int);
int answer(char[]);
int getQuestions();
void getMax();
int checkUsed(int);
int max;
int* usedQ;

int main()
{
    char choice[10];
    getMax();

#define SIZE max

    //Description
    printf("Welcome to Nathan's quiz. This is a random quiz program\n");
    printf("Choose the # of questions on the quiz (At least 1, at most %d)\n", max/2);
    scanf("%s", choice);

    srand(time(NULL));

    usedQ = (int*) malloc(max * sizeof(int));
    usedQ[0] = -1;

    printf("Searhing... \n");
    printf("Questions ready\n");

    int count = 0;

    int a = atoi(choice);
    for (int x = 0; x < a; x++) {
        count += getQuestions();
    }
    free(usedQ);
    printf("You answered %d out of %d correctly", count, a);
    return 0;
}

//Pull questions from .txt bank
int getQuestions() {
    FILE* fp;
    int ans = 0;
    fp = fopen("C:\\Temp\\tmp\\quiz.txt", "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }
    else {
        char line[256];
        int count = 0;
        int lineNumber;
        
        for(;;){
            lineNumber = random(0, max);

            if (checkUsed(lineNumber) == 0) {
                break;
            }
        } 
        
        while (fgets(line, sizeof line, fp) != NULL) {
            if (count == lineNumber) {
                printf("Question: %s", line);
                fgets(line, sizeof line, fp);
                ans = answer(line);
                break;
            }
            count++; 
        }
    }
    fclose(fp);
    return ans;
}

int checkUsed(int lineNumber) { //int is bool. 1 = true (has been used), 0 = false (hasn't been used)
    int test;
    for (int x = 0; x < max; x++)
    {
        if (usedQ[x] == lineNumber) {
            return 1;
        }
        if (usedQ[x] == -1) {
            usedQ[x] = lineNumber;
            usedQ[x + 1] = -1;              
            return 0;
        }
    }

    //Should never reach this point
    return 0;
}

int answer(char ans[]) {    //int is bool. 1 = true, 0 = false
    char input[50];
    ans[strlen(ans) - 1] = '\0';
    scanf("%s", input);
    if (strcmp(input, ans) == 0) {
        printf("Correct!\n");
        return 1;
    }
    printf("Boo, incorrect smh\n");
    return 0;
}

int random(int min, int max) {
    int randNum;
    for (;;) {
        randNum = rand() % max;
        if (randNum % 2 == 0) {
            break;
        }
    }
    return randNum;
}

void getMax() {
    FILE* fp;
    fp = fopen("C:\\Temp\\tmp\\quiz.txt", "r");
    char line[256];
    max = 0;
    while (fgets(line, sizeof line, fp) != NULL) {
        max++;
    }
    fclose(fp);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
