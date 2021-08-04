/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 14:17:07 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/03 18:31:19 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <command_list.h>
#include <error.h>

t_command_list	*command_list_create(void)
{
	t_command_list	*command_list;

	command_list = malloc(sizeof(t_command_list));
	if (!command_list)
		return (error_p(-1));
	command_list->pipes = 0;
	command_list->size = 0;
	return (command_list);
}

t_pipe_line	*pipe_line_create(void)
{
	t_pipe_line	*pipe_line;

	pipe_line = malloc(sizeof(t_pipe_line));
	if (!pipe_line)
		return (error_p(-1));
	pipe_line->commands = 0;
	pipe_line->size = 0;
	pipe_line->logic_operator = -1;
	return (pipe_line);
}

t_command	*command_create(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (error_p(-1));
	command->args = 0;
	command->in = 0;
	command->out = 0;
	return (command);
}

t_file	*file_create(char *path, t_file_mode mode)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		return (error_p(-1));
	file->path = path;
	file->mode = mode;
	return (file);
}
