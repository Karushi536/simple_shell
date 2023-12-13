#include "shell.h"

/**
 * main - Simple shell entry point
 *
 * Return: Always 0
 */
int main(void)
{
	char *line;
	char **args;

	while (1)
	{
	printf("#cisfun$ ");
	line = read_line();
	args = split_line(line);
	execute(args);

	free(line);
	free(args);
	}

	return (0);
}

