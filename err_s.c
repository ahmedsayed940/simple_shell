#include "shell.h"

/**
 *_eputs - prints string
 * @s: string
 */
void _eputs(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_eputchar(s[i]);
		i++;
	}
}

/**
 * _eputchar - character to stderr
 * @c: char
 * Return: 1 or -1
 */
int _eputchar(char c)
{
	static int i;
	static char buf[1024];

	if (c == FLUSH || i >= 1024)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - character to fd
 * @c: char
 * @fd: filedescriptor
 * Return: 1 or -1
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[1024];

	if (c == FLUSH || i >= 1024)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - prints string
 * @s: string
 * @fd: filedescriptor
 * Return: i
 */
int _putsfd(char *s, int fd)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _putfd(*s++, fd);
	}
	return (i);
}
