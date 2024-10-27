#ifndef COMMANDS_H
#define COMMANDS_H

#include "constants.h"
#include "globals.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>

// Save error message to log file
void log_error(const char *cmd, const char *error_msg);

// Change to home directory
Status cd_home();

// Print working directory
Status pwd2();

// Change directory
// Usage: cd <path>
// If no path is provided, change to home directory.
// If path is provided, change to that directory.
// 'cd -' will change to the previous directory.
Status cd2(const char *path);

// List directory contents
// Usage: ls <directory>
// If no directory is provided, list contents of current directory.
Status ls2(const char *directory);

// Create a new file
// Usage: touch <file>
Status touch2(const char *filename);

// Print a message
// Usage: echo <message>
Status echo2(const char *message);

// Print contents of a file
// Usage: cat2 <file>
Status cat2(const char *filename);

// Copy a file
// Usage: cp <source> <destination>
Status cp2(const char *src, const char *dest);

// Remove a file or a directory
// Usage: rm2 <file> or rm2 -r <directory>
Status rm2(const char *pathname, Bool recursive);

// Rename a file
// Usage: rename2 <file> <newname>
Status rename2(const char *filename, const char *newname);

// Print command history
Status history2();

Status execute_external_command(char *argv[]);

// Execute a command without redirection or piping
Status execute_normal_command(int argc, char *argv[]);

Status execute_command(int argc, char *argv[]);

#endif
