#include "main.h"

/**
 * main - fork,wait,execve
 * Return: Always 0.
 */

int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};

	for (int i = 0; i < 5; i++)
	{
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("error fork");
			return (1);
		}
		if (pid == 0)
		{
			execve("/bin/ls", argv, NULL);
			perror("error execve");
			return (1);
		}
		else
		{
			int status;

			wait(&status);
		}
	}
	return (0);
}
