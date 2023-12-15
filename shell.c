#include "shell.h"

/**
 * main - it defines the point beginning at the execution point of the program
 * @ac: denoting argument count
 * @av: denoting argument vector
 *
 * Return: 0 on code success, 1 if error encountered
 */
int main(int ac, char **av)
{
	s_type s_typeinfo[] = { SYSTEMINFOINIT };
	int file_descp = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_descp)
		: "r" (file_descp));

	if (ac == 2)
	{
		file_descp = open(av[1], O_RDONLY);
		if (file_descp == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				output(av[0]);
				output(": 0: Can't open ");
				output(av[1]);
				putoutchar('\n');
				putoutchar(FLUSH_INDICATOR);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		s_typeinfo->rdfiledes = file_descp;
	}
	initenvar(s_typeinfo);
	rdhist(s_typeinfo);
	strexec(s_typeinfo, av);
	return (EXIT_SUCCESS);
}
