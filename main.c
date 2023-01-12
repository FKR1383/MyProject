#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#define maximum_size_of_input 1000000

void main_function(); // this function is the input receiver of the program
void createfile(char *); // this function creates a .txt file with specified path
FILE *open_or_create_file(char * , char*); // this function open an existing file or creates a new file by supposed path
void insertstr(char *); // command 2
FILE *find_path(char * , char * , int *); // this function find path of a command
void find_string(char * , char * , int *); // this function find string after --str and saves it ro second argument

/*
 * first Name: Farzam
 * last Name: Koohi Ronaghi
 * student Id: 401106403
 */

int main()
{
    mkdir("root");
    while (1)
    {
        main_function();
    }
}

void main_function()
{
    char *input = (char *)calloc(maximum_size_of_input , sizeof(char));
    gets(input);
    strtok(input , " ");
    // checker is the first word of command
    if (strcmp(input , "createfile") == 0){
        createfile(input);
    } else if (strcmp(input , "insertstr") == 0) {
        insertstr(input);
    } //else if (){
    //}
    else {
        printf("invalid command\n");
    }
    free(input);
}

void createfile(char *command) {
    command = strtok(NULL, " ");
    if (command == NULL || strcmp(command, "--file") != 0) {
        printf("invalid command\n");
        return;
    }
    char *path = (char *) calloc(maximum_size_of_input, sizeof(char));
    path[0] = '\0';
    command = strtok(NULL , "");
    strcpy(path , command);
    FILE *file = open_or_create_file(path , "w");
    if (file != NULL) {
        fclose(file);
    }
}

FILE *open_or_create_file(char *path , char *type)
{
    if (path[0] == '\0')
    {
        printf("invalid command\n");
        return NULL;
    }
    if (path[0] == '/') {
        if (strlen(path) < 11) {
            printf("invalid address\n");
            return NULL;
        }
        if (path[1] == 'r' && path[2] == 'o' && path[3] == 'o' && path[4] == 't' && path[5] == '/' && path[strlen(path)-1] == 't' && path[strlen(path)-2] == 'x' && path[strlen(path)-3] == 't' && path[strlen(path)-4] == '.' && path[strlen(path)-5] != '/') {
            char *virual_path = (char *)calloc(strlen(path) , sizeof(char));
            virual_path[0] = '\0';
            path++;
            if (strcmp(type , "w") == 0 && access(path, F_OK) == 0) {
                printf("This file exists\n");
                return NULL;
            } else if (strcmp(type , "r+") == 0 && access(path, F_OK) == -1) {
                printf("This file doesn't exist\n");
                return NULL;
            }
            strtok(path , "/");
            while (path != NULL)
            {
                strcat(virual_path , path);
                path = strtok(NULL , "/");
                if (path != NULL) {
                    mkdir(virual_path);
                    strcat(virual_path, "/");
                }
            }
            return fopen(virual_path , type);
        } else {
            printf("invalid address\n");
            return NULL;
        }
    } else if (path[0] == '"' && path[strlen(path)-1] == '"') {
        path++;
        path[strlen(path)-1] = '\0';
        return open_or_create_file(path , type);
    } else {
        printf("invalid address\n");
        return NULL;
    }
}

void insertstr(char *command)
{
    command = strtok(NULL , "");
    char *resume = (char *) calloc(maximum_size_of_input , sizeof(char));
    strcpy(resume , command);
    strtok(command , " ");
    int skip;
    if (command == NULL || strcmp(command, "--file") != 0) {
        printf("invalid command\n");
        return;
    }
    FILE *file = find_path(command , "r+" , &skip);
    if (file == NULL) {
        return;
    }
    resume += (7 + skip);
    if (resume == NULL)
    {
        printf("invalid command\n");
        return;
    }
    resume++;
    if (resume == NULL) {
        printf("invalid command\n");
        return;
    }
    char *string = calloc(strlen(resume) + 1 , sizeof(char));
    find_string(resume , string , &skip);
    printf("%s\n" , string);
}

FILE *find_path(char *resume, char *type , int *skip)
{
    // this function starts with --file
    if (resume == NULL) {
        printf("invalid command\n");
        return NULL;
    }
    resume = strtok(NULL , "");
    if (resume == NULL)
    {
        printf("invalid command\n");
        return NULL;
    }
    if (resume[0] == '/') {
        strtok(resume , " ");
        char *path = (char *) calloc(strlen(resume)+1 , sizeof(char));
        strcpy(path , resume);
        *skip = strlen(path);
        return open_or_create_file(path , type);
    }
    if (resume[0] == '\"') {
        char *path = (char *) calloc(maximum_size_of_input , sizeof(char));
        int i = 0;
        for (; ; i++)
        {
            path[i] = resume[i];
            if (path[i] == '\"' && i != 0)
                break;
        }
        path[i+1] = '\0';
        *skip = strlen(path);
        return open_or_create_file(path , type);
    }
}

void find_string(char *resume , char *string , int *skip)
{
    // this function starts with --str
    strtok(resume , " ");
    if (resume == NULL || strcmp(resume , "--str") != 0) {
        printf("invalid command\n");
        return;
    }
    resume = strtok(NULL , "");
    if (resume == NULL){
        printf("invalid command\n");
        return;
    }
    if (resume[0] != '\"') {
        strcpy(string , strtok(resume , " "));
        *skip = strlen(string);
        return;
    }
    else {
        int i = 0;
        for (; ; i++)
        {
            string[i] = resume[i+1];
            if (string[i] == '\"' && i != 0) {
                if (string[i-1] != '\\')
                    break;
                else {

                }
            }
        }
        string[i] = '\0';
        *skip = strlen(string);
        return;
    }
}