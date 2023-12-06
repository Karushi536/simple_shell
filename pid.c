#include <stdio.h>
#include <unistd.h>

/**
 *
 * main - PID
 *
 * Return: 0 success
 */
int main(void)
{
	pid_t pid;

	pid = getpid();
	printf("The process id is %u", pid);
	return (0);
}
