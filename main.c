#include "main.h"

/**
 * main - programme simple shell
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
	int onf = 1;
	char *buffer[50];

	if (argc > 1)
	{
		set_buff(argv, buffer);
		execut_command(buffer);
		exit(EXIT_SUCCESS);
	}
	while (onf)
	{
		print_head();

		user_input(buffer);

		if (buffer[0] != NULL)
			execut_command(buffer);

		reset_bauf(buffer);
		for_free(buffer);
	}
	return (0);
}
