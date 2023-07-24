#include "shell.h"

/**
 * is_interactive - check wether the shell is in interactive mode
 * @state: the current state of the shell
 *
 * return: true or false
 */
bool is_interactive(state_t *state)
{
	return (state->fd <= 2 && isatty(STDIN_FILENO));
}
