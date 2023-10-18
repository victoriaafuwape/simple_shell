#include "main.h"

/**
 * _setenv - Sets or updates an environment variable.
 * @name: Name of the environment variable.
 * @value: Value to set for the environment variable.
 * @overwrite: Flag to indicate whether to overwrite if the variable exists.
 *
 * Return: 0 on success, or NULL if memory allocation fails.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char *env_var;

	if (name == NULL || value == NULL || (overwrite != 0 && overwrite != 1))
		return (-1);

	env_var = _getenv(name);

	if (env_var != NULL && overwrite == 0)
		return (0);

	if (env_var != NULL)
	{
		if (_unsetenv(name) != 0)
			return (-1);
	}

	if (_setenv(name, value, 1) != 0)
		return (-1);

	return (0);
}
