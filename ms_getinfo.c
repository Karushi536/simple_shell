#include "shell.h"

/**
 * ms_clear_info - initializes info_t struct
 * @info: struct address
 */
void ms_clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * ms_set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void ms_set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
	info->argv = ms_strtow(info->arg, " \t");
	if (!info->argv)
	{

	info->argv = malloc(sizeof(char *) * 2);
	if (info->argv)
		{
		info->argv[0] = _strdup(info->arg);
		info->argv[1] = NULL;
		}
	}
	for (i = 0; info->argv && info->argv[i]; i++)
	;
	info->argc = i;

	ms_replace_alias(info);
	ms_replace_vars(info);
	}
}

/**
 * ms_free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void ms_free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
	if (!info->cmd_buf)
		free(info->arg);
	if (info->env)
		ms_free_list(&(info->env));
	if (info->history)
		ms_free_list(&(info->history));
	if (info->alias)
		ms_free_list(&(info->alias));
	ffree(info->environ);
	info->environ = NULL;
	bfree((void **)info->cmd_buf);
	if (info->readfd > 2)
		close(info->readfd);
	_putchar(BUF_FLUSH);
	}
}
