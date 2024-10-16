#ifndef COMMANDS_H
#define COMMANDS_H

#include "constants.h"
#include "globals.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

status cd_home();

status pwd2();
status cd2(const char *path);
status ls2(const char *directory);
status touch2();
status echo2();
status cat2();
status cp2();
status rm2();
status rename2();
status history2();

status execute_command();

#endif
