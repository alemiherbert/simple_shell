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
 * join_path - concatenate two strings with '/' as a separator
 * @dir: the name of the directory
 * @file: the name of the file
 *
 * Return: a pointer to the new path string or NULL
 */
char *join_path(const char *dir, const char *file)
{
	size_t dir_len = strlen(dir);
	size_t file_len = strlen(file);
	size_t total_len = (++dir_len) + (++file_len);
	char *result = malloc(sizeof(char) * total_len);

	if (result != NULL)
		snprintf(result, total_len, "%s/%s", dir, file);

	return (result);
}

/**
 * free_tokens - free the tokens
 * @tokens: the tokens
 */
void free_tokens(char **tokens)
{
	if (tokens != NULL)
	{
		for (size_t i = 0; tokens[i] != NULL; i++)
		{
			free(tokens[i]);
		}
		free(tokens);
	}
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
