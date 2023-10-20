#include "shell.h"

/**
 * get_env_token - Get the first token from the PATH environment variable.
 *
 * Description:
 *   This function retrieves the first token from the PATH environment
 *   variable. It copies the value of PATH to 'path_copy', tokenizes it using
 *   ':' as a delimiter and returns the first token. If PATH is not set or if
 *   there's a memory allocation error, it returns NULL.
 *
 * Return:
 *   A pointer to the first token from the PATH environment variable.
 *   NULL if PATH is not set or on memory allocation failure.
 */
char **get_env_token(void)
{
	char *PATH = getenv("PATH");
	char **result = malloc(2 * sizeof(char *));
	char *path_copy = NULL, *token = NULL;

	if (!PATH)
	{
		free(result);
		return (NULL);
	}

	path_copy = malloc(_strlen(PATH) + 1);
	if (path_copy == NULL)
	{
		free(result);
		return (NULL);
	}
	_strcpy(path_copy, PATH);

	token = strtok(path_copy, ":");
	result[0] = path_copy;
	result[1] = token;
	return (result);
}

/**
 * get_cmd_path - Get the full path of a command from the system's PATH.
 * @cmd: The name of the command.
 *
 * Description:
 *   This function searches for the full path of a command named 'cmd' in the
 *   system's PATH environment variable. It iterates through each directory in
 *   PATH, combines the directory path and the command name, and checks if the
 *   resulting path is executable using 'access'. It returns the full path of
 *   the command if found, or NULL if the command is not found or an error
 *   occurs.
 *
 * Return:
 *   A dynamically allocated string containing the full path of the command.
 *   NULL if the command is not found or an error occurs.
 */
char *get_cmd_path(const char *cmd)
{
	char *path_copy = NULL, *token = NULL;
	char *full_path = NULL;
	size_t full_path_len;
	char **env_token_result = get_env_token();

	if (env_token_result == NULL)
	{
		return (NULL);
	}
	path_copy = env_token_result[0];
	token = env_token_result[1];
	while (token != NULL)
	{
		full_path_len = strlen(token) + strlen(cmd) + 2;
		full_path = malloc(full_path_len);
		if (full_path == NULL)
		{
			free(path_copy);
			free(env_token_result);
			return (NULL);
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			free(env_token_result);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	free(env_token_result);
	return (NULL);
}
