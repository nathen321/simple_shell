#ifndef MAIN_H
#define MAIN_H

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@h: the h node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the h line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *h;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void get_cmd(info_t *);
void exec_cmd(info_t *);

/* path.c */
int check_cmd(info_t *, char *);
char *duppl_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int loophsh(char **);

/* error string functions */
void _eputs(char *);
int _eputchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* string functions */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts(const char *, const char *);
char *_strcat(char *, char *);

/* string functions 2 */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* string functions 3 */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* string functions 4 */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* memory functions */
char *_memset(char *, char, unsigned int);
void f_free(char **);
void *realloc_mem(void *, unsigned int, unsigned int);

/* memory functions 2 */
int free_block(void **);

/* more functions */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* more functions 2 */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin emulators */
int exitsh(info_t *);
int change_cd(info_t *);
int help(info_t *);

/* builtin emulators 2 */
int myh(info_t *);
int myalias(info_t *);

/* getline */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* info  */
void rm_inf(info_t *);
void upd_inf(info_t *, char **);
void free_inf(info_t *, int);

/* envirmnt */
char *get_env(info_t *, const char *);
int env(info_t *);
int set_env(info_t *);
int unset_env(info_t *);
int gen_env_list(info_t *);

/* envirmnt 2*/
char **get_environ(info_t *);
int unset_environ(info_t *, char *);
int set_environ(info_t *, char *, char *);

/* file io functions  */
char *get_hf(info_t *info);
int writeh(info_t *info);
int readh(info_t *info);
int cr_h_ls(info_t *info, char *buf, int linecount);
int modifyh(info_t *info);

/* list str*/
list_t *app_node_h(list_t **, const char *, int);
list_t *app_node_t(list_t **, const char *, int);
size_t print_lststr(const list_t *);
int rm_node(list_t **, unsigned int);
void free_ls(list_t **);

/* list str 2 */
size_t get_lslen(const list_t *);
char **convert_ls_str(list_t *);
size_t print_ls(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t node_index(list_t *, list_t *);

/* a chain */
int is_a_chain(info_t *, char *, size_t *);
void verify_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int update_vars(info_t *);
int modify_string(char **, char *);

#endif
