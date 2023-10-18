#include "main.h"

static char buffer[BUFFER_SIZE];
static int buf_index;
static int buf_size;

/**
 * realloc_buffer - Reallocate memory for the line buffer.
 * @lineptr: A pointer to a pointer to the line buffer.
 * @n: A pointer to the size of the buffer.
 *
 * Return: The size of the reallocated buffer or -1 on error.
 */
size_t realloc_buffer(char **lineptr, size_t *n)
{
	size_t size = *n;
	char *new_line;
	size_t i;

	while ((size_t)*n <= (size_t)size)
	{
		size *= 2;
		new_line = malloc(size);
		if (new_line == NULL)
		{
			free(*lineptr);
			*lineptr = NULL;
			return (-1);
		}
		for (i = 0; i < (size_t)*n; i++)
		{
			new_line[i] = (*lineptr)[i];
		}
		free(*lineptr);
		*lineptr = new_line;
	}
	*n = size;
	return (size);
}

/**
 * read_line - Read a line from a stream into a buffer.
 * @lineptr: A pointer to a pointer to the line buffer.
 * @n: A pointer to the size of the buffer.
 * @stream: The input stream to read from.
 *
 * Return: The size of the read line or -1 on error.
 */
ssize_t read_line(char **lineptr, size_t *n, FILE *stream)
{
	char *line = *lineptr;
	size_t size = *n;
	ssize_t line_size = 0;
	int c;

	while (1)
	{
		if (buf_index >= buf_size)
		{
			buf_size = read(fileno(stream), buffer, BUFFER_SIZE);
			if (buf_size <= 0)
			{
				if (line_size == 0)
				{
					free(line);
					*lineptr = NULL;
					return (-1);
				}
				break;
			}
			buf_index = 0;
		}
		c = buffer[buf_index++];
		line[line_size] = (char)c;
		line_size++;
		if ((size_t)line_size >= (size_t)size)
		{
			if (realloc_buffer(lineptr, n) == (size_t)-1)
				return (-1);
			line = *lineptr;
			size = *n;
		}
		if (c == '\n' || c == EOF)
			break;
	}
	line[line_size] = '\0';
	return (line_size);
}

/**
 * alloc_buffer - Allocate memory for the line buffer.
 * @lineptr: A pointer to a pointer to the line buffer.
 * @n: A pointer to the size of the buffer.
 *
 * Return: The size of the allocated buffer or -1 on error.
 */
size_t alloc_buffer(char **lineptr, size_t *n)
{
	char *line = *lineptr;
	char *new_line;
	size_t size = *n;
	size_t i;

	if (line == NULL || size == 0)
	{
		size = 128;
		line = malloc(size);
		if (line == NULL)
			return (-1);
	}
	while ((size_t)size <= (size_t)*n)
	{
		size *= 2;
		new_line = malloc(size);
		if (new_line == NULL)
		{
			free(line);
			*lineptr = NULL;
			return (-1);
		}
		for (i = 0; i < (size_t)*n; i++)
			new_line[i] = line[i];

		free(line);
		line = new_line;
	}
	*lineptr = line;
	*n = size;
	return (size);
}

/**
 * _getline - Read a line from a stream.
 * @lineptr: A pointer to a pointer to the line buffer.
 * @n: A pointer to the size of the buffer.
 * @stream: The input stream to read from.
 *
 * Return: The size of the read line or -1 on error.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t size;
	ssize_t line_size;

	size = alloc_buffer(lineptr, n);
	if (size == (size_t)-1)
		return (-1);

	line_size = read_line(lineptr, n, stream);
	if (line_size == -1)
		return (-1);

	return (line_size);
}
