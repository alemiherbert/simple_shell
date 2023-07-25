#include "shell.h"

/**
 * main - a command line executor
 * @argc: the argument count
 * @argv: the argument vector
 * Return: Always 0
 */
int main(void)
{
    char *command, **args, *line = NULL;
    size_t len = MAX_BUFFER_SIZE;
    ssize_t nread;
    bool status = true;

    do
    {
        printf("$ ");
        nread = getline(&line, &len, stdin);

        if (nread == EOF)
        {
            free(line);
            break;
        }

        args = tokenise(line, DELIM);

        command = locate_executable(args[0]);
        run_command(command, args);

        if (line != NULL)
        {
            free(line);
            line = NULL;
        }
        free(command);
        free(args);
    } while (status == true);
    return (0);
}
