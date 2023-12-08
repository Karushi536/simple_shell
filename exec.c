#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
/**
 * @brief Entry point of the program.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 *
 * @return Returns 0 on success.
 */
int main(int argc, char *argv[])
{

	char *args[] = {"/bin/ls", "-l", NULL};
	char *env[] = {NULL};/*No environment variables needed*/

	execve("/bin/ls", args, env);

	/*If execve() returns, an error occurred*/
	perror("execve");
	return (1);
}
