/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:36 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/14 08:59:28 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <token_stream.h>
#include <error.h>

t_token	*ts_pop_token(t_token_stream *ts);
char	*ts_get_prompt(char *new_prompt);
int		ts_push_token(t_token_stream *ts, t_token *token);
int		ts_check_for_wildcard(t_token_stream *ts,
			t_token *token, t_vvector *envs);

t_token_stream	*ts_create(char *prompt)
{
	t_token_stream	*ts;

	ts = malloc(sizeof(t_token_stream));
	if (!ts)
		return (error_p(-1));
	ts->line_read = 0;
	ts->line_cur = 0;
	ts->prompt = prompt;
	ts_get_prompt(prompt);
	ts->buffer = 0;
	ts->size = 0;
	return (ts);
}

void	ts_free_buffer(t_token_stream *ts)
{
	t_list	*tmp;

	while (ts->size--)
	{
		tmp = ts->buffer;
		ts->buffer = tmp->next;
		token_free(tmp->content);
		free(tmp);
	}
}

void	ts_free(t_token_stream *ts)
{
	if (ts)
	{
		if (ts->line_read)
			free(ts->line_read);
		if (ts->size)
			ts_free_buffer(ts);
		free(ts);
	}
}

t_token	*ts_get_token(t_token_stream *ts, t_vvector *envs)
{
	t_token	*token;

	if (ts->size)
		return (ts_pop_token(ts));
	token = get_token(&ts->line_cur, envs);
	if (token && ts_check_for_wildcard(ts, token, envs))
	{
		token_free(token);
		return (ts_pop_token(ts));
	}
	return (token);
}
