#include "shell.h"

#define MAX_COMMAND_LENGTH 100
/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
	fflush(stdout);
}
/**
 * Main - function for the simple shell
 * return: 0 on successful execution
 */
int main(void)
{
	pid_t child_pid; /*Declare pid_t at the beginning */
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		display_prompt();

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{

			printf("\n");
			break;
		}

		command[strcspn(command, "\n")] = '\0';

		/*fork a new process*/
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			/*child process*/

			/*Execute command using execvp*/
			if (execlp(command, command, (char *)NULL) == -1)
			{
				/*If execvp fails, print an error message*/
				perror(command);
				exit(EXIT_FAILURE);
			}
		}

		else
		{
			int status;

			waitpid(child_pid, &status, 0);

			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				printf("%s: No such file or directory\n", command);
			}
		}
	}

	printf("\n");
	return (0);
}
