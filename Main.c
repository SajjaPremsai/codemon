#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>



#include "List.h"

void main(){
    char input[256];
    char command[256], args[256];

    char * cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        perror("getcwd failed");
        exit(EXIT_FAILURE);
    }

    while(1){
        printf("%s </> ", cwd); 
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  

        int args_count = sscanf(input, "%s %s", command, args);
        if (args_count == 0) {
            continue;  // Ignore empty input
        }

        if (strcmp(command, "ls") == 0) {
            list_directories(cwd);  
        }

        if (strcmp(command, "cd") == 0) {
            if (chdir(args) == 0) {
                cwd = getcwd(NULL, 0);
            } else {
                perror("cd failed");
            }
        }

        if (strcmp(command, "clear") == 0) {
            system("clear");  
        }

        if (strcmp(command, "exit") == 0) {
            break; 
        }
    }
}