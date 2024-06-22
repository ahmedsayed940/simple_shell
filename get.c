#include "shell.h"

/**
 * get_history - gets history
 * @h: struct
 * Return: string
 */

char *get_history(my_t *h)
{
	char *buf, *d;

	d = _getenv(h, "HOME=");
	if (!d)
		return (NULL);
	buf = malloc(sizeof(char) * (_len(d) + _len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_cpy(buf, d);
	_cat(buf, "/");
	_cat(buf, HIST_FILE);
	return (buf);
}

/**
 * w_history - create file
 * @h: struct
 * Return: 1 or -1
 */
int w_history(my_t *h)
{
	ssize_t fd;
	char *fn = get_history(h);
	list_t *node = NULL;

	if (!fn)
		return (-1);

	fd = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (fd == -1)
		return (-1);
	for (node = h->history; node; node = node->next)
	{
		_putsfd(node->s, fd);
		_putfd('\n', fd);
	}
	_putfd(FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * r_history - reads history
 * @h: struct
 * Return: 0 or else
 */
int r_history(my_t *h)
{
	int i, last = 0, l = 0;
	ssize_t fd, len, fs = 0;
	struct stat st;
	char *buf = NULL, *fn = get_history(h);

	if (!fn)
		return (0);

	fd = open(fn, O_RDONLY);
	free(fn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fs = st.st_size;
	if (fs < 2)
		return (0);
	buf = malloc(sizeof(char) * (fs + 1));
	if (!buf)
		return (0);
	len = read(fd, buf, fs);
	buf[fs] = 0;
	if (len <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fs; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			history_list(h, buf + last, l++);
			last = i + 1;
		}
	if (last != i)
		history_list(h, buf + last, l++);
	free(buf);
	h->h_count = l;
	while (h->h_count-- >= HIST_MAX)
		rm_node(&(h->history), 0);
	renum_history(h);
	return (h->h_count);
}

/**
 * history_list - adds to history
 * @h: Struct
 * @buf: buffer
 * @l: linecount
 * Return: Always 0
 */
int history_list(my_t *h, char *buf, int l)
{
	list_t *node = NULL;

	if (h->history)
		node = h->history;
	_nodeend(&node, buf, l);

	if (!h->history)
		h->history = node;
	return (0);
}

/**
 * renum_history - renumbers history
 * @h: Struct
 * Return: count
 */
int renum_history(my_t *h)
{
	list_t *node = h->history;
	int i = 0;

	while (node)
	{
		node->n = i++;
		node = node->next;
	}
	return (h->h_count = i);
}
