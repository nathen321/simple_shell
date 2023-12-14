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
	struct stat st;

	if (pid == -1)
	{
		perror("error fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (stat(args[0], &st) == 0)
		{
			execve(args[0], args, NULL);
		}
		else
		{
			printf("%s: No such file or directory", args[0]);
		}
		perror("error execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}
