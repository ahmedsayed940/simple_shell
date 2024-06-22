#include "shell.h"

/**
 * hsh - main
 * @h: parameters
 * @argv: arguments
 * Return: 0 or 1
 */
int hsh(my_t *h, char **argv)
{
	ssize_t r = 0;
	int ret = 0;

	while (r != -1 && ret != -2)
	{
		my_clear(h);
		if (my_int(h))
			_puts("$ ");
		_eputchar(FLUSH);
		r = _getinput(h);
		if (r != -1)
		{
			my_set(h, argv);
			ret = find_built(h);
			if (ret == -1)
				find_klam(h);
		}
		else if (my_int(h))
			_putchar('\n');
		my_free(h, 0);
	}
	w_history(h);
	my_free(h, 1);
	if (!my_int(h) && h->status)
		exit(h->status);
	if (ret == -2)
	{
		if (h->err_num == -1)
			exit(h->status);
		exit(h->err_num);
	}
	return (ret);
}

/**
 * find_built - builtin command
 * @h: parameters
 * Return: 0 if succes else if else
 */
int find_built(my_t *h)
{
	int i, ret = -1;
	my_built builtintbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].t; i++)
		if (_cmp(h->argv[0], builtintbl[i].t) == 0)
		{
			h->l_count++;
			ret = builtintbl[i].f(h);
			break;
		}
	return (ret);
}

/**
 * find_klam - command
 * @h: parameter
 * Return: void
 */
void find_klam(my_t *h)
{
	char *pa = NULL;
	int i, j;

	h->pa = h->argv[0];
	if (h->l_flag == 1)
	{
		h->l_count++;
		h->l_flag = 0;
	}
	for (i = 0, j = 0; h->arg[i]; i++)
		if (!dlm(h->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	pa = find_pa(h, _getenv(h, "PATH="), h->argv[0]);
	if (pa)
	{
		h->pa = pa;
		fork_klam(h);
	}
	else
	{
		if ((my_int(h) || _getenv(h, "PATH=")
			|| h->argv[0][0] == '/') && is_klam(h, h->argv[0]))
			fork_klam(h);
		else if (*(h->arg) != '\n')
		{
			h->status = 127;
			print_err(h, "NOT FOUND 404 !!\n");
		}
	}
}

/**
 * fork_klam - forks cmd
 * @h: struct
 */
void fork_klam(my_t *h)
{
	pid_t child;

	child = fork();
	if (child == -1)
	{
		perror("ERROR!!");
		return;
	}
	if (child == 0)
	{
		if (execve(h->pa, h->argv, _getenviron(h)) == -1)
		{
			my_free(h, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(h->status));
		if (WIFEXITED(h->status))
		{
			h->status = WEXITSTATUS(h->status);
			if (h->status == 126)
				print_err(h, "Permission denied\n");
		}
	}
}
