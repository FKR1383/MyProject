#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

void program(); // This function is the command giver in our VIM
void decide(char * , char *); // This function is the processor of our commands
void createfile(char *); // this function creates folders and a text file
void insertstr(char *); // this function insert some texts in our .txt file
FILE* openfile(char *); // this function open file for edit and adding text and return pointer to that file
void editing_text(char *); // this function use for insert text in file (a child of insertstr)

/*
 * first Name: Farzam
 * last Name: Koohi Ronaghi
 * student Id: 401106403
 * number of attempt: 2
 * date : 1401/10/15
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
    // help is an extra string that is equal to command
    char *help = calloc(strlen(command) + 1 ,  sizeof(char));
    strcpy(help , command);
    char *operation = strtok(help , " ");
    decide(command , operation);
    return;
}

void decide(char *command , char *operation)
{
    // checking all situations for our commands
    if (strcmp(operation , "createfile") == 0){
        // new command is our command without first word
        char *newcommand = strchr(command, ' ');
        if(newcommand != NULL)
            command = newcommand + 1;
        else {
            printf("invalid command\n");
            return;
        }
        createfile(command);
        return;
    }
    else if (strcmp(operation , "insertstr") == 0)
    {
        // new command is our command without first word
        char *newcommand = strchr(command, ' ');
        if(newcommand != NULL)
            command = newcommand + 1;
        else {
            printf("invalid command\n");
            return;
        }
        insertstr(command);
        return;
    }
    /*else if()
    {

    }*/
}

void createfile(char *command)
{
    // first, We must check that our command is null or not
    char *help = calloc(strlen(command)+1 , sizeof(command));
    strcpy(help , command);
    char *file = strtok(help , " ");
    if (file == NULL)
    {
        printf("invalid command\n");
        return;
    }
    if (strcmp(file , "--file") == 0)
    {
        char *newcommand = strchr(command, ' ');
        if(newcommand != NULL)
            command = newcommand + 1;
        else {
            printf("invalid command\n");
            return;
        }
        // now, command will show us the path (directories) and file name
        if (command[0] == '"' && command[strlen(command)-1] == '"')
        {
            // minimum length of command must be /root/a.txt
            if (strlen(command) < 11)
            {
                printf("invalid command\n");
                return;
            }
            if (command[1] == '/' && command[2] == 'r' && command[3] == 'o' && command[4] == 'o' && command[5] == 't' && command[strlen(command)-2] == 't' && command[strlen(command)-3] == 'x' && command[strlen(command)-4] == 't' && command[strlen(command)-5] == '.')
            {
                //finding the end /
                int last = strlen(command)-1;
                while(command[last] != '/')
                    last--;
                char *dir = calloc(strlen(command) , sizeof(char));
                int j = 0;
                for (int i = 2; i <= last; i++)
                {
                    if (command[i] == '/')
                    {
                        dir[j] = '\0';
                        mkdir(dir);
                    }
                    dir[j] = command[i];
                    j++;
                }
                for (int i = last+1; i != strlen(command)-1; i++)
                {
                    dir[j] = command[i];
                    j++;
                }
                dir[j] = '\0';
                if (access(dir, F_OK) == 0) {
                    printf("The file exists!\n");
                    return;
                } else {
                    FILE *fptr;
                    fptr = fopen(dir, "w");
                    fclose(fptr);
                    return;
                }
            }
            else
            {
                printf("invalid command\n");
                return;
            }
        }
        else if (command[0] == '/')
        {
            if (command[1] == 'r' && command[2] == 'o' && command[3] == 'o' && command[4] == 't' && command[strlen(command)-1] == 't' && command[strlen(command)-2] == 'x' && command[strlen(command)-3] == 't' && command[strlen(command)-4] == '.')
            {
                // finding the end //
                int last = strlen(command)-1;
                while(command[last] != '/')
                    last--;
                char *dir = calloc(strlen(command) , sizeof(char));
                int j = 0;
                for (int i = 1; i <= last; i++)
                {
                    if (command[i] == '/')
                    {
                        dir[j] = '\0';
                        mkdir(dir);
                    }
                    dir[j] = command[i];
                    j++;
                }
                for (int i = last+1; i != strlen(command); i++)
                {
                    dir[j] = command[i];
                    j++;
                }
                dir[j] = '\0';
                if (access(dir, F_OK) == 0) {
                    printf("The file exists!\n");
                    return;
                } else {
                    FILE *fptr;
                    fptr = fopen(dir, "w");
                    fclose(fptr);
                    return;
                }
            }
            else
            {
                printf("invalid command\n");
                return;
            }
        }
        else
        {
            printf("invalid command\n");
            return;
        }
    }
    else
    {
        printf("invalid command\n");
        return;
    }
}

void insertstr(char *command)
{
    char *help = calloc(strlen(command)+1 , sizeof(command));
    strcpy(help , command);
    char *file = strtok(help , " ");
    if (file == NULL)
    {
        printf("invalid command\n");
        return;
    }
    if (strcmp(file , "--file") == 0)
    {
        char *newcommand = strchr(command, ' ');
        if(newcommand != NULL)
            command = newcommand + 1;
        else {
            printf("invalid command\n");
            return;
        }
        char *path = calloc(strlen(command) , sizeof(char));
        FILE *now;
        int i = 0;
        if (command[0] == '"') {
            while (i != strlen(command))
            {
                path[i] = command[i];
                i++;
                if (i != 1 && command[i-1] == '"')
                    break;
            }
            path[i] = '\0';
            now = openfile(path);
            // this function opens file for edit
        }
        else if (command[0] == '/')
        {
            while (i != strlen(command))
            {
                path[i] = command[i];
                i++;
                if (command[i] == ' ')
                    break;
            }
            path[i] = '\0';
            now = openfile(path);
        }
        else
        {
            printf("invalid command\n");
            return;
        }
        if (now == NULL)
        {
            return;
        }
        i++;
        int j = 0;
        char *text_pos = calloc(strlen(command) , sizeof(command));
        while (i != strlen(command))
        {
            text_pos[j] = command[i];
            j++;
            i++;
        }
        text_pos[j] = '\0';
        editing_text(text_pos);
    }
    else
    {
        printf("invalid command\n");
        return;
    }
}

FILE *openfile(char *command)
{
    if (command[0] == '"' && command[strlen(command)-1] == '"') {
        // minimum length of command must be /root/a.txt
        if (strlen(command) < 11) {
            printf("invalid command\n");
            return NULL;
        }
        if (command[1] == '/' && command[2] == 'r' && command[3] == 'o' && command[4] == 'o' && command[5] == 't' && command[strlen(command)-2] == 't' && command[strlen(command)-3] == 'x' && command[strlen(command)-4] == 't' && command[strlen(command)-5] == '.') {
            //finding the end /
            int last = strlen(command)-1;
            while(command[last] != '/')
                last--;
            char *dir = calloc(strlen(command) , sizeof(char));
            int j = 0;
            for (int i = 2; i <= last; i++) {
                if (command[i] == '/') {
                    dir[j] = '\0';
                    mkdir(dir);
                }
                dir[j] = command[i];
                j++;
            }
            for (int i = last+1; i != strlen(command)-1; i++) {
                dir[j] = command[i];
                j++;
            }
            dir[j] = '\0';
            if (access(dir, F_OK) == -1) {
                printf("The file doesn't exists!\n");
                return NULL;
            }
            FILE *fptr;
            fptr = fopen(dir, "r+");
            return fptr;
        }
        else {
            printf("invalid command\n");
            return NULL;
        }
    }
    else if (command[0] == '/') {
        if (command[1] == 'r' && command[2] == 'o' && command[3] == 'o' && command[4] == 't' && command[strlen(command)-1] == 't' && command[strlen(command)-2] == 'x' && command[strlen(command)-3] == 't' && command[strlen(command)-4] == '.') {
            // finding the end //
            int last = strlen(command)-1;
            while(command[last] != '/')
                last--;
            char *dir = calloc(strlen(command) , sizeof(char));
            int j = 0;
            for (int i = 1; i <= last; i++) {
                if (command[i] == '/') {
                    dir[j] = '\0';
                    mkdir(dir);
                }
                dir[j] = command[i];
                j++;
            }
            for (int i = last+1; i != strlen(command); i++) {
                dir[j] = command[i];
                j++;
            }
            dir[j] = '\0';
            if (access(dir, F_OK) == -1) {
                printf("The file doesn't exists!\n");
                return NULL;
            }
            FILE *fptr;
            fptr = fopen(dir, "r+");
            return fptr;
            }
        }
        else {
            printf("invalid command\n");
            return NULL;
        }
}

void editing_text(char *text_pos)
{
    char *help = calloc(strlen(text_pos)+1 , sizeof(text_pos));
    strcpy(help , text_pos);
    char *str = strtok(help , " ");
    if (str == NULL)
    {
        printf("invalid command\n");
        return;
    }
    if (strcmp(str , "--str") == 0)
    {
        char *newcommand = strchr(text_pos, ' ');
        if(newcommand != NULL)
            text_pos = newcommand + 1;
        else {
            printf("invalid command\n");
            return;
        }
        char *past_command = calloc(strlen(text_pos) , sizeof(char));
        strcpy(past_command , text_pos);
        char *text = calloc(strlen(text_pos) , sizeof(char));
        if (past_command[0] == '"')
        {
            // we must find the (real) second '"' :)))
            int last =  strlen(past_command) - 1;
            while (last >= 0)
            {
                if (past_command[last] == '"')
                    break;
                last--;
            }
            if (last == 0)
            {
                printf("invalid command\n");
                return;
            }
            int i;
            for (i = 1; i <= last-1; i++)
            {
                text[i-1] = past_command[i];
            }
            text[i-1] = '\0';
            text_pos = text_pos + strlen(text) + 3;
        }
        else
        {
            text = strtok(past_command , " ");
            if (text == NULL)
            {
                printf("invalid command\n");
                return;
            }
            text_pos = text_pos + strlen(text) + 1;
        }
        // our text saved in text variable
        // our text_pos now just have pos
        if (text_pos == NULL)
        {
            printf("invalid command\n");
            return;
        }
        strcpy(past_command , text_pos);
        char *pos = strtok(past_command , " ");
        if (strcmp(pos , "--pos") == 0)
        {
            past_command = past_command + strlen(pos) + 1;
            // edame darad .....
        }
        else
        {
            printf("invalid command\n");
            return;
        }
    }
    else
    {
        printf("invalid command\n");
        return;
    }
}

/*
 * Remember!
 * 1 - invalid commands must place at the end of the decide function!
 */