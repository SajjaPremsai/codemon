#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void list_directories(char * dir_path){
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    // return 1;
    closedir(dir);
}