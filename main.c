#include "shell.h"

/**
 * main - a command line executor
 * @argc: the argument count
 * @argv: the argument vector
 * Return: Always 0
 */
int main(void)
{
	char **args, *line = NULL;
	bool status = true;

	do {
		printf("$ ");
		line = readline(stdin);
		if (line == NULL)
		{
			putchar('\n');
			free(line);
			break;
		}

		args = tokenise(line, DELIM);

		if (strcmp(args[0], "exit") == 0)
			exit(EXIT_FAILURE);

		status = run_command(locate_executable(args[0]), args);
		if (status == false)
			perror(args[0]);

		if (line != NULL)
		{
			free(line);
			line = NULL;
		}
		free(args);
	} while (status == true);
	return (0);
}
