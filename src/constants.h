#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BUFF_SIZE 255  // Max size of input buffer
#define MAX_CMD 50     // Max tokens in a command (including the command itself)
#define MAX_CMD_LEN 30 // Max length of a token
#define MAX_HISTORY 200 // Max number of commands in history

typedef enum { OK, ERROR, QUIT } status;
typedef enum { TRUE, FALSE } boolean;

#endif
