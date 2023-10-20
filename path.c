#include "shell.h"

char *get_cmd_path(const char *cmd)
{
	char *PATH = getenv("PATH");
	char *path_copy = NULL, *token = NULL;
	char *full_path = NULL;
	size_t full_path_len;

	if (!PATH)
	{
		return NULL;
	}

	path_copy = malloc(strlen(PATH) + 1);
	if (path_copy == NULL)
	{
		return NULL;
	}
	strcpy(path_copy, PATH);

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path_len = strlen(token) + strlen(cmd) + 2;

		full_path = malloc(full_path_len);
		if (full_path == NULL)
		{
			free(path_copy);
			return NULL;
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return full_path;
		}

		free(full_path);
		full_path = NULL;
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return NULL;
}
