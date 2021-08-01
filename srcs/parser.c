/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:07 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 18:21:36 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <parser.h>
#include <error.h>

//static int	check_token(

static int	get_redirect(t_cmd_assembler *asmr, t_token_stream *ts, int kind)
{
	t_token	*token;

	token_stat = ts_get_token(ts, &token);
	if (!token)
		return (error(EEND));
	if (token->kind != WORD)
	{
		token_free(token);
		return (-1);
	}
	token->kind = kind;
	token_stat = cmd_assembler_cmd_edit(asmr, token);
	free(token);
	return (0);
}

static int	get_command_line(t_cmd_aasembler *asmr, t_token_stream *ts)
{
	t_token	*token;

	if (cmd_assembler_cmd_new(asmr) == -1)// || get_command_line(asmr, ts) == -1)
		return (-1);
	token = ts_get_token(ts);
	if (!token || token->kind < WORD || token->kind > DLESS)
	{
		token_free(token);
		return (-1);
	}
	while (token)
	{
		if (token->kind >= GREAT && token->kind <= DLESS)
			token_stat = get_redirect(asmr, ts, token->kind);
		else if (token->kind == WORD)
			token_stat = cmd_assembler_cmd_edit(asmr, token);
		else
			return (ts_putback(ts, token));
		free(token);
		if (!token_stat)
			token_stat = ts_get_token(ts, &token);
	}
	return (0);
}

static int	get_pipe_line(t_cmd_assembler *asmr, t_token_stream *ts)
{
	t_token	*token;
	int		token_stat;

	if (cmd_assembler_pipeline_new(asmr) || get_command_line(asmr, ts) == -1)
		return (-1);
	token_stat = ts_get_token(ts, &token);
	while (!token_stat)
	{
		if (token->kind == PIPE)
			token_stat = -(cmd_assembler_pipeline_new(asmr)
				|| get_command_line(asmr, ts));
		else
			return (ts_putback(ts, token));
		free(token);
		if (!token_stat)
			token_stat = ts_get_token(ts, &token);
	}
	/*
	 *	token_stat == 1 -> ERROR MESSAGE
	 */
	return (token_stat);
}

t_command_list	*parse_line_read(t_cmd_assembler *asmr, t_token_stream *ts)
{
	t_token	*token;
	int		token_stat;

	if (get_pipe_line(asmr, ts) == -1)
		return (-1);
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
		return (-1);
	return (cmd_assembler_make(asmr));
}
