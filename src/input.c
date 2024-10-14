#include "input.h"
#include "globals.h"

status get_input() {
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), stdin);
    // Replace the last '\n' with '\0'
    buf[strlen(buf) - 1] = '\0';
    if (strcmp(buf, "quit") == 0 || strcmp(buf, "exit") == 0) {
        return QUIT;
    }
    return OK;
}

status parse_input() {
    // Reset the command array and token counter
    memset(command, 0, sizeof(command));
    argc = 0;

    int len = strlen(buf);
    int i, j;
    for (i = 0, j = 0; i < len; i++) {
        if (buf[i] == '|' || buf[i] == '>') {
            // If there was a token being built, end it and start a new token
            // for '|' or '>'
            if (j > 0) {
                command[argc++][j] = '\0';
                j = 0;
            }
            // Treat '|' or '>' as separate tokens
            command[argc][0] = buf[i];
            command[argc++][1] = '\0';
        } else if (buf[i] != ' ') {
            command[argc][j++] = buf[i];
        } else if (j > 0) { // Space after a non-space character
            // If there was a token being built, end it
            command[argc++][j] = '\0';
            j = 0;
        }
    }

    // Add the last token if there are characters left
    if (j > 0) {
        command[argc++][j] = '\0';
    }

    return OK;
}
