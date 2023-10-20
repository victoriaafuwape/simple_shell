#include "shell.h"

/**
 * signal_handler - Handle the SIGINT signal.
 * @signum: The signal number (SIGINT).
 *
 * Description:
 *   This function is a signal handler for SIGINT (Ctrl+C). When SIGINT is
 *   received, it writes a newline and a command prompt to the standard output.
 */
void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n#Ifvy$ ", 8);
		fflush(stdout);
	}
}

/**
 * clean_up - Perform cleanup operations.
 *
 * Description:
 *   This function performs cleanup operations by freeing dynamically allocated
 *   memory for 'pInfo->args' and 'pInfo->line'. It sets these pointers to NULL
 *   after freeing the memory.
 */
void clean_up(ShellContext *pInfo)
{
	if (pInfo->args)
	{
		free(pInfo->args);
		pInfo->args = NULL;
	}

	if (pInfo->line)
	{
		free(pInfo->line);
		pInfo->line = NULL;
	}
}

/**
 * error_printer - Print an error message to the standard error.
 * @cmd_name: The name of the command that caused the error.
 *
 * Description:
 *   This function prints an error message to the standard error (stderr).
 *   It includes the program name, line number, and the name of the command
 *   that caused the error. It is used to report command not found errors.
 */
void error_printer(char *cmd_name, ShellContext *pInfo)
{
	int num, temp_num, digit_count, i;
	char ch;

	write(STDERR_FILENO, pInfo->program_name, _strlen(pInfo->program_name));
	write(STDERR_FILENO, ": ", 2);

	num = pInfo->line_number, temp_num = num, digit_count = 0;

	while (temp_num)
	{
		temp_num /= 10;
		digit_count++;
	}

	for (i = 0; i < digit_count; i++)
	{
		ch = (num % 10) + '0';
		write(STDERR_FILENO, &ch, 1);
		num /= 10;
	}

	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd_name, _strlen(cmd_name));
	write(STDERR_FILENO, ": not found\n", 12);
}
