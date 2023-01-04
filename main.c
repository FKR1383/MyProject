#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

void program(); // This function is the command giver in our VIM
void decide(char * , char *); // This function is the processor of our commands

/*
 * first Name: Farzam
 * last Name: Koohi Ronaghi
 * student Id: 401106403
 * number of attempt: 1
 * date : 1401/10/14
 */

int main()
{
    // creating root folder after being executed
    // this folder is created beside of .exe file
    mkdir("root");
    while (1)
    {
        program();
    }
}

void program()
{
    // this use for saving commands
    char *command = calloc(2000000000 , sizeof(char));
    gets(command);
    // printf("%s\n" , command); // this is for debugging
    char *operation = strtok(command , " ");
    // printf("%s\n" , operation); // this is for debugging
    decide(command , operation);
    free(command);
    // free the memory that saves our command
}

void decide(char *command , char *operation)
{
    // checking all situations for our commands
    if (strcmp(operation , "createfile") == 0)
    {
        // new command is our command without first word

    }
}

/*
 * Remember!
 * 1 - invalid commands must place at the end of the decide function!
 */