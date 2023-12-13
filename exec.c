#include "main.h"

/**
 * execut_command - fork,wait,execve
 * @args: array of strings
 * Return: ...
 */

void execut_command(char *args[])
{
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("error fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(args[0], args, NULL);
		perror("error execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}
