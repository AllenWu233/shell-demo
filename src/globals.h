#ifndef GLOBALS_H
#define GLOBALS_H

#include "constants.h"

extern char buf[BUFF_SIZE];                // Buffer to store the input command
extern char current_path[BUFF_SIZE];       // Current working directory
extern char command[MAX_CMD][MAX_CMD_LEN]; // Array to store the parsed tokens
extern int
    argc; // Counter to keep track of the number of tokens. '|' and '>' are
          // treated as separate tokens regardless of surrounding spaces
extern char history[MAX_HISTORY]
                   [BUFF_SIZE]; // Array to store the history of commands
extern int history_cnt;  // Counter to keep track of the number of commands in
                         // the history
extern boolean has_pipe; // Flag to indicate if there is a pipe in the command
extern boolean
    has_redirect; // Flag to indicate if there is a redirect in the command

#endif
