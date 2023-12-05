#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/**
 * main - Entry point of the program
 *
 * Return: Always 0 (success)
 */

int main(void)
{
	char *args[] = {"/bin/ls", NULL};

	execve(args[0], args, NULL);

	if (strcmp(args[0], "exit") == 0)
	{
		printf("Goodbye!\n");
		exit(0);
	}
	return (0);
}
