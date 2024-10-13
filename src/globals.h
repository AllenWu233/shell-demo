#ifndef GLOBALS_H
#define GLOBALS_H

#include "constants.h"

extern char buf[BUFF_SIZE];
extern char current_path[BUFF_SIZE];
extern char command[MAX_CMD][MAX_CMD_LEN];
// Arguments number of a command (including command name itself)
// '|' and '<' are treated as arguments when parsing
extern int argc;

#endif
