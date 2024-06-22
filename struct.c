#include "shell.h"

/**
 * my_clear - my_t struct
 * @h: struct
 */
void my_clear(my_t *h)
{
	h->arg = NULL;
	h->argv = NULL;
	h->pa = NULL;
	h->argc = 0;
}

/**
 * my_set - my_t struct
 * @h: struct
 * @av: argument
 */
void my_set(my_t *h, char **av)
{
	int i = 0;

	h->fname = av[0];
	if (h->arg)
	{
		h->argv = _strtow(h->arg, " \t");
		if (!h->argv)
		{

			h->argv = malloc(sizeof(char *) * 2);
			if (h->argv)
			{
				h->argv[0] = _dup(h->arg);
				h->argv[1] = NULL;
			}
		}
		for (i = 0; h->argv && h->argv[i]; i++)
			;
		h->argc = i;

		re_alias(h);
		re_vars(h);
	}
}

/**
 * my_free - frees my_t struct
 * @h: struct
 * @a: true if free
 */
void my_free(my_t *h, int a)
{
	_free(h->argv);
	h->argv = NULL;
	h->pa = NULL;
	if (a)
	{
		if (!h->klam_buf)
			free(h->arg);
		if (h->_env)
			_freelist(&(h->_env));
		if (h->history)
			_freelist(&(h->history));
		if (h->alias)
			_freelist(&(h->alias));
		_free(h->_environ);
			h->_environ = NULL;
		bfree((void **)h->klam_buf);
		if (h->readfd > 2)
			close(h->readfd);
		_putchar(FLUSH);
	}
}
