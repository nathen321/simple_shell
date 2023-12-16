#include "main.h"

/**
 * get_hf - gets the h file
 * @info: parameter struct
 *
 * Return: allocated string containg h file
 */

char *get_hf(info_t *info)
{
	char *buf, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * writeh - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writeh(info_t *info)
{
	ssize_t fd;
	char *filename = get_hf(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->h; node; node = node->next)
	{
		puts_fd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readh - reads h from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readh(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hf(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			cr_h_ls(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		cr_h_ls(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		rm_node(&(info->h), 0);
	modifyh(info);
	return (info->histcount);
}

/**
 * cr_h_ls - adds entry to a h linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the h linecount, histcount
 *
 * Return: Always 0
 */
int cr_h_ls(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->h)
		node = info->h;
	app_node_t(&node, buf, linecount);

	if (!info->h)
		info->h = node;
	return (0);
}

/**
 * modifyh - renumbers the h linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int modifyh(info_t *info)
{
	list_t *node = info->h;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
