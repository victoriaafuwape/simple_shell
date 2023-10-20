#include "shell.h"

/**
 * read_line - Read a line of input from stdin.
 *
 * Description:
 *   This function reads a line of input from the standard input (stdin)
 *   and stores it in the 'pInfo->line' buffer.
 *   If an error occurs or an empty line is entered,
 *   it cleans up and exits the program.
 */
void read_line(ShellContext *pInfo)
{
	size_t len = 0;
	ssize_t nread = getline(&pInfo->line, &len, stdin);

	if (nread == -1)
	{
		pInfo->eof_reached = 1;
		/* write(STDOUT_FILENO, "\n", 1); */
		clean_up(pInfo);
		exit(0);
	}
	else
	{
		pInfo->eof_reached = 0;
	}
}

/**
 * count_tokens - Count the number of tokens in a string.
 * @str: The input string to be tokenized.
 * @delim: The delimiter used to tokenize the string.
 *
 * Description:
 *   This function counts the number of tokens in the 'str' string,
 *   using the 'delim' as the delimiter.
 *   It creates a copy of 'str' because strtok modifies the input string.
 *   If memory allocation fails or an error occurs, it prints an error message,
 *   cleans up, and exits the program.
 *
 * Return:
 *   The number of tokens found in 'str'.
 */
int count_tokens(char *str, const char *delim, ShellContext *pInfo)
{
	char *token;
	int count = 0;
	char *str_copy = malloc(_strlen(str) + 1);

	if (str_copy == NULL)
	{
		error_printer("malloc", pInfo);
		clean_up(pInfo);
		exit(1);
	}

	_strcpy(str_copy, str);

	token = strtok(str_copy, delim);
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delim);
	}

	free(str_copy);
	return (count);
}

/**
 * parse_line - Parse the line into tokens and store them in pInfo->args.
 *
 * Description:
 *   This function parses the line stored in 'pInfo->line' into tokens using
 *   the delimiter "\n\t\r ". It allocates memory for 'pInfo->args' to hold the
 *   tokenized arguments and stores them. If memory allocation fails or an
 *   error occurs, it prints an error message and exits the program.
 */
void parse_line(ShellContext *pInfo)
{
	char *token;
	int i = 0;
	int num_tokens;

	num_tokens = count_tokens(pInfo->line, "\n\t\r ", pInfo);

	pInfo->args = malloc((num_tokens + 1) * sizeof(char *));
	if (pInfo->args == NULL)
	{
		error_printer("malloc", pInfo);
		exit(1);
	}

	token = strtok(pInfo->line, "\n\t\r ");
	while (token != NULL)
	{
		pInfo->args[i++] = token;
		token = strtok(NULL, "\n\t\r ");
	}

	pInfo->args[i] = NULL;
}

/**
 * execute_line - Execute the command stored in pInfo->args.
 *
 * Description:
 *   This function forks a child process to execute the command stored
 *   in 'pInfo->args'. It checks for NULL or empty strings in 'pInfo->args'
 *   and handles errors during forking or execution.  It also waits for the
 *   child process to complete and cleans up allocated memory.
 */
void execute_line(ShellContext *pInfo)
{
	pid_t pid;
	char *cmd_path;

	if (pInfo->args == NULL || pInfo->args[0] == NULL)
	{
		clean_up(pInfo);
		return;
	}
	if (pInfo->args[0][0] == '/')
	{
		cmd_path = malloc(strlen(pInfo->args[0]) + 1);
		if (cmd_path == NULL)
		{
			error_printer("malloc", pInfo);
			clean_up(pInfo);
			exit(1);
		}
		strcpy(cmd_path, pInfo->args[0]);
	}
	else
	{
		cmd_path = get_cmd_path(pInfo->args[0]);
		if (cmd_path == NULL)
		{
			error_printer("Command not found", pInfo);
			clean_up(pInfo);
			return;
		}
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, pInfo->args, NULL) == -1)
		{
			error_printer(cmd_path, pInfo);
			clean_up(pInfo);
			exit(0);
		}
	}
	else if (pid < 0)
	{
		error_printer("fork", pInfo);
		clean_up(pInfo);
		exit(1);
	}
	else
	{
		wait(NULL);
	}
	clean_up(pInfo);
	free(cmd_path);
}
