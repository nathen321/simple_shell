#include "main.h"

/**
 * reset_bauf - reset de command buffer
 * @are: array of string
 * Return: ....
 */
void reset_bauf(char *are[])
{
	unsigned int i = 0;

	while (are[i] != NULL)
	{
		are[i] = NULL;
		i++;
	}
}

/**
 * user_input - take input from the user
 * @are: array of string
 * Return: ....
 */
void user_input(char *are[])
{
	unsigned int i = 0;
	char *buffer;
	size_t bufsize = 32;
	char *token;
	const char s[2] = " ";
	int size = 0;
	ssize_t chars_read;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}


	chars_read = getline(&buffer, &bufsize, stdin);

	while (buffer[i])
	{
		size++;
		i++;
	}
	i = 0;
	buffer[size - 1] = '\0';
	token = strtok(buffer, s);

	if (chars_read == 1 || are[0] == s)
	{
		reset_bauf(are);
		free(buffer);
		return;
	}

	while (token != NULL)
	{
		are[i] = token;
		token = strtok(NULL, s);
		i++;
	}
}
