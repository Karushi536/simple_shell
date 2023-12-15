#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

/* for defining custom getline()*/
#define ENABLE_GETLINE 0
#define ENABLE_STRTOK 0

#define HISTORY_FILE_NAME	".simple_shell_history"
#define MAX_HISTORY_ENTRIES	4096

/* to/for number conevrsion */
#define LOWERCASE_ENABLED	1
#define UNSIGNED_ENABLED	2

/* for merging several commands */
#define NORM	0
#define OR		1
#define AND		2
#define CHAIN	3


/* for read&writing buffers */
#define R_BUF_SZ 1024
#define W_BUF_SZ 1024
#define FLUSH_INDICATOR -1


extern char **environ;


/**
 * struct built - it contains a builtin string and related function
 * @cmd: it is the builtin command flag
 * @handler: the function
 */typedef struct lststr
{
	int no;
	char *string;
	struct lststr *next_node;
} lst_t;

/**
 *struct argbundle - this holds pseudo-arguments for a function
 *@argstr: user input fetched by getline
 *@argvstr: string array obtained from user input
 *@path: path of current argument string
 *@argc_no: number of arguments
 *@line_tt: number of errors
 *@error_no: exit()s error code
 *@counter_line: the number of lines in each output
 *@filename: filename of current program
 *@envcpy: singly linked list local environ copy
 *@environcpy: edited environ copy
 *@hist: node in singly linked list
 *@aka: alternate name of node
 *@altered_env: denote environ change
 *@status: d_typeinfo about the last exec'd command
 *@buf_cmd: pointer address to buf_cmd, it is used when chaining commands
 *@buf_operation: variable to specify command opperation ||, &&, ;
 *@rdfiledes: file descriptor from which line input is read
 *@numhist: keeps track of the history line number count
 */
typedef struct argbundle
{
	char *argstr;
	char **argvstr;
	char *path;
	int argc_no;
	unsigned int line_tt;
	int error_no;
	int counter_line;
	char *filename;
	lst_t *envcpy;
	lst_t *hist;
	lst_t *aka;
	char **environcpy;
	int altered_env;
	int status;

	char **buf_cmd;
	int buf_operation;
	int rdfiledes;
	int numhist;
} d_type;

#define SYSTEMINFOINIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct built - this contains a builtin string and related function
 * @cmd: it is the builtin command flag
 * @handler: it is the function
 */
typedef struct modbuild
{
	char *cmd;
	int (*handler)(d_type *);
} tblbuild;

/* used in the file (strparse.c)*/
int cmd_exist(s_type *, char *);
char *dup_str(char *, int, int);
char *cmd_path(s_type *, char *, char *);

/*used in the file (strget.c) */
ssize_t getSysInput(s_type *);
int custGetLine(s_type *, char **, size_t *);
void sigintHandler(int);

/* used in the file (strtoken.c) */
char **tkzStr(char *, char *);
char **tkzStr2(char *, char);

/* used in the file (strexec.c) */
int strexec(s_type *, char **);
int search_builtin(s_type *);
void search_cmd(s_type *);
void child_fork(s_type *);

/* used in the file (loopexec.c) */
int loopexec(char **);

/* used in the file (strerr1.c) */
int atoiErr(char *);
void outputErr(s_type *, char *);
int print_int(int, int);
char *stringify_no(long int, int, int);
void strip_comments(char *);

/* used in the file (str.c) */
int str_len(char *);
int str_cmp(char *, char *);
char *str_start(const char *, const char *);
char *str_cat(char *, char *);

/* used in the file (strerr1.c) */
void output(char *);
int putoutchar(char);
int writechar(char c, int fd);
int writestr(char *string, int fd);

/* used in the file (str1.c) */
char *str_cpy(char *, char *);
char *str_dup(const char *);
void _puts(char *);
int _putchar(char);

/* used in the file (dynmcmemory.c) */
char *filblock(char *, char, unsigned int);
void freemem(char **);
void *reallocmem(void *, unsigned int, unsigned int);

/* used in the file (freemem.c) */
int clearmem(void **);

/* used in the file(stratoi.c)*/
int modsys(s_type *);
int delimchar(char, char *);
int alphachar(int);
int strtint(char *);

/* used in the file (prdfndcmd.c)*/
int exitbin(s_type *);
int cdbin(s_type *);
int helpbin(s_type *);

/* used in the file (prdfndcmd1.c) */
int histdisp(s_type *);
int createaka(s_type *);

/* used in the file (strenv.c)*/
char **strenv(s_type *);
int rmsetenv(s_type *, char *);
int setenvset(s_type *, char *, char *);

/* used in the file (strenviron.c) */
char *retrienv(s_type *, const char *);
int managenv(s_type *);
int modsetenv(s_type *);
int unsetenvrm(s_type *);
int initenvar(s_type *);

/* used in the file (strinfo.c)*/
void resetinfo(s_type *);
void settinginfo(s_type *, char **);
void memfrinfo(s_type *, int);

/* used in the file (nodemod.c) */
lst_t *putnode_start(lst_t **, const char *, int);
lst_t *putnode_end(lst_t **, const char *, int);
size_t printstrlst(const lst_t *);
int rmnodeindex(lst_t **, unsigned int);
void memfree(lst_t **);

/* used in the file (nodemod1.c) */
size_t szlst(const lst_t *);
char **lsttostr(lst_t *);
size_t putlst(const lst_t *);
lst_t *specprefix(lst_t *, char *, char);
ssize_t retrindex(lst_t *, lst_t *);

/* used in the (manhistory.c) */
char *rethistfile(s_type *s_typeinfo);
int wrthist(s_type *s_typeinfo);
int rdhist(s_type *s_typeinfo);
int conhistlist(s_type *d_typeinfo, char *buf, int linecount);
int renohist(s_type *d_typed_typeinfo);

/* used in the (strvar.c) */
int check_opp(s_type *, char *, size_t *);
void chainproc(s_type *, char *, size_t *, size_t, size_t);
int akasub(s_type *);
int varsub(s_type *);
int strsub(char **, char *);

/* used in the (term.c) */
char *str_n_cpy(char *, char *, int);
char *str_n_cat(char *, char *, int);
char *str_chr(char *, char);

#endif
