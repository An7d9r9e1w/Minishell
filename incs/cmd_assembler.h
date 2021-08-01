/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_assembler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 12:05:54 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 12:07:39 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_ASSEMBLER_H
# define CMD_ASSEMBLER_H

#include <token.h>

typedef struct s_cmd_aasembler
{
	/**/
}	t_cmd_aasembler;


{
	t_token	*token;
	int		token_stat;

	if (cmd_assembler_new_cmd(asmr) == -1)// || get_command_line(asmr, ts) == -1)
		return (-1);
	token_stat = ts_get_token(ts, &token);
	while (!token_stat)
	{
		token_stat = cmd_assembler_cmd_edit(token);
		if (token_stat == 1)
		{
			ts_putback(ts, token);
			break ;
		}
		free(token);
		if (!token_stat)
			token_stat = ts_get_token(ts, &token);
	}
	return (token_stat);
}

int	get_pipe_line(t_cmd_assembler *asmr, t_token_stream *ts)
{
	t_token	*token;
	int		token_stat;

	if (cmd_assembler_new_pipeline(asmr) || get_command_line(asmr, ts) == -1)
		return (-1);
	token_stat = ts_get_token(ts, &token);
	while (!token_stat)
	{
		if (token->kind == PIPE)
			token_stat = -(cmd_assembler_add_pipeline(asmr)
				|| get_command_line(asmr, ts) == -1);
		else
		{
			ts_putback(ts, token);
			break ;
		}
		free(token);
		if (!token_stat)
			token_stat = ts_get_token(ts, &token);
	}
	return (token_stat);
}

t_command_list	*parse_line_read(t_cmd_assembler *asmr, t_token_stream *ts)
{
	t_token	*token;
	int		token_stat;

	if (get_pipe_line(asmr, ts) == -1)
		return (0);
	token_stat = ts_get_token(ts, &token);
	while (!token_stat)
	{
		if (token->kind == AND || token->kind == OR)
		{
			asmr->pipe_line->logical_operator = (token->kind == AND);
			token_stat = get_pipe_line(asmr, ts);
		}
		else
			break ;
		free(token);
		if (!token_stat)
			token_stat = ts_get_token(ts, &token);
	}
	if (token_stat == -1)
		return (0);
	return (cmd_assembler_make(asmr));
}
#endif	/*CMD_ASSEMBLER_H*/
