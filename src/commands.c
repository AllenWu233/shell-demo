#include "commands.h"

status pwd2() {
    char buf[BUFF_SIZE];
    getcwd(buf, sizeof(char) * BUFF_SIZE);
    printf("%s\n", buf);
    return 0;
}

status cd_home() {
    char *home = getenv("HOME");

    if (home == NULL) {
        fprintf(stderr, "HOME environment variable not set\n");
        return ERROR;
    }

    if (chdir(home) != 0) {
        perror("chdir");
    }
    return OK;
}

status cd2(const char *path) {
    // if () {
    //     perror("-shell-demo: cd2: too many arguments\n");
    //     return ERROR;
    // }
    if (path == NULL) {
        return cd_home();
    } else if (strcmp(path, "-") == 0) {
        if (chdir("..") != 0) {
            perror("cd2");
            return ERROR;
        }
    }
    // else if (strcmp(path, "") == 0) {
    //     return cd_home();
    //     }
    else {
        if (chdir(path) != 0) {
            perror("cd2");
            return ERROR;
        }
    }
    return OK;
}

status ls2(const char *directory) {
    DIR *dir;
    struct dirent *entry;
    if (directory == NULL) {
        dir = opendir(".");
    }

    dir = opendir(directory);
    if (dir == NULL) {
        perror("ls2");
        return ERROR;
    }

    printf("Listing contents of directory '%s':\n", directory);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            printf(" Dir: %s/\n", entry->d_name);
        } else {
            printf("File: %s\n", entry->d_name);
        }
    }

    closedir(dir);
    return OK;
}

status execute_command() {
    if (strcmp(command[0], "pwd2") == 0) {
        pwd2();
    } else if (strcmp(command[0], "cd2") == 0) {
        cd2(command[1]);
    } else if (strcmp(command[0], "ls2") == 0) {
        ls2(command[1]);
    }
    // } else if (strcmp(command[0], "touch2") == 0) {
    //     touch2();
    // } else if (strcmp(command[0], "echo2") == 0) {
    //     echo2();
    // } else if (strcmp(command[0], "cat2") == 0) {
    //     cat2();
    // } else if (strcmp(command[0], "cp2") == 0) {
    //     cp2();
    // } else if (strcmp(command[0], "rm2") == 0) {
    //     rm2();
    // } else if (strcmp(command[0], "rename2") == 0) {
    //     rename2();
    // } else if (strcmp(command[0], "history2") == 0) {
    //     history2();
    // } else {
    //     ;
    // }
    return OK;
}
