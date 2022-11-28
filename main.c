#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORD 212
#define NUM_WORDS  1

char selected_word[5];
char user_input[5];
char arr[6][5];
int numbers[6][5];

void instructions()
{
    printf("\nWELCOME TO WORDLE !!!\n");
    printf("\nGuess the WORDLE in six tries.\n");
    printf("\nEach guess must be a valid five-letter word. Hit the enter button to submit.\n");
    printf("\nAfter each guess, the color of the tiles will change to show how close your guess was to the word.\n");
    printf("\nYELLOW: letter exists in the word but not in the position as indicated by the player");
    printf("\nGREEN: The letter exists in the word at the same position as indicated by the user.");
    printf("\nBEST OF LUCK!!!\n");
}

void display()
{
    for(int i=0; i<=13; i++)
    {
        if(i%2 != 0)
        {
            for (int j=1; j<=16; j++)
            {
                printf("-");
            }
            printf("\n");
        }
        else
        {
            for(int j=0; j<=15; j++)
            {
                if(j%3 == 0 && i!=0)
                    printf("|");
                else if (j%3 == 1 && i!=0)
                {

                    if (i==2) {
                        if(numbers[i-2][j/3]==2)
                            printf("\033[0;32m");
                        else if(numbers[i-2][j/3]==1)
                            printf("\033[0;33m");
                        printf("%c",toupper(arr[i-2][j/3]));
                    }
                    else {
                        if(numbers[(i-1)/2][j/3]==2)
                            printf("\033[0;32m");
                        else if(numbers[(i-1)/2][j/3]==1)
                            printf("\033[0;33m");
                        printf("%c",toupper(arr[(i-1)/2][j/3]));
                    }
                    printf("\033[0m"); // resets color back to default
                }
                else
                    printf(" ");
            }
            printf("\n");
        }
    }
    printf("\n");
}

void select_word()
{
    FILE *fp = fopen("words.txt", "r");
    if (fp == NULL) 
    {
        perror("Unable to locate word list");
        exit(EXIT_FAILURE);
    }
    /* Count words in file */
    char word[MAX_WORD];
    long wc = 0;
    while (fgets(word, sizeof word, fp) != NULL)
    {
        ++wc;
    }
    /* Store random words in array */
    char randwords[NUM_WORDS][MAX_WORD];
    srand((unsigned) time(NULL));
    for (size_t i = 0; i < NUM_WORDS; i++) 
    {
        rewind(fp);
        int sel = rand() % wc + 1;
        for (int j = 0; j < sel; j++) 
        {
            if (fgets(word, sizeof word, fp) == NULL) 
            {
                perror("Error in fgets()");
            }
        }
        strcpy(randwords[i], word);
        }
    if (fclose(fp) != 0) 
    {
        perror("Unable to close file");
    }
    for(int i=0; i<5; i++)
    {
        selected_word[i] = word[i];
    }

}

void taking_input()
{
    printf("Enter a 5 letter word: ");
    scanf("%s",user_input);
}

int main()
{
    char ch=' ';
    
    for(int i=0;i<6; i++)
    {
        for(int j=0; j<5; j++)
        {
            arr[i][j] = ch;
            numbers[i][j] = 0;
        }
    }
    instructions();
    display();
    select_word();
    int won = 0;
    for(int x=0; x<=5; x++)
    {
        taking_input();
        while (strlen(user_input)!=5) {
            printf("\nONLY FIVE LETTER VALID WORDS ALLOWED!!\n");
            taking_input();
        }
            for(int y=0; y<=4; y++)
            {
                arr[x][y] = user_input[y];
                if (selected_word[y] == tolower(user_input[y]))
                    numbers[x][y] = 2;
                else {
                    int flag = 0;
                    for(int t=0; t<5; t++) {
                        if(tolower(user_input[y]) == selected_word[t])
                            flag = 1;
                    }
                    if (flag == 1)
                        numbers[x][y] = 1;
                }
            }
        display();

        if((numbers[x][0]==2)&&(numbers[x][1]==2)&&(numbers[x][2]==2)&&(numbers[x][3]==2)&&(numbers[x][4]==2))
        {
            printf("\nYOU WON IN %d CHANCES!!!",(x+1));
            won = 1;
            break;
        }
    }
    if(won==0)
    {
        printf("\nYOU LOST :-(\n");
        printf("\nThe correct answer is: ");
        for(int z=0; z<5; z++)
          printf("%c",toupper(selected_word[z]));
        printf("\n");
        printf("\n\nBetter luck next time!");
    }
}