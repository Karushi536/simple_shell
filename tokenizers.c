#include "shell.h"

/**
 * **strtow - fn divides a string into words, ignoring repeated delimiters
 * @str: function parameter one The input string.
 * @d: function parameter two The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *d)
{
	int i, l, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, l = 0; l < numwords; l++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[l] = malloc((k + 1) * sizeof(char));
		if (!s[l])
		{
			for (k = 0; k < l; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[l][m] = str[i++];
		s[l][m] = 0;
	}
	s[l] = NULL;
	return (s);
}

/**
 * **strtow2 - fn divides a string into words using a specified delimiter
 * @str: funtion parameter one The input string.
 * @d: funtion parameter two The delimiter.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow2(char *str, char d)
{
	int i, l, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, l = 0; l < numwords; l++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[l] = malloc((k + 1) * sizeof(char));
		if (!s[l])
		{
			for (k = 0; k < l; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[l][m] = str[i++];
		s[l][m] = 0;
	}
	s[l] = NULL;
	return (s);
}
