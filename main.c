#include "shell.h"

/**
 * main - a command line executor
 * @argc: the argument count
 * @argv: the argument vector
 * Return: Always 0
 */
int main(int argc, char **argv, char **env)
{
	bool status = true;
	char *cmd, **args, *line, *error_msg, *oldpwd;
	unsigned long int index = 0;

	do
	{
		if (isatty(STDIN_FILENO))
		{
			write(1, "$ ", 2);
			readLine(&line);
		}

		if (line == NULL)
		{
			write(1, "\n", 1);
			free(line);
			break;
		}

		splitLine(line, &args);

		if (!args)
			exit(EXIT_FAILURE);

		if (strcmp(args[0], "exit") == 0)
			break;

		status = run_command(locate_executable(args[0]), args);
		if (status == false)
			perror(args[0]);

		if (line != NULL)
		{
			free(line);
			line = NULL;
		}
		free(args);
		free(error_msg);
		free(oldpwd);
	} while (status == true);
	return (0);
}
