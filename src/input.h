#ifndef INPUT_H
#define INPUT_H

#include "constants.h"
#include "globals.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

Bool has_redirect(int argc, char *argv[]);

Bool has_pipe(int argc, char *argv[]);

// Add input to history array
Status add_to_history();

// Get user input, including spaces
// and save history of input to array 'historys'
Status get_input();

/*
 * Parse the input string stored in 'buf' and tokenize it based on spaces,
 * treating '|' and '>' as individual tokens. Store the tokens in the 'command'
 * array. Multiple consecutive spaces are treated as a single space.
 *
 * The function iterates over the characters in 'buf', building tokens based on
 * spaces.
 * '|' and '>' are treated as separate tokens regardless of surrounding spaces.
 * The tokens are stored in the 'command' array for further processing.
 *
 * Returns:
 *     'OK' on successful parsing.
 */
Status parse_input();

// Gheck redirect type
Redirect parse_redirect(int argc, char *argv[]);

char *get_redirect_filename(int argc, char *argv[]);

#endif
