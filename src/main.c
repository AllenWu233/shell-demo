#include "parse-input.h"
#include <stdio.h>

char buf[BUFF_SIZE];
char current_path[BUFF_SIZE];
char command[MAX_CMD][MAX_CMD_LEN];
int argc;

int run() {
    while (1) {
        // Print path in prompt
        // memset(current_path, 0, BUFF_SIZE);
        // getcwd(current_path, sizeof(current_path));
        // printf("[user@shelldemo: %s]%% ", current_path);
        // Get user input
        get_input();
#ifdef DEBUG
        printf("[Debug]user input: %s\n", buf);
#endif

        parse();
#ifdef DEBUG
        printf("[Debug]argc: %d\n", argc);
        for (int i = 0; i < argc; i++) {
            printf("[Debug]command[%d]: %s\n", i, command[i]);
        }
#endif
    }
    return 0;
}

int main() {
    printf("===== Welcome to Allen's shell demo! =====\n");
    run();
    printf("===== Goodbye from shell demo! =====\n");
    return 0;
}
