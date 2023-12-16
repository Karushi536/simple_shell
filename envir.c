#include "shell.h"

/**
 * _myenv - showcases the current environment settings
 * @info: This holds potential arguments. Ensures a constant
 *	function prototype.
 * Return: Always returns 0 on completion.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - retrieves the value of an environment variable
 * @info: This contains potential arguments. Maintains
 *	constant function prototype.
 * @name: Name of the environment variable.
 *
 * Return: The value of the specified environment variable.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *x;

	while (node)
	{
		x = starts_with(node->str, name);
		if (x && *x)
			return (x);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Creates a new environment variable or updates an existing one
 * @info: This structure contains potential arguments. Ensures a constant
 *	function prototype.
 * Return: Always returns 0 upon successful execution.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Eradicates an environment variable
 * @info: This structure orchestrates potential arguments. Preserves
 *	the sanctity of constant function prototypes.
 * Return: Triumphs with a return of 0 upon success.
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - assembles an environment linked list
 * @info: This contains potential arguments. Ensures a constant
 *        function prototype.
 * Return: Always returns 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
