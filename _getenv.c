#include "main.h"

/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable to retrieve.
 *
 * Return: A pointer to the value of the variable if found, NULL if otherwise.
 */
char *_getenv(const char *name)
{
	int i, len;
	char *var;

	for (i = 0; environ[i] != NULL; i++)
	{
		var = environ[i];
		len = _strlen(name);

		if (_strncmp(var, name, len) == 0 && var[len] == '=')
			return (&var[len + 1]);
	}

	return (NULL);
}
