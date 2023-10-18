#include "main.h"

/**
 * handle_env - Handle the "env" command to print environment variables.
 * @input: The input string to process.
 * @env_var: A pointer to an array of environment variables.
 *
 * Return: Nothing.
 */
void handle_env(char *input, char **env_var)
{
	if (_strncmp(input, "env\n", 4) == 0)
	{
		while (*env_var)
		{
			_printf(*env_var);
			_putchar(10);
			env_var++;
		}
	}
}

/**
 * handle_setenv - Handles the "setenv" command.
 * @input: The input string to process.
 *
 * Return: Nothing.
 */
void handle_setenv(char *input)
{
	char *var_name, *var_value, *err;
	int result;

	if (_strncmp(input, "setenv", 6) == 0)
	{
		var_name = input + 6;
		var_name = _strtok(var_name, " ");
		var_value = _strtok(NULL, " ");
		if (var_name != NULL && var_value != NULL)
		{
			result = _setenv(var_name, var_value, 1);
			if (result != 0)
			{
				err = "Failed to set environment variable.\n";
				write(STDERR_FILENO, err, _strlen(err));
			}
		}
		else
		{
			err = "Invalid syntax. Usage: setenv VARIABLE VALUE\n";
			write(STDERR_FILENO, err, _strlen(err));
		}
	}
}

/**
 * handle_unsetenv - Handles the "unsetenv" command.
 * @input: The input string to process.
 *
 * Return: Nothing.
 */
void handle_unsetenv(char *input)
{
	char *var_name;
	char *err;
	int result;

	if (_strncmp(input, "unsetenv", 8) == 0)
	{
		var_name = input + 8;
		var_name = _strtok(var_name, " ");
		if (var_name != NULL)
		{
			result = _unsetenv(var_name);
			if (result != 0)
			{
				err = "Failed to unset environment variable.\n";
				write(STDERR_FILENO, err, _strlen(err));
			}
		}
		else
		{
			err = "Invalid syntax. Usage: unsetenv VARIABLE\n";
			write(STDERR_FILENO, err, _strlen(err));
		}
	}
}
