#include "shell.h"

/**
 * _strlen -this function name brings back the length of a string
 * @s: function parameter The string that length needs checking
 *
 * Return: the Integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - fn Compares two strings lexicographically.
 * @s1: fp one The first string.
 * @s2: fp two The second string.
 *
 * Return: Negative if s1 is less than s2,
 *	positive if s1 is greater than s2,
 *	zero if s1 is equal to s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - fn Checks if the substring 'needle' starts with 'haystack'.
 * @haystack: fp one The string to search.
 * @needle: fp two The substring to find.
 *
 * Return: Address of the next character in 'haystack' or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - fn Concatenates the contents of two strings.
 * @dest: fp one The destination buffer.
 * @src: fp two The source buffer.
 *
 * Return: A pointer to the destination buffer having the concatenated strings.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
