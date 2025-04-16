#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TASKS 100

void main() {
    FILE *data = fopen("./Data/data.txt", "w");
    FILE *index_data = fopen("./Data/index_data.txt", "w");
    FILE *index_status = fopen("./Data/index_status.txt", "w");

    if (data == NULL || index_data == NULL || index_status == NULL) {
        printf("Error opening files!\n");
        return;
    }

    char task[256];
    char status[256];

    for (int i = 0; i < NUM_TASKS; i++) {
        snprintf(task, sizeof(task), "Task %d", i + 1);

        if (i % 2 == 0) {
            snprintf(status, sizeof(status), "Not Yet Started");
        } else {
            snprintf(status, sizeof(status), "Done");
        }

        long offset = ftell(data);


        fprintf(data, "%s|%s,\n", task,status);

        fprintf(index_data, "%ld|%s,\n", offset, task);


        fprintf(index_status, "%ld|%s,\n", offset, status);
    }

    fclose(data);
    fclose(index_data);
    fclose(index_status);

    printf("Successfully added %d tasks and statuses.\n", NUM_TASKS);
}
