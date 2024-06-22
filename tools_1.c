#include "shell.h"

/**
 * my_int - interactive mode
 * @h: struct
 * Return: 1 or 0
 */
int my_int(my_t *h)
{
	return (isatty(STDIN_FILENO) && h->readfd <= 2);
}

/**
 * dlm -delimeter
 * @c: char
 * @s: string
 * Return: 1 or 0
 */
int dlm(char c, char *s)
{
	while (*s)
		if (*s++ == c)
			return (1);
	return (0);
}

/**
 *_alpha - alphabet
 *@c: char
 *Return: 1 or 0
 */

int _alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts to integer
 *@s: string
 *Return: int
 */

int _atoi(char *s)
{
	int i, sign = 1, f = 0, x;
	unsigned int r = 0;

	for (i = 0;  s[i] != '\0' && f != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			f = 1;
			r *= 10;
			r += (s[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (sign == -1)
		x = -r;
	else
		x = r;

	return (x);
}

/**
 * _erratoi - converts to int
 * @s: string
 * Return: 0 or -1
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int r = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			r *= 10;
			r += (s[i] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}
