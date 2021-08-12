/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flows.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:57:17 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/12 13:43:45 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <executor.h>
#include <error.h>
#include <get_next_line.h>
#include <string_utils.h>

/*__attribute__ ((noreturn))*/
static void	heredoc(char *limiter, int out)
{
	char	*line;
	int		gnl_stat;

	write(STDOUT_FILENO, "> ", 2);
	gnl_stat = get_next_line(STDIN_FILENO, &line);
	while (gnl_stat > -1 && mstrcmp(limiter, line))
	{
		write(out, line, mstrlen(line));
		write(out, "\n", 1);
		if (!gnl_stat)
			break ;
		free(line);
		write(STDOUT_FILENO, "> ", 2);
		gnl_stat = get_next_line(STDIN_FILENO, &line);
	}
	close(out);
	if (gnl_stat == -1)
		exit(error(-1, 0, 1));
	free(line);
	exit(0);
}

static int	try_exec_heredoc(char *limiter)
{
	pid_t	pid;
	int		fildes[2];

	if (pipe(fildes) == -1)
		return (error(-1, 0, 0));
	pid = fork();
	if (pid == -1)
	{
		close(fildes[0]);
		close(fildes[1]);
		return (error(-1, 0, 0));
	}
	if (!pid)
	{
		close(fildes[0]);
		heredoc(limiter, fildes[1]);
	}
	close(fildes[1]);
	if (waitpid(pid, fildes + 1, 0) == -1)
	{
		close(fildes[0]);
		return (error(-1, 0, 0));
	}
	return (fildes[0]);
}

static int	open_files(t_file *files, int size)
{
	int	fd;

	fd = -1;
	while (size--)
	{
		if (files->mode == HERE_DOC)
			fd = try_exec_heredoc(files->path);
		else
		{
			if (files->mode == READ)
				fd = O_RDONLY;
			else
				fd = O_WRONLY | O_CREAT | O_TRUNC * (files->mode == TRUNC)
					| O_APPEND * (files->mode == APPEND);
			fd = open(files->path, fd, 0644);
			if (fd == -1)
				return (error(-1, files->path, 0));
		}
		if (fd == -1)
			return (-1);
		if (size)
			close(fd);
		++files;
	}
	return (fd);
}

static int command_files(t_file *files, int size, int *fd)
{
	if (files)
	{
		if (*fd > 2)
			close(*fd);
		*fd = open_files(files, size);
		if (*fd == -1)
			return (-1);
	}
	return (0);
}

int	set_flows(int size, t_command *command, int *fildes)
{
	//if (fildes[1] > 2)
	//	close(fildes[1]);
	if (!size)
	{
		fildes[0] = STDIN_FILENO;
		fildes[1] = STDOUT_FILENO;
	}
	else if (pipe(fildes) == -1)
		exit(error(-1, 0, 1));
	return (-(command_files(command->in, command->in_size, fildes) == -1
		|| command_files(command->out, command->out_size, fildes + 2) == -1));
}
