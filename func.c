#include "main.h"

/**
 * run_commands - Executes command from stdin.
 * @argv: A pointer to the input string.
 * @d: A pointer to a struct data.
 *
 * Return: Nothing.
 */
int run_commands(char **argv, struct data *d)
{
	char *command_path;

	if (argv == NULL || argv[0] == NULL)
		return (1);

	command_path = search_path(argv[0], environ);
	if (command_path != NULL || access(argv[0], X_OK) == 0)
	{
		if (command_path)
		{
			if (execve(command_path, argv, environ) == -1)
				perror(d->shell_name);

			free(command_path);
		}
		else
		{
			if (execve(argv[0], argv, environ) == -1)
				perror(d->shell_name);
		}
	}
	else
	{
		perror(d->shell_name);
	}
	free(argv);
	return (1);
}

/**
 * get_path - Extracts the value of the PATH environment variable.
 * @envp: An array of environment variables.
 *
 * Return: A pointer to the string containing the PATH value, or NULL.
 */
char *get_path(char **envp)
{
	char *env_path = NULL;
	char *path_env = "PATH=";
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		if (_strncmp(envp[i], path_env, _strlen(path_env)) == 0)
		{
			env_path = envp[i] + _strlen(path_env);
			break;
		}
	}
	return (env_path);
}

/**
 * search_path - Searches for a command in the directories listed in the PATH.
 * @command: The command to search for.
 * @envp: An array of environment variables.
 *
 * Return: A pointer to the full path of the command if found, or NULL.
 */
char *search_path(char *command, char **envp)
{
	char *env_path = get_path(envp);
	char *token;
	char *full_path = NULL;
	int full_path_len;

	if (env_path == NULL)
		return (NULL);

	token = _strtok(env_path, ":");
	while (token != NULL)
	{
		full_path_len = _strlen(token) + _strlen(command) + 2;
		full_path = malloc(full_path_len);
		if (full_path == NULL)
			return (NULL);

	_strcpy(full_path, token);
	_strcat(full_path, "/");
	_strcat(full_path, command);
	if (access(full_path, X_OK) == 0)
		return (full_path);

	free(full_path);
	token = _strtok(NULL, ":");
	}
	return (NULL);
}

/**
 * tokenize_input - Tokenizes an input string into an array of strings.
 * @input: The input string to tokenize.
 *
 * Return: A dynamically allocated array of strings containing the tokens.
 */
char **tokenize_input(char *input)
{
	char delimiter[] = " ";
	char **argv = (char **)malloc(MAX_SPACE * sizeof(char *));
	int i = 0;
	char *token;

	if (argv == NULL)
		return (NULL);

	token = _strtok(input, delimiter);
	argv[i] = token;
	while (token != NULL)
	{
		i++;
		if (i >= MAX_SPACE)
		{
			return (NULL);
		}
		token = _strtok(NULL, delimiter);
		argv[i] = token;
	}
	argv[i + 1] = NULL;
	return (argv);
}

/**
 * create_child - Create a child process to execute a command.
 * @input: The input string containing the command to execute.
 * @length: The length of the input string.
 * @d: A pointer to the data structure containing shell information.
 *
 * Return: 0 on success, -1 on failure.
 */
int create_child(char *input, ssize_t length, struct data *d)
{
	char **tokenize;
	pid_t child;
	int status;

	input[length - 1] = '\0';
	tokenize = tokenize_input(input);
	child = fork();
	if (child == -1)
	{
		perror("Error:");
		return (-1);
	}
	if (child == 0)
	{
		run_commands(tokenize, d);
	}
	else
		wait(&status);
	return (0);
}
