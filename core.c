#include "shell.h"

/**
 * read_line - Read a line of input from stdin.
 * @pInfo: Pointer to the shell context.
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
 * @pInfo: Pointer to the shell context.
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
 * @pInfo: Pointer to the shell context.
 *
 * Description:
 *   This function parses the line stored in 'pInfo->line' into tokens using
 *   the delimiter "\n\t\r ". It allocates memory for 'pInfo->args' to hold the
 *   tokenized arguments and stores them. If memory allocation fails or an
 *   error occurs, it prints an error message and exits the program.
 */
void parse_line(ShellContext *pInfo)
{
    char *cmd_token;
    char *arg_token;
    int i = 0, j = 0;
    int num_cmds, num_tokens;
    char **args;

    num_cmds = count_tokens(pInfo->line, ";", pInfo);

    pInfo->args = malloc((num_cmds + 1) * sizeof(char **));
    if (pInfo->args == NULL)
    {
        error_printer("malloc", pInfo);
        exit(1);
    }

    cmd_token = strtok(pInfo->line, ";");
    while (cmd_token != NULL)
    {
        num_tokens = count_tokens(cmd_token, " \n\t\r", pInfo);

        args = malloc((num_tokens + 1) * sizeof(char *));
        if (args == NULL)
        {
            error_printer("malloc", pInfo);
            exit(1);
        }

        arg_token = strtok(cmd_token, " \n\t\r");
        while (arg_token != NULL)
        {
            args[j++] = arg_token;
            arg_token = strtok(NULL, " \n\t\r");
        }
        args[j] = NULL;

        pInfo->args[i++] = args;
        cmd_token = strtok(NULL, ";");
    }
    pInfo->args[i] = NULL;
}
/**
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
*/
