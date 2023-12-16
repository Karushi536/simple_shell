#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: The string to be converted.
 * Return: 0 if no numbers are present in the string,
 *	the converted number otherwise, and -1 on error.
 */
int _erratoi(char *s)
{
	int p = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: Investigate why this causes main to return 255 */
	for (p = 0;  s[p] != '\0'; p++)
	{
		if (s[p] >= '0' && s[p] <= '9')
		{
			result *= 10;
			result += (s[p] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - displays an error message
 * @info: The parameter and return information struct.
 * @estr: String specifying the type of error.
 * Return: Returns 0 if no numbers are found in the string,
 *	the converted number otherwise, and -1 on error.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - outputs a decimal (integer) number in base 10
 * @input: The numeric input to be printed.
 * @fd: The file descriptor for writing.
 *
 * Return: The count of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int p, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (p = 1000000000; p > 1; p /= 10)
	{
		if (_abs_ / p)
		{
			__putchar('0' + current / p);
			count++;
		}
		current %= p;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - conversion function, analogous to itoa
 * @num: The number to be converted.
 * @base: The base for conversion.
 * @flags: Argument flags influencing the conversion.
 *
 * Return: The resulting string.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long m = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		m = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[m % base];
		m /= base;
	} while (m != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - replaces the first instance of '#' with '\0' in the string
 * @buf: Address of the string to be modified.
 *
 * Return: Always returns 0 on success.
 */
void remove_comments(char *buf)
{
	int p;

	for (p = 0; buf[p] != '\0'; p++)
		if (buf[p] == '#' && (!p || buf[p - 1] == ' '))
		{
			buf[p] = '\0';
			break;
		}
}
