#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>


#define DELIM " \a\n\r\t"
#define TOKEN_SIZE 64
#define BUFFER_SIZE 256

extern char **environ;


void displayPrompt(int, struct stat);
ssize_t getLine(char **lineptr, size_t *n, FILE *stream);

int readLine(char **line);
int splitLine(char *line, char ***args);
void freeTokens(char **args, int num_args);


char *readline(FILE *stream);
char **tokenise(char *command, char *delim);
char *join_path(const char *dir, const char *file);
char *locate_executable(const char *filename);
void free_tokens(char **tokens);
bool run_command(char *command, char **args);

void handle_error(short code);


int cd(char *path);

void sigint_handler(int signum);

#endif
