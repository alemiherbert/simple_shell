#include "shell.h"

/**
 * main - a command line executor
 * @argc: the argument count
 * @argv: the argument vector
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	bool status = true;
	state_t state;

	do
	{
		if (is_interactive(&state));
			printf("$ ");

		nread = getline(&line, &len, stdin);
		if (nread == EOF)
			status = false;
		
		printf("%s", line);
	} while (status == true);
	return (0);
}
