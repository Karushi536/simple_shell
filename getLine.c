#include "shell.h"

/**
 * input_buf - Gathers and buffers chained commands for subsequent processing
 * @info: Parameter struct containing necessary information.
 * @buf: Address of the buffer where commands are stored.
 * @len: Address of the variable tracking the length of the buffer.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t q = 0;
	size_t len_p = 0;

	if (!*len) /* If there is nothing left in the buffer, refill it */
	{
		/* Free the memory occupied by info->cmd_buf */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		q = getline(buf, &len_p, stdin);
#else
		q = _getline(info, buf, &len_p);
#endif
		if (q > 0)
		{
			if ((*buf)[q - 1] == '\n')
			{
				(*buf)[q - 1] = '\0'; /* Eliminate the trailing newline character */
				q--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* Check if ';' is present in *buf, indicating a command chain */
			{
				*len = q;
				info->cmd_buf = buf;
			}
		}
	}
	return (q);
}

/**
 * get_input - retrieves a line excluding the newline character
 * @info: Parameter struct containing relevant information.
 *
 * Return: The number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* Buffer for the ';' command chain */
	static size_t i, l, len;
	ssize_t q = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	q = input_buf(info, &buf, &len);
	if (q == -1) /* End of File (EOF) */
		return (-1);
	if (len)	/* Commands are still present in the chain buffer */
	{
		l = i; /* Initialize a new iterator to the current position in buf */
		p = buf + i; /* Obtain a pointer for return */

		check_chain(info, buf, &l, i, len);
		while (l < len) /* Iterate to the next semicolon or reach the end */
		{
			if (is_chain(info, buf, &l))
				break;
			l++;
		}

		i = l + 1; /* Increment past the nullified ';' */
		if (i >= len) /* Has the end of the buffer been reached? */
		{
			i = len = 0; /* Reset the position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Return a pointer to the current command position */
		return (_strlen(p)); /* Return the length of the current command */
	}

	*buf_p = buf; /* If not a chain, return the buffer from _getline() */
	return (q); /* Return the length of the buffer from _getline() */
}

/**
 * read_buf - function name reads a buffer
 * @info: this is parameter struct containing relevant information.
 * @buf: this is buffer to be read.
 * @i: this is size of the buffer.
 *
 * Return: q.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t q = 0;

	if (*i)
		return (0);
	q = read(info->readfd, buf, READ_BUF_SIZE);
	if (q >= 0)
		*i = q;
	return (q);
}

/**
 * _getline - reads the next line of input from STDIN
 * @info: Parameter struct containing necessary information.
 * @ptr: Address of the pointer to the buffer (can be preallocated or NULL)
 * @length: Size of the preallocated ptr buffer if not NULL.
 *
 * Return: The read string.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t q = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	q = read_buf(info, buf, &len);
	if (q == -1 || (q == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* Memory Allocation Failure! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - function name blocks the Ctrl-C signal
 * @sig_num: This is the signal number.
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
