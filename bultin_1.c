#include "shell.h"

/**
 * my_exit - exit
 * @h: Struct
 *  Return: exit
 */
int my_exit(my_t *h)
{
	int x;

	if (h->argv[1])
	{
		x = _erratoi(h->argv[1]);
		if (x == -1)
		{
			h->status = 2;
			print_err(h, "NOT a number: ");
			_eputs(h->argv[1]);
			_eputchar('\n');
			return (1);
		}
		h->err_num = _erratoi(h->argv[1]);
		return (-2);
	}
	h->err_num = -1;
	return (-2);
}

/**
 * my_cd - change cd
 * @h: Struct
 * Return: Always 0
 */
int my_cd(my_t *h)
{
	char *s, *d, buf[1024];
	int ret;

	s = getcwd(buf, 1024);
	if (!s)
		_puts("ERROR!!\n");
	if (!h->argv[1])
	{
		d = _getenv(h, "HOME=");
		if (!d)
			ret = chdir((d = _getenv(h, "PWD=")) ? d : "/");
		else
			ret = chdir(d);
	}
	else if (_cmp(h->argv[1], "-") == 0)
	{
		if (!_getenv(h, "OLD PWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(h, "OLD PWD=")), _putchar('\n');
		ret = chdir((d = _getenv(h, "OLD PWD=")) ? d : "/");
	}
	else
		ret = chdir(h->argv[1]);
	if (ret == -1)
	{
		print_err(h, "can't CD to ");
		_eputs(h->argv[1]), _eputchar('\n');
	}
	else
	{
		set_env(h, "OLD PWD", _getenv(h, "PWD="));
		set_env(h, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * my_help - changes the current directory of the process
 * @h: Struct
 *  Return: Always 0
 */
int my_help(my_t *h)
{
	char **a;

	a = h->argv;
	_puts("WORKS \n");
	if (0)
		_puts(*a);
	return (0);
}

/**
 * my_history - history list
 * @h: Struct
 *  Return: Always 0
 */
int my_history(my_t *h)
{
	print_list(h->history);
	return (0);
}
