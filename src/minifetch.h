#ifndef MINIFETCH_H
#define MINIFETCH_H

#include "constants.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>

#define RESET "\033[0m"

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define GRAY "\033[90m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"
#define BLACK_BG "\033[40m"
#define RED_BG "\033[41m"
#define GREEN_BG "\033[42m"
#define YELLOW_BG "\033[43m"
#define BLUE_BG "\033[44m"
#define MAGENTA_BG "\033[45m"
#define CYAN_BG "\033[46m"
#define WHITE_BG "\033[47m"
#define GRAY_BG "\033[100m"
#define BRIGHT_RED_BG "\033[101m"
#define BRIGHT_GREEN_BG "\033[102m"
#define BRIGHT_YELLOW_BG "\033[103m"
#define BRIGHT_BLUE_BG "\033[104m"
#define BRIGHT_MAGENTA_BG "\033[105m"
#define BRIGHT_CYAN_BG "\033[106m"
#define BRIGHT_WHITE_BG "\033[107m"

void print_color_line();
void print_info();

// Print system information in a fancy way
Status minifetch();

#endif
