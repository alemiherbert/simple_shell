#include "shell.h"

/**
 * main - a command line executor
 * @argc: the argument count
 * @argv: the argument vector
 * Return: Always 0
 */
int main(void)
{
	char **command, *line = NULL;
	size_t len = 0;
	ssize_t nread;

	do
	{
		printf("$ ");
		nread = getline(&line, &len, stdin);
		command = tokenise(line, DELIM);

	} while (nread != EOF);
	return (0);
}
