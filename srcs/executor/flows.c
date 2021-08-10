/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flows.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:57:17 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/10 11:58:21 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include <executor.h>
#include <error.h>

static int	open_files(t_file *files, int size)
{
	int	fd;
	int	oflag;

	fd = -1;
	while (size--)
	{
		if (files->mode < READ)
			oflag = O_WRONLY | O_CREAT | O_TRUNC * (files->mode == TRUNC)
				| O_APPEND * (files->mode == APPEND);
		else
			oflag = O_RDONLY;
		fd = open(files->path, oflag, 0644);
		if (fd == -1)
			return (error(-1, files->path, 0));
		if (size)
			close(fd);
		++files;
	}
	return (fd);
}

int	set_flows(t_command *command, int *fildes, int *out)
{
	if (fildes[1] > 2)
		close(fildes[1]);
	if (command->in)
	{
		if (*fildes > 2)
			close(*fildes);
		*fildes = open_files(command->in, command->in_size);
		if (*fildes == -1)
			return (-1);
	}
	if (command->out)
	{
		if (*out > 2)
			close(*out);
		*out = open_files(command->out, command->out_size);
		if (*out == -1)
			return (-1);
	}
	return (0);
}
