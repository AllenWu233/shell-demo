#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BUFF_SIZE 1024 // Max size of input buffer
#define MAX_CMD 50     // Max tokens in a command (including the command itself)
#define MAX_CMD_LEN 30 // Max length of a token
#define MAX_HISTORY 1000 // Max number of commands in history

typedef enum { OK, ERROR, QUIT } Status;
typedef enum { TRUE, FALSE } Bool;
typedef enum { NONE = 0, APPEND, WRITE, ERR_RDCT } Redirect;

#endif
