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
 * execute_command - Executes the given command using execvp
 * @command: The command to execute
 */
void execute_command(const char *command)
{
	if (execlp(command, command, (char *)NULL) == -1)
	{
	perror(command);
	exit(EXIT_FAILURE);
	}
}

/**
 * handle_child_process - Handles the logic for the child process
 * @command: The command to execute
 */
void handle_child_process(const char *command)
{
	execute_command(command);
}

/**
 * handle_parent_process - Handles the logic for the parent process
 * @child_pid: The process ID of the child process
 * @command: The command being executed
 */
void handle_parent_process(pid_t child_pid, const char *command)
{
	int status;

	waitpid(child_pid, &status, 0);

	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
	printf("%s: No such file or directory\n", command);
	}
}

/**
 * main - Entry point for the shell program.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(void)
{
	pid_t child_pid;
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

	/* fork a new process */
	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
	/* child process */
	handle_child_process(command);
	}
	else
	{
	/* parent process */
	handle_parent_process(child_pid, command);
	}
	}

	return (0);
}
