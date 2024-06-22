#include "shell.h"

/**
 * print_err - error message
 * @h: struct
 * @s: string
 * Return: 0 or -1
 */
void print_err(my_t *h, char *s)
{
	_eputs(h->fname);
	_eputs(": ");
	print_d(h->l_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(h->argv[0]);
	_eputs(": ");
	_eputs(s);
}

/**
 * print_d - prints base 10
 * @x: input
 * @fd: filedescriptor
 * Return: int
 */
int print_d(int x, int fd)
{
	int (*klam)(char) = _putchar;
	int i, num = 0;
	unsigned int m6lq, tmp;

	if (fd == STDERR_FILENO)
		klam = _eputchar;
	if (x < 0)
	{
		m6lq = -x;
		klam('-');
		num++;
	}
	else
		m6lq = x;
	tmp = m6lq;
	for (i = 100000000; i > 1; i /= 10)
	{
		if (m6lq / i)
		{
			klam('0' + tmp / i);
			num++;
		}
		tmp %= i;
	}
	klam('0' + tmp);
	num++;

	return (num);
}

/**
 * convert_n - clone of itoa
 * @num: number
 * @b: base
 * @f: flags
 * Return: string
 */
char *convert_n(long int num, int b, int f)
{
	static char *a;
	static char buf[50];
	char sign = 0;
	char *p;
	unsigned long n = num;

	if (!(f & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	a = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';

	do	{
		*--p = a[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--p = sign;
	return (p);
}

/**
 * rm_comments - replaces '#' with '\0'
 * @p: pointer
 * Return: Always 0;
 */
void rm_comments(char *p)
{
	int i;

	for (i = 0; p[i] != '\0'; i++)
		if (p[i] == '#' && (!i || p[i - 1] == ' '))
		{
			p[i] = '\0';
			break;
		}
}
