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
	int size;
	ssize_t chars_read;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}


	chars_read = getline(&buffer, &bufsize, stdin);

	size = strlen(buffer);
	buffer[size - 1] = '\0';
	token = strtok(buffer, s);

	if (chars_read == 1)
	{
		reset_bauf(are);
		return;
	}

	while (token != NULL)
	{
		are[i] = token;
		token = strtok(NULL, s);
		i++;
	}
}

/**
 * main - programme simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	int onf = 1;
	char *buffer[50];

	while (onf)
	{
		printf("$ ");

		user_input(buffer);

		if (buffer[0] != NULL)
			execut_command(buffer);

		reset_bauf(buffer);
	}
	return (0);
}
