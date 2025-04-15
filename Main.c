#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "List.h"
#include "DisplayFiles.h"

int main() {
    char input[256]; 
    char **args = malloc(10 * sizeof(char *)); 
    if (!args) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    
    char *cwd = getcwd(NULL, 0);    
    if (cwd == NULL) {
        perror("getcwd failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        char prompt[512];
        snprintf(prompt, sizeof(prompt), "%s </> ", cwd);
        char *input = readline(prompt);
        if (input == NULL) {
            break; 
        }

        if (strlen(input) > 0) {
            add_history(input); 
        }
        input[strcspn(input, "\n")] = '\0';

        int i = 0;
        args[i] = strtok(input, " ");
        
        while (args[i] != NULL) {
            i++;
            
            if (i >= 10) {
                args = realloc(args, (i + 1) * sizeof(char *)); 
                if (!args) {
                    perror("realloc failed");
                    exit(EXIT_FAILURE);
                }
            }
            args[i] = strtok(NULL, " ");
        }

        if (args[0] == NULL) {
            continue;
        }

        if (strcmp(args[0], "ls") == 0) {
            list_directories(cwd);
        }
        else if (strcmp(args[0], "cd") == 0) {
            if (args[1] != NULL) {
                if (chdir(args[1]) == 0) {
                    cwd = getcwd(NULL, 0);
                } else {
                    perror("cd failed");
                }
            } else {
                printf("Usage: cd <directory>\n");
            }
        }
        else if (strcmp(args[0], "cat") == 0) {
            if (args[1] != NULL) {
                cat_command(args[1]);
            } else {
                printf("Usage: cat <filename>\n");
            }
        }
        else if (strcmp(args[0], "clear") == 0) {
            system("clear");
        }
        else if (strcmp(args[0], "exit") == 0) {
            break;
        }
        else {
            printf("%s: command not found\n", args[0]);
        }
    }

    free(args);
    free(cwd);
    return 0;
}