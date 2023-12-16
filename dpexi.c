#include "shell.h"

/**
 * _strncpy - copies a string to a specified destination
 * @dest: Destination string for the copy.
 * @src: Source string to be duplicated.
 * @n: Number of characters to copy.
 * Return: The resulting copied string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int p, l;
	char *s = dest;

	p = 0;
	while (src[p] != '\0' && p < n - 1)
	{
		dest[p] = src[p];
		p++;
	}
	if (p < n)
	{
		l = p;
		while (l < n)
		{
			dest[l] = '\0';
			l++;
		}
	}
	return (s);
}

/**
 * _strncat - combines two strings
 * @dest: The initial string.
 * @src: The additional string.
 * @n: The maximum number of bytes to utilize.
 * Return: The combined string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int p, l;
	char *s = dest;

	p = 0;
	l = 0;
	while (dest[p] != '\0')
		p++;
	while (src[l] != '\0' && l < n)
	{
		dest[p] = src[l];
		p++;
		l++;
	}
	if (l < n)
		dest[p] = '\0';
	return (s);
}

/**
 * _strchr - searches for a character in a string
 * @s: The string to be examined.
 * @c: The character to be located.
 * Return: A pointer to the memory location in the string.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
