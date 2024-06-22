#include "shell.h"

/**
 * list_l - length of list
 * @h: head
 * Return: size
 */
size_t list_l(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_s - array of strings
 * @h: head
 * Return: array of strings
 */
char **list_s(list_t *h)
{
	list_t *node = h;
	size_t i = list_l(h), j;
	char **ss;
	char *s;

	if (!h || !i)
		return (NULL);
	ss = malloc(sizeof(char *) * (i + 1));
	if (!ss)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		s = malloc(_len(node->s) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(ss[j]);
			free(ss);
			return (NULL);
		}

		s = _cpy(s, node->s);
		ss[i] = s;
	}
	ss[i] = NULL;
	return (ss);
}

/**
 * print_list - ptint list
 * @h: head
 * Return: size
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_n(h->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _nodestarts - node string
 * @h: head
 * @px: string
 * @c: char
 * Return: node or null
 */
list_t *_nodestarts(list_t *h, char *px, char c)
{
	char *p = NULL;

	while (h)
	{
		p = _starts(h->s, px);
		if (p && ((c == -1) || (*p == c)))
			return (h);
		h = h->next;
	}
	return (NULL);
}

/**
 * get_node - index of node
 * @h: head
 * @node: node
 * Return: index or -1
 */
ssize_t get_node(list_t *h, list_t *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}
