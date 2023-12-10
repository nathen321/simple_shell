#include "main.h"
/**
 * user_input; - take input from the user
 *
 * Return: ....
 */
void user_input(char *are[])
{
	unsigned int i = 0;
	char *buffer;
	size_t bufsize = 32;
	char *token;
	const char s[2] = " ";

	buffer = (char *)malloc(bufsize * sizeof(char));
	if( buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	getline(&buffer,&bufsize,stdin);
	token = strtok(buffer, s);

	while( token != NULL )
	{
		are[i] = token;
		token = strtok(NULL, s);
		i++;
	}
}

/**
 * reset_bauf - reset de command buffer
 *
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
 * main - programme simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	unsigned int i = 0;
	int onf = 1;
	char *buffer[50];

	while (onf)
	{
		printf("$ ");
		user_input(buffer);

		while (buffer[i])
		{
			printf("%s\n", buffer[i]);
			i++;
		}
		i = 0;
		/* hna la parti execution */

		reset_bauf(buffer);
	}
	return (0);
}
