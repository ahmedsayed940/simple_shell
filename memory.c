#include "shell.h"

/**
 **_memset - fills memory
 *@p: pointer
 *@b: bytes
 *@x: amount
 *Return: pointer
 */
char *_memset(char *p, char b, unsigned int x)
{
	unsigned int i;

	for (i = 0; i < x; i++)
		p[i] = b;
	return (p);
}

/**
 * _free - frees string
 * @ss: string of strings
 */
void _free(char **ss)
{
	char **p = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(p);
}

/**
 * _realloc - reallocates
 * @p: pointer
 * @s1: old size
 * @s2: new size
 * Return: pointer
 */
void *_realloc(void *p, unsigned int s1, unsigned int s2)
{
	char *c;

	if (!p)
		return (malloc(s2));
	if (!s2)
		return (free(p), NULL);
	if (s2 == s1)
		return (p);

	c = malloc(s2);
	if (!c)
		return (NULL);

	s1 = s1 < s2 ? s1 : s2;
	while (s1--)
		c[s1] = ((char *)p)[s1];
	free(p);
	return (c);
}

/**
 * bfree - free
 * @p: pointer
 * Return: 1 or 0.
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
