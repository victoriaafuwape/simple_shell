#include "shell.h"

/**
 * _strncmp - Compares the first n characters of the two strings s1 and s2.
 * @s1: A pointer to the first string you want to compare.
 * @s2: A pointer to the second string you want to compare.
 * @n: The maximum number of characters to compare.
 *
 * Return: An integer value based on the comparison.
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}

		if (*s1 == '\0')
		{
			return (0);
		}

		s1++;
		s2++;
		n--;
	}

	return (0);
}
