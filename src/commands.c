#include "commands.h"
#include "constants.h"
#include "globals.h"
#include "input.h"

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

Status execute_normal_command(int argc, char *argv[]) {
    if (argc <= 0 || argv == NULL) {
        fprintf(stderr, "-shell-demo: no command given\n");
    }

    char *cmd = argv[0];
    if (strcmp(cmd, "pwd2") == 0) {
        if (argc > 1) {
            // fprintf(stderr, "pwd2: too many arguments\n");
            log_error("pwd2", "too many arguments");
            return ERROR;
        }
        if (pwd2() == ERROR) {
            log_error("pwd2", "unknown error");
            return ERROR;
        }
    }

    else if (strcmp(cmd, "cd2") == 0) {
        if (argc == 1) {
            if (cd2(NULL) == ERROR) {
                log_error("cd2", "cannot change to home directory");
                return ERROR;
            }
        } else if (argc == 2) {
            if (cd2(argv[1]) == ERROR) {
                log_error("cd2", "cannot change to the directory");
                return ERROR;
            }
        } else {
            log_error("cd2", "too many arguments");
            return ERROR;
        }
    }

    else if (strcmp(cmd, "ls2") == 0) {
        if (argc == 1) {
            if (ls2(NULL) == ERROR) {
                log_error("ls2", "cannot list current directory");
                return ERROR;
            }
        } else if (argc == 2) {
            if (ls2(argv[1]) == ERROR) {
                log_error("ls2", "cannot list the directory");
                return ERROR;
            }
        } else {
            log_error("ls2", "too many arguments");
            return ERROR;
        }
    }

    else if (strcmp(cmd, "touch2") == 0) {
        if (argc == 1) {
            log_error("touch2", "missing file name");
            return ERROR;
        } else if (argc == 2) {
            if (touch2(argv[1]) == ERROR) {
                log_error("touch2", "cannot create file");
                return ERROR;
            }
        } else {
            log_error("touch2", "too many arguments");
            return ERROR;
        }
    }

    else if (strcmp(cmd, "echo2") == 0) {
        if (argc == 1) {
            if (echo2(NULL) == ERROR) {
                log_error("echo2", "unknown error");
                return ERROR;
            }
        } else if (argc == 2) {
            if (echo2(argv[1]) == ERROR) {
                log_error("echo2", "unknown error");
                return ERROR;
            }
        } else {
            log_error("echo2", "too many arguments");
            return ERROR;
        }
    }

    else if (strcmp(cmd, "cat2") == 0) {
        if (argc == 1) {
            log_error("cat2", "missing file name");
            return ERROR;
        }
        if (cat2(argv[1]) == ERROR) {
            log_error("cat2", "cannot read file");
            return ERROR;
        }
    }

    else if (strcmp(cmd, "cp2") == 0) {
        if (argc <= 2) {
            log_error("cp2", "too few arguments");
            return ERROR;
        } else if (argc == 3) {
            if (cp2(argv[1], argv[2]) == ERROR) {
                log_error("cp2", "cannot copy file");
                return ERROR;
            }
        } else {
            log_error("cp2", "too many arguments");
            return ERROR;
        }
    }

    else if (strcmp(cmd, "rm2") == 0) {
        if (argc == 1) {
            log_error("rm2", "missing file name");
            return ERROR;
        } else if (argc == 2) {
            if (strcmp(argv[1], "-r") == 0) {
                log_error("rm2", "missing directory name");
                return ERROR;
            }
            if (rm2(argv[1], FALSE) == ERROR) {
                log_error("rm2", "cannot remove file");
                return ERROR;
            }
        } else if (argc == 3 && strcmp(argv[1], "-r") == 0) {
            if (rm2(argv[2], TRUE) == ERROR) {
                log_error("rm2", "cannot remove directory");
                return ERROR;
            }
        } else {
            log_error("rm2", "too many arguments");
            return ERROR;
        }
    }

    else if (strcmp(cmd, "rename2") == 0) {
        if (argc <= 2) {
            log_error("rename2", "too few arguments");
            return ERROR;
        } else if (argc == 3) {
            if (rename2(argv[1], argv[2]) == ERROR) {
                log_error("rename2", "cannot rename file");
            }
        } else {
            log_error("rename2", "too many arguments");
            return ERROR;
        }
    }

    else if (strcmp(cmd, "history2") == 0) {
        if (argc > 1) {
            log_error("history2", "too many arguments");
            return ERROR;
        }
        if (history2() == ERROR) {
            log_error("history2", "unknown error");
        }
    }

    // If command is not recognized, execute it as a system command
    else {
        if (system(buf) != 0) {
            log_error(cmd, "unknown error");
            return ERROR;
        }
    }

    return OK;
}

Status execute_command(int argc, char *argv[]) {
    Status result;

    if (has_pipe == TRUE) {
        return OK;
    } else if (has_redirect == TRUE) {
        Redirect redirect_type = parse_redirect(argc, argv);
        char *filename = get_redirect_filename(argc, argv);

        // Save original stdout
        int stdout_copy = dup(STDOUT_FILENO);
        if (stdout_copy == -1) {
            perror("dup");
            return ERROR;
        }

        int flags = O_WRONLY | O_CREAT;
        if (redirect_type == WRITE) {
            flags |= O_TRUNC;
        } else {
            flags |= O_APPEND;
        }

        int fd = open(filename, flags, 0644);
        if (fd == -1) {
            perror("Redirection failed");
            close(stdout_copy);
            return ERROR;
        }

        // Redirect stdout to the file
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            close(fd);
            close(stdout_copy);
            return ERROR;
        }

        if (redirect_type == WRITE) {
            result = execute_normal_command(argc - 2, argv);
        } else {
            result = execute_normal_command(argc - 3, argv);
        }

        // Restore original stdout
        if (dup2(stdout_copy, STDOUT_FILENO) == -1) {
            perror("dup2");
            result = ERROR;
        }

        close(fd);
        close(stdout_copy);

        return result;

    } else {
        return execute_normal_command(argc, argv);
    }
}
