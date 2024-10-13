#include "parse-input.h"
#include "globals.h"

// Get user input, including spaces
status get_input() {
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), stdin);
    // Replace the last '\n' with '\0'
    buf[strlen(buf) - 1] = '\0';
    return strlen(buf);
}

// Parse user input and get command and its parameters
status parse() {
    int i, j;
    for (i = 0; i < MAX_CMD; i++) {
        for (j = 0; j < MAX_CMD_LEN; j++) {
            command[i][j] = '\0';
        }
    }
    argc = 0;
    int len = strlen(buf);
    for (i = 0, j = 0; i < len; i++) {
        if (buf[i] != ' ') {
            command[argc][j++] = buf[i];
        } else {
            if (j != 0) {
                command[argc][j] = '\0';
                argc++;
                j = 0;
            }
        }
    }
    if (j != 0) {
        command[argc++][j] = '\0';
    }
    return 0;
}
