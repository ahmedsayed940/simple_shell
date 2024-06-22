#include "shell.h"

/**
 * _chain - chain delimeter
 * @h: struct
 * @buf: buffer
 * @p: pointer
 * Return: 1 or 0
 */
int _chain(my_t *h, char *buf, size_t *p)
{
	size_t x = *p;

	if (buf[x] == '|' && buf[x + 1] == '|')
	{
		buf[x] = 0;
		x++;
		h->klam_buf_type = KLAM_OR;
	}
	else if (buf[x] == '&' && buf[x + 1] == '&')
	{
		buf[x] = 0;
		x++;
		h->klam_buf_type = KLAM_AND;
	}
	else if (buf[x] == ';')
	{
		buf[x] = 0;
		h->klam_buf_type = KLAM_CHAIN;
	}
	else
		return (0);
	*p = x;
	return (1);
}

/**
 * check_chain - checks chain
 * @h: struct
 * @buf: buffer
 * @p: pointer
 * @i: start
 * @len: length
 */
void check_chain(my_t *h, char *buf, size_t *p, size_t i, size_t len)
{
	size_t x = *p;

	if (h->klam_buf_type == KLAM_AND)
	{
		if (h->status)
		{
			buf[i] = 0;
			x = len;
		}
	}
	if (h->klam_buf_type == KLAM_OR)
	{
		if (!h->status)
		{
			buf[i] = 0;
			x = len;
		}
	}

	*p = x;
}

/**
 * re_alias - replace alias
 * @h: struct
 * Return: 1 or 0
 */
int re_alias(my_t *h)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = _nodestarts(h->alias, h->argv[0], '=');
		if (!node)
			return (0);
		free(h->argv[0]);
		p = _chr(node->s, '=');
		if (!p)
			return (0);
		p = _dup(p + 1);
		if (!p)
			return (0);
		h->argv[0] = p;
	}
	return (1);
}

/**
 * re_vars - replace vars
 * @h: struct
 * Return: 1 or 0
 */
int re_vars(my_t *h)
{
	int i = 0;
	list_t *node;

	for (i = 0; h->argv[i]; i++)
	{
		if (h->argv[i][0] != '$' || !h->argv[i][1])
			continue;

		if (!_cmp(h->argv[i], "$?"))
		{
			re_s(&(h->argv[i]),
				_dup(convert_n(h->status, 10, 0)));
			continue;
		}
		if (!_cmp(h->argv[i], "$$"))
		{
			re_s(&(h->argv[i]),
				_dup(convert_n(getpid(), 10, 0)));
			continue;
		}
		node = _nodestarts(h->_env, &h->argv[i][1], '=');
		if (node)
		{
			re_s(&(h->argv[i]),
				_dup(_chr(node->s, '=') + 1));
			continue;
		}
		re_s(&h->argv[i], _dup(""));

	}
	return (0);
}

/**
 * re_s - replaces string
 * @o: old string
 * @n: new string
 * Return: 1 or 0
 */
int re_s(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
