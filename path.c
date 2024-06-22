#include "shell.h"

/**
 * is_klam - command
 * @h: struct
 * @pa: path
 * Return: 1 or 0
 */
int is_klam(my_t *h, char *pa)
{
	struct stat st;

	(void)h;
	if (!pa || stat(pa, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_c - duplicates
 * @pa: PATH
 * @strt: start
 * @stp: stop
 *
 * Return: pointer to new buffer
 */
char *dup_c(char *pa, int strt, int stp)
{
	static char buf[1024];
	int i = 0, j = 0;

	for (j = 0, i = strt; i < stp; i++)
		if (pa[i] != ':')
			buf[j++] = pa[i];
	buf[j] = 0;
	return (buf);
}

/**
 * find_pa - find PATH
 * @h: struct
 * @pa: PATH
 * @klam: cmd
 *
 * Return: path or NULL
 */
char *find_pa(my_t *h, char *pa, char *klam)
{
	int i = 0, pos = 0;
	char *path;

	if (!pa)
		return (NULL);
	if ((_len(klam) > 2) && _starts(klam, "./"))
	{
		if (is_klam(h, klam))
			return (klam);
	}
	while (1)
	{
		if (!pa[i] || pa[i] == ':')
		{
			path = dup_c(pa, pos, i);
			if (!*path)
				_cat(path, klam);
			else
			{
				_cat(path, "/");
				_cat(path, klam);
			}
			if (is_klam(h, path))
				return (path);
			if (!pa[i])
				break;
			pos = i;
		}
		i++;
	}
	return (NULL);
}
