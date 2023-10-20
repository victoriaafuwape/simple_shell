#include "shell.h"

/**
 * _strcpy - Copies the string pointed to by the source string.
 * @dest: A pointer to the destination string.
 * @src: A pointer to th source string.
 *
 * Return: A pointer to what was copied.
 */
char *_strcpy(char *dest, const char *src)
{
	char *mainDest;

	mainDest = dest;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';

	return (mainDest);
}
