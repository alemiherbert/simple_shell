#include "shell.h"

/**
 * tokenise - split a string into tokens
 * @command: the string
 *
 * Return: a pointer to the tokens or NULL
 */
char **tokenise(char *command)
{
	char *token, **tokens, *temp_command;
	size_t i = 0;

	if (command == NULL)
		return (NULL);

	tokens = malloc(sizeof(char *) * MAX_TOKEN_SIZE);
	if (tokens == NULL)
		return (NULL);

	/* work with a copy of the command to avoid modifying it */
	temp_command = strdup(command);

	do {
		if (token == NULL)
			token = strtok(command, DELIM);
		else
			token = strtok(NULL, DELIM);
		tokens[i++] = token;
	} while (token != NULL && i < MAX_TOKEN_SIZE);

	free(temp_command);
	return (tokens);
}
