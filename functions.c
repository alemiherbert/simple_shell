#include "shell.h"

int cd(char *path)
{
	return (chdir(path));
}
