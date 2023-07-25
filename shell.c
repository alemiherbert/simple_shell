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
	int status;
	pid_t pid;

	do
	{
		printf("$ ");

		nread = getline(&line, &len, stdin);
		command = tokenise(line, DELIM);
		pid = fork();
		if (pid == 0)
		{
			status = execve(locate_executable(command[0]), command, NULL);
			if (status == -1);
				perror("./shell");
		}
		if (pid == -1)
			perror("./shell");
		else
			wait(&status);

	} while (nread != EOF);
	return (0);
}
