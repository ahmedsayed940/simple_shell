#include "shell.h"

/**
 * _populate - populates env
 * @h: Struct
 * Return: Always 0
 */
int _populate(my_t *h)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_nodeend(&node, environ[i], 0);
	h->_env = node;
	return (0);
}

/**
 * _getenviron - returns environ
 * @h: Struct
 * Return: Always 0
 */
char **_getenviron(my_t *h)
{
	if (!h->_environ || h->env_ch)
	{
		h->_environ = list_s(h->_env);
		h->env_ch = 0;
	}

	return (h->_environ);
}

/**
 * unset_env - Remove environment
 * @h: Struct
 * @v: var
 * Return: 1 or 0
 */
int unset_env(my_t *h, char *v)
{
	list_t *node = h->_env;
	size_t i = 0;
	char *p;

	if (!node || !v)
		return (0);

	while (node)
	{
		p = _starts(node->s, v);
		if (p && *p == '=')
		{
			h->env_ch = rm_node(&(h->_env), i);
			i = 0;
			node = h->_env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (h->env_ch);
}

/**
 * set_env - Initialize environment
 * @h: Struct
 * @v: var
 * @x: value
 * Return: Always 0
 */
int set_env(my_t *h, char *v, char *x)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!v || !x)
		return (0);

	buf = malloc(_len(v) + _len(x) + 2);
	if (!buf)
		return (1);
	_cpy(buf, v);
	_cat(buf, "=");
	_cat(buf, x);
	node = h->_env;
	while (node)
	{
		p = _starts(node->s, v);
		if (p && *p == '=')
		{
			free(node->s);
			node->s = buf;
			h->env_ch = 1;
			return (0);
		}
		node = node->next;
	}
	_nodeend(&(h->_env), buf, 0);
	free(buf);
	h->env_ch = 1;
	return (0);
}
