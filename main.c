#include "shell.h"

/**
 * main - Entry point for a simple shell program.
 * @argc: The number of arguments passed to the program (unused).
 * @argv: An array of strings representing command-line arguments.
 *
 * Description:
 *   This function serves as the entry point for a simple shell program.
 *   It initializes a `ShellContext` structure with the program's name from
 *   'argv'. It also sets up a signal handler for SIGINT. If the program is run
 *   interactively, it continuously displays a command prompt,
 *   reads and parses user input, and executes commands.
 *   If not run interactively, it processes a single command.
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
	else
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

	clean_up(pInfo);
	return (0);
}
	/**
	else
	{
		pInfo->line_number++;
		read_line(pInfo);
		parse_line(pInfo);
		execute_line(pInfo);
	}

	clean_up(pInfo);

	return (0);
}
	*/
