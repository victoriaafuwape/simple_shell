#include "main.h"

/**
 * _printf - Prints a string.
 * @str: A pointer to the string.
 *
 * Return: Nothing.
 */
void _printf(const char *str)
{
	if (!str)
		return;

	while (*str)
	{
		write(STDOUT_FILENO, str, 1);
		str++;
	}
}
