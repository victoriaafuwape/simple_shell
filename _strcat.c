#include "shell.h"

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string to which `src` will be concatenated.
 * @src: The source string to be concatenated to `dest`.
 *
 * Return: A pointer to the destination string (`dest`).
 */
char *_strcat(char *dest, const char *src)
{
	int length = 0;
	int i;

	while (dest[length] != 0)
	{
		length++;
	}
	for (i = 0; src[i] != 0; i++)
	{
		dest[length] = src[i];
		length++;
	}
	dest[length] = '\0';
	return (dest);
}
