#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H

#include "constants.h"
#include "globals.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Add input to history array
status add_to_history();

// Get user input, including spaces
// and save history of input to array 'historys'
status get_input();

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
status parse_input();

#endif
