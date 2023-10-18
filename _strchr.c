#include "main.h"

/**
 * _strchr - Finds the first occurrence of a specific character in a string.
 * @s: A pointer to the given string.
 * @c: The integer representation of the character to be found.
 *
 * Return: A pointer to the location where c is found within the string.
 */
char *_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);

	s++;
	}
	return (NULL);
}
