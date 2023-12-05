#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Entry point of the program
 *
 * Return: Always 0 (success)
 */

int main(void)
{
	char *args[] = {"/bin/ls", NULL};

	execve(args[0], args, NULL);

/* Adding a blank line after declarations */
	if (strcmp(args[0], "exit") == 0){
		printf ("Goodbye!\n");
		exit(0);
/* this is to make it stop */
return (0);
}
