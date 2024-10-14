#ifndef GLOBALS_H
#define GLOBALS_H

#include "constants.h"

extern char buf[BUFF_SIZE];                // Buffer to store the input command
extern char current_path[BUFF_SIZE];       // Current working directory
extern char command[MAX_CMD][MAX_CMD_LEN]; // Array to store the parsed tokens
extern int
    argc; // Counter to keep track of the number of tokens. '|' and '>' are
          // treated as separate tokens regardless of surrounding spaces

#endif
