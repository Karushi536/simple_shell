#ifndef SHELL_H
#define SHELL_H_


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

/* Define structure for info */
typedef struct info_s
{
	char *fname;
	char **argv;
	int line_count;
	int readfd; // TODO: Define the data type for readfd
/* Add the env member to info_t structure */
	struct list_s *env;
} info_t;
/* Define structure for singly linked list */
typedef struct list_s
{
    char *str;
    struct list_s *next;
} list_t;
/* Initialize an instance of the info_t structure */
#define INFO_INIT {NULL, NULL, 0, 0}

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

/* Function prototypes for main.c */
void display_prompt(void);
void user_input(char *command, size_t size);
void execute_command(const char *command);
char *read_line(void);
char **split_line(char *line);
void execute(char **args);
#endif
