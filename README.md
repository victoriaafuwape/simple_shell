# Simple Shell

Simple Shell is a Unix command-line interpreter project developed by Victoria Afuwape and Ifeoma Jonah as part of the ALX program. The goal of this project is to create a minimalistic shell that mimics the behavior of the standard Unix shell (/bin/sh) while meeting specific requirements and adding some additional features.

## Team Members

- Victoria Afuwape
  - Twitter: [https://twitter.com/victoriaafuwape]

- Ifeoma Jonah
  - Twitter: [https://twitter.com/ifeomajonah]

## Project Overview

The Simple Shell project aims to create a command-line interpreter with the following features and functionalities:

### Simple Shell 0.1

- Display a prompt and wait for the user to input a command.
- Commands should be single words (no arguments or special characters).
- If an executable is not found, display an error message and continue to the next prompt.
- Handle the "end of file" condition (Ctrl+D).
- Handle errors gracefully.

### Simple Shell 0.2

- Extend Simple Shell 0.1 to handle command lines with arguments.

### Simple Shell 0.3

- Extend Simple Shell 0.2 to handle the PATH variable.
- Avoid calling `fork` if the command doesn't exist.

### Simple Shell 0.4

- Implement the `exit` built-in command to exit the shell without arguments.

### Simple Shell 1.0

- Implement the `env` built-in command to print the current environment.

### Simple Shell 0.1.1

- Write a custom `getline` function to read input efficiently.
- Use a buffer to read multiple characters at once and minimize calls to `read`.
- Do not use the standard `getline` function.

### Simple Shell 0.2.1

- Avoid using `strtok` to tokenize input.

### Simple Shell 0.4.1

- Extend the `exit` built-in command to accept an integer status as an argument.

### Setenv and Unsetenv

- Implement the `setenv` and `unsetenv` built-in commands:
  - `setenv VARIABLE VALUE`: Initialize or modify an environment variable.
  - `unsetenv VARIABLE`: Remove an environment variable.

### CD (Change Directory)

- Implement the `cd` built-in command:
  - Changes the current directory of the process.
  - Supports `cd DIRECTORY` and `cd -` (return to the previous directory).
  - Updates the `PWD` environment variable.

### Command Separators (;)

- Handle command separators (`;`) to execute multiple commands in a single line.

### Logical Operators (&& and ||)

- Handle logical operators (`&&` and `||`) for conditional command execution.

### Alias

- Implement the `alias` built-in command to manage command aliases.

### Variables

- Handle variable replacement, including special variables like `$?` and `$$`.

### Comments

- Support comments in the form of `#` at the beginning of a line.

### File as Input

- Allow the shell to take a file as a command-line argument.
- Execute commands from the specified file, one per line.
- In this mode, the shell should not display a prompt or read from stdin.

## Compilation

To compile the Simple Shell, you can use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Testing

You can test the Simple Shell in both interactive and non-interactive modes:

### Interactive Mode

```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

### Non-Interactive Mode

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

## Contributing

Contributions to the Simple Shell project are welcome. Feel free to fork the repository, make improvements, and submit pull requests.

