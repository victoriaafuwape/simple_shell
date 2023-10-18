#include "main.h"

/**
 * _strtok - Splits a string and returns an array of each word of the string.
 * @str: A pointer to the string to be tokenized.
 * @delim: A pointer to the delimiter character(s).
 *
 * Return: A pointer to the next token, or NULL if no more tokens are found.
 */
char *_strtok(char *str, const char *delim)
{
	static char *next;
	char *token;

	if (str != NULL)
		next = str;

	if (next == NULL)
		return (NULL);

	while (*next != '\0' && _strchr(delim, *next) != NULL)
		next++;

	if (*next == '\0')
	{
		next = NULL;
		return (NULL);
	}
	token = next;

	while (*next != '\0' && _strchr(delim, *next) == NULL)
	{
		next++;
	}
	if (*next != '\0')
		*next++ = '\0';

	return (token);
}
