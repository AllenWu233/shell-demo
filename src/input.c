#include "input.h"
#include "globals.h"

status add_to_history() {
    if (history_cnt >= MAX_HISTORY) {
        // Shift the history array to the left
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            memcpy(history[i], history[i + 1], sizeof(history[i]));
        }
        history_cnt--;
    }
    memcpy(history[history_cnt++], buf, sizeof(buf));
    return OK;
}

status get_input() {
    has_pipe = FALSE;
    has_redirect = FALSE;
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), stdin);
    if (strcmp(buf, "\n") == 0) { // Empty input
        return ERROR;
    }
    buf[strlen(buf) - 1] = '\0';

    add_to_history();

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
            if (buf[i] == '|')
                has_pipe = TRUE;
            if (buf[i] == '>')
                has_redirect = TRUE;
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
