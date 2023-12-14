#include "shell.h"

/**
 * _get_environ - Get the environment variable array.
 *
 * Return: Pointer to the environment variable array.
 */

char **_get_environ(void)
{
	extern char **environ;
	return environ;
}
