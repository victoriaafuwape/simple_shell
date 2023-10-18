#include "main.h"

/**
 * handle_exit - Handles the "exit" command.
 * @input: The input string to process.
 *
 * Return: Nothing.
 */
void handle_exit(char *input)
{
	char *arg;
	int status;

	if (_strncmp(input, "exit", 4) == 0)
	{
		arg = input + 4;
		if (*arg == '\n')
		{
			free(input);
			exit(0);
		}
		else if (*arg == ' ')
		{
			status = atoi(arg);
			free(input);
			exit(status);
		}
	}
}

/**
 * main - Entry point for a simple shell program.
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line argument strings.
 *
 * Return: 0 on successful execution.
 */
int main(int argc __attribute__((unused)), char **argv)
{
	struct data d;
	ssize_t length = 0;
	size_t buffer_size = 0;
	char *input = NULL;
	int input_from_terminal = isatty(STDIN_FILENO);

	d.shell_name = argv[0];
	while (length >= 0)
	{
		if (input_from_terminal)
		{
			printf("#Ifvy$ ");
			fflush(stdout);
		}
		length = _getline(&input, &buffer_size, stdin);
		if (length == -1)
			break;

		else if (*input != '\0' && *input != '#')
		{
			handle_exit(input);
			handle_env(input, environ);
			handle_setenv(input);
			handle_unsetenv(input);
			if (_strncmp(input, "cd ", 3) == 0 ||
			    _strncmp(input, "cd\n", 3) == 0)
				handle_cd(input);
			else
				create_child(input, length, &d);
		}
		free(input);
		input = NULL;
		buffer_size = 0;
	}
	if (input)
	{
		free(input);
	}
	return (0);
}
