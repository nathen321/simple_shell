#include "main.h"

/**
 * rm_inf - initializes info_t struct
 * @info: struct address
 */
void rm_inf(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * upd_inf - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void upd_inf(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		update_vars(info);
	}
}

/**
 * free_inf - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_inf(info_t *info, int all)
{
	f_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_ls(&(info->env));
		if (info->h)
			free_ls(&(info->h));
		if (info->alias)
			free_ls(&(info->alias));
		f_free(info->environ);
			info->environ = NULL;
		free_block((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
