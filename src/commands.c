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
    } else {
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

status touch2(const char *filename) {
    if (filename == NULL) {
        fprintf(stderr, "touch2: missing filename\n");
        return ERROR;
    }

    if (utime(filename, NULL) != 0) {
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("touch2");
            return ERROR;
        }
        fclose(file);
    }

    return OK;
}

status echo2(const char *message) {
    printf("%s\n", message);
    return OK;
}

status history2() {
    for (int i = 0; i < history_cnt; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
    return OK;
}

status cat2(const char *filename) {
    FILE *file;
    char ch;

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("cat2");
        return ERROR;
    }
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
    return OK;
}

status cp2(const char *src, const char *dest) {
    FILE *source, *target;
    char ch;

    source = fopen(src, "rb");
    if (source == NULL) {
        perror("cp2");
        return ERROR;
    }

    target = fopen(dest, "wb");
    if (target == NULL) {
        fclose(source);
        perror("cp2");
        return ERROR;
    }

    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, target);
    }

    fclose(source);
    fclose(target);
    return OK;
}

status rename2(const char *filename, const char *newname) {
    if (rename(filename, newname) != 0) {
        perror("rename2");
        return ERROR;
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
            return pwd2();
        } else if (strcmp(cmd, "cd2") == 0) {
            if (argc == 1) {
                return cd2(NULL);
            } else if (argc == 2) {
                return cd2(command[1]);
            } else {
                fprintf(stderr, "cd2: too many arguments\n");
                return ERROR;
            }
        } else if (strcmp(cmd, "ls2") == 0) {
            if (argc == 1) {
                return ls2(NULL);
            } else if (argc == 2) {
                return ls2(command[1]);
            } else {
                fprintf(stderr, "ls2: too many arguments\n");
                return ERROR;
            }
        } else if (strcmp(cmd, "touch2") == 0) {
            if (argc == 1) {
                fprintf(stderr, "touch2: missing filename\n");
            } else if (argc == 2) {
                return touch2(command[1]);
            } else {
                fprintf(stderr, "touch2: too many arguments\n");
                return ERROR;
            }
        } else if (strcmp(cmd, "echo2") == 0) {
            if (argc == 1) {
                return echo2("");
            } else if (has_pipe == FALSE && has_redirect == FALSE) {
                char *message = buf + 6; // Remove "echo2 "
                return echo2(message);
            }
        } else if (strcmp(cmd, "cat2") == 0) {
            if (argc == 1) {
                fprintf(stderr, "cat2: missing filename\n");
                return ERROR;
            }
            return cat2(command[1]);
        } else if (strcmp(cmd, "cp2") == 0) {
            if (argc <= 2) {
                fprintf(stderr, "cp2: too few arguments\n");
                return ERROR;
            } else if (argc == 3) {
                return cp2(command[1], command[2]);
            } else {
                fprintf(stderr, "cp2: too many arguments\n");
                return ERROR;
            }
        } else if (strcmp(cmd, "rm2") == 0) {
            if (argc <= 2) {
                fprintf(stderr, "rm2: too few arguments\n");
                return ERROR;
            } else if (argc == 3) {
                // return rm2(command[1], command[2]);
            } else {
                fprintf(stderr, "rm2: too many arguments\n");
                return ERROR;
            }
        } else if (strcmp(cmd, "rename2") == 0) {
            if (argc <= 2) {
                fprintf(stderr, "rename2: too few arguments\n");
                return ERROR;
            } else if (argc == 3) {
                return rename2(command[1], command[2]);
            } else {
                fprintf(stderr, "rename2: too many arguments\n");
                return ERROR;
            }
        }

        else if (strcmp(cmd, "history2") == 0) {
            if (argc > 1) {
                fprintf(stderr, "history2: too many arguments\n");
                return ERROR;
            }
            history2();
        } else {
            ;
        }
    }
    return OK;
}
