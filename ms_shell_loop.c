#include "shell.h"

/**
 * ms_shell_loop - main shell loop
 * @info: parameter & return info struct
 * @av: argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int ms_shell_loop(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (ms_interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (ms_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!ms_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", ms_myexit},
		{"env", ms_myenv},
		{"help", ms_myhelp},
		{"history", ms_myhistory},
		{"setenv", ms_mysetenv},
		{"unsetenv", ms_myunsetenv},
		{"cd", ms_mycd},
		{"alias", ms_myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!ms_is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = ms_find_path(info, ms_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		ms_fork_cmd(info);
	}
	else
	{
		if ((ms_interactive(info) || ms_getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && ms_is_cmd(info, info->argv[0]))
			ms_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			ms_print_error(info, "not found\n");
		}
	}
}

