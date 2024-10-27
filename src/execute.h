#ifndef EXECUTE_H
#define EXECUTE_H

#include "commands.h"
#include "input.h"

Status execute_external_command(char *argv[]);

// Execute a built-in or external command without redirection or piping
Status execute_normal_command(int argc, char *argv[]);

Status execute_command_with_redirect(int argc, char *argv[]);

Status execute_command_with_pipe(int argc, char *argv[]);

Status execute_command(int argc, char *argv[]);

#endif
