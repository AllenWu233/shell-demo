#include "execute.h"

Status execute_external_command(char *argv[]) {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        log_error(argv[0], "failed to create pipe");
        return ERROR;
    }

    pid_t pid = fork();
    if (pid == -1) {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        log_error(argv[0], "fork failed");
        return ERROR;
    }

    if (pid == 0) {        // Child process
        close(pipe_fd[0]); // Close read end

        // Redirect stderr to pipe
        dup2(pipe_fd[1], STDERR_FILENO);
        close(pipe_fd[1]);

        execvp(argv[0], argv);

        // If execvp returns, it failed
        char error_msg[256];
        snprintf(error_msg, sizeof(error_msg), "failed to execute: %s",
                 strerror(errno));
        log_error(argv[0], error_msg);
        exit(1);
    } else {               // Parent process
        close(pipe_fd[1]); // Close write end

        // Read error output from child
        char buffer[4096];
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1);
        close(pipe_fd[0]);

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0) {
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';
                    // Remove trailing newline if present
                    if (buffer[bytes_read - 1] == '\n') {
                        buffer[bytes_read - 1] = '\0';
                    }
                    log_error(argv[0], buffer);
                } else {
                    char error_msg[256];
                    snprintf(error_msg, sizeof(error_msg),
                             "command failed with exit code %d", exit_status);
                    log_error(argv[0], error_msg);
                }
                return ERROR;
            }
        } else if (WIFSIGNALED(status)) {
            char error_msg[256];
            snprintf(error_msg, sizeof(error_msg),
                     "command terminated by signal %d", WTERMSIG(status));
            log_error(argv[0], error_msg);
            return ERROR;
        }
    }
    return OK;
}

Status execute_normal_command(int argc, char *argv[]) {
    if (argc <= 0 || argv == NULL) {
        fprintf(stderr, "-shell-demo: no command given\n");
    }
    // Ensure the argv are correctly terminated
    argv[argc] = NULL;

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
        // if (system(buf) != 0) {
        //     log_error(cmd, "unknown error");
        //     return ERROR;
        // }
        if (execute_external_command(argv) == ERROR) {
            return ERROR;
        }
    }

    return OK;
}

Status execute_command_with_redirect(int argc, char *argv[]) {
    Status result;

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
}

Status execute_command_with_pipe(int argc, char *argv[]) {}

Status execute_command(int argc, char *argv[]) {
    if (has_pipe == TRUE) {
        return execute_command_with_pipe(argc, argv);
    } else if (has_redirect == TRUE) {
        return execute_command_with_redirect(argc, argv);
    } else {
        return execute_normal_command(argc, argv);
    }
}
