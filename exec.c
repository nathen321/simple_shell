#include "main.h"

/**
 * execut_command - fork,wait,execve
 * Return: ...
 */

void execut_command(char *args[])
{
	int status;
	char path[128] = "/bin/";
	char *word = args[0];
	pid_t pid = fork();

	strcat(path, word);

	if (pid == -1)
	{
		perror("error fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		printf ("[%s]\n", path);
		execve(path, args, NULL);
		perror("error execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}
