#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
/**
 * main - Entry point of the program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
	fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
	return (1);
	}

/* Add the provided directory to the ls_args array */
	char *directory = argv[1];
	char *ls_args[] = {"/bin/ls", "-l", directory, NULL};
	char *env[] = {NULL}; /* No environment variables needed */

/* Existing code: execve call */
	execve("/bin/ls", ls_args, env);

/* If execve() returns, an error occurred */
	perror("execve");
	return (1);
}
