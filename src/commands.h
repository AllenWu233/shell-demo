#ifndef COMMANDS_H
#define COMMANDS_H

#include "constants.h"
#include "globals.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>

// Change to home directory
status cd_home();

// Print working directory
status pwd2();

// Change directory
// Usage: cd <path>
// If no path is provided, change to home directory.
// If path is provided, change to that directory.
// 'cd -' will change to the previous directory.
status cd2(const char *path);

// List directory contents
// Usage: ls <directory>
// If no directory is provided, list contents of current directory.
status ls2(const char *directory);

// Create a new file
// Usage: touch <file>
status touch2(const char *filename);

// Print a message
// Usage: echo <message>
status echo2(const char *message);

// Print contents of a file
// Usage: cat2 <file>
status cat2(const char *filename);

// Copy a file
// Usage: cp <source> <destination>
status cp2(const char *src, const char *dest);

// Remove a file or a directory
// Usage: rm2 <file> or rm2 -r <directory>
status rm2(const char *flag, const char *filename);

// Rename a file
// Usage: rename2 <file> <newname>
status rename2(const char *filename, const char *newname);

// Print command history
status history2();

status execute_command();

#endif
