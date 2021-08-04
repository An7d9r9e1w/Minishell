/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_assembler_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 14:05:04 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/03 14:22:37 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <cmd_assembler.h>
/*#include <error.h>*/

static int	cmd_assembler_cmd_make(t_cmd_assembler *asmr)
{
	t_command	*cmd;

	if (!asmr->commands->size)
		return (0);
	cmd = asmr->commands->arr[asmr->commands->size - 1];
	if (asmr->args->size)
	{
		cmd->args = vvector_copy(asmr->args);
		if (!cmd->args)
			return (-1);
	}
	if (asmr->in->size)
	{
		cmd->in = vvector_export(asmr->in, sizeof(t_file), &cmd->in_size);
		if (!cmd->in || vvector_clear(asmr->in) == -1)
			return (-1);
	}
	if (asmr->out->size)
	{
		cmd->out = vvector_export(asmr->out, sizeof(t_file), &cmd->out_size);
		if (!cmd->out || vvector_clear(asmr->out) == -1)
			return (-1);
	}
	return (0);
}

int	cmd_assembler_cmd_new(t_cmd_assembler *asmr)
{
	if (cmd_assembler_cmd_make(asmr) == -1)
		return (-1);
	return (vvector_put(asmr->commands, command_create()));
}

static int	cmd_assembler_pipeline_make(t_cmd_assembler *asmr)
{
	t_pipe_line	*pipe;

	if (cmd_assembler_cmd_make(asmr) == -1)
		return (-1);
	if (asmr->pipes->size)
	{
		pipe = asmr->pipes->arr[asmr->pipes->size - 1];
		pipe->size = asmr->commands->size;
		pipe->commands = vvector_export(asmr->commands,
				sizeof(t_command), &pipe->size);
		if (!pipe->commands || vvector_clear(asmr->commands))
			return (-1);
//	logic_operator;
	}
	return (0);
}

int	cmd_assembler_pipeline_new(t_cmd_assembler *asmr)
{
	if (cmd_assembler_pipeline_make(asmr) == -1)
		return (-1);
	return (vvector_put(asmr->pipes, pipe_line_create()));
}

t_command_list	*cmd_assembler_make(t_cmd_assembler *asmr)
{
	t_command_list	*command_list;

	if (cmd_assembler_pipeline_make(asmr) == -1)
		return (0);
	command_list = command_list_create();
	if (!command_list)
		return (0);
	command_list->size = asmr->pipes->size;
	command_list->pipes = vvector_export(asmr->pipes,
			sizeof(t_pipe_line), &command_list->size);
	if (!command_list->pipes || vvector_clear(asmr->pipes) == -1)
	{
		free(command_list);
		return (0);
	}
	return (command_list);
}
