#include "commands.h"
#include "input.h"
#include <stdio.h>

char buf[BUFF_SIZE];
char current_path[BUFF_SIZE];
char command[MAX_CMD][MAX_CMD_LEN];
int argc;

// Print current path in prompt
void print_prompt() {
    memset(current_path, 0, BUFF_SIZE);
    getcwd(current_path, sizeof(current_path));
    printf("[user@shelldemo: %s]%% ", current_path);
}

void run() {
    while (1) {
        print_prompt();
        // Get user input
        if (get_input() == QUIT) {
            return;
        }
#ifdef DEBUG
        printf("[Debug]user input: %s\n", buf);
#endif

        parse_input();
#ifdef DEBUG
        printf("[Debug]argc: %d\n", argc);
        for (int i = 0; i < argc; i++) {
            printf("[Debug]command[%d]: %s\n", i, command[i]);
        }
#endif

        execute_command();
    }
}

int main() {
    printf("===== Welcome to Allen's shell demo! =====\n");
    cd_home();
    run();
    printf("===== Goodbye from shell demo! =====\n");
    return 0;
}
