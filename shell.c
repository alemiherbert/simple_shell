#include "shell.h"

/**
 * readLine - read a line from standard input
 * @line: pointer to store the read line
 *
 * Return: number of characters read, or -1 on failure
 */
int readLine(char **line)
{
	size_t len = 0;
	ssize_t nread;

	if (line == NULL)
		return (-1);

	nread = getline(line, &len, stdin);

	if (nread == EOF)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}

	return (nread);
}

/**
 * getLine - read a line from a given stream
 * @lineptr: pointer to store the read line
 * @n: pointer to store the allocated buffer size
 * @stream: the stream to read from
 *
 * Return: number of characters read, or -1 on failure or EOF
 */
ssize_t getLine(char **lineptr, size_t *n, FILE *stream)
{
	int ch;
	size_t size = BUFFER_SIZE, pos = 0;
	char *new_line;

	if (lineptr == NULL || n == NULL)
		return (-1);

	if (*lineptr == NULL || *n < 1)
	{
		*lineptr = malloc(size);
		if (*lineptr == NULL)
			return (-1);
		*n = size;
	}

	while ((ch = fgetc(stream)) != EOF)
	{
		if (pos >= *n - 1)
		{
			size_t new_size = *n * 2;
			new_line = (char *)realloc(*lineptr, new_size);
			if (new_line == NULL)
			{
				free(*lineptr);
				*lineptr = NULL;
				return (-1);
			}
			*lineptr = new_line;
			*n = new_size;
		}

		(*lineptr)[pos++] = ch;

		if (ch == '\n')
			break;
	}

	(*lineptr)[pos] = '\0';

	return ((ch == EOF && pos == 0) ? -1 : (ssize_t)pos);
}

void freeTokens(char **args, int num_args)
{
	if (args == NULL)
		return;

	for (int i = 0; i < num_args; i++)
	{
		free(args[i]);
	}
	free(args);
}

/**
 * splitLine - split the line into individual arguments
 * @line: the input line to be split
 * @args: pointer to store the array of arguments
 *
 * Return: number of arguments or -1 on failure
 */
int splitLine(char *line, char ***args)
{
	char *token, **tokens = NULL, **new_tokens;
	int size = BUFFER_SIZE;
	int pos = 0;

	if (line == NULL || args == NULL)
		return (-1);

	tokens = (char **)malloc(sizeof(char *) * size);
	if (tokens == NULL)
	{
		perror("Memory allocation error");
		return -1;
	}

	token = strtok(line, DELIM);
	do
	{
		if (pos >= size)
		{
			size += BUFFER_SIZE;
			new_tokens = (char **)realloc(tokens, size * sizeof(char *));
			if (new_tokens == NULL)
			{
				perror("Memory reallocation error");
				freeTokens(tokens, pos);
				return (-1);
			}
			tokens = new_tokens;
		}

		tokens[pos] = strdup(token);
		if (tokens[pos] == NULL)
		{
			perror("Memory allocation error");
			freeTokens(tokens, pos);
			return (-1);
		}

		pos++;

		token = strtok(NULL, DELIM);
	} while (token != NULL);

	tokens[pos] = NULL;
	*args = tokens;

	return (pos);
}

/**
 * readline - read a line from a given stream
 * @stream: the stream
 *
 * Return: pointer to the string or NULL
 */
char *readline(FILE *stream)
{
	char *line = NULL;
	size_t len = BUFFER_SIZE;
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

	size = TOKEN_SIZE;
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

		if (i >= TOKEN_SIZE)
		{
			size += TOKEN_SIZE;
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
			return (strdup(filename));
		else
			return (NULL);
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
			return (NULL);
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

	if (pid == 0)
	{
		status = execve(command, args, NULL);
		if (status <= -1)
			return (false);
	}
	else
		waitpid(pid, &status, 2);

	return (true);
}
