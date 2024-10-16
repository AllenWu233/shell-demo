#ifndef COMMANDS_H
#define COMMANDS_H

#include "constants.h"
#include "globals.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utime.h>

// Change to home directory
status cd_home();

// Print working directory
status pwd2();

// Change directory
// Usage: cd [path]
// If no path is provided, change to home directory.
// If path is provided, change to that directory.
// 'cd -' will change to the previous directory.
status cd2(const char *path);

// List directory contents
// Usage: ls [directory]
// If no directory is provided, list contents of current directory.
status ls2(const char *directory);

// Create a new file
// Usage: touch [file]
status touch2(const char *filename);

status echo2();
status cat2();
status cp2();
status rm2();
status rename2();
status history2();

status execute_command();

#endif
