#include "main.h"

/**
 * change_dir - Change the current working directory.
 * @path: The path to change to.
 *
 * Return: 0 on success, -1 on failure.
 */
int change_dir(const char *path)
{
	if (chdir(path) == -1)
	{
		perror("chdir");
		return (-1);
	}
	return (0);
}

/**
 * set_variables - Set the environment variables PWD and OLDPWD.
 * @pwd: The new value for PWD.
 * @oldpwd: The new value for OLDPWD.
 *
 * Return: 0 on success, -1 on failure.
 */
int set_variables(const char *pwd, const char *oldpwd)
{
	if (_setenv("PWD", pwd, 1) != 0)
	{
		write(STDERR_FILENO,
		      "cd: Failed to set PWD\n",
		      _strlen("cd: Failed to set PWD\n"));
		return (-1);
	}
	if (_setenv("OLDPWD", oldpwd, 1) != 0)
	{
		write(STDERR_FILENO,
		      "cd: Failed to set OLDPWD\n",
		      _strlen("cd: Failed to set OLDPWD\n"));
		return (-1);
	}
	return (0);
}

/**
 * cd_home - Handle changing to the user's home directory.
 *
 * Return: Nothing.
 */
void cd_home(void)
{
	char current_dir[PATH_MAX];
	char *home_dir = _getenv("HOME");

	if (home_dir == NULL)
	{
		write(STDERR_FILENO,
		      "cd: HOME environment variable not set\n",
		      _strlen("cd: HOME environment variable not set\n"));
		return;
	}
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		perror("getcwd");

	if (change_dir(home_dir) == 0)
		set_variables(home_dir, current_dir);
}

/**
 * cd_prev - Handle changing to the previous directory.
 *
 * Return: Nothing.
 */
void cd_prev(void)
{
	char current_dir[PATH_MAX];
	char *old_dir = _getenv("OLDPWD");

	if (old_dir == NULL)
	{
		write(STDERR_FILENO,
		      "cd: OLDPWD not set\n", _strlen("cd: OLDPWD not set\n"));
		return;
	}
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		perror("getcwd");

	if (change_dir(old_dir) == 0)
		set_variables(old_dir, current_dir);
}

/**
 * handle_cd - Handle the "cd" command.
 * @input: The input string to process.
 *
 * Return: Nothing.
 */
void handle_cd(char *input)
{
	char current_dir[PATH_MAX];
	char *dir;
	size_t len;

	if (_strncmp(input, "cd", 2) == 0)
	{
		dir = input + 2;
		while (*dir == ' ' || *dir == '\t')
			dir++;

		if (*dir == '\0' || *dir == '\n')
			cd_home();

		else if (_strncmp(dir, "-", 1) == 0)
			cd_prev();

		else
		{
			len = _strlen(dir);
			if (dir[len - 1] == '\n')
				dir[len - 1] = '\0';

			if (getcwd(current_dir, sizeof(current_dir)) == NULL)
				perror("getcwd");

			if (change_dir(dir) == 0)
				set_variables(dir, current_dir);
		}
	}
}
