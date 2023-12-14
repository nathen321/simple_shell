#include "main.h"

/**
 * printer - .....
 * @string: ....
 * Return: ....
 */

void printer (char *string)
{
	write(1, string, strlen(string));
}

/**
 * printer - .....
 * @buffer: ....
 * Return: ....
 */
void for_free(char *buffer[])
{
	int i = 0;

	while (buffer[i])
	{
		free(buffer[i]);
		i++;
	}
}

/**
 * set_buffer - .....
 * @string: ....
 * Return: ....
 */
void set_buff(char *argv[], char *buffer[])
{
	unsigned int i = 0;

	while (argv[i + 1])
	{
		buffer[i] = argv[i +1];
		i++;
	}
}
