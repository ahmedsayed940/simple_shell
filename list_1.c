#include "shell.h"

/**
 * _node - adds node
 * @h: head
 * @s: string
 * @n: index
 * Return: size
 */
list_t *_node(list_t **h, const char *s, int n)
{
	list_t *_new;

	if (!h)
		return (NULL);
	_new = malloc(sizeof(list_t));
	if (!_new)
		return (NULL);
	_memset((void *)_new, 0, sizeof(list_t));
	_new->n = n;
	if (s)
	{
		_new->s = _dup(s);
		if (!_new->s)
		{
			free(_new);
			return (NULL);
		}
	}
	_new->next = *h;
	*h = _new;
	return (_new);
}

/**
 * _nodeend - adds node to end
 * @h: head
 * @s: string
 * @n: index
 * Return: size
 */
list_t *_nodeend(list_t **h, const char *s, int n)
{
	list_t *_new, *node;

	if (!h)
		return (NULL);

	node = *h;
	_new = malloc(sizeof(list_t));
	if (!_new)
		return (NULL);
	_memset((void *)_new, 0, sizeof(list_t));
	_new->n = n;
	if (s)
	{
		_new->s = _dup(s);
		if (!_new->s)
		{
			free(_new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = _new;
	}
	else
		*h = _new;
	return (_new);
}

/**
 * print_liststr - prints string
 * @h: head
 * Return: size
 */
size_t print_liststr(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * rm_node - delete node
 * @h: head
 * @n: index
 * Return: 1 or 0
 */
int rm_node(list_t **h, unsigned int n)
{
	list_t *node, *prev;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!n)
	{
		node = *h;
		*h = (*h)->next;
		free(node->s);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (i == n)
		{
			prev->next = node->next;
			free(node->s);
			free(node);
			return (1);
		}
		i++;
		prev = node;
		node = node->next;
	}
	return (0);
}

/**
 * _freelist - free nodes
 * @h: head
 */
void _freelist(list_t **h)
{
	list_t *node, *next, *head;

	if (!h || !*h)
		return;
	head = *h;
	node = head;
	while (node)
	{
		next = node->next;
		free(node->s);
		free(node);
		node = next;
	}
	*h = NULL;
}
