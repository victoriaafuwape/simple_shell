#ifndef MAIN_H

/* standard libraries */
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

/* data structures */
/**
 * struct ShellContext - Structure to hold shell context information.
 * @shell_name: Pointer to the name of the shell.
 *
 * Description:
 *   This structure is used to hold context information for the shell program.
 */
typedef struct shell_context
{
	const char *program_name;
	int eof_reached;
	int line_number;
	char *line;
	char **args;
} ShellContext;

 /* global variable */
extern ShellContext Info;
extern ShellContext *pInfo;

/* shell function prototypes */
/* core.c */
void read_line(ShellContext *pInfo);
int count_tokens(char *str, const char *delim, ShellContext *pInfo);
void parse_line(ShellContext *pInfo);
void execute_line(ShellContext *pInfo);

/* path.c */
char *get_cmd_path(const char *cmd);

/* utility.c */
void signal_handler(int signum);
void clean_up(ShellContext *pInfo);
void error_printer(char *cmd_name, ShellContext *pInfo);

/* custom standard function prototypes */
/* stdlib.h */
int _putenv(char *string);
int _atoi(const char *nptr);
char *_getenv(const char *name);
int _unsetenv(const char *name);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _setenv(const char *name, const char *value, int overwrite);

 /* string.h */
size_t _strlen(const char *s);
char *_strchr(const char *s, int c);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
char *_strtok(char *str, const char *delim);
int _strncmp(const char *s1, const char *s2, size_t n);

/* unistd.h */
pid_t _getppid(void);

#endif /* MAIN_H */
