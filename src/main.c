#include "commands.h"
#include "constants.h"
#include "input.h"
#include <stdio.h>

char buf[BUFF_SIZE];
char current_path[MAX_PATH_LEN];
char original_path[MAX_PATH_LEN];
char err_log_path[MAX_PATH_LEN];
char cmd_line[MAX_CMD][MAX_CMD_LEN];
char history[MAX_HISTORY][BUFF_SIZE];
char *argv[MAX_CMD];
int argc;
int history_cnt;
Bool has_pipe;
Bool has_redirect;

const char *const redirect_str[] = {"NONE", "APPEND", "WRITE", "ERR_RDCT"};

// Print current path in prompt
void print_prompt() {
    memset(current_path, 0, MAX_PATH_LEN);
    getcwd(current_path, sizeof(current_path));
    printf("[%s@shelldemo: %s]%% ", getenv("USER"), current_path);
}

void run() {
    while (1) {
        print_prompt();
        // Get user input
        if (get_input() == QUIT) {
            return;
        }
#ifdef DEBUG
        // fprintf(stderr, "[Debug]user input: %s\n", buf);
#endif

        parse_input();
#ifdef DEBUG
        fprintf(stderr, "[Debug]argc: %d\n", argc);
        for (int i = 0; i < argc; i++) {
            // fprintf(stderr, "[Debug]cmd_line[%d]: %s\n", i, cmd_line[i]);
            fprintf(stderr, "[Debug]argv[%d]: %s\n", i, *(argv + i));
        }
        Redirect type = parse_redirect(argc, argv);
        fprintf(stderr, "[Debug]redirect type: %s\n", redirect_str[type]);
        char *filename = get_redirect_filename(argc, argv);
        fprintf(stderr, "[Debug]redirect filename: %s\n", filename);
#endif

        execute_command(argc, argv);
    }
}

int main() {
    memset(history, 0, sizeof(history));
    argc = 0;
    history_cnt = 0;
    has_pipe = FALSE;
    has_redirect = FALSE;

    // Save original path
    getcwd(original_path, sizeof(char) * BUFF_SIZE);
    // Set error log path
    if (snprintf(err_log_path, MAX_PATH_LEN, "%s/.shelldemo_err.log",
                 original_path) >= MAX_PATH_LEN) {
        fprintf(stderr,
                "-shell-demo: Error: Path too long for error log file\n");
    }

    printf("===== Welcome to Allen's shell demo! =====\n");
    if (cd_home() == ERROR) {
        printf("Use current directory as working directory");
    }
#ifdef DEBUG
    system("mkdir /tmp/test");
    cd2("/tmp/test");
#endif
    run();
    printf("===== Goodbye from shell demo! =====\n");
}
