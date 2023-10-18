#include "main.h"

/**
 * _unsetenv - Unset an environment variable.
 * @name: The name of the environment variable to unset.
 *
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *name)
{
	if (name == NULL)
		return (-1);

	if (unsetenv(name) != 0)
		return (-1);

	return (0);
}
