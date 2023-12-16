#include "shell.h"

/**
 * _eputs - outputs the specified string
 * @str: function parameter The string to be printed.
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int p = 0;

	if (!str)
		return;
	while (str[p] != '\0')
	{
		_eputchar(str[p]);
		p++;
	}
}

/**
 * _eputchar - function name writes the character c to stderr
 * @c: parameter the character to be printed.
 *
 * Return: On success, returns 1.
 * On error, returns -1 and sets errno appropriately.
 */
int _eputchar(char c)
{
	static int p;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || p >= WRITE_BUF_SIZE)
	{
		write(2, buf, p);
		p = 0;
	}
	if (c != BUF_FLUSH)
		buf[p++] = c;
	return (1);
}

/**
 * _putfd - outputs the character c to the provided file descriptor
 * @c: Parameter one The character to be printed.
 * @fd: parameter two The file descriptor for writing.
 *
 * Return: On success, returns 1.
 * On error, returns -1 and sets errno accordingly.
 */
int _putfd(char c, int fd)
{
	static int p;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || p >= WRITE_BUF_SIZE)
	{
		write(fd, buf, p);
		p = 0;
	}
	if (c != BUF_FLUSH)
		buf[p++] = c;
	return (1);
}

/**
 * _putsfd - prints the specified string to the given file descriptor
 * @str: parameter one The string to be printed.
 * @fd: parameter two The file descriptor to write to.
 *
 * Return: The number of characters put.
 */

int _putsfd(char *str, int fd)
{
	int p = 0;

	if (!str)
		return (0);
	while (*str)
	{
		p += _putfd(*str++, fd);
	}
	return (p);
}
