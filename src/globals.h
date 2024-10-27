#ifndef GLOBALS_H
#define GLOBALS_H

#include "constants.h"

extern char buf[BUFF_SIZE];              // Buffer to store the input command
extern char original_path[MAX_PATH_LEN]; // Original working directory]
extern char current_path[MAX_PATH_LEN];  // Current working directory
extern char err_log_path[MAX_PATH_LEN];
extern char cmd_line[MAX_CMD][MAX_CMD_LEN]; // Array to store the parsed tokens
extern char *argv[MAX_CMD];
extern int
    argc; // Counter to keep track of the number of tokens. '|' and '>' are
          // treated as separate tokens regardless of surrounding spaces
extern char history[MAX_HISTORY]
                   [BUFF_SIZE]; // Array to store the history of commands
extern int history_cnt; // Counter to keep track of the number of commands in
                        // the history
extern Bool has_pipe;   // Flag to indicate if there is a pipe in the command
extern Bool
    has_redirect; // Flag to indicate if there is a redirect in the command

#endif
