#include "shell.h"

/**
 * readline - read a line from a given stream
 * @stream: the stream
 *
 * Return: pointer to the string or NULL
 */
char *readline(FILE *stream)
{
	char *line = NULL;
	size_t len = MAX_BUFFER_SIZE;
	ssize_t nread;

	nread = getline(&line, &len, stream);
	if (nread == EOF)
	{
		free(line);
		return (NULL);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

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
    char *command = NULL, *path, **tokens, *tmp_command;
    struct stat st;

    if (filename[0] == '/')
    {
        if (stat(filename, &st) == 0)
            return strdup(filename);
        else
            return NULL;
    }

    path = getenv("PATH");
    if (path == NULL)
        path = "/bin:/usr/bin";

    tokens = tokenise(strdup(path), ":");

    for (i = 0; tokens[i] != NULL; i++)
    {
        tmp_command = join_path(tokens[i], filename);
        if (tmp_command == NULL)
        {
            free(command);
            free_tokens(tokens);
            return NULL;
        }

        if (stat(tmp_command, &st) == 0)
        {
            free(command);
            command = tmp_command;
            break;
        }

        free(tmp_command);
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
