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

	do {
		printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == EOF)
		{
			putchar('\n');
			free(line);
			exit(EXIT_FAILURE);
		}

		args = tokenise(line, DELIM);

		if (strcmp(args[0], "exit") == 0)
			exit(EXIT_FAILURE);

		command = locate_executable(args[0]);
		status = run_command(command, args);
		if (status == false)
			perror(command);

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
