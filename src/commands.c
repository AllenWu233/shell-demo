#include "commands.h"

void log_error(const char *cmd, const char *error_msg) {
    FILE *err_log = fopen(err_log_path, "a");
    if (err_log != NULL) {
        time_t now = time(NULL);
        char *time_str = ctime(&now);
        time_str[strlen(time_str) - 1] = '\0';
        fprintf(err_log, "[%s] Command: %s - Error: %s\n", time_str, cmd,
                error_msg);
        fclose(err_log);
    }
    fprintf(stderr, "%s: %s\n", cmd, error_msg);
}

Status pwd2() {
    char buf[BUFF_SIZE];
    getcwd(buf, sizeof(char) * BUFF_SIZE);
    printf("%s\n", buf);
    return OK;
}

Status cd_home() {
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

Status cd2(const char *path) {
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

Status ls2(const char *directory) {
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
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        if (entry->d_type == DT_DIR) {
            printf(" Dir: %s/\n", entry->d_name);
        } else {
            printf("File: %s\n", entry->d_name);
        }
    }

    closedir(dir);
    return OK;
}

Status touch2(const char *filename) {
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

Status echo2(const char *message) {
    if (message != NULL) {
        printf("%s\n", message);
    }
    return OK;
}

Status cat2(const char *filename) {
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

Status cp2(const char *src, const char *dest) {
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

Status rename2(const char *filename, const char *newname) {
    if (rename(filename, newname) != 0) {
        perror("rename2");
        return ERROR;
    }
    return OK;
}

Status rm2(const char *filename, Bool recursive) {
    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("rm2");
        return ERROR;
    }

    if (S_ISDIR(st.st_mode)) {
        if (recursive == FALSE) {
            fprintf(stderr, "rm2: cannot remove %s: Is a directory\n",
                    filename);
            return ERROR;
        }

        DIR *dir = opendir(filename);
        if (!dir) {
            perror("rm2");
            return ERROR;
        }

        struct dirent *entry;
        char full_path[MAX_PATH_LEN];
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0)
                continue;

            if (snprintf(full_path, sizeof(full_path), "%s/%s", filename,
                         entry->d_name) >= MAX_PATH_LEN) {
                perror("snprintf");
                return ERROR;
            }
            rm2(full_path, recursive);
        }
        closedir(dir);
        rmdir(filename);
    } else {
        unlink(filename);
    }
    return OK;
}

Status history2() {
    for (int i = 0; i < history_cnt; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
    return OK;
}
