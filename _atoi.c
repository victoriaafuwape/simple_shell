#include "shell.h"

/**
 * _atoi - Converts a string to an integer.
 * @nptr: The input string to be converted.
 *
 * Return: The integer value represented by the string.
 */
int _atoi(const char *nptr)
{
	int result = 0;
	int sign = 1;
	int digit;

	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
	{
		nptr++;
	}
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
	{
		nptr++;
	}

	while (*nptr >= '0' && *nptr <= '9')
	{
		digit = *nptr - '0';
		if (result > (INT_MAX - digit) / 10)
			return ((sign == 1) ? INT_MAX : INT_MIN);

		result = result * 10 + digit;
		nptr++;
	}
	return (sign * result);
}
