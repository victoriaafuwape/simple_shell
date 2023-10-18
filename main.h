#ifndef MAIN_H
#define MAIN_H

/*
 * #include <dirent.h>
 * #include <signal.h>
 * #include <fcntl.h>
 * #include <string.h>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

 /* global variable */
extern char **environ;

/* macro */
#define MAX_SPACE 1024
#define BUFFER_SIZE 1024

/* built structures */
/**
 * struct node - Structure to represent a linked list node.
 * @dir: A pointer to a string representing a directory.
 * @next: A pointer to the next node in the linked list.
 */
struct node
{
	char *dir;
	struct node *next;
};

/**
 * struct data - Structure to hold data.
 *@shell_name: The name of the shell program.
 */
struct data
{
	const char *shell_name;
};

/* custom shell.h */
void cd_home(void);
void cd_prev(void);
void handle_cd(char *input);
char *get_path(char **envp);
void handle_exit(char *input);
int input_counter(char *input);
void handle_setenv(char *input);
int change_dir(const char *path);
void handle_unsetenv(char *input);
char **tokenize_input(char *input);
char *find_file(const char *filename);
void handle_env(char *input, char **env_var);
char *search_path(char *command, char **envp);
int run_commands(char **argv, struct data *d);
size_t alloc_buffer(char **lineptr, size_t *n);
size_t realloc_buffer(char **lineptr, size_t *n);
int set_variables(const char *pwd, const char *oldpwd);
size_t _getline_alloc_buffer(char **lineptr, size_t *n);
ssize_t read_line(char **lineptr, size_t *n, FILE *stream);
int create_child(char *input, ssize_t length, struct data *d);

/* custom stdio.h */
int _putchar(char c);
void _printf(const char *str);

/* custom stdlib.h */
int _putenv(char *string);
int _atoi(const char *nptr);
char *_getenv(const char *name);
int _unsetenv(const char *name);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _setenv(const char *name, const char *value, int overwrite);

 /* custom string.h */
char *_strdup(const char *s);
size_t _strlen(const char *s);
char *_strchr(const char *s, int c);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
char *_strtok(char *str, const char *delim);
int _strncmp(const char *s1, const char *s2, size_t n);

/* custom unistd.h */
pid_t _getppid(void);

#endif /* MAIN_H */
