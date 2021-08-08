/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_assembler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 14:04:54 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/03 18:20:13 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <cmd_assembler.h>
#include <error.h>

t_cmd_assembler	*cmd_assembler_create(void)
{
	t_cmd_assembler	*asmr;

	asmr = malloc(sizeof(t_cmd_assembler));
	if (!asmr)
		return (error_p(-1));
	asmr->pipes = 0;
	asmr->commands = 0;
	asmr->args = 0;
	asmr->in = 0;
	asmr->out = 0;
	asmr->pipes = vvector_create();
	asmr->commands = vvector_create();
	asmr->args = vvector_create();
	asmr->in = vvector_create();
	asmr->out = vvector_create();
	if (asmr->pipes == 0 || asmr->commands == 0 || asmr->args == 0
		|| asmr->in == 0 || asmr->out == 0)
	{
		cmd_assembler_free(asmr);
		return (0);
	}
	return (asmr);
}

void	cmd_assembler_free(t_cmd_assembler *asmr)
{
	unsigned int	i;

	while (asmr->pipes->size--)
		pipe_line_free(asmr->pipes->arr[asmr->pipes->size]);
	asmr->pipes->size = 0;
	vvector_free(asmr->pipes);
	while (asmr->commands->size--)
		command_free(asmr->commands->arr[asmr->commands->size]);
	asmr->commands->size = 0;
	vvector_free(asmr->commands);
	vvector_free(asmr->args);
	i = -1;
	while (++i < asmr->in->size)
		free(((t_file *)asmr->in->arr[i])->path);
	vvector_free(asmr->in);
	i = -1;
	while (++i < asmr->out->size)
		free(((t_file *)asmr->out->arr[i])->path);
	vvector_free(asmr->out);
	free(asmr);
}

int	cmd_assembler_cmd_edit(t_cmd_assembler *asmr, t_token *token)
{
	if (token->kind == WORD)
		return (vvector_put(asmr->args, token->value));
	else if (token->kind == LESS)
		return (vvector_put(asmr->in, file_create(token->value, READ)));
	else if (token->kind == DLESS)
		return (vvector_put(asmr->in, file_create(token->value, HERE_DOC)));
	else if (token->kind == GREAT)
		return (vvector_put(asmr->out, file_create(token->value, TRUNC)));
	else if (token->kind == DGREAT)
		return (vvector_put(asmr->out, file_create(token->value, APPEND)));
	return (error(EBADTOKEN, 0, 0));
}
