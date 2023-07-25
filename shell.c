#include "shell.h"

/**
 * tokenise - split a string into tokens
 * @command: the string
 * @delim: the delimiter
 *
 * Return: a pointer to the tokens or NULL
 */
char **tokenise(char *command, char *delim)
{
	char *token = NULL, **tokens, *temp_command;
	size_t size, i;

	size = MAX_TOKEN_SIZE;
	if (command == NULL)
		return (NULL);

	tokens = malloc(sizeof(char *) * size);
	if (tokens == NULL)
		return (NULL);

	/* work with a copy of the command to avoid modifying it */
	temp_command = strdup(command);

	token = strtok(temp_command, delim);
	for (i = 0; token != NULL; i++)
	{
		tokens[i] = strdup(token);

		if (i >= MAX_TOKEN_SIZE)
		{
			size += MAX_TOKEN_SIZE;
			tokens = realloc(tokens, sizeof(char *) * size);
			if (tokens == NULL)
				return (NULL);
		}
		token = strtok(NULL, delim);
	}

	tokens[i] = NULL;
	free(temp_command);
	return (tokens);
}

/**
 * locate_executable - find the path to an executable
 * @filename: the name of the executable
 *
 * Return: a string containing the path to the executable or NULL
 */
char *locate_executable(const char *filename)
{
	size_t i;
	char *command = NULL, *path, **tokens;
	struct stat st;

	path = getenv("PATH");
	tokens = tokenise(strdup(path), ":");

	if (stat(filename, &st) == 0)
	{
		command = strdup(filename);
	}
	else
	{
		for (i = 0; tokens[i] != NULL; i++)
		{
			free(command);
			command = join_path(tokens[i], filename);
			if (stat(command, &st) == 0)
				break;
		}
	}
	free_tokens(tokens);
	return (command);
}

/**
 * run_command - executes a command
 * @command: the command
 * @args: the arguments to the command
 *
 * Return: 1 if success, else 0
 */
bool run_command(char *command, char **args)
{
	int status;
	pid_t pid = fork();

	if (pid <= -1)
		return (false);
	else if (pid == 0)
	{
		status = execve(command, args, NULL);
		if (status <= -1)
			return (false);
	}
	else
		wait(&status);

	return (true);
}
