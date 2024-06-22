#include "shell.h"

/**
 * i_buf - buffer
 * @h: struct
 * @buf: buffer
 * @len: address
 * Return: bytes
 */
ssize_t i_buf(my_t *h, char **buf, size_t *len)
{
	ssize_t y = 0;
	size_t p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, _sig);
#if USE_GETLINE
		y = getline(buf, &p, stdin); /* rag3*/
#else
		y = _getline(h, buf, &p);
#endif
		if (y > 0)
		{
			if ((*buf)[y - 1] == '\n')
			{
				(*buf)[y - 1] = '\0';
				y--;
			}
			h->l_flag = 1;
			rm_comments(*buf);
			history_list(h, *buf, h->h_count++);
			{
				*len = y;
				h->klam_buf = buf;
			}
		}
	}
	return (y);
}

/**
 * _getinput - gets a line
 * @h: struct
 * Return: bytes
 */
ssize_t _getinput(my_t *h)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t y = 0;
	char **pp = &(h->arg), *p;

	_putchar(FLUSH);
	y = i_buf(h, &buf, &len);
	if (y == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(h, buf, &j, i, len);
		while (j < len)
		{
			if (_chain(h, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			h->klam_buf_type = KLAM_NORM;
		}

		*pp = p;
		return (_len(p));
	}

	*pp = buf;
	return (y);
}

/**
 * r_buf - reads buffer
 * @h: struct
 * @buf: buffer
 * @z: size
 * Return: y
 */
ssize_t r_buf(my_t *h, char *buf, size_t *z)
{
	ssize_t y = 0;

	if (*z)
		return (0);
	y = read(h->readfd, buf, 1024);
	if (y >= 0)
		*z = y;
	return (y);
}

/**
 * _getline - gets the next line
 * @h: struct
 * @ptr: pointer
 * @l: size
 * Return: z
 */
int _getline(my_t *h, char **ptr, size_t *l)
{
	static char buf[1024];
	static size_t i, len;
	size_t j;
	ssize_t y = 0, z = 0;
	char *p = NULL, *pp = NULL, *c;

	p = *ptr;
	if (p && l)
		z = *l;
	if (i == len)
		i = len = 0;

	y = r_buf(h, buf, &len);
	if (y == -1 || (y == 0 && len == 0))
		return (-1);

	c = _chr(buf + i, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : len;
	pp = _realloc(p, z, z ? z + j : j + 1);
	if (!pp)
		return (p ? free(p), -1 : -1);

	if (z)
		_strncat(pp, buf + i, j - i);
	else
		_strncpy(pp, buf + i, j - i + 1);

	z += j - i;
	i = j;
	p = pp;

	if (l)
		*l = z;
	*ptr = p;
	return (z);
}

/**
 * _sig - blocks ctrl-C
 * @num: number
 * Return: void
 */
void _sig(__attribute__((unused))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH);
}
