#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>

#define STDERR_FILENO 2

/* Define flags for convert_number */
#define CONVERT_UNSIGNED 1
#define CONVERT_LOWERCASE 2

/**
 * struct list_s - singly linked list
 * @str: string data
 * @next: points to the next node
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

/**
 * struct info_s - shell information structure
 * @fname: program filename
 * @argv: argument vector
 * @line_count: line count
 * @readfd: file descriptor for reading
 * @status: command execution status
 * @err_num: error number
 * @env: linked list local copy of environ
 */
typedef struct info_s
{
	char *fname;
	char **argv;
	int line_count;
	int readfd;
	int status;
	int err_num;
	list_t *env;
} info_t;

/* Initialize an instance of the info_t structure */
#define INFO_INIT {NULL, NULL, 0, 0, 0, 0, NULL}

/**
 * struct passinfo - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} passinfo_t;

/* Function prototypes for errors1.c */
int _erratoi(char *s);
void print_error(info_t *info, char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

/* Function prototypes for environ.c */
int _myenv(info_t *info);
char *_getenv(info_t *info, const char *name);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);

/* Function prototypes for builtin.c */
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

/* Function prototypes for main.c */
void display_prompt(void);
void user_input(char *command, size_t size);
void execute_command(const char *command);
char *read_line(void);
char **split_line(char *line);
void execute(char **args);

/* Function declarations for getenv.c */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);

/* realloc.c */
char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* Function declarations for lists.c */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

/* Function declarations for getLine.c */
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

/* Function declarations for history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* Function declarations for memory.c */
int bfree(void **ptr);

/* Function declarations for string1.c */
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
void _puts(const char *str);
int _putchar(char c);

/* Function declarations for string.c */
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, const char *src);

/* Function declarations for builtin1.c */
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);

/* tokenizer.c */
char **ms_strtow(char *str, char *d);
char **ms_strtow2(char *str, char d);

/* lists1.c */
size_t ms_list_len(const list_t *h);
char **ms_list_to_strings(list_t *head);
size_t ms_print_list(const list_t *h);
list_t *ms_node_starts_with(list_t *node, char *prefix, char c);
ssize_t ms_get_node_index(list_t *head, list_t *node);

/**
 * ms_clear_info - initializes info_t struct
 * @info: struct address
 */
void ms_clear_info(info_t *info);

/**
 * ms_set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void ms_set_info(info_t *info, char **av);

/**
 * ms_free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void ms_free_info(info_t *info, int all);

/**
 * ms_is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int ms_is_cmd(info_t *info, char *path);

/**
 * ms_dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *ms_dup_chars(char *pathstr, int start, int stop);

/**
 * ms_find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *ms_find_path(info_t *info, char *pathstr, char *cmd);

/* Function prototypes for new functions in shell_loop.c */
int ms_shell_loop(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);

#endif /* SHELL_H */

