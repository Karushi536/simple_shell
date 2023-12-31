#include "shell.h"

/**
 * get_environ - fn Retrieves a copy of 'environ' variable as a string array.
 * @info: fp Structure containing potential arguments for maintaining
 *	a constant function prototype.
 *
 * Return: Always returns 0 on success.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Function name Removes an environment variable.
 * @info: fp one Structure containing potential arguments for maintaining
 *	a constant function prototype.
 * @var: fp two The name of the environment variable to be deleted.
 *
 * Return: 1 on successful deletion, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *x;

	if (!node || !var)
		return (0);

	while (node)
	{
		x = starts_with(node->str, var);
		if (x && *x == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - fn Initializes new environment variable/ modifies an existing one.
 * @info: fp one Structure containing potential arguments used to maintain
 *	a constant function prototype.
 * @var: fp two The name of the environment variable.
 * @value: fp three The value to set for the environment variable.
 *
 * Return: Always returns 0 on success.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *x;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		x = starts_with(node->str, var);
		if (x && *x == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
