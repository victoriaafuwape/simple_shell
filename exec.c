#include "shell.h"

/**
 * prepare_command - Prepare the full path of the command to execute.
 * @pInfo: Pointer to the ShellContext structure.
 *
 * Description:
 *   This function prepares the full path of the command to execute based on
 *   whether it is an absolute path or not. If the command starts with '/',
 *   it is considered an absolute path, and a copy of it is created. Otherwise,
 *   it attempts to find the command in the system's PATH using 'get_cmd_path'.
 *   If successful, it returns the full path of the command. If not found or
 *   if memory allocation fails, it handles errors and returns NULL.
 *
 * Return:
 *   A pointer to the full path of the command, or NULL on error.
 */
char *prepare_command(ShellContext *pInfo, char **current_args)
{
    char *cmd_path;

    if (current_args[0] == NULL)
    {
        return (NULL);
    }

    if (current_args[0][0] == '/')
    {
        cmd_path = malloc(strlen(current_args[0]) + 1);
        if (cmd_path == NULL)
        {
            error_printer("malloc", pInfo);
            clean_up(pInfo);
            exit(1);
        }
        strcpy(cmd_path, current_args[0]);
    }
    else
    {
        cmd_path = get_cmd_path(current_args[0]);
        if (cmd_path == NULL)
        {
            error_printer(current_args[0], pInfo);
            clean_up(pInfo);
            return (NULL);
        }
    }
    return (cmd_path);
}
/**
char *prepare_command(ShellContext *pInfo)
{
	char *cmd_path;

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
			error_printer(pInfo->args[0], pInfo);
			clean_up(pInfo);
			return (NULL);
		}
	}
	return (cmd_path);
}
*/
/**
 * fork_and_execute - Fork a child process and execute the command.
 * @pInfo: Pointer to the ShellContext structure.
 * @cmd_path: The full path of the command to execute.
 *
 * Description:
 *   This function forks a child process and attempts to execute the command
 *   using 'execve'. It handles errors during forking or execution and performs
 *   cleanup operations if necessary.
 */
void fork_and_execute(ShellContext *pInfo, char *cmd_path, char **current_args)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (execve(cmd_path, current_args, NULL) == -1)
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
}

/**
void fork_and_execute(ShellContext *pInfo, char *cmd_path)
{
	pid_t pid = fork();

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
}
*/
/**
 * execute_line - Execute the command stored in pInfo->args.
 * @pInfo: Pointer to the ShellContext structure.
 *
 * Description:
 *   This function executes the command specified in 'pInfo->args'. It first
 *   checks for NULL or empty strings in 'pInfo->args'. If the command is not
 *   found in the system's PATH, it calls 'prepare_command' to get the full
 *   path and then forks and executes the command using 'fork_and_execute'.
 *   It also handles cleanup of allocated memory.
 */
void execute_line(ShellContext *pInfo)
{
    char *cmd_path;
    int i = 0;

    while (pInfo->args[i] != NULL)
    {
        pInfo->line_number++;
        cmd_path = prepare_command(pInfo, pInfo->args[i]);
        if (cmd_path == NULL)
        {
            i++;
            continue;
        }
        fork_and_execute(pInfo, cmd_path, pInfo->args[i]);
        free(cmd_path);
        i++;
    }
    clean_up(pInfo);
}
/**
void execute_line(ShellContext *pInfo)
{
	char *cmd_path;

	if (pInfo->args == NULL || pInfo->args[0] == NULL)
	{
		clean_up(pInfo);
		return;
	}

	cmd_path = prepare_command(pInfo);
	if (cmd_path == NULL)
	{
		return;
	}

	fork_and_execute(pInfo, cmd_path);

	clean_up(pInfo);
	free(cmd_path);
}
*/
