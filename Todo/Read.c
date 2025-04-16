#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 512


void trim_trailing_comma(char *str) {
    int len = strlen(str);
    if (str[len - 1] == ',') {
        str[len - 1] = '\0';  
    }
}


void search_by_task(const char *task_name) {
    FILE *data = fopen("./Data/data.txt", "r");
    FILE *index_data = fopen("./Data/index_data.txt", "r");

    if (data == NULL || index_data == NULL) {
        printf("Error opening files!\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    long offset;
    char task[MAX_LINE_LENGTH];
    char status[MAX_LINE_LENGTH];

    while (fscanf(index_data, "%ld|%[^,],\n", &offset, task) != EOF) {
        trim_trailing_comma(task); 

        // printf("Checking task: %s\n", task);  
        if (strcmp(task, task_name) == 0) {

            fseek(data, offset, SEEK_SET);
            fgets(line, sizeof(line), data); 


            sscanf(line, "%[^|]|%s", task, status);
            printf("Task: %s Status: %s\n", task, status);
        }
    }

    fclose(data);
    fclose(index_data);
}


void search_by_status(const char *status_name) {
    FILE *data = fopen("./Data/data.txt", "r");
    FILE *index_status = fopen("./Data/index_status.txt", "r");

    if (data == NULL || index_status == NULL) {
        printf("Error opening files!\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    long offset;
    char task[MAX_LINE_LENGTH];
    char status[MAX_LINE_LENGTH];

    while (fscanf(index_status, "%ld|%[^,],\n", &offset, status) != EOF) {
        trim_trailing_comma(status);  

        // printf("Checking status: %s\n", status); 
        if (strcmp(status, status_name) == 0) {

            fseek(data, offset, SEEK_SET);
            fgets(line, sizeof(line), data); 


            sscanf(line, "%[^|]|%s", task, status);
            printf("Task: %s Status: %s\n", task, status);
        }
    }

    fclose(data);
    fclose(index_status);
}


void search_by_task_and_status(const char *task_name, const char *status_name) {
    FILE *data = fopen("./Data/data.txt", "r");
    FILE *index_data = fopen("./Data/index_data.txt", "r");
    FILE *index_status = fopen("./Data/index_status.txt", "r");

    if (data == NULL || index_data == NULL || index_status == NULL) {
        printf("Error opening files!\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    long offset;
    char task[MAX_LINE_LENGTH];
    char status[MAX_LINE_LENGTH];

    while (fscanf(index_data, "%ld|%[^,],\n", &offset, task) != EOF) {
        trim_trailing_comma(task); 

        // printf("Checking task: %s\n", task); 
        if (strcmp(task, task_name) == 0) {

            fseek(data, offset, SEEK_SET);
            fgets(line, sizeof(line), data);  

            
            sscanf(line, "%[^|]|%s", task, status);

            if (strcmp(status, status_name) == 0) {
                printf("Task: %s Status: %s\n", task, status);
            }
        }
    }

    fclose(data);
    fclose(index_data);
    fclose(index_status);
}

int main() {

    const char *task_name = "Task 2";  
    const char *status_name = "Done";  


    // printf("\nSearching by Task Name:\n");
    // search_by_task(task_name);


    printf("\nSearching by Status Name:\n");
    search_by_status(status_name);

    // printf("\nSearching by Task and Status:\n");
    // search_by_task_and_status(task_name, status_name);

    return 0;
}
