#include "shell.h"

/**
 * bfree - function name frees a pointer and sets the address to NULL
 * @ptr: function parameter Address of the pointer to be freed.
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
