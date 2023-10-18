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
	char *env_var, *new_env_var;
	char **new_environ;
	int i, env_count = 0;

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
	new_env_var = malloc(_strlen(name) + _strlen(value) + 2);
	if (new_env_var == NULL)
		return (-1);
	_strcpy(new_env_var, name);
	_strcat(new_env_var, "=");
	_strcat(new_env_var, value);
	while (environ[env_count] != NULL)
		env_count++;
	new_environ = malloc(sizeof(char *) * (env_count + 2));
	if (new_environ == NULL)
	{
		free(new_env_var);
		return (-1);
	}
	for (i = 0; i < env_count; i++)
		new_environ[i] = environ[i];
	new_environ[env_count] = new_env_var;
	new_environ[env_count + 1] = NULL;
	environ = new_environ;
	return (0);
}
