#include "shell.h"
/**
 *main - entry point for the program
 *
 * This function is the starting point of the program.
 * It returns an integer value to the operating system.
 * 
 * return: 0 on successful execution.
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
