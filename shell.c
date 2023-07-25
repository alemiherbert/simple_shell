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
	size_t i = 0;

	if (command == NULL)
		return (NULL);

	tokens = malloc(sizeof(char *) * MAX_TOKEN_SIZE);
	if (tokens == NULL)
		return (NULL);

	/* work with a copy of the command to avoid modifying it */
	temp_command = strdup(command);

	token = strtok(temp_command, delim);
	while (token != NULL && i < MAX_TOKEN_SIZE)
	{
		tokens[i] = strdup(token);
		token = strtok(NULL, delim);
		i++;
	}

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
	char *command;
	char *path = getenv("PATH");
	char **tokens = tokenise(path, ":");
	struct stat st;

	if (tokens != NULL)
	{
		for (i = 0; tokens[i] != NULL; i++)
		{
			command = join_path(tokens[i], filename);
			if (command != NULL && stat(command, &st) == 0)
			{
				free_tokens(tokens);
				return (command);
			}
			free(command);
		}
		free_tokens(tokens);
	}
	return (NULL);
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
			return false;
	}
	else
	wait (&status);

	return (true);
}
