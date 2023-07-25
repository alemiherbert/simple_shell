#include "shell.h"

/**
 * handle_error - custom error handler
 * @code: the error code
 */
void handle_error(short code)
{
    switch (code)
    {
    case 1:
        dprintf(STDERR_FILENO, "General error\n");
        break;
    case 2:
        dprintf(STDERR_FILENO, "Missing keyword, command, or permission problem\n");
        break;
    case 126:
        dprintf(STDERR_FILENO, "Permission problem or command is not executable\n");
        break;
    case 127:
        dprintf(STDERR_FILENO, "Command not found\n");
        break;
    case 128:
        dprintf(STDERR_FILENO, "Invalid argument to exit\n");
        break;
    case 129:
        dprintf(STDERR_FILENO, "Fatal error signal 1\n");
        break;
    case 130:
        dprintf(STDERR_FILENO, "Script terminated by Control-C\n");
        break;
    default:
        dprintf(STDERR_FILENO, "Unknown error code\n");
        break;
    }

    exit(code);
}