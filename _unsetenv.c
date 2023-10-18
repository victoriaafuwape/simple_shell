#include "main.h"

/**
 * _unsetenv - Unset an environment variable.
 * @name: The name of the environment variable to unset.
 *
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *name)
{
	int i;

	if (name == NULL)
		return (-1);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, _strlen(name))
		    == 0 && environ[i][_strlen(name)] == '=')
		{
			while (environ[i] != NULL)
			{
				environ[i] = environ[i + 1];
				i++;
			}
			return (0);
		}
	}
	return (-1);
}
