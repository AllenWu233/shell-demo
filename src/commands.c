#include "commands.h"
#include "globals.h"

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
    } else {
        dir = opendir(directory);
    }

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

status history2() {
    for (int i = 0; i < history_cnt; i++) {
        printf("%d: %s\n", i + 1, historys[i]);
    }
    return OK;
}

status execute_command() {
    if (argc == 0) {
        fprintf(stderr, "-shell-demo: no command given\n");
    }

    char *cmd = command[0];
    if (has_pipe == FALSE && has_redirect == FALSE) {
        if (strcmp(cmd, "pwd2") == 0) {
            if (argc > 1) {
                fprintf(stderr, "pwd2: too many arguments\n");
                return ERROR;
            }
            pwd2();
        } else if (strcmp(cmd, "cd2") == 0) {
            if (argc == 1) {
                cd2(NULL);
            } else if (argc == 2) {
                cd2(command[1]);
            } else {
                fprintf(stderr, "cd2: too many arguments\n");
                return ERROR;
            }
        } else if (strcmp(cmd, "ls2") == 0) {
            if (argc == 1) {
                ls2(NULL);
            } else if (argc == 2) {
                ls2(command[1]);
            } else {
                fprintf(stderr, "ls2: too many arguments\n");
                return ERROR;
            }
        } else if (strcmp(cmd, "history2") == 0) {
            if (argc > 1) {
                fprintf(stderr, "history2: too many arguments\n");
                return ERROR;
                history2();
            }
        } else {
            ;
        }
    }
    return OK;
}
