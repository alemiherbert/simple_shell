#include "shell.h"

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
