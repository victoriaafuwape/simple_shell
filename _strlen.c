#include "main.h"

/**
 * _strlen - Gets the length of a string.
 * @s: A pointer to the string.
 *
 * Return: The length of the string.
 */
size_t _strlen(const char *s)
{
	size_t length = 0;

	while (*(s + length) != 0)
	{
		length++;
	}
	return (length);
}
