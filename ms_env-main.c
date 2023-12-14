#include "shell.h"

/**
 * main - Entry point for the program.
 * This function is the starting point of the program.
 * It returns an integer value to the operating system.
 *
 * Return: 0 on success, 1 on failure.
 *
 */

int main(void)
{

	char command[128];

	while (1)
	{

		display_prompt();
		user_input(command, sizeof(command));
		execute_command(command);
	}
	return (0);
}
