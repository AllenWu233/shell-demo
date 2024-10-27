#include "minifetch.h"

const char *logo = "\
    ███████╗██╗  ██╗███████╗██╗     ██╗     ██████╗ ███████╗███╗   ███╗ ██████╗   \n\
    ██╔════╝██║  ██║██╔════╝██║     ██║     ██╔══██╗██╔════╝████╗ ████║██╔═══██╗  \n\
    ███████╗███████║█████╗  ██║     ██║     ██║  ██║█████╗  ██╔████╔██║██║   ██║  \n\
    ╚════██║██╔══██║██╔══╝  ██║     ██║     ██║  ██║██╔══╝  ██║╚██╔╝██║██║   ██║  \n\
    ███████║██║  ██║███████╗███████╗███████╗██████╔╝███████╗██║ ╚═╝ ██║╚██████╔╝  \n\
    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚═════╝ ╚══════╝╚═╝     ╚═╝ ╚═════╝ ";

void print_color_line() {
    printf("\n\
    [40m   [41m   [42m   [43m   [44m   [45m   [46m   [47m   [m\n\
    [100m   [101m   [102m   [103m   [104m   [105m   [106m   [107m   [m\n");
}

void print_info() {
    struct utsname sys_info;
    if (uname(&sys_info) < 0) {
        perror("uname");
        exit(EXIT_FAILURE);
    }

    struct passwd *pw = getpwuid(getuid());
    if (pw == NULL) {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) < 0) {
        perror("gethostname");
        exit(EXIT_FAILURE);
    }

    printf("  %sUser: %s\n", BRIGHT_RED, pw->pw_name);
    printf("  %sHost: %s\n", BRIGHT_MAGENTA, hostname);
    printf("  %sOS: %s %s\n", BRIGHT_YELLOW, sys_info.sysname,
           sys_info.release);
    printf("  %sKernel: %s\n", BRIGHT_GREEN, sys_info.version);
    print_color_line();
}

Status minifetch(void) {
    printf("\n%s%s%s\n", MAGENTA, logo, RESET);
    print_info();
    printf("\n  %sminifetch Version 1.0   %s\n", GRAY_BG, RESET);
    printf("  %sCopyright (C) 2024 Allen%s\n\n", GRAY_BG, RESET);
    return OK;
}
