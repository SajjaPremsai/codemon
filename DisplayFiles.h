#include<stdio.h>
#include<stdlib.h>

void cat_command(const char *filename){
    FILE *file = fopen(filename,"r");
    if(file == NULL){
        perror("cat");
        return;
    }
    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }
    printf("\n");
    fflush(stdout);
    fclose(file);
}