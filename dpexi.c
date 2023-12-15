#include "shell.h"

/**
 * _strncpy - this copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
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
 **_strncat - it concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
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
 * _strchr - it locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
