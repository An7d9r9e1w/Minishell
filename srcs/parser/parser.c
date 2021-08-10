/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:07 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/10 10:53:44 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <parser.h>
#include <error.h>

static int	get_redirect(t_cmd_assembler *asmr, t_token_stream *ts,
		t_vvector *envs, t_token *t)
{
	t_token	*token;

	free(t->value);
	token = ts_get_token(ts, envs);
	if (!token)
		return (error(EEND, 0, 0));
	if (token->kind != WORD)
	{
		error(EBADTOKEN, token->value, 0);
		token_free(token);
		return (-1);
	}
	token->kind = t->kind;
	cmd_assembler_cmd_edit(asmr, token);
	free(token);
	return (error(-2, 0, 0));
}

static int	check_command_line_first_token(t_token *token)
{
	if (error(-2, 0, 0))
		return (-1);
	if (!token)
		return (error(EEND, 0, 0));
	if (token->kind < WORD || token->kind > DLESS)
	{
		error(EBADTOKEN, token->value, 0);
		token_free(token);
		return (-1);
	}
	return (0);
}

static int	get_command_line(t_cmd_assembler *asmr,
		t_token_stream *ts, t_vvector *envs)
{
	t_token	*token;
	int		stat;

	if (cmd_assembler_cmd_new(asmr))
		return (-1);
	token = ts_get_token(ts, envs);
	if (check_command_line_first_token(token) == -1)
		return (-1);
	while (token)
	{
		if (token->kind >= GREAT && token->kind <= DLESS)
			stat = get_redirect(asmr, ts, envs, token);
		else if (token->kind == WORD)
			stat = cmd_assembler_cmd_edit(asmr, token);
		else if (token->kind == ERROR)
			return (check_command_line_first_token(token));
		else
			return (ts_putback(ts, token));
		free(token);
		if (stat)
			return (-1);
		token = ts_get_token(ts, envs);
	}
	return (error(-2, 0, 0));
}

static int	get_pipe_line(t_cmd_assembler *asmr,
		t_token_stream *ts, t_vvector *envs)
{
	t_token	*token;
	int		stat;

	if (cmd_assembler_pipeline_new(asmr) || get_command_line(asmr, ts, envs))
		return (-1);
	token = ts_get_token(ts, envs);
	while (token)
	{
		if (token->kind == PIPE)
			stat = get_command_line(asmr, ts, envs);
		else
			return (ts_putback(ts, token));
		token_free(token);
		if (stat)
			return (-1);
		token = ts_get_token(ts, envs);
	}
	return (error(-2, 0, 0));
}

t_command_list	*parse_line_read(t_cmd_assembler *asmr,
		t_token_stream *ts, t_vvector *envs)
{
	t_token	*token;
	int		stat;

	if (get_pipe_line(asmr, ts, envs))
		return (0);
	token = ts_get_token(ts, envs);
	while (token)
	{
		if (token->kind == AND || token->kind == OR)
		{
			((t_pipe_line *)asmr->pipes->arr[asmr->pipes->size - 1])
				->logic_operator = (token->kind == OR);
			stat = get_pipe_line(asmr, ts, envs);
		}
		else
			break ;
		token_free(token);
		if (stat)
			return (0);
		token = ts_get_token(ts, envs);
	}
	if (error(-2, 0, 0))
		return (0);
	return (cmd_assembler_make(asmr));
}
