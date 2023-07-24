#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

#define DELIM " \a\t\n"
#define MAX_TOKEN_SIZE 512
#define MAX_BUFFER_SIZE 1024

char **tokenise(char *command, char *delim);
char *join_path(const char *dir, const char *file);
char *locate_executable(const char *filename);

#endif
