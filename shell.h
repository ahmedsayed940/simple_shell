#ifndef SHELL_H
#define SHELL_H

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

#define FLUSH -1
#define KLAM_NORM		0
#define KLAM_OR			1
#define KLAM_AND		2
#define KLAM_CHAIN		3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE		0
#define USE_STRTOK		0
#define HIST_FILE		".simple_shell_history"
#define HIST_MAX		4096

extern char **environ;


/**
 * struct list_str - singly linked list
 * @n: the number field
 * @s: string
 * @next: next
 */
typedef struct list_str
{
	int n;
	char *s;
	struct list_str *next;
} list_t;

/**
 *struct info - info
 *@arg: args
 *@argv: array of args
 *@pa: path
 *@argc: arg count
 *@l_count: count
 *@err_num: err
 *@l_flag: flag
 *@fname: filename
 *@_env: copy env
 *@_environ: env
 *@history: history
 *@alias: alias
 *@env_ch: env changed
 *@status: status
 *@klam_buf: pointer
 *@klam_buf_type: ||, &&, ;
 *@readfd: fd
 *@h_count: history count
 */
typedef struct info
{
	char *arg;
	char **argv;
	char *pa;
	int argc;
	unsigned int l_count;
	int err_num;
	int l_flag;
	char *fname;
	list_t *_env;
	list_t *history;
	list_t *alias;
	char **_environ;
	int env_ch;
	int status;

	char **klam_buf;
	int klam_buf_type;
	int readfd;
	int h_count;
} my_t;

#define _INFO \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct built_in - builtin
 *@t: flag
 *@f: function
 */
typedef struct built_in
{
	char *t;
	int (*f)(my_t *);
} my_built;


/* HSH.c */
int hsh(my_t *, char **);
int find_built(my_t *);
void find_klam(my_t *);
void fork_klam(my_t *);

/* PATH.c */
int is_klam(my_t *, char *);
char *dup_c(char *, int, int);
char *find_pa(my_t *, char *, char *);

/* ERR_S.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char, int);
int _putsfd(char *, int);

/* STRINGS.c */
int _len(char *);
int _cmp(char *, char *);
char *_starts(const char *, const char *);
char *_cat(char *, char *);
char *_cpy(char *, char *);
char *_dup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_chr(char *, char);
char **_strtow(char *, char *);
char **_strtow2(char *, char);

/* MEMORY.c */
char *_memset(char *, char, unsigned int);
void _free(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

/* TOOLS.c */
int my_int(my_t *);
int dlm(char, char *);
int _alpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_err(my_t *, char *);
int print_d(int, int);
char *convert_n(long int, int, int);
void rm_comments(char *);

/* BUILTIN.c */
int my_exit(my_t *);
int my_cd(my_t *);
int my_help(my_t *);
int my_history(my_t *);
int unset_a(my_t *, char *);
int set_a(my_t *, char *);
int print_alias(list_t *);
int my_alias(my_t *);

/* GETLINE.c */
ssize_t i_buf(my_t *, char **, size_t *);
ssize_t _getinput(my_t *);
ssize_t r_buf(my_t *, char *, size_t *);
int _getline(my_t *, char **, size_t *);
void _sig(int);

/* MY.c module */
void my_clear(my_t *);
void my_set(my_t *, char **);
void my_free(my_t *, int);

/* ENV.c */
char *_getenv(my_t *, const char *);
int my_env(my_t *);
int my_setenv(my_t *);
int my_unsetenv(my_t *);
int _populate(my_t *);
char **_getenviron(my_t *);
int unset_env(my_t *, char *);
int set_env(my_t *, char *, char *);

/* IO.c */
char *get_history(my_t *h);
int w_history(my_t *h);
int r_history(my_t *h);
int history_list(my_t *, char *, int);
int renum_history(my_t *h);

/* LIST.c */
list_t *_node(list_t **, const char *, int);
list_t *_nodeend(list_t **, const char *, int);
size_t print_liststr(const list_t *);
int rm_node(list_t **, unsigned int);
void _freelist(list_t **);
size_t list_l(const list_t *);
char **list_s(list_t *);
size_t print_list(const list_t *);
list_t *_nodestarts(list_t *, char *, char);
ssize_t get_node(list_t *, list_t *);

/* CHAIN.c */
int _chain(my_t *, char *, size_t *);
void check_chain(my_t *, char *, size_t *, size_t, size_t);
int re_alias(my_t *);
int re_vars(my_t *);
int re_s(char **, char *);

#endif
