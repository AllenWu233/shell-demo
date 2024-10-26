#include "input.h"
#include "globals.h"

Status add_to_history() {
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

Status get_input() {
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

Status parse_input() {
    // Reset the command array and token counter
    memset(cmd_line, 0, sizeof(cmd_line));
    memset(argv, 0, sizeof(argv));
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
                cmd_line[argc][j] = '\0';
                argv[argc] = cmd_line[argc];
                argc++;
                j = 0;
            }
            // Treat '|' or '>' as separate tokens
            cmd_line[argc][0] = buf[i];
            cmd_line[argc][1] = '\0';
            argv[argc] = cmd_line[argc];
            argc++;
        } else if (buf[i] != ' ') {
            cmd_line[argc][j++] = buf[i];
        } else if (j > 0) { // Space after a non-space character
            // If there was a token being built, end it
            cmd_line[argc][j] = '\0';
            argv[argc] = cmd_line[argc];
            argc++;
            j = 0;
        }
    }

    // Add the last token if there are characters left
    if (j > 0) {
        cmd_line[argc][j] = '\0';
        argv[argc] = cmd_line[argc];
        argc++;
    }

    return OK;
}

Redirect parse_redirect(int argc, char *argv[]) {
    if (has_redirect == FALSE) {
        return NONE;
    }

    int cnt = 0;
    Redirect redirect_type = NONE;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], ">") == 0) {
            if (cnt > 0) {
                if (redirect_type == WRITE && strcmp(argv[i - 1], ">") == 0 &&
                    i == argc - 2) {
                    redirect_type = APPEND;
                } else {
                    return ERR_RDCT;
                }
            }
            if (redirect_type == NONE) {
                redirect_type = WRITE;
            }
            cnt++;
        }
    }

    if (redirect_type == WRITE && strcmp(argv[argc - 2], ">") != 0) {
        redirect_type = ERR_RDCT;
    }
    return redirect_type;
}

char *get_redirect_filename(int argc, char *argv[]) {
    if (argc >= 3 && strcmp(argv[argc - 2], ">") == 0) {
        return argv[argc - 1];
    }
    return NULL;
}

Bool parse_pipe() { return TRUE; }
