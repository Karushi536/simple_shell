#include "shell.h"

/**
 * _myhistory - retrieves and prints the command history list, with each
 *	command displayed on a separate line and numbered from 0.
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * Return: Always 0 on success.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - configures an alias by associating the given string
 *	with the provided parameter structure.
 * @info: Parameter structure containing relevant information.
 * @str: The string to be set as an alias.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *x, h;
	int ret;

	x = _strchr(str, '=');
	if (!x)
		return (1);
	h = *x;
	*x = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*x = h;
	return (ret);
}

/**
 * set_alias - assigns an alias by linking the specified string
 *	with the provided parameter structure.
 * @info: Parameter structure containing necessary information.
 * @str: The string to be set as an alias.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *x;

	x = _strchr(str, '=');
	if (!x)
	{
	return (1);
	}
	if (!*++x)
	{
	return (unset_alias(info, str));
	}

	unset_alias(info, str);
	return ((add_node_end(&(info->alias), str, 0) == NULL) ? 1 : 0);
}


/**
 * print_alias - displays the string associated with an alias node
 * @node: The alias node to be printed.
 *
 * Return: Always returns 0 on success, 1 on error.
 */

int print_alias(list_t *node)
{
	char *x = NULL, *v = NULL;

	if (node)
	{
		x = _strchr(node->str, '=');
		for (v = node->str; v <= x; v++)
			_putchar(*v);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - replicates the functionality of the alias builtin (man alias)
 * @info: Structure containing potential arguments. Maintains
 *	a consistent function prototype.
 * Return: Always returns 0.
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *x = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		x = _strchr(info->argv[i], '=');
		if (x)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
