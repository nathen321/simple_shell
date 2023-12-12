#include "main.h"

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
		print_head();

		user_input(buffer);

		if (buffer[0] != NULL)
			execut_command(buffer);

		reset_bauf(buffer);
	}
	return (0);
}
