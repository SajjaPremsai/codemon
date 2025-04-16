#include <stdio.h>
#include <stdlib.h>

void main() {
    FILE *data = fopen("data.txt", "w");
    FILE *index_data = fopen("index_data.txt", "w");
    FILE *index_status = fopen("index_status.txt", "w");

    if (data == NULL || index_data == NULL || index_status == NULL) {
        printf("Error opening files!\n");
        return;
    }

    char *tasks[] = {"Task 1", "Task 2"};
    char *statuses[] = {"Not Yet Started", "Done"};

    for (int i = 0; i < 2; i++) {
        long offset = ftell(data);

        fprintf(data, "%s\n", tasks[i]);

        fprintf(index_data, "%ld|%s\n", offset, tasks[i]);

        fprintf(index_status, "%ld|%s\n", offset, statuses[i]);
    }

    fclose(data);
    fclose(index_data);
    fclose(index_status);
}
