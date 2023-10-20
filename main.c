#include "shell.h"

/**
 * handle_interactive_mode - Handle interactive mode of the shell.
 * @pInfo: Pointer to the shell context.
 *
 * Description:
 *   This function handles the interactive mode of the shell, continuously
 *   displaying a command prompt, reading and parsing user input, and executing
 *   commands.
 */
void handle_interactive_mode(ShellContext *pInfo)
{
	while (1)
	{
		pInfo->line_number++;
		write(STDOUT_FILENO, "#Ifvy$ ", 7);
		fflush(stdout);
		read_line(pInfo);
		parse_line(pInfo);
		execute_line(pInfo);
	}
}

/**
 * handle_noninteractive_mode - Handle non-interactive mode of the shell.
 * @pInfo: Pointer to the shell context.
 *
 * Description:
 *   This function handles the non-interactive mode of the shell, reading and
 *   processing input from a file until EOF is reached.
 */
void handle_noninteractive_mode(ShellContext *pInfo)
{
	while (pInfo->eof_reached == 0)
	{
		pInfo->line_number++;
		read_line(pInfo);

		if (pInfo->eof_reached == 1)
		{
			break;
		}

		parse_line(pInfo);
		execute_line(pInfo);
	}
}

/**
 * main - Entry point for the shell program.
 * @argc: The number of arguments passed to the program (unused).
 * @argv: An array of strings representing command-line arguments.
 *
 * Description:
 *   This function serves as the entry point for the shell program. It
 *   initializes the shell context, sets up a signal handler for SIGINT,
 *   and handles both interactive and non-interactive modes of the shell.
 *
 * Return:
 *   Always returns 0 upon successful execution.
 */

int main(int argc __attribute__((unused)), char **argv)
{
	ShellContext Info = {NULL};
	ShellContext *pInfo = &Info;

	pInfo->program_name = argv[0];
	pInfo->line_number = 0;

	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		error_printer("signal", pInfo);
		clean_up(pInfo);
		exit(1);
	}

	if (isatty(STDIN_FILENO))
	{
		handle_interactive_mode(pInfo);
	}
	else
	{
		handle_noninteractive_mode(pInfo);
	}

	clean_up(pInfo);
	return (0);
}
