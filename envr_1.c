#include "shell.h"

/**
 * my_env - current environment
 * @h: Struct
 * Return: Always 0
 */
int my_env(my_t *h)
{
	print_liststr(h->_env);
	return (0);
}

/**
 * _getenv - gets environ
 * @h: Struct
 * @n: name
 * Return: value
 */
char *_getenv(my_t *h, const char *n)
{
	list_t *node = h->_env;
	char *p;

	while (node)
	{
		p = _starts(node->s, n);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - Initialize environment
 * @h: Struct
 * Return: Always 0
 */
int my_setenv(my_t *h)
{
	if (h->argc != 3)
	{
		_eputs("ERROR\n");
		return (1);
	}
	if (set_env(h, h->argv[1], h->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Remove environment
 * @h: Struct
 * Return: Always 0
 */
int my_unsetenv(my_t *h)
{
	int i;

	if (h->argc == 1)
	{
		_eputs("Few arguements.\n");
		return (1);
	}
	for (i = 1; i <= h->argc; i++)
		unset_env(h, h->argv[i]);

	return (0);
}
