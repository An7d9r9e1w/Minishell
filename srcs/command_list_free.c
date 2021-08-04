/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 14:17:12 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/03 17:50:59 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <command_list.h>

static void	command_clear(t_command *command)
{
	void		*begin;

	begin = command->args;
	if (command->args)
		while (*command->args)
			free(*command->args++);
	free(begin);
	begin = command->in;
	if (command->in)
		while (command->in_size--)
			free(command->in++->path);
	free(begin);
	begin = command->out;
	if (command->out)
		while (command->out_size--)
			free(command->out++->path);
	free(begin);
}

static void	pipe_line_clear(t_pipe_line *pipe_line)
{
	while (pipe_line->size--)
		command_clear(pipe_line->commands + pipe_line->size);
	free(pipe_line->commands);
}

void	command_free(t_command *command)
{
	command_clear(command);
	free(command);
}

void	pipe_line_free(t_pipe_line *pipe_line)
{
	pipe_line_clear(pipe_line);
	free(pipe_line);
}

void	command_list_free(t_command_list *command_list)
{
	if (!command_list)
		return ;
	while (command_list->size--)
		pipe_line_clear(command_list->pipes + command_list->size);
	free(command_list->pipes);
	free(command_list);
}
