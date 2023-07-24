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
		return NULL;

	tokens = malloc(sizeof(char *) * MAX_TOKEN_SIZE);
	if (tokens == NULL)
		return NULL;

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
	return tokens;
}

int main(void)
{
	// testing
	char *command = "This is a sample command";
	char **tokens = tokenise(command, DELIM);

	if (tokens != NULL)
	{
		for (size_t i = 0; tokens[i] != NULL; i++)
		{
			printf("Token %zu: %s\n", i, tokens[i]);
		}

		// Free memory allocated for tokens
		free(tokens);
	}

	return (0);
}