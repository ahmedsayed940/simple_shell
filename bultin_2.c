#include "shell.h"
/**
 * unset_a - unsets alias
 * @h: struct
 * @s: string
 * Return: 0 or 1
 */
int unset_a(my_t *h, char *s)
{
	char *p, c;
	int ret;

	p = _chr(s, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = rm_node(&(h->alias),
		get_node(h->alias, _nodestarts(h->alias, s, -1)));
	*p = c;
	return (ret);
}

/**
 * set_a - sets alias
 * @h: struct
 * @s: string
 * Return: 0 or 1
 */
int set_a(my_t *h, char *s)
{
	char *p;

	p = _chr(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_a(h, s));

	unset_a(h, s);
	return (_nodeend(&(h->alias), s, 0) == NULL);
}

/**
 * print_alias - prints alias
 * @node: node
 * Return: 0 or 1
 */
int print_alias(list_t *node)
{
	char *p = NULL, *y = NULL;

	if (node)
	{
		p = _chr(node->s, '=');
		for (y = node->s; y <= p; y++)
			_putchar(*y);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics alias
 * @h: Struct
 * Return: Always 0
 */
int my_alias(my_t *h)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (h->argc == 1)
	{
		node = h->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; h->argv[i]; i++)
	{
		p = _chr(h->argv[i], '=');
		if (p)
			set_a(h, h->argv[i]);
		else
			print_alias(_nodestarts(h->alias, h->argv[i], '='));
	}

	return (0);
}
