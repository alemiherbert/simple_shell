#include "shell.h"

/**
 * sigint_handler - handle Ctrl+C
*/
int sigint_hander(int signum)
{
    if (signum == SIGINT)
        write(1, "\n$ ", 3);
}